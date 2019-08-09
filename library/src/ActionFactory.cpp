#include "ActionFactory.hpp"
#include <iostream>



std::shared_ptr<absAction> ActionFactory::createAction(const char c )
{
    switch(c)
    {
        case 'A':
        case 'a':
            return std::make_shared<RefineAllGeometries>();
        case 'R':
        case 'r':
            return std::make_shared<Repeat>();
        case 'u':
        case 'U':
            return std::make_shared<Undo>();
        default:
            std::cout <<"returning nullptr " << '\n';
            return nullptr;
    }


}