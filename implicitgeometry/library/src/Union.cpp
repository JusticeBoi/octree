#include "Union.hpp"

namespace implicit
{

Union::Union(  AbsImplicitGeometry* operand1, AbsImplicitGeometry* operand2 ) :
    AbsOperation( operand1, operand2 )
{
}

bool Union::inside( double x, double y, double z ) const
{
    return operand1_->inside( x, y ) || operand2_->inside( x, y );
}

bool Union::is2D() const { return operand1_->is2D() && operand2_->is2D();}
} // implicit
