#include "octree.hpp"



int main(int argc, char *argv[])
{

	int max_level = std::stoi(std::string(argv[1]));

	std::shared_ptr<octree> o = std::make_shared<octree>(0.0,1.0,0.0,1.0,0.0,1,0,std::weak_ptr<octree>());
	o->generateQuadTree(max_level);
	o->showVtk(o->getAllPointsDeepestLevel(max_level));
	o->showVtk(o->getAllPoints(max_level));


	return 0;
}
