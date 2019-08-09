#!/bin/sh

#requires cmake with ssl support and version >3.14
current_dir=$(pwd)
git clone git://vtk.org/VTK.git VTK
mkdir VTK-build 
wget download.qt.io/official_releases/qt/5.13/5.13.0/single/qt-everywhere-src-5.13.0.tar.xz
cores=$(( $(lscpu | awk '/^Socket\(s\)/{ print $2 }') * $(lscpu | awk '/^Core\(s\) per socket/{ print $4 }') ))
tar xvf qt-everywhere-src-5.13.0.tar.xz
cd qt-everywhere-src-5.13.0
./configure -v -platform linux-g++-64
make -j${cores}
sudo make install
cd VTK-build
cmake -DVTK_QT_VERSION:STRING=5 \
      -DQT_QMAKE_EXECUTABLE:PATH=/usr/local/Qt-5.13.0/bin/qmake \
      -DVTK_Group_Qt:BOOL=ON \
      -DCMAKE_PREFIX_PATH:PATH=/usr/local/Qt-5.13.0/lib/cmake \
      -DCMAKE_INSTALL_PREFIX:PATH=${current_dir}/VTK-Install \
      -DBUILD_SHARED_LIBS:BOOL=ON ../VTK

make -j${cores}


