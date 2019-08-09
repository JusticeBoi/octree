#ifndef __node_HPP__
#define  __node_HPP__

#include "vtk_and_std_headers.hpp"
#include "AbsImplicitGeometry.hpp"
#include "Circle.hpp"
#include "Sphere.hpp"
#include "Union.hpp"
#include "Difference.hpp"
#include "Intersection.hpp"
#include "Rectangle.hpp"





enum bounds
{
	X_MIN,
	X_MAX,
	Y_MIN,
	Y_MAX,
	Z_MIN,
	Z_MAX
};

class node : public std::enable_shared_from_this<node>
{
	std::weak_ptr<node> m_parent = std::weak_ptr<node>();
	//std::vector<std::shared_ptr<node>> m_children = std::vector<std::shared_ptr<node>>(8,nullptr); 
	std::vector<std::shared_ptr<node>> m_children ; 
	double _x_min = 0;
	double _x_max = 0;
	double _y_min = 0;
	double _y_max = 0;
	double _z_min = 0;
	double _z_max = 0;
	int _level = 0;
	int max_level;
    const implicit::AbsImplicitGeometry* _geo ;

	void divideCell();
	bool amICut(const int no_points);

public:
	node() = delete;
	//node(double xmin,double xmax, double ymin, double ymax,double zmin,double zmax,int level,
	//		std::weak_ptr<node> parent, const implicit::AbsImplicitGeometry* geo,
    //        std::vector<std::shared_ptr<node>>* all_nodes );

	node(double xmin,double xmax, double ymin, double ymax,double zmin,double zmax,int level,
			std::weak_ptr<node> parent, const implicit::AbsImplicitGeometry* geo
            );

    bool hasChildren() const;
    bool isRoot() const;
	void generateQuadTree(const int max_level);
	void showAll(const std::vector<std::vector<double>>& points);
	//std::vector<std::vector<double>> getAllPoints() const;
	//std::vector<std::vector<double>> getAllPointsDeepestLevel() const;
	int getLevelOfNode() const ;
	void WriteUnstrucredGrid(const std::string output_name );
	void WriteUnstrucredGridDeepestLevel(const std::string output_name );
	vtkSmartPointer<vtkUnstructuredGrid> assembleUGrid(const std::vector<std::vector<double>>& points) const;

    void extendQuadTree(const  int extend_by_level );
	std::vector<std::shared_ptr<node>>* my_ptr_to_all_nodes;

    std::shared_ptr<node> getParent() const;
    std::vector<std::vector<double>> getAllPointsDeepestLevel() const;
    std::vector<std::vector<double>> getAllPoints() const;
    void getAllPointsDeepestLevelRecursive(const node* n, std::vector<std::vector<double>>& fill) const;
    void getAllPointsRecursive(const node* n, std::vector<std::vector<double>>& fill) const;








};

#endif
