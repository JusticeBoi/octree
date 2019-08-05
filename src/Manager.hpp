#ifndef __Manager_HPP__
#define  __Manager_HPP__

#include "octree.hpp"
#include <limits>
#include "Timer.hpp"
#include "absAction.hpp"
#include "ActionFactory.hpp"
#include "Command.hpp"
#include <execution>

class Memento;
class absAction;
class Manager
{

    public:
        Manager () = delete;
        Manager( double xmin, double xmax, double ymin, double ymax,
                double zmin = std::numeric_limits<double>::epsilon(),
                double zmax = std::numeric_limits<double>::epsilon()) ;

        void Render( vtkSmartPointer<vtkDataSet> renderable );
        void ResetRendererAndRender(vtkSmartPointer<vtkDataSet> renderable_);
        void addNewShape(vtkSmartPointer<vtkDataSet> renderable );
        void addGeometry(const implicit::AbsImplicitGeometry* geo );
        vtkSmartPointer<vtkDataSet> addedDSet;
        void start();


        void createRootNodes();
        void generateQuadTree(const unsigned int max_level);

        void renderAllGeometriesAndStart();
        void updateRenderAllGeometries(const std::vector<vtkSmartPointer<vtkDataSet>>* renderables = nullptr);

        void extendAllGeoTreeDepth(const unsigned int extend_level ); 

        std::vector<std::shared_ptr<node>> rootNodes_;
        std::vector< std::vector<std::shared_ptr<node>> > vectorOfAllNodes; 


        std::shared_ptr<Memento>& createMemento();
        void appendCommand(Command* command );

        void applyAction(absAction* action);
        void executeLastCommand();
        std::shared_ptr<Command> getLastCommand();
        std::shared_ptr<Command> getCommand(size_t index_from_last);





        std::vector<std::shared_ptr<Memento>> mementoHistory_;   
    private:
        bool is2D_;
        std::vector<std::shared_ptr<Command>> commandHistory_;  
        int numCommands_;
        //std::vector<std::shared_ptr<implicit::AbsImplicitGeometry>> geos_;
        std::vector<const implicit::AbsImplicitGeometry*> geos_;
        std::array<double,6> bbox_;

        std::unique_ptr<ActionFactory> actionFactory_;



        vtkSmartPointer<vtkRenderer> renderer_;
        vtkSmartPointer<vtkRenderWindow> renderWindow_;
        vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor_;
        vtkSmartPointer<vtkInteractorObserver> style;



        
};

inline void KeypressCallbackFunction (
  vtkObject* caller,
  long unsigned int vtkNotUsed(eventId),
  void* clientData,
  void* vtkNotUsed(callData) )
{
 vtkRenderWindowInteractor *iren = 
    static_cast<vtkRenderWindowInteractor*>(caller);
    Manager* m = static_cast<Manager*>(clientData);

    std::shared_ptr<absAction> action = ActionFactory::createAction(iren->GetKeySym()[0]);
    if ( action )
    {
        std::shared_ptr<Command> c = std::make_shared<Command>(m, action);
        c->execute();
    }
    else
    {
        std::cout <<"action is nullptr " <<'\n';
    }

    std::cout <<"pressed  "<<iren->GetKeySym() << '\n';
}



#endif
