#pragma once
#ifndef __VTK_LIB_HPP__
#define  __VTK_LIB_HPP__

#include "octree.hpp"

//vtk includes


static vtkSmartPointer<vtkUnstructuredGrid> MakeVoxel(std::vector<std::vector<double>> points_for_hex)
{
  // A voxel is a representation of a regular grid in 3-D space.
  int numberOfVertices = 8;

  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  for(auto point_info : points_for_hex)
  {
	  points->InsertNextPoint(point_info[0],point_info[1], point_info[2]);
  }
//  points->InsertNextPoint(0, 0, 0);
//  points->InsertNextPoint(1, 0, 0);
//  points->InsertNextPoint(0, 1, 0);
//  points->InsertNextPoint(1, 1, 0);
//  points->InsertNextPoint(0, 0, 1);
//  points->InsertNextPoint(1, 0, 1);
//  points->InsertNextPoint(0, 1, 1);
//  points->InsertNextPoint(1, 1, 1);

  vtkSmartPointer<vtkVoxel> voxel =
    vtkSmartPointer<vtkVoxel>::New();
  for (int i = 0; i < numberOfVertices; ++i)
    {
    voxel->GetPointIds()->SetId(i, i);
    }

  vtkSmartPointer<vtkUnstructuredGrid> ug =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  ug->SetPoints(points);
  ug->InsertNextCell(voxel->GetCellType(),voxel->GetPointIds());

  return ug;
}

static vtkSmartPointer<vtkUnstructuredGrid> MakeVoxel(std::vector<std::vector<double>> points_for_hex, vtkSmartPointer<vtkUnstructuredGrid> ug)
{
  // A voxel is a representation of a regular grid in 3-D space.
  int numberOfVertices = 8;

  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  for(auto point_info : points_for_hex)
  {
	  points->InsertNextPoint(point_info[0],point_info[1], point_info[2]);
  }
//  points->InsertNextPoint(0, 0, 0);
//  points->InsertNextPoint(1, 0, 0);
//  points->InsertNextPoint(0, 1, 0);
//  points->InsertNextPoint(1, 1, 0);
//  points->InsertNextPoint(0, 0, 1);
//  points->InsertNextPoint(1, 0, 1);
//  points->InsertNextPoint(0, 1, 1);
//  points->InsertNextPoint(1, 1, 1);

  vtkSmartPointer<vtkVoxel> voxel =
    vtkSmartPointer<vtkVoxel>::New();
  for (int i = 0; i < numberOfVertices; ++i)
    {
    voxel->GetPointIds()->SetId(i, i);
    }

  ug->SetPoints(points);
  ug->InsertNextCell(voxel->GetCellType(),voxel->GetPointIds());

  return ug;
}


static vtkSmartPointer<vtkVoxel> MakeVoxelAndReturnVoxel(std::vector<std::vector<double>> points_for_hex)
				{
	// A voxel is a representation of a regular grid in 3-D space.
	int numberOfVertices = 8;

	vtkSmartPointer<vtkPoints> points =
			vtkSmartPointer<vtkPoints>::New();
	for(auto point_info : points_for_hex)
	{
		points->InsertNextPoint(point_info[0],point_info[1], point_info[2]);
	}
	vtkSmartPointer<vtkVoxel> voxel =
			vtkSmartPointer<vtkVoxel>::New();
	for (int i = 8; i < numberOfVertices; ++i)
	{
		voxel->GetPointIds()->SetId(i, i);
	}

	return voxel;
				}


#endif
