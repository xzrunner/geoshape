cmake_minimum_required(VERSION 3.16)

project(geoshape)

add_definitions(
    -DNO_RTTR
)

################################################################################
# Source groups
################################################################################
set(no_group_source_files
    "include/geoshape/config.h"
    "include/geoshape/Serialize.h"
    "include/geoshape/Shape2D.h"
    "include/geoshape/Shape3D.h"
    "include/geoshape/typedef.h"
    "source/Serialize.cpp"
)
source_group("" FILES ${no_group_source_files})

set(2d
    "include/geoshape/Arc.h"
    "include/geoshape/Bezier.h"
    "include/geoshape/Circle.h"
    "include/geoshape/Ellipse.h"
    "include/geoshape/Line2D.h"
    "include/geoshape/Point2D.h"
    "include/geoshape/Polygon2D.h"
    "include/geoshape/Polyline2D.h"
    "include/geoshape/Polyline2DImpl.h"
    "include/geoshape/Rect.h"
    "source/Arc.cpp"
    "source/Bezier.cpp"
    "source/Circle.cpp"
    "source/Ellipse.cpp"
    "source/Line2D.cpp"
    "source/Point2D.cpp"
    "source/Polygon2D.cpp"
    "source/Polyline2D.cpp"
    "source/Polyline2DImpl.cpp"
    "source/Rect.cpp"
)
source_group("2d" FILES ${2d})

set(3d
    "include/geoshape/Arc3D.h"
    "include/geoshape/Box.h"
    "include/geoshape/Line3D.h"
    "include/geoshape/Point3D.h"
    "include/geoshape/Polygon3D.h"
    "include/geoshape/Polyline3D.h"
    "include/geoshape/Sphere.h"
    "source/Arc3D.cpp"
    "source/Box.cpp"
    "source/Line3D.cpp"
    "source/Point3D.cpp"
    "source/Polygon3D.cpp"
    "source/Polyline3D.cpp"
    "source/Sphere.cpp"
)
source_group("3d" FILES ${3d})

set(ALL_FILES
    ${no_group_source_files}
    ${2d}
    ${3d}
)

################################################################################
# Target
################################################################################

add_library(${PROJECT_NAME} STATIC ${ALL_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE include external/sm external/primitive/include)
