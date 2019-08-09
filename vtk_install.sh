#!/bin/sh


git clone git://vtk.org/VTK.git VTK
mkdir VTK-build 
wget download.qt.io/official_releases/qt/5.13/5.13.0/single/qt-everywhere-src-5.13.0.tar.xz
cd VTK-build
cores=$(( $(lscpu | awk '/^Socket\(s\)/{ print $2 }') * $(lscpu | awk '/^Core\(s\) per socket/{ print $4 }') ))
tar xvf qt-everywhere-src-5.13.0.tar.xz
cd qt-everywhere-src-5.13.0
./configure -v -platform linux-g++-64
make -j${cores}
sudo make install


