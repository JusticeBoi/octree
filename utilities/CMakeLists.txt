cmake_minimum_required(VERSION 3.5)

project(octree)

#SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "/usr/local/boost_1_66_0/include")
#SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "/usr/local/boost_1_66_0/lib")
SET(BOOST_ROOT "/usr/local/boost_1_66_0")
#SET(Boost_NO_SYSTEM_PATHS ON)
#SET(BOOST_INCLUDEDIR "/usr/local/boost_1_66_0/include")
#SET(BOOST_LIBRARYDIR "/usr/local/boost_1_66_0/lib")

find_package(Boost 1.66.0 COMPONENTS filesystem system timer)

include_directories(${Boost_INCLUDE_DIR})
include_directories(checks/inc)
include_directories(compare/inc)
include_directories(diagnostics/inc)
include_directories(exceptions/inc)
include_directories(logging/inc)
include_directories(..)

file( GLOB CHECKS_SOURCE_FILES checks/src/*.cpp )
file( GLOB COMPARE_SOURCE_FILES compare/src/*.cpp )
file( GLOB DIAGNOSTICS_SOURCE_FILES diagnostics/src/*.cpp )
file( GLOB EXCEPTIONS_SOURCE_FILES exceptions/src/*.cpp )
file( GLOB LOGGING_SOURCE_FILES logging/src/*.cpp )
file( GLOB REST_SOURCE src/*.cpp )

SET( ALL_SOURCES  ${CHECKS_SOURCE_FILES} ${COMPARE_SOURCE_FILES} ${DIAGNOSTICS_SOURCE_FILES} ${EXCEPTIONS_SOURCE_FILES} ${LOGGING_SOURCE_FILES} ${REST_SOURCE} )

file( GLOB CHECKS_HEADER_FILES checks/inc/*.hpp )
file( GLOB COMPARE_HEADER_FILES compare/inc/*.hpp )
file( GLOB DIAGNOSTICS_HEADER_FILES diagnostics/inc/*.hpp )
file( GLOB EXCEPTIONS_HEADER_FILES exceptions/inc/*.hpp )
file( GLOB LOGGING_HEADER_FILES logging/inc/*.hpp )
file( GLOB REST_HEADER inc/*.hpp )

SET( ALL_HEADERS  ${CHECKS_HEADER_FILES} ${COMPARE_HEADER_FILES} ${DIAGNOSTICS_HEADER_FILES} ${EXCEPTIONS_HEADER_FILES} ${LOGGING_HEADER_FILES} ${REST_HEADER} )


add_library( utilities SHARED ${ALL_SOURCES} ${ALL_HEADERS} )

target_link_libraries( utilities ${Boost_LIBRARIES} )
