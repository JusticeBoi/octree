#ifndef __Memento_HPP__
#define  __Memento_HPP__
#include "vtk_and_std_headers.hpp"

class Manager;
class Memento
{
    public:
        Memento(const vtkSmartPointer<vtkDataSet> dataSet);
        Memento(const Memento& m) = default;

        vtkSmartPointer<vtkDataSet> getMemory();

    private:
        vtkSmartPointer<vtkDataSet> dSet_ = nullptr;

};




#endif
