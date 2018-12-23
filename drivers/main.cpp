#include "octree.hpp"

using AbsGeo = implicit::AbsImplicitGeometry;
using Circle = implicit::Circle;
using Rectangle = implicit::Rectangle;
using Union = implicit::Union;
using Difference = implicit::Difference;
using Intersection = implicit::Intersection;

int main(int argc, char *argv[])
{

	if (argc != 2)
	{
		std::cerr<<"write the max tree depth as an argument"<<std::endl;
		return -1;
	}
	int max_level = std::stoi(std::string(argv[1]));

    AbsGeo* circle = new Circle(0.0,0.0,1.0); 
    AbsGeo* rec = new Rectangle(-1.0, -1.0, 1.0,1.0); 
    AbsGeo* rec_slender = new Rectangle(-0.2, -3.0, 0.2,3.0); 
    AbsGeo* circle_small = new Circle(0.0,0.0,0.2); 
    AbsGeo* intersect = new Intersection(circle, rec);
    AbsGeo* uni = new Union(intersect, rec_slender);
    AbsGeo* difference = new Difference(uni, circle_small);


	std::shared_ptr<node> o = std::make_shared<node>(-4.0, 4.0 ,-4.0 ,4.0 , 0.0 , 0.1, 0 ,std::weak_ptr<node>());
    node::setGeometry( difference);


	auto start = std::chrono::steady_clock::now();
	o->generateQuadTree(max_level);
	auto end = std::chrono::steady_clock::now();
	auto diff = end - start;
	std::cout <<"duration generatequadtree :  "<< std::chrono::duration <double, std::milli> (diff).count() << " ms" << std::endl;
    std::cout<<node::getTotalNumberOfNodes()<<std::endl;
    o->showAll(o->getAllPointsDeepestLevel());
    o->showAll(o->getAllPoints());

    delete circle;
    delete rec;
    delete rec_slender;
    delete circle_small;
    delete uni;
    delete intersect;
    delete difference;


	return 0;
}
