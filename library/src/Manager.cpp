#include "Manager.hpp"
#include "Command.hpp"
#include "Memento.hpp"
#include "mouseInteractor.hpp"

#include "utilities/inc/logging.hpp"
#include "utilities/inc/functionessentials.hpp"


Manager::Manager(double xmin, double xmax, double ymin, double ymax,
            double zmin ,
            double zmax ) 
{
    FUNCTION_START;

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

    //style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New(); 

    vtkSmartPointer<customMouseInteractorStyle> style_2 =
                vtkSmartPointer<customMouseInteractorStyle>::New();
    style_2->setManager(this);

    renderWindowInteractor_->SetInteractorStyle(style_2);

	renderer_->SetBackground(.3, .6, .3); // Background color green
    renderer_->ResetCamera();
    FUNCTION_END;

    

}

void Manager::addGeometry( std::shared_ptr<implicit::AbsImplicitGeometry> geo )
{
    FUNCTION_START;
    if ( !geo_ )
    {
        geo_ = geo;
    }
    else
    {
        //std::cout <<"count before: "<<geo_.use_count()<<'\n';
        geos_.push_back(geo_);
        geo_ = std::make_shared<implicit::Union>(geo_.get(),geo.get());
        //std::cout <<"count after: "<<geo_.use_count()<<'\n';
    }
    FUNCTION_END;
}
void Manager::appendCommand(Command* command )
{
    FUNCTION_START;
    commandHistory_.emplace_back(command->getCommand());
    ++numCommands_;
    FUNCTION_END;
}
std::shared_ptr<Command> Manager::getLastCommand()
{
    FUNCTION_START;
    //std::cout<<"getLastCommand"<<'\n';
    //std::cout <<"size of commandHistory_ : " << commandHistory_.size() << '\n';
    return (commandHistory_.size()) ? commandHistory_.back() : nullptr;
    FUNCTION_END;
}

// 0 is last
std::shared_ptr<Command> Manager::getCommand(size_t index_from_last)
{
    FUNCTION_START;
    int noOverflow = static_cast<int>(commandHistory_.size()) - static_cast<int>(index_from_last) - 1 ;
    return ( noOverflow >= 0 ) ?  commandHistory_[noOverflow] : nullptr;
    FUNCTION_END;
}
void Manager::executeLastCommand()
{
    FUNCTION_START;
    commandHistory_.back()->execute();
    FUNCTION_END;
}
void Manager::applyAction(absAction* action)
{
    FUNCTION_START;
    //this->createMemento();
    action->actOnManager(this);
     
    FUNCTION_END;
}

std::shared_ptr<Memento>& Manager::createMemento()
{

    SCOPED_FUNCTION_START;
    return mementoHistory_.emplace_back(std::make_shared<Memento>(rootNode_->assembleUGrid(rootNode_->getAllPointsAtLevel(this->rendered_level ) ) ) );

    SCOPED_FUNCTION_END;


}

void Manager::ResetRendererAndRender(const vtkSmartPointer<vtkDataSet> renderable_)
{
    SCOPED_FUNCTION_START;
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
    SCOPED_FUNCTION_END;
}
void Manager::Render( const vtkSmartPointer<vtkDataSet> renderable_)
{
    SCOPED_FUNCTION_START;
        //std::cout <<"inside Render" << '\n';
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
        //std::cout <<"before add actor" << '\n';
		renderer_->AddActor(actor);

		renderer_->SetBackground(.3, .6, .3); // Background color green
        //std::cout <<"before render actor" << '\n';
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
    SCOPED_FUNCTION_END;
}
void Manager::addNewShape(vtkSmartPointer<vtkDataSet> renderable)
{
    FUNCTION_START;
    addedDSet = renderable;
    FUNCTION_END;
}

bool Manager::isOnly2DGeometry()
{
    return (geo_) ? geo_->is2D() : false; 
}

void Manager::createRootNodes()
{
    SCOPED_FUNCTION_START;
    if ( geo_ )
    {

        if ( geo_->is2D()  )
        {
            is2D_ = true;
            bbox_[Z_MIN] = std::numeric_limits<double>::epsilon();
            bbox_[Z_MAX] = std::numeric_limits<double>::epsilon();
        }

        rootNode_ = std::make_unique<node>(bbox_[X_MIN], bbox_[X_MAX], bbox_[Y_MIN], bbox_[Y_MAX], bbox_[Z_MIN], bbox_[Z_MAX],0, std::weak_ptr<node>() ,geo_.get());
    }
    SCOPED_FUNCTION_END;
    
}
void Manager::renderAllGeometriesAndStart()
{
    SCOPED_FUNCTION_START;
    rendered_level = rootNode_->getMaxLevel();
    Render(rootNode_->assembleUGrid(rootNode_->getAllPointsAtLevel( ) ));
    start();
    SCOPED_FUNCTION_END;

}

void Manager::updateRenderAllGeometries(const vtkSmartPointer<vtkDataSet> renderables)
{
    SCOPED_FUNCTION_START;
    if ( renderables )
    {
        utilities::InfoLogger << "Rendering data of size : "<< renderables->GetActualMemorySize()<<" kbs"<< '\n';
        ResetRendererAndRender( renderables );
    }
    else
    {
        auto render = rootNode_->assembleUGrid( rootNode_->getAllPointsAtLevel( ) ) ; 
        utilities::InfoLogger << "Rendering data of size : "<< render->GetActualMemorySize()<<" kbs"<< '\n';
        ResetRendererAndRender( render );
    }
    SCOPED_FUNCTION_END;
}
void Manager::updateRenderWholeTree()
{
    SCOPED_FUNCTION_START;

    auto render = rootNode_->assembleUGrid( rootNode_->getAllPointsUntil( ) ) ; 
    utilities::InfoLogger << "Rendering data of size : "<< render->GetActualMemorySize()<<" kbs"<< '\n';
    ResetRendererAndRender( render );

    SCOPED_FUNCTION_END;
}
void Manager::generateQuadTree(const int max_level)
{
   SCOPED_FUNCTION_START;
   rootNode_->generateQuadTree(max_level);
    SCOPED_FUNCTION_END;

}
void Manager::extendAllGeoTreeDepth(const int extend_level )
{
    FUNCTION_START;
    rootNode_->extendQuadTree(extend_level);
    FUNCTION_END;
}

void Manager::start()
{
    SCOPED_FUNCTION_START;
    renderWindowInteractor_->Start();
    SCOPED_FUNCTION_END;
};

