#include "Command.hpp"
#include "Manager.hpp"
#include "Memento.hpp"

Command::Command(Manager* manager, std::shared_ptr<absAction> action ) : m_(manager),a_(action){};

std::shared_ptr<Command> Command::getCommand()
{
    return shared_from_this();
}
void Command::execute()
{
    m_->appendCommand(this);
    m_->applyAction(a_.get());
}
std::shared_ptr<absAction>& Command::getAction()
{
    return a_;
}


//Command* Command::_commandList[] = {nullptr};
//Memento* Command::_mementoList[] = {nullptr};
//int Command::_numCommands = 0;
//int Command::_highWater = 0;

