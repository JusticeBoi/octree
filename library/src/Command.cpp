#include "Command.hpp"
#include "Manager.hpp"
#include "Memento.hpp"
#include "utilities/inc/logging.hpp"
#include "utilities/inc/functionessentials.hpp"

Command::Command(Manager* manager, std::shared_ptr<absAction> action ) : m_(manager),a_(action){};

std::shared_ptr<Command> Command::getCommand()
{
    FUNCTION_START;
    return shared_from_this();
    FUNCTION_END;
}
void Command::execute()
{
    SCOPED_FUNCTION_START;
    m_->appendCommand(this);
    m_->applyAction(a_.get());
    SCOPED_FUNCTION_END;
}
std::shared_ptr<absAction>& Command::getAction()
{
    FUNCTION_START;
    return a_;
    FUNCTION_END;
}


//Command* Command::_commandList[] = {nullptr};
//Memento* Command::_mementoList[] = {nullptr};
//int Command::_numCommands = 0;
//int Command::_highWater = 0;

