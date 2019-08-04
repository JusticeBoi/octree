#include "Manager.hpp"
#include "Command.hpp"
#include "Memento.hpp"


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

    if ( zmin <= std::numeric_limits<double>::epsilon() && zmax <= std::numeric_limits<double>::epsilon() ) is2D_ = true;
    else is2D_ = false;

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
    renderer_->ResetCamera();

    

}

void Manager::addGeometry(const implicit::AbsImplicitGeometry* geo )
{
    geos_.push_back(geo);
}
void Manager::appendCommand(Command* command )
{
    commandHistory_.emplace_back(command->getCommand());
    ++numCommands_;
}
std::shared_ptr<Command> Manager::getLastCommand()
{
    std::cout<<"getLastCommand"<<'\n';
    std::cout <<"size of commandHistory_ : " << commandHistory_.size() << '\n';
    return (commandHistory_.size()) ? commandHistory_.back() : nullptr;
}

// 0 is last
std::shared_ptr<Command> Manager::getCommand(size_t index_from_last)
{
    int noOverflow = static_cast<int>(commandHistory_.size()) - static_cast<int>(index_from_last) - 1 ;
    return ( noOverflow >= 0 ) ?  commandHistory_[noOverflow] : nullptr;
}
void Manager::executeLastCommand()
{
    commandHistory_.back()->execute();
}
void Manager::applyAction(absAction* action)
{
    action->actOnManager(this);
     
}

void Manager::createMemento()
{
    std::vector<vtkSmartPointer<vtkDataSet>> mementos;
    std::transform( std::cbegin( rootNodes_ ), std::cend( rootNodes_ ), std::back_inserter( mementos), [](auto node)
            {
                    return node->assembleUGrid( node->getAllPointsDeepestLevel( ) ); 
            });

    mementoHistory_.emplace_back(std::make_shared<Memento>(mementos));



}

void Manager::ResetRendererAndRender(vtkSmartPointer<vtkDataSet> renderable_)
{
    std::cout <<"RemoveAllViewProps"<<'\n';
    //renderer_->RemoveAllViewProps();
    
    auto actorsCollection = renderer_->GetActors();
    actorsCollection->InitTraversal();
    auto o = actorsCollection->GetNextItem();

    while (o != 0 )
    {
        std::cout <<"removing"<<'\n';
        renderer_->RemoveActor(o);
        o = actorsCollection->GetNextItem();
    }



	vtkSmartPointer<vtkDataSetMapper> mapper =
			vtkSmartPointer<vtkDataSetMapper>::New();

	mapper->SetInputData(renderable_);

	vtkSmartPointer<vtkActor> actor =
			vtkSmartPointer<vtkActor>::New();

	actor->SetMapper(mapper);
	actor->GetProperty()->SetRepresentationToWireframe();
	renderer_->AddActor(actor);
	renderer_->SetBackground(.3, .6, .3); // Background color green
    renderer_->ResetCamera();
    renderer_->ResetCameraClippingRange();
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
        //vtkSmartPointer<vtkAxesActor> axes = 
        // vtkSmartPointer<vtkAxesActor>::New();

        // vtkSmartPointer<vtkOrientationMarkerWidget> widget = 
        //        vtkSmartPointer<vtkOrientationMarkerWidget>::New();
        // widget->SetOutlineColor( 0.9300, 0.5700, 0.1300 );
        // widget->SetOrientationMarker( axes );
        // widget->SetInteractor( renderWindowInteractor_ );
        // widget->SetViewport( 0.0, 0.0, 0.4, 0.4 );
        // widget->SetEnabled( 1 );
        // widget->InteractiveOn();
        // renderer_->ResetCamera();
		renderWindow_->Render();
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
    
    auto is2D = std::find_if(std::cbegin(geos_), std::cend(geos_),[](const implicit::AbsImplicitGeometry* geo )
            {
                return geo->is2D();
            });
    if ( is2D != std::cend(geos_) )
    {
        //2D
        std::cout <<"2D2D"<<'\n';
        is2D_ = true;
        bbox_[Z_MIN] = std::numeric_limits<double>::epsilon();
        bbox_[Z_MAX] = std::numeric_limits<double>::epsilon();
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
                    //Render( node->assembleUGrid( node->getAllPoints( ) ) );
                    Render( node->assembleUGrid( node->getAllPointsDeepestLevel( ) ) );
            });

    start();

}

void Manager::updateRenderAllGeometries()
{
    std::for_each( std::begin(rootNodes_), std::end( rootNodes_ ), [this]( auto node )
            {
                auto allPoints = node->getAllPointsDeepestLevel();
                std::cout <<"size of allPoints : " << allPoints.size() << '\n';
                    ResetRendererAndRender( node->assembleUGrid( allPoints ) );
            });
}
void Manager::generateQuadTree(const unsigned int max_level)
{
	auto start = std::chrono::steady_clock::now();
    std::for_each(std::begin(rootNodes_), std::end(rootNodes_),[max_level]( auto node )
             {
                if ( !node->hasChildren( ) )
                {
                    node->generateQuadTree(max_level);
                }
             });
   auto end = std::chrono::steady_clock::now();
   auto diff = end - start;
   std::cout <<"duration Manager generateQuadTree :  "<< std::chrono::duration <double, std::milli> (diff).count() << " ms" << std::endl;

}
void Manager::extendAllGeoTreeDepth(const unsigned int extend_level )
{
    std::for_each( std::begin(rootNodes_), std::end(rootNodes_), [extend_level](auto nodes)
            {
                nodes->extendQuadTree( extend_level );
            });
}

void Manager::start(){ renderWindowInteractor_->Start();};

