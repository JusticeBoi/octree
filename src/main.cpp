#include "octree.hpp"


int main(int argc, char *argv[])
{

	if (argc != 2)
	{
		std::cerr<<"write the max tree depth as an argument"<<std::endl;
	}
	int max_level = std::stoi(std::string(argv[1]));

	auto isInsideSphere = [](std::vector<double> center_vec)
					{
					return ((center_vec[0]-0.5)*(center_vec[0]-0.5) + (center_vec[1]-0.5)*(center_vec[1]-0.5) + (center_vec[2]-0.5)*(center_vec[2]-0.5) <= 0.1*0.1) ? 1: 0;
					};

	std::vector<double> Prism_Boundary{0.3,0.70,0.3,0.7,0.3,0.7 };
	auto isInsideRect = [&Prism_Boundary](std::vector<double> center_vec)
						{
						 if ( (center_vec[0] < Prism_Boundary[1] && center_vec[0] > Prism_Boundary[0]) && (center_vec[1] < Prism_Boundary[3] && center_vec[1] > Prism_Boundary[2])&& (center_vec[2] < Prism_Boundary[5] && center_vec[2] > Prism_Boundary[4])  ) return true;
						 else return false;
						};

	auto isInsideHeart = [](std::vector<double> center_vec)
							{
		return (pow(pow(center_vec[0],2) + (9.0/4.0)*pow(center_vec[1],2) + pow(center_vec[2],2) -1,3) -
				(0.1)*pow(center_vec[0],2)*pow(center_vec[2],3) - (9.0/80.0)*pow(center_vec[1],2)*pow(center_vec[2],3) < 0.0) ? 1 : 0;
							};

	auto isInsideHeart_1 = [](std::vector<double> center_vec)
								{
			return (pow(pow(center_vec[0],2) + pow(center_vec[1],2) -1 ,3) -
					pow(center_vec[0],2)*pow(center_vec[1],3)  < 0.0) ? 1 : 0;
								};
	std::shared_ptr<octree> o = std::make_shared<octree>(-1.5, 1.5 ,-1.5 ,1.5 , -1.5 , 1.5, 0 ,std::weak_ptr<octree>(),isInsideHeart_1);



	o->generateQuadTree(max_level);
//	o->WriteUnstrucredGrid("sphere.vtu");
	o->showAll(o->getAllPointsDeepestLevel());
//	o->showAll(o->getAllPoints());


	return 0;
}
