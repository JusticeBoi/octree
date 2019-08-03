#include "Difference.hpp"

namespace implicit
{

Difference::Difference(  AbsImplicitGeometry* operand1, AbsImplicitGeometry* operand2 ) :
    AbsOperation( operand1, operand2 )
{
}

bool Difference::inside( double x, double y, double z ) const
{
    return operand1_->inside( x, y ) && !operand2_->inside( x, y );
}

} // implicit
