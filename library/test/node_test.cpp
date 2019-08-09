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
	    		std::weak_ptr<node> parent, const implicit::AbsImplicitGeometry* geo ) : node(xmin, xmax, ymin, ymax, zmin, zmax, level, parent, geo ) {++numberOfConstructions;};

};
int nodeMock::numberOfConstructions = 0;
TEST_CASE( "node_test" )
{



    std::shared_ptr<implicit::AbsImplicitGeometry> sphere = std::make_shared<implicit::Sphere>(0.0,0.0,0.0,1.1); 

    std::shared_ptr<node> rootNode = std::make_shared<nodeMock>(0.0, 1.0, 0.0, 1.0, 0.0, 1.0,0, std::weak_ptr<node>(),sphere.get()); 

    CHECK(!rootNode->hasChildren());

    CHECK(nodeMock::numberOfConstructions == 1);


    /* a cube has 8 points */
    CHECK(rootNode->getAllPoints().size() == 8);

    CHECK(rootNode->getAllPointsDeepestLevel().size() == 8);


    CHECK(rootNode->getLevelOfNode() == 0);

    rootNode->generateQuadTree(1);

    CHECK(rootNode->getParent() == nullptr);

    CHECK(rootNode->hasChildren());

    CHECK(rootNode->getAllPoints().size() == 8 + 8*8);

    CHECK(rootNode->getAllPointsDeepestLevel().size() ==  8*8);

    CHECK(rootNode->getLevelOfNode() ==  0);

    rootNode->extendQuadTree(1);

    CHECK(rootNode->getParent() == nullptr);




    std::shared_ptr<node> rootNode_2 = std::make_shared<node>(0.0, 1.0, 0.0, 1.0, 0.0, 1.0,0, std::weak_ptr<node>(),sphere.get() ); 

    CHECK(!rootNode_2->hasChildren());
    CHECK(rootNode_2->isRoot());


    /* a cube has 8 points */
    CHECK(rootNode_2->getAllPoints().size() == 8);

    CHECK(rootNode_2->getAllPointsDeepestLevel().size() == 8);


    CHECK(rootNode_2->getLevelOfNode() == 0);

    rootNode_2->extendQuadTree(1);

    CHECK(rootNode_2->hasChildren());

    CHECK(rootNode_2->isRoot());


    CHECK(rootNode_2->getAllPoints().size() == 8 + 8*8);

    CHECK(rootNode_2->getAllPointsDeepestLevel().size() ==  8*8);

    CHECK(rootNode_2->getLevelOfNode() ==  0);











}
