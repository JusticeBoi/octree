#ifndef __Action_HPP__
#define  __Action_HPP__
#include <memory>

class Manager;


class absAction 
{
    public:
        virtual void actOnManager( Manager* m ) = 0;
        virtual std::shared_ptr<absAction> clone( ) = 0;
        static int undoCounter;
        virtual ~absAction() = default;

};

class RefineAllGeometries : public absAction
{
    public:
        void actOnManager( Manager* m ) override;
        std::shared_ptr<absAction> clone( ) override;
};
class Coarsen : public absAction
{
    public:
        void actOnManager( Manager* m ) override;
        std::shared_ptr<absAction> clone( ) override;
};


class Repeat : public absAction
{
    public:
         void actOnManager( Manager* m ) override;
         std::shared_ptr<absAction> clone() override;
};

class Undo : public absAction
{
    public:
         void actOnManager( Manager* m ) override;
         std::shared_ptr<absAction> clone( ) override;
};


#endif
