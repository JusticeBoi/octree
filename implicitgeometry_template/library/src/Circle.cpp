

#include "Circle.hpp"
namespace implicit
{

    Circle::Circle(double x, double y, double radius):x_(x), y_(y), radius_(radius){}
    
    bool Circle::inside(double x, double y, double z) const 
    {
        double dx = x - x_;
        double dy = y - y_;
    
        return std::hypot( dx, dy ) <= radius_; 
    }
}

