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

    const implicit::AbsImplicitGeometry* rec = new implicit::Rectangle(0., 0., 0.3, 0.3 );

    const std::shared_ptr<implicit::AbsImplicitGeometry> rec_shared = std::make_shared<implicit::Rectangle>(0., 0., 0.3, 0.3 );

    const std::shared_ptr<implicit::AbsImplicitGeometry> circle_shared = std::make_shared<implicit::Circle>(0.3, 0.3, 0.1 );
    const std::shared_ptr<implicit::AbsImplicitGeometry> sphere = std::make_shared<implicit::Sphere>(0.3, 0.3, 0.3, 0.1 );

    const std::shared_ptr<implicit::AbsImplicitGeometry> recAndCircle = std::make_shared<implicit::Union>(rec_shared.get(), circle_shared.get() );


    std::vector<std::shared_ptr<node>> fill_me_up1;
    std::vector<std::shared_ptr<node>> fill_me_up2;


    Manager M(-1., 1., -1., 1., -1., 1.);
    //M.addGeometry(&(*rec_shared));
    //M.addGeometry(rec_shared.get());
    //M.addGeometry(rec_shared);
    //M.addGeometry(circle_shared);
    M.addGeometry(sphere);
    //M.addGeometry(sphere.get());
    M.createRootNodes();
    //M.StoredNodesInfo();
    //M.generateQuadTree(max_level);
    M.renderAllGeometriesAndStart();



    delete rec;
	return 0;
}
