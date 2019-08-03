#include "octree.hpp"
#include "Manager.hpp"
#include <memory>


int main(int argc, char *argv[])
{

	if (argc != 2)
	{
		std::cerr<<"write the max tree depth as an argument"<<std::endl;
		return -1;
	}
	int max_level = std::stoi(std::string(argv[1]));

	auto isInsideSphere = [](const std::vector<double>& center_vec)
					{
					return ((center_vec[0]-0.5)*(center_vec[0]-0.5) + (center_vec[1]-0.5)*(center_vec[1]-0.5) + (center_vec[2]-0.5)*(center_vec[2]-0.5) <= 0.1*0.1) ? 1: 0;
					};

	std::vector<double> Prism_Boundary{0.3,0.70,0.3,0.7,0.3,0.7 };
	auto isInsideRect = [&Prism_Boundary](const std::vector<double>& center_vec)
						{
						 if ( (center_vec[0] < Prism_Boundary[1] && center_vec[0] > Prism_Boundary[0]) && (center_vec[1] < Prism_Boundary[3] && center_vec[1] > Prism_Boundary[2])&& (center_vec[2] < Prism_Boundary[5] && center_vec[2] > Prism_Boundary[4])  ) return true;
						 else return false;
						};

	//auto isInsideHeart = [](const std::vector<double>& center_vec)
	//						{
	//	return (pow(pow(center_vec[0],2) + (9.0/4.0)*pow(center_vec[1],2) + pow(center_vec[2],2) -1,3) -
	//			(0.1)*pow(center_vec[0],2)*pow(center_vec[2],3) - (9.0/80.0)*pow(center_vec[1],2)*pow(center_vec[2],3) < 0.0) ? 1 : 0;
	//						};

	//auto isInsideHeart_1 = [](const std::vector<double>& center_vec)
//								{
   // 		return ((pow(pow(center_vec[0],2) + pow(center_vec[1],2) -1 ,3) -
   // 				pow(center_vec[0],2)*pow(center_vec[1],3)  < 0.0) && (center_vec[2] == 0))  ? 1 : 0;
   // 							};
	//&& (center_vec[2] == 0)

	//std::shared_ptr<node> o = std::make_shared<node>(-1.5, 1.5 ,-1.5 ,1.5 , -1.5 , 1.5, 0 ,std::weak_ptr<node>(),isInsideRect);
    //std::unique_ptr<implicit::AbsImplicitGeometry> rec = std::make_unique<implicit::Rectangle>(0., 0., 0.6, 0.6);
    const implicit::AbsImplicitGeometry* rec = new implicit::Rectangle(0., 0., 0.3, 0.3 );

    const std::shared_ptr<implicit::AbsImplicitGeometry> rec_shared = std::make_shared<implicit::Rectangle>(0., 0., 0.3, 0.3 );

    const std::shared_ptr<implicit::AbsImplicitGeometry> circle_shared = std::make_shared<implicit::Circle>(0.3, 0.3, 0.1 );

    //const implicit::AbsImplicitGeometry* circle = new implicit::Circle(0., 0., 0.3 );
    std::vector<std::shared_ptr<node>> fill_me_up1;
    std::vector<std::shared_ptr<node>> fill_me_up2;
	//std::shared_ptr<node> o1 = std::make_shared<node>(-1, 1. ,-1 ,1. , 0. , 0.0001, 0 ,std::weak_ptr<node>(),&(*rec_shared), fill_me_up1);
	//std::shared_ptr<node> o2 = std::make_shared<node>(-1, 1. ,-1 ,1. , 0. , 0.0001, 0 ,std::weak_ptr<node>(),&(*circle_shared), fill_me_up2);


	//auto start = std::chrono::steady_clock::now();
	//o1->generateQuadTree(max_level);
	//o2->generateQuadTree(max_level);
	//auto end = std::chrono::steady_clock::now();
	//auto diff = end - start;
	//std::cout <<"duration generatequadtree :  "<< std::chrono::duration <double, std::milli> (diff).count() << " ms" << std::endl;
    Manager M(-1., 1., -1., 1.);
    M.addGeometry(&(*rec_shared));
    M.createRootNodes();
    //M.generateQuadTree(max_level);
    M.renderAllGeometriesAndStart();

    //M.renderAllGeometriesAndStart();

    //M.addedDSet = o2->assembleUGrid(o2->getAllPointsDeepestLevel());
    // 
    //std::cout <<"size of getAllPointsDeepestLevel : " << o2->getAllPointsDeepestLevel().size() << '\n';
    //M.Render(o1->assembleUGrid(o1->getAllPointsDeepestLevel()));
    //M.start();
    //
	//o2->WriteUnstrucredGridDeepestLevel("heart.vtu");
	//o->showAll(o->getAllPointsDeepestLevel());
	//o->showAll(o->getAllPoints());

    delete rec;
	return 0;
}