#include "absAction.hpp"
#include "Manager.hpp"

void RefineAllGeometries::actOnManager(Manager* m) 
{
    std::cout<<"acting on RefineAllGeometries" <<'\n';
    m->extendAllGeoTreeDepth( 1 );
    m->updateRenderAllGeometries( );
}
std::shared_ptr<absAction> RefineAllGeometries::clone( )
{

    std::cout <<"cloning a RefineAllGeometries" <<'\n';
    return std::make_shared<RefineAllGeometries>(*this);
}

void Redo::actOnManager(Manager* m) 
{
    std::cout<<"acting on redo" <<'\n';
    std::shared_ptr<Command> lastCommand = m->getLastCommand( );
    std::shared_ptr<Command> command = m->getCommand( 1 );
    if ( command && !dynamic_cast<Redo*>( command->getAction( ).get( ) ) )
    {
        lastCommand->getAction( ) = command->getAction( )->clone( );
        lastCommand->getAction( )->actOnManager( m );
    }

    //lastCommand->getAction()->actOnManager(m);
    
    //m->executeLastCommand();
}
std::shared_ptr<absAction> Redo::clone()
{
    std::cout <<"cloning a redo" <<'\n';

    return std::make_shared<Redo>(*this);
}
