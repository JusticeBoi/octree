
#include "Difference.hpp"

namespace implicit
{
    Difference::Difference(AbsImplicitGeometry* operand1, AbsImplicitGeometry* operand2): AbsOperation(operand1, operand2){}
    
    //Difference::~Difference() 
    //{
    //    std::cout <<"Difference Destructor " <<'\n';
    //    delete operand1_;
    //    delete operand2_;
    //}

   bool Difference::inside(double x, double y, double z) const 
   {
       return operand1_->inside(x,y,z) && !operand2_->inside(x,y,z);
   }

}

