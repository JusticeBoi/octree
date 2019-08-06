#include "catch.hpp"
#include "octree.hpp"
#include "AbsImplicitGeometry.hpp"
#include "Sphere.hpp"
#include "Manager.hpp"


class nodeMock: public node
{
    public:
        static int numberOfConstructions;
	    nodeMock(double xmin,double xmax, double ymin, double ymax,double zmin,double zmax,int level,
	    		std::weak_ptr<node> parent, const implicit::AbsImplicitGeometry* geo,
                std::vector<std::shared_ptr<node>>* all_nodes ) : node(xmin, xmax, ymin, ymax, zmin, zmax, level, parent, geo, all_nodes ) {++numberOfConstructions;};

};
int nodeMock::numberOfConstructions = 0;
TEST_CASE( "node_test" )
{



    std::vector<std::shared_ptr<node>> fill_this; 
    std::shared_ptr<implicit::AbsImplicitGeometry> sphere = std::make_shared<implicit::Sphere>(0.0,0.0,0.0,1.1); 

    std::shared_ptr<node> rootNode = std::make_shared<nodeMock>(0.0, 1.0, 0.0, 1.0, 0.0, 1.0,0, std::weak_ptr<node>(),sphere.get(), &fill_this); 

    CHECK(!rootNode->hasChildren());

    CHECK(nodeMock::numberOfConstructions == 1);

    CHECK(fill_this.size() == 1);

    /* a cube has 8 points */
    CHECK(rootNode->getAllPoints().size() == 8);

    CHECK(rootNode->getAllPointsDeepestLevel().size() == 8);

    CHECK(rootNode->my_ptr_to_all_nodes == &fill_this);

    CHECK(rootNode->getLevelOfNode() == 0);

    rootNode->generateQuadTree(1);

    CHECK(rootNode->hasChildren());

    CHECK(rootNode->getAllPoints().size() == 8 + 8*8);

    CHECK(rootNode->getAllPointsDeepestLevel().size() ==  8*8);

    CHECK(rootNode->getLevelOfNode() ==  0);

    CHECK(fill_this.size() == 9);

    for(auto node : fill_this )
    {
        if ( node->isRoot() ) CHECK(rootNode->getAllPoints() == node->getAllPoints() );
        else
        {
            CHECK(node->getLevelOfNode() == 1);

            CHECK(!node->hasChildren());

            CHECK(node->my_ptr_to_all_nodes == &fill_this);

            CHECK(!node->isRoot());

        }
    }


    rootNode->extendQuadTree(1);


    for(auto node : fill_this )
    {
        CHECK(node->my_ptr_to_all_nodes == &fill_this );
        if ( node->getLevelOfNode() == 2 )
        {
            CHECK( !node->hasChildren());
            CHECK( !node->isRoot());
        }
        if ( !node->isRoot() ) CHECK(node->getParent());
    }

    std::vector<std::shared_ptr<node>> fill_this_2; 
    std::shared_ptr<node> rootNode_2 = std::make_shared<node>(0.0, 1.0, 0.0, 1.0, 0.0, 1.0,0, std::weak_ptr<node>(),sphere.get(), &fill_this_2); 

    CHECK(!rootNode_2->hasChildren());
    CHECK(rootNode_2->isRoot());

    CHECK(fill_this_2.size() == 1);

    /* a cube has 8 points */
    CHECK(rootNode_2->getAllPoints().size() == 8);

    CHECK(rootNode_2->getAllPointsDeepestLevel().size() == 8);

    CHECK(rootNode_2->my_ptr_to_all_nodes == &fill_this_2);

    CHECK(rootNode_2->getLevelOfNode() == 0);

    rootNode_2->extendQuadTree(1);

    CHECK(rootNode_2->hasChildren());

    CHECK(rootNode_2->isRoot());


    CHECK(rootNode_2->getAllPoints().size() == 8 + 8*8);

    CHECK(rootNode_2->getAllPointsDeepestLevel().size() ==  8*8);

    CHECK(rootNode_2->getLevelOfNode() ==  0);

    CHECK(fill_this_2.size() == 9);

    for(auto node : fill_this_2 )
    {
        CHECK(node->my_ptr_to_all_nodes == &fill_this_2 );
        if ( node->isRoot() ) CHECK(rootNode_2->getAllPoints() == node->getAllPoints() );
        else
        {

            CHECK(node->getParent());

            CHECK(node->getLevelOfNode() == 1);

            CHECK(!node->hasChildren());

            CHECK(node->my_ptr_to_all_nodes == &fill_this_2);

            CHECK(!node->isRoot());

        }
    }










}
