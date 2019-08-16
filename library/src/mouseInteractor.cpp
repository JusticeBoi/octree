#include "mouseInteractor.hpp"
#include "vtk_and_std_headers.hpp"
#include "Manager.hpp"
#include "utilities/inc/logging.hpp"
#include "utilities/inc/functionessentials.hpp"


vtkStandardNewMacro(customMouseInteractorStyle);
void customMouseInteractorStyle::OnLeftButtonDown()
{
    utilities::InfoLogger << "Pressed left mouse button." << '\n';
     if ( m_->isOnly2DGeometry() )
     {
        int x = this->Interactor->GetEventPosition()[0];
        int y = this->Interactor->GetEventPosition()[1];
        //std::cout << "(x,y) = (" << x << "," << y << ")" << std::endl;
        vtkSmartPointer<vtkCoordinate> coordinate =
          vtkSmartPointer<vtkCoordinate>::New();
        coordinate->SetCoordinateSystemToDisplay();
        coordinate->SetValue(x,y,0);

        // This doesn't produce the right value if the sphere is zoomed in???
        double* world = coordinate->GetComputedWorldValue(this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer());
        utilities::InfoLogger << "World coordinate: " << world[0] << ", " << world[1] << ", " << world[2] << '\n';
        std::array<double,3> p = {world[0], world[1], world[2] }; 
        m_->rootNode_->refineTowardsPoint(p);
        m_->updateRenderWholeTree( );
     }

      // Forward events
      vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
}

void customMouseInteractorStyle::OnMiddleButtonDown() 
{
    utilities::InfoLogger << "Pressed middle mouse button." << '\n';
  // Forward events
  vtkInteractorStyleTrackballCamera::OnMiddleButtonDown();
}

void customMouseInteractorStyle::OnRightButtonDown() 
{
    utilities::InfoLogger << "Pressed right mouse button." << '\n';
  // Forward events
  vtkInteractorStyleTrackballCamera::OnRightButtonDown();
}


void customMouseInteractorStyle::setManager(Manager* m)
{
    m_ = m;
}

void customMouseInteractorStyle::OnMouseWheelForward() 
{
    utilities::InfoLogger << "Pressed mouse wheel forward." << '\n';

    std::shared_ptr<absAction> action = std::make_shared<RefineAllGeometries>();
    std::shared_ptr<Command> c = std::make_shared<Command>( m_, action );
    c->execute( );

    //vtkInteractorStyleTrackballCamera::OnMouseWheelForward();
}

void customMouseInteractorStyle::OnMouseWheelBackward() 
{
    utilities::InfoLogger << "Pressed mouse wheel backward." << '\n';

    std::shared_ptr<absAction> action = std::make_shared<Coarsen>();
    std::shared_ptr<Command> c = std::make_shared<Command>( m_, action );
    c->execute( );

    //vtkInteractorStyleTrackballCamera::OnMouseWheelForward();
}
