#include "Memento.hpp"


Memento::Memento(const std::vector<vtkSmartPointer<vtkDataSet>>& dataset): dSet_(dataset) {};

std::vector<vtkSmartPointer<vtkDataSet>> Memento::getMemory()
{
    return dSet_.size() ? dSet_ : std::vector<vtkSmartPointer<vtkDataSet>>();  
}
