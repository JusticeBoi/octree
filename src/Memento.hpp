#ifndef __Memento_HPP__
#define  __Memento_HPP__
#include "vtk_and_std_headers.hpp"

class Manager;
class Memento
{
    public:
        Memento(const std::vector<vtkSmartPointer<vtkDataSet>>& dataSet);
        Memento(const Memento& m) = default;

        std::vector<vtkSmartPointer<vtkDataSet>> getMemory();

    private:
        std::vector<vtkSmartPointer<vtkDataSet>> dSet_;

};




#endif
