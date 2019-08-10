# Specify the minimum version for CMake

cmake_minimum_required(VERSION 3.5)

# Project's name

project(octree)
# Set the output folder where your program will be created
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
#set(CMAKE_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(VTK_DIR "/home/oguz/personal_projects/octree/VTK-Install")
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_FLAGS "-march=native -fopenmp -Ofast -Wall -Wextra -Wno-unused-parameter -Wshadow -Wnon-virtual-dtor -g  ")
#SET(GCC_LINK_FLAGS  "-ltbb")
#SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_LINK_FLAGS}")

find_package(VTK REQUIRED PATHS /home/oguz/personal_projects/octree/VTK-Install NO_DEFAULT_PATH)
#message(${VTK_INCLUDE_DIRS})
#include(${VTK_USE_FILE})
include_directories(implicitgeometry/library/inc)
include_directories(implicitgeometry/library/inc)
include_directories(implicitgeometry/external/catch)
include_directories( library/inc )
include_directories( . )

add_subdirectory(implicitgeometry)
add_subdirectory(utilities)

file( GLOB LIBRARY_SOURCE_FILES library/src/*.cpp )
file( GLOB TEST_SOURCE_FILES library/test/*.cpp )
add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})

add_executable(driver drivers/main.cpp ${LIBRARY_SOURCE_FILES} )
add_executable(octree_testrunner ${TEST_SOURCE_FILES}  ${LIBRARY_SOURCE_FILES})

target_link_libraries(driver ${VTK_LIBRARIES} implicitgeometry utilities )
target_link_libraries(octree_testrunner ${VTK_LIBRARIES} implicitgeometry utilities )
