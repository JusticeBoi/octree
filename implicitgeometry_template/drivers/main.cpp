#include "implicitgeometry.hpp"
class Entity
{
    public:
        Entity(int a ):a_(a)
        {
            std::cout <<"Entity "<<a <<" Created " <<'\n';
        }
        int a_;
        ~Entity()
        {
            std::cout <<"Entity Destroyed " <<'\n';
        }


};
int main( )
{

    implicit::AbsImplicitGeometry* circle = new implicit::Circle(0.0,0.0,1.0);


    implicit::AbsImplicitGeometry* circle_2 = new implicit::Circle(0.0,0.0,0.5);
    implicit::AbsImplicitGeometry* square = new implicit::Rectangle(0.0,0.0,2.0,2.0);
    implicit::AbsImplicitGeometry* rectangle_2 = new implicit::Rectangle(0.0,0.0,0.5,5.0);
    

    implicit::AbsOperation* intersection = new implicit::Intersection(circle,square);

    implicit::AbsOperation* uni = new implicit::Union(intersection,rectangle_2);


    implicit::AbsOperation* dif = new implicit::Difference(uni,circle_2);
    std::cout << dif->inside(1.0,2.0) <<'\n';

    delete rectangle_2;
    delete square;
    delete circle_2;
    delete circle;

    return 0;
}
