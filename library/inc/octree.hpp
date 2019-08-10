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
	node(double xmin,double xmax, double ymin, double ymax,double zmin,double zmax,int level,
			std::weak_ptr<node> parent, const implicit::AbsImplicitGeometry* geo
            );

    bool hasChildren() const;
    bool isRoot() const;
	void generateQuadTree(const int max_level);
	int getLevelOfNode() const ;
	int getMaxLevel() const ;
	void WriteUnstrucredGrid(const std::string output_name );
	void WriteUnstrucredGridDeepestLevel(const std::string output_name );
	vtkSmartPointer<vtkUnstructuredGrid> assembleUGrid(const std::vector<std::vector<double>>& points) const;

    void extendQuadTree(const  int extend_by_level );

    std::shared_ptr<node> getParent() const;

    void getAllPointsAtLevelRecursive(const node* n, int max_level, std::vector<std::vector<double>>& fill) const;
    void getAllPointsUntilRecursive(const node* n, int level, std::vector<std::vector<double>>& fill) const;

    std::vector<std::vector<double>> getAllPointsAtLevel(int max_level = -1) const;
    std::vector<std::vector<double>> getAllPointsUntil(int max_level = -1) const;









};

#endif
