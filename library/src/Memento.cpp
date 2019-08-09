#include "Memento.hpp"


Memento::Memento(const vtkSmartPointer<vtkDataSet> dataset): dSet_(dataset) {};

vtkSmartPointer<vtkDataSet> Memento::getMemory()
{
    return dSet_ ;  
}
