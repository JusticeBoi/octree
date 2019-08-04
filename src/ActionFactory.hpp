#ifndef __ActionFactory_HPP__
#define  __ActionFactory_HPP__
#include "absAction.hpp"
#include <memory>

class ActionFactory
{
    public:
        static std::shared_ptr<absAction> createAction(const char c );
};

#endif
