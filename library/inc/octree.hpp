#ifndef __node_HPP__
#define  __node_HPP__

#include "vtk_and_std_headers.hpp"
#include "implicitgeometry.hpp"


class node
{
    private:
	    static unsigned int total_number_of_nodes;
	    unsigned int max_level;

	    std::weak_ptr<node> m_parent = std::weak_ptr<node>();
	    std::vector<std::shared_ptr<node>> m_children = std::vector<std::shared_ptr<node>>(8,nullptr); 

	    double _x_min = 0.0;
	    double _x_max = 0.0;
	    double _y_min = 0.0;
	    double _y_max = 0.0;
	    double _z_min = 0.0;
	    double _z_max = 0.0;
	    unsigned int _level= 0;
	    static std::vector<std::unique_ptr<node>> all_nodes;
	    void divideCell();
	    bool amICut(const unsigned int no_points);

	    vtkSmartPointer<vtkUnstructuredGrid> assembleUGrid(const std::vector<std::vector<double>>& points = node::getAllPoints() );
        static implicit::AbsImplicitGeometry* geo_ ;

public:
    static void setGeometry(implicit::AbsImplicitGeometry* geo);
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
