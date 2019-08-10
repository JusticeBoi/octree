#include "absAction.hpp"
#include "Manager.hpp"
#include "Memento.hpp"

void RefineAllGeometries::actOnManager( Manager* m )  
{
    undoCounter = 1;
    m->createMemento();
    std::cout<<"acting on RefineAllGeometries" <<'\n';
    if ( m->rendered_level < m->rootNode_->getMaxLevel( ) )
    {
        ++m->rendered_level;
        const vtkSmartPointer<vtkDataSet> renderable = m->rootNode_->assembleUGrid( m->rootNode_->getAllPointsAtLevel(m->rendered_level )); 
        std::cout <<"rendered_level : " << m->rendered_level<<'\n';
        m->updateRenderAllGeometries( renderable );
    }
    else
    {
        m->extendAllGeoTreeDepth( 1 );
        m->rendered_level = m->rootNode_->getMaxLevel( ) ; 
        std::cout <<"rendered_level : " << m->rendered_level<<'\n';
        m->updateRenderAllGeometries( );
    }
}
std::shared_ptr<absAction> RefineAllGeometries::clone( )
{

    std::cout <<"cloning a RefineAllGeometries" <<'\n';
    return std::make_shared<RefineAllGeometries>( *this );
}


void Coarsen::actOnManager( Manager *m )
{
    int render_level = m->rendered_level;
    if( render_level != 0 )
    {
        --render_level;
        m->rendered_level = render_level;
        const vtkSmartPointer<vtkDataSet> renderable = m->rootNode_->assembleUGrid( m->rootNode_->getAllPointsAtLevel( render_level )); 
        std::cout <<"rendered_level : " << m->rendered_level<<'\n';
        m->updateRenderAllGeometries( renderable );
    }

}

std::shared_ptr<absAction> Coarsen::clone( )
{

    std::cout <<"cloning a Coarsen" <<'\n';
    return std::make_shared<Coarsen>( *this );
}

void Repeat::actOnManager( Manager* m ) 
{
    m->createMemento();
    std::cout<<"acting on repeat" <<'\n';
    std::shared_ptr<Command> lastCommand = m->getLastCommand( );
    std::shared_ptr<Command> secondToLastcommand = m->getCommand( 1 );
    if ( secondToLastcommand && !dynamic_cast<Repeat*>( secondToLastcommand->getAction( ).get( ) ) )
    {
        lastCommand->getAction( ) = secondToLastcommand->getAction( )->clone( );
        m->createMemento( );
        lastCommand->getAction( )->actOnManager( m );
    }
}
std::shared_ptr<absAction> Repeat::clone( )
{
    std::cout <<"cloning a repeat" <<'\n';

    return std::make_shared<Repeat>( *this );
}
int absAction::undoCounter = 1;

void Undo::actOnManager( Manager* m ) 
{
    if ( undoCounter == 1 ) m->createMemento( );
    std::cout <<"undo counter : " << undoCounter <<'\n';
    auto lastMemory = m->mementoHistory_.rbegin( );
    auto itoLastMemory = m->mementoHistory_.rbegin( ) + undoCounter++;
    //auto itoLastMemory = m->mementoHistory_.rbegin() + undoCounter++;
    //std::iter_swap(lastMemory, itoLastMemory);
    //std::vector<vtkSmartPointer<vtkDataSet>> memoryToRender = (*lastMemory)->getMemory();
    vtkSmartPointer<vtkDataSet> memoryToRender = ( *itoLastMemory )->getMemory( );
    m->updateRenderAllGeometries( memoryToRender );
}
std::shared_ptr<absAction> Undo::clone( )
{

    std::cout <<"cloning a Undo" <<'\n';
    return std::make_shared<Undo>( *this );
}
