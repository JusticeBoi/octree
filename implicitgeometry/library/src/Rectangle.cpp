#include "Rectangle.hpp"

namespace implicit
{

Rectangle::Rectangle( double x1, double y1, double x2, double y2 ) :
    x1_( x1 ), y1_( y1 ), x2_( x2 ), y2_( y2 )
{    
}

bool Rectangle::inside( double x, double y, double z ) const
{
    return x >= x1_ && x <= x2_ && y >= y1_ && y <= y2_;
}

} // implicit
