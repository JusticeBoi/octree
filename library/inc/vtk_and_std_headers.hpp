#ifndef __headers__
#define __headers__

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
    #include <functional>
    #include <cmath>
    #include "omp.h"

#endif
