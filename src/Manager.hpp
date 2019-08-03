#ifndef __Manager_HPP__
#define  __Manager_HPP__

#include "octree.hpp"
#include <limits>
#include "Timer.hpp"

class Command;
class Memento;
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
        void updateRenderAllGeometries();

        void extendAllGeoTreeDepth(const unsigned int extend_level ); 

        std::vector<std::shared_ptr<node>> rootNodes_;
        std::vector< std::vector<std::shared_ptr<node>> > vectorOfAllNodes; 




    private:
        std::vector<std::shared_ptr<Memento>> mementoHistory_;
        std::vector<std::shared_ptr<Command>> commandHistory_;

        //std::vector<std::shared_ptr<implicit::AbsImplicitGeometry>> geos_;
        std::vector<const implicit::AbsImplicitGeometry*> geos_;
        std::array<double,6> bbox_;



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
    std::cout <<"pressed  "<<iren->GetKeySym() << '\n';
    if ( iren->GetKeySym()[0] == 'a')
    {
        //m->rootNodes_[0]->extendQuadTree(2);
        m->extendAllGeoTreeDepth(1);
        m->updateRenderAllGeometries();


        std::cout <<"YES"<<'\n';
    }
}



#endif
