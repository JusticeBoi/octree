#pragma once
#ifndef __OCTREE_HPP__
#define  __OCTREE_HPP__

#include <iostream>
#include <vector>
#include <fstream>
#include <memory>
#include <chrono>
#include <vtk-8.1/vtkPoints.h>
#include <vtk-8.1/vtkXMLUnstructuredGridReader.h>
#include <vtk-8.1/vtkXMLUnstructuredGridWriter.h>
#include <vtk-8.1/vtkUnstructuredGrid.h>
#include <vtk-8.1/vtkSmartPointer.h>
#include <vtk-8.1/vtkCellData.h>
#include <vtk-8.1/vtkDataArray.h>
#include <vtk-8.1/vtkDoubleArray.h>
#include <vtk-8.1/vtkDataSetMapper.h>
#include <vtk-8.1/vtkActor.h>
#include <vtk-8.1/vtkActor2D.h>
#include <vtk-8.1/vtkRenderWindow.h>
#include <vtk-8.1/vtkRenderer.h>
#include <vtk-8.1/vtkRenderWindowInteractor.h>
#include <vtk-8.1/vtkPointData.h>
#include <vtk-8.1/vtkPolyData.h>
#include <vtk-8.1/vtkVoxel.h>
#include <vtk-8.1/vtkHexahedron.h>
#include <vtk-8.1/vtkRenderWindowInteractor.h>
#include <vtk-8.1/vtkProperty.h>
#include <vtk-8.1/vtkCamera.h>
#include <vtk-8.1/vtkTextProperty.h>
#include <vtk-8.1/vtkTextMapper.h>

#include <vtk-8.1/vtkHexagonalPrism.h>
#include <vtk-8.1/vtkPentagonalPrism.h>
#include <vtk-8.1/vtkPolyhedron.h>
#include <vtk-8.1/vtkPyramid.h>
#include <vtk-8.1/vtkTetra.h>
#include <vtk-8.1/vtkWedge.h>

#include <string>
#include <cstdlib>

#include "vtk_lib.hpp"


class octree
{
	static unsigned int total_number_of_nodes;
	unsigned int max_level;
	std::weak_ptr<octree> m_parent;
	std::vector<std::shared_ptr<octree>> m_children;
	double _x_min;
	double _x_max;
	double _y_min;
	double _y_max;
	double _z_min;
	double _z_max;
	int _level;

	std::vector<octree> getAllNodes();
	bool isInside_sphere(double r,double c_x,double c_y,double c_z);
	void divideCell();
	bool amICut(int no_points);
	vtkSmartPointer<vtkUnstructuredGrid> assembleUGrid(std::vector<std::vector<double>> points);

public:
	octree();
	octree(double xmin,double xmax, double ymin, double ymax,double zmin,double zmax,int level,std::weak_ptr<octree> parent );
	void generateQuadTree(unsigned int max_level);
	void showAll(std::vector<std::vector<double>> points);
	std::vector<std::vector<double>> getAllPoints();
	static std::vector<std::shared_ptr<octree>> all_nodes;
	std::vector<std::vector<double>> getAllPointsDeepestLevel();
	double getLevelOfNode();
	void WriteUnstrucredGrid(std::string output_name );















};

#endif
