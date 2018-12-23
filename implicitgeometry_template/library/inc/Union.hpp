#ifndef __INC_UNION_HPP__
#define __INC_UNION_HPP__
#include "AbsOperation.hpp"


namespace implicit
{

    class Union : public AbsOperation
    {
        public:
            Union(AbsImplicitGeometry* operand1, AbsImplicitGeometry* operand2);
            bool inside( double x, double y ,double z) const override ;
            //~Union() override; 
    };

}
#endif //__INC_UNION_HPP__
