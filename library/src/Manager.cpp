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

void Manager::addGeometry( std::shared_ptr<implicit::AbsImplicitGeometry> geo )
{
    if ( !geo_ )
    {
        geo_ = geo;
    }
    else
    {
        std::cout <<"count before: "<<geo_.use_count()<<'\n';
        geos_.push_back(geo_);
        geo_ = std::make_shared<implicit::Union>(geo_.get(),geo.get());
        std::cout <<"count after: "<<geo_.use_count()<<'\n';
    }
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
    //this->createMemento();
    action->actOnManager(this);
     
}

std::shared_ptr<Memento>& Manager::createMemento()
{

    return mementoHistory_.emplace_back(std::make_shared<Memento>(rootNode_->assembleUGrid(rootNode_->getAllPointsAtLevel( ) ) ) );



}

void Manager::ResetRendererAndRender(const vtkSmartPointer<vtkDataSet> renderable_)
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
    renderer_->ResetCamera();
    renderer_->ResetCameraClippingRange();
	renderWindow_->Render();
}
void Manager::Render( const vtkSmartPointer<vtkDataSet> renderable_)
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
    if ( geo_ )
    {

        if ( geo_->is2D()  )
        {
            //2D
            std::cout <<"2D2D"<<'\n';
            is2D_ = true;
            bbox_[Z_MIN] = std::numeric_limits<double>::epsilon();
            bbox_[Z_MAX] = std::numeric_limits<double>::epsilon();
        }

        rootNode_ = std::make_unique<node>(bbox_[X_MIN], bbox_[X_MAX], bbox_[Y_MIN], bbox_[Y_MAX], bbox_[Z_MIN], bbox_[Z_MAX],0, std::weak_ptr<node>() ,geo_.get());
    }
}
void Manager::renderAllGeometriesAndStart()
{
    rendered_level = rootNode_->getMaxLevel();
    Render(rootNode_->assembleUGrid(rootNode_->getAllPointsAtLevel( ) ));
    start();

}

void Manager::updateRenderAllGeometries(const vtkSmartPointer<vtkDataSet> renderables)
{
	auto start = std::chrono::steady_clock::now();
    if ( renderables )
    {
        ResetRendererAndRender( renderables );
    }
    else
    {
        ResetRendererAndRender( rootNode_->assembleUGrid( rootNode_->getAllPointsAtLevel( ) ) );
    }
   auto end = std::chrono::steady_clock::now();
   auto diff = end - start;
   std::cout <<"duration Manager updateRenderAllGeometries :  "<< std::chrono::duration <double, std::milli> (diff).count() << " ms" << std::endl;
}
void Manager::generateQuadTree(const int max_level)
{
   auto start = std::chrono::steady_clock::now();
   rootNode_->generateQuadTree(max_level);
   auto end = std::chrono::steady_clock::now();
   auto diff = end - start;
   std::cout <<"duration Manager generateQuadTree :  "<< std::chrono::duration <double, std::milli> (diff).count() << " ms" << std::endl;

}
void Manager::extendAllGeoTreeDepth(const int extend_level )
{
    rootNode_->extendQuadTree(extend_level);
}

void Manager::start(){ renderWindowInteractor_->Start();};

