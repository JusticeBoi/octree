#include "ActionFactory.hpp"
#include <iostream>

#include "utilities/inc/logging.hpp"
#include "utilities/inc/functionessentials.hpp"


std::shared_ptr<absAction> ActionFactory::createAction(const char c )
{
    switch(c)
    {
        case 'A':
        case 'a':
            return std::make_shared<RefineAllGeometries>();
        case 'C':
        case 'c':
            return std::make_shared<Coarsen>();
        case 'R':
        case 'r':
            return std::make_shared<Repeat>();
         // Undo is under development
        //case 'u':
        //case 'U':
        //    return std::make_shared<Undo>();
        default:
        utilities::InfoLogger <<c<<" is an undefined Action \n";
        return nullptr;
    }


}
