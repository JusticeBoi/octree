#ifndef __MOUSEINTERACTOR_HPP__
#define  __MOUSEINTERACTOR_HPP__

#include <vtkInteractorStyleTrackballCamera.h>

class Manager;
class customMouseInteractorStyle : public vtkInteractorStyleTrackballCamera
{
  public:
    static customMouseInteractorStyle* New();
    vtkTypeMacro(customMouseInteractorStyle, vtkInteractorStyleTrackballCamera);

    virtual void OnLeftButtonDown() override;

    virtual void OnMiddleButtonDown() override;

    virtual void OnRightButtonDown() override;


    void setManager( Manager * );

  private:
    Manager* m_;

};





#endif
