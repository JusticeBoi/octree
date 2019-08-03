#include "Intersection.hpp"

namespace implicit
{

Intersection::Intersection(  AbsImplicitGeometry* operand1, AbsImplicitGeometry* operand2 ) :
    AbsOperation( operand1, operand2 )
{
}

bool Intersection::inside( double x, double y, double z ) const
{
    return operand1_->inside( x, y ) && operand2_->inside( x, y );
}

} // implicit
