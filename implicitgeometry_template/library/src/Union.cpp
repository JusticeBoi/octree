#include "Union.hpp"

namespace implicit
{
    Union::Union(AbsImplicitGeometry* operand1, AbsImplicitGeometry* operand2): AbsOperation(operand1, operand2){}
    
    //Union::~Union() 
    //{
    //    std::cout <<"Union Destructor " <<'\n';
    //    delete operand1_;
    //    delete operand2_;
    //}

   bool Union::inside(double x, double y, double z) const 
   {
       return operand1_->inside(x,y,z) || operand2_->inside(x,y,z);
   }

}

