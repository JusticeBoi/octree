#include "Manager.hpp"



Manager::Manager(double xmin, double xmax, double ymin, double ymax,
            double zmin ,
            double zmax ) 
{
    bbox_[X_MIN] = xmin;  
    bbox_[X_MAX] = xmax;  

    bbox_[Y_MIN] = ymin;  
    bbox_[Y_MAX] = ymax;  

    bbox_[Z_MIN] = zmin;  
    bbox_[Z_MAX] = zmax;  

    renderer_ = vtkSmartPointer<vtkRenderer>::New();
    renderWindow_= vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow_->AddRenderer(renderer_);

    renderWindowInteractor_ = vtkSmartPointer<vtkRenderWindowInteractor>::New();

    renderWindowInteractor_->SetRenderWindow(renderWindow_);

    vtkSmartPointer<vtkCallbackCommand> keypressCallback =
                            vtkSmartPointer<vtkCallbackCommand>::New();
    keypressCallback->SetCallback ( KeypressCallbackFunction );
    keypressCallback->SetClientData(this);

    renderWindowInteractor_->AddObserver (
    vtkCommand::KeyPressEvent, keypressCallback );

    style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New(); 
	renderer_->SetBackground(.3, .6, .3); // Background color green

    

}

void Manager::addGeometry(const implicit::AbsImplicitGeometry* geo )
{
    geos_.push_back(geo);
}

void Manager::ResetRendererAndRender(vtkSmartPointer<vtkDataSet> renderable_)
{
    renderer_->RemoveAllViewProps();

	vtkSmartPointer<vtkDataSetMapper> mapper =
			vtkSmartPointer<vtkDataSetMapper>::New();

	mapper->SetInputData(renderable_);

	vtkSmartPointer<vtkActor> actor =
			vtkSmartPointer<vtkActor>::New();

	actor->SetMapper(mapper);
	actor->GetProperty()->SetRepresentationToWireframe();
	renderer_->AddActor(actor);
	renderer_->SetBackground(.3, .6, .3); // Background color green
	renderWindow_->Render();
}
void Manager::Render(vtkSmartPointer<vtkDataSet> renderable_)
{
        std::cout <<"inside Render" << '\n';
		vtkSmartPointer<vtkDataSetMapper> mapper =
				vtkSmartPointer<vtkDataSetMapper>::New();

		mapper->SetInputData(renderable_);

		vtkSmartPointer<vtkActor> actor =
				vtkSmartPointer<vtkActor>::New();

		actor->SetMapper(mapper);
		actor->GetProperty()->SetRepresentationToWireframe();

		//vtkSmartPointer<vtkRenderer> renderer =
		//		vtkSmartPointer<vtkRenderer>::New();

		//vtkSmartPointer<vtkRenderWindow> renderWindow =
		//		vtkSmartPointer<vtkRenderWindow>::New();

		//renderWindow->AddRenderer(renderer);

		//vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
		//		vtkSmartPointer<vtkRenderWindowInteractor>::New();

		//renderWindowInteractor->SetRenderWindow(renderWindow);

		// Add the actor to the scene
        std::cout <<"before add actor" << '\n';
		renderer_->AddActor(actor);

		renderer_->SetBackground(.3, .6, .3); // Background color green
        std::cout <<"before render actor" << '\n';
		renderWindow_->Render();
		//renderWindowInteractor_->Start();
}
void Manager::addNewShape(vtkSmartPointer<vtkDataSet> renderable)
{
    addedDSet = renderable;
}

void Manager::createRootNodes()
{
    if ( rootNodes_.size() || !geos_.size() )
    {
        std::runtime_error(" Either root nodes are already created or there is no geometry to  create!"); 
    }
    
    std::transform(std::cbegin(geos_), std::cend(geos_), std::back_inserter(rootNodes_),[this](const implicit::AbsImplicitGeometry* geo )
            {
                std::vector<std::shared_ptr<node> >& vec = vectorOfAllNodes.emplace_back(std::vector<std::shared_ptr<node>>());

                return std::make_shared<node>( bbox_[X_MIN], bbox_[X_MAX], bbox_[Y_MIN], bbox_[Y_MAX], bbox_[Z_MIN], bbox_[Z_MAX],0, std::weak_ptr<node>() ,geo, &vec );
            });
}
void Manager::renderAllGeometriesAndStart()
{
    std::cout <<"size of rootNodes_[0]->my_ptr_to_all_nodes->size() " << rootNodes_[0]->my_ptr_to_all_nodes->size() <<'\n';
    std::for_each( std::begin(rootNodes_), std::end( rootNodes_ ), [this]( auto node )
            {
                    Render( node->assembleUGrid( node->getAllPointsDeepestLevel( ) ) );
            });

    start();

}

void Manager::updateRenderAllGeometries()
{
    std::for_each( std::begin(rootNodes_), std::end( rootNodes_ ), [this]( auto node )
            {
                    ResetRendererAndRender( node->assembleUGrid( node->getAllPointsDeepestLevel( ) ) );
            });
}
void Manager::generateQuadTree(const unsigned int max_level)
{
    std::for_each(std::begin(rootNodes_), std::end(rootNodes_),[max_level]( auto node )
             {
                if ( !node->hasChildren() )
                {
                    node->generateQuadTree(max_level);
                }
             });

}
void Manager::extendAllGeoTreeDepth(const unsigned int extend_level )
{
    std::for_each( std::begin(rootNodes_), std::end(rootNodes_), [extend_level](auto nodes)
            {
                nodes->extendQuadTree(extend_level);
            });
}
void Manager::start(){ renderWindowInteractor_->Start();};

