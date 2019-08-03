#include "Circle.hpp"
#include <cmath>

namespace implicit
{

Circle::Circle( double x, double y, double r ) :
    x_( x ), y_( y ), r_( r )
{
    
}

bool Circle::inside( double x, double y, double z ) const
{
    double dx = x - x_;
    double dy = y - y_;
    
    return r_ >= std::sqrt( dx * dx + dy * dy );
}

} // implicit
