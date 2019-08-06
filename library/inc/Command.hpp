#ifndef __Command_HPP__
#define  __Command_HPP__
#include <memory>

class Manager;
class absAction;
class Memento;
class Command : public std::enable_shared_from_this<Command>
{

    public:
        Command(Manager* manager, std::shared_ptr<absAction> action );  
        Command() = default;

        Command(const Command& rhs) = delete;
        Command& operator=(const Command& rhs) = delete;
        Command(Command&& rhs) = delete;
        Command& operator=(Command&& rhs) = delete;

        virtual void execute();
        void undo();
        void redo();
        std::shared_ptr<absAction>& getAction();



        std::shared_ptr<Command> getCommand();

    private:
        Manager* m_;
        std::shared_ptr<absAction> a_;

        //static Command * _commandList[20];
        //static Memento * _mementoList[20];
        //static int _numCommands;
        //static int _highWater;
        
};









#endif
