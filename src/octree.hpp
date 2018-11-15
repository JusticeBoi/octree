#ifndef __node_HPP__
#define  __node_HPP__

#include "vtk_and_std_headers.hpp"

constexpr bool func ( double x, double y, double z)
{
			//return ((pow(x*x + y*y -1 ,3) -
//					x*x*pow(y,3)  < 0.0) && (z == 0))  ? 1 : 0;
   return (x*x + y*y + z*z <=2) ? 1 : 0 ; 
}

template<typename CallBackFunction>
bool my_function(double _x, double _y, double _z, CallBackFunction&& callback)
{
    return callback(_x,_y,_z);
}

typedef bool (*fptr)(double x, double y, double z);
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
	unsigned int _level= 0;
    static fptr _isInsideFunc;
	static std::vector<std::unique_ptr<node>> all_nodes;
	bool isInside_sphere(double r,double c_x,double c_y,double c_z);
	void divideCell();
	bool amICut(const unsigned int no_points);
	vtkSmartPointer<vtkUnstructuredGrid> assembleUGrid(const std::vector<std::vector<double>>& points = node::getAllPoints() );

public:
    static void setInsideOutsideTestFunction(bool (*_isInsideFunc)(double x, double y, double z));
    //fptr setInsideOutsideTestFunction(fptr);
	node();
	node(double xmin,double xmax, double ymin, double ymax,double zmin,double zmax,unsigned int level,
			std::weak_ptr<node> parent);
	void generateQuadTree(const unsigned int max_level);
	void showAll(const std::vector<std::vector<double>>& points = node::getAllPoints());
	static std::vector<std::vector<double>> getAllPoints() ;
	std::vector<std::vector<double>> getAllPointsDeepestLevel() const;
	unsigned int getLevelOfNode() const ;
	void WriteUnstrucredGrid(const std::string output_name );
	void WriteUnstrucredGridDeepestLevel(const std::string output_name );
    static unsigned int getTotalNumberOfNodes();



};

#endif
