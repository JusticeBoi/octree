#include "absAction.hpp"
#include "Manager.hpp"
#include "Memento.hpp"

void RefineAllGeometries::actOnManager(Manager* m) 
{
    undoCounter = 1;
    m->createMemento();
    std::cout<<"acting on RefineAllGeometries" <<'\n';
    m->extendAllGeoTreeDepth( 1 );
    //std::vector<vtkSmartPointer<vtkDataSet>> latestMemory = m->createMemento()->getMemory();
    //m->updateRenderAllGeometries(&latestMemory );
    m->updateRenderAllGeometries();
}
std::shared_ptr<absAction> RefineAllGeometries::clone( )
{

    std::cout <<"cloning a RefineAllGeometries" <<'\n';
    return std::make_shared<RefineAllGeometries>(*this);
}

void Repeat::actOnManager(Manager* m) 
{
    m->createMemento();
    std::cout<<"acting on repeat" <<'\n';
    std::shared_ptr<Command> lastCommand = m->getLastCommand( );
    std::shared_ptr<Command> secondToLastcommand = m->getCommand( 1 );
    if ( secondToLastcommand && !dynamic_cast<Repeat*>( secondToLastcommand->getAction( ).get( ) ) )
    {
        lastCommand->getAction( ) = secondToLastcommand->getAction( )->clone( );
        m->createMemento();
        lastCommand->getAction( )->actOnManager( m );

    }

    //lastCommand->getAction()->actOnManager(m);
    
    //m->executeLastCommand();
}
std::shared_ptr<absAction> Repeat::clone()
{
    std::cout <<"cloning a repeat" <<'\n';

    return std::make_shared<Repeat>(*this);
}
int absAction::undoCounter = 1;
void Undo::actOnManager(Manager* m) 
{
    if ( undoCounter == 1 ) m->createMemento();
    std::cout <<"undo counter : " << undoCounter <<'\n';
    auto lastMemory = m->mementoHistory_.rbegin();
    auto itoLastMemory = m->mementoHistory_.rbegin() + undoCounter++;
    //auto itoLastMemory = m->mementoHistory_.rbegin() + undoCounter++;
    //std::iter_swap(lastMemory, itoLastMemory);
    //std::vector<vtkSmartPointer<vtkDataSet>> memoryToRender = (*lastMemory)->getMemory();
    std::vector<vtkSmartPointer<vtkDataSet>> memoryToRender = (*itoLastMemory)->getMemory();
    m->updateRenderAllGeometries(&memoryToRender);
}
std::shared_ptr<absAction> Undo::clone( )
{

    std::cout <<"cloning a Undo" <<'\n';
    return std::make_shared<Undo>(*this);
}
