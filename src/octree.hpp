#ifndef __node_HPP__
#define  __node_HPP__

#include "vtk_and_std_headers.hpp"



enum bounds
{
	X_MIN,
	X_MAX,
	Y_MIN,
	Y_MAX,
	Z_MIN,
	Z_MAX
};

class node
{
	static unsigned int total_number_of_nodes;
	unsigned int max_level;
	std::weak_ptr<node> m_parent = std::weak_ptr<node>();
	std::vector<std::shared_ptr<node>> m_children = std::vector<std::shared_ptr<node>>(8,nullptr); 
	double _x_min = 0;
	double _x_max = 0;
	double _y_min = 0;
	double _y_max = 0;
	double _z_min = 0;
	double _z_max = 0;
	unsigned int _level = 0;
	std::function<bool(const std::vector<double>&)> _isInsideFunc;

	bool isInside_sphere(double r,double c_x,double c_y,double c_z);
	void divideCell();
	bool amICut(const unsigned int no_points);
	vtkSmartPointer<vtkUnstructuredGrid> assembleUGrid(const std::vector<std::vector<double>>& points);

public:
	node();
	node(double xmin,double xmax, double ymin, double ymax,double zmin,double zmax,unsigned int level,
			std::weak_ptr<node> parent,std::function<bool(const std::vector<double>)> isInsideFunc );
	void generateQuadTree(const unsigned int max_level);
	void showAll(const std::vector<std::vector<double>>& points);
	std::vector<std::vector<double>> getAllPoints() const;
	static std::vector<std::shared_ptr<node>> all_nodes;
	std::vector<std::vector<double>> getAllPointsDeepestLevel() const;
	unsigned int getLevelOfNode() const ;
	void WriteUnstrucredGrid(const std::string output_name );
	void WriteUnstrucredGridDeepestLevel(const std::string output_name );















};

#endif
