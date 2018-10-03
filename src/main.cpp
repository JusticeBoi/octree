#include "octree.hpp"



int main(int argc, char *argv[])
{

	std::string lev = argv[1];
	std::cout <<lev<<std::endl;
	int max_level = std::stoi(lev);

	std::shared_ptr<octree> o = std::make_shared<octree>(0.0,1.0,0.0,1.0,0.0,1,0,std::weak_ptr<octree>());
	o->generateQuadTree(max_level);
//	o->getAllPoints(2);
//	o->getAllPointsDeepestLevel(2);
	o->showVtk(o->getAllPointsDeepestLevel(max_level));
	o->showVtk(o->getAllPoints(max_level));



//	std::cout << o->all_nodes.size() <<std::endl;
	return 0;
}
