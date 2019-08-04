#ifndef __Action_HPP__
#define  __Action_HPP__
#include <memory>

class Manager;


class absAction 
{
    public:
        virtual void actOnManager(Manager* m ) = 0;
        virtual std::shared_ptr<absAction> clone() = 0;

};

class RefineAllGeometries : public absAction
{
    void actOnManager(Manager* m) override;
    std::shared_ptr<absAction> clone() override;
};

class Redo : public absAction
{
         void actOnManager(Manager* m ) override;
         std::shared_ptr<absAction> clone() override;
};



#endif
