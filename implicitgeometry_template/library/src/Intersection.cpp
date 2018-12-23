#include "Intersection.hpp"

namespace implicit
{
    Intersection::Intersection(AbsImplicitGeometry* operand1, AbsImplicitGeometry* operand2): AbsOperation(operand1, operand2){}
    
    //Intersection::~Intersection() 
    //{
    //    std::cout <<"Intersection Destructor " <<'\n';
    //    delete operand1_;
    //    delete operand2_;
    //}

   bool Intersection::inside(double x, double y ,double z) const 
   {
       return operand1_->inside(x,y,z) && operand2_->inside(x,y,z);
   }

}
