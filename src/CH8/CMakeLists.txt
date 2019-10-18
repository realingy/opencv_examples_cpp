cmake_minimum_required(VERSION 3.5)

# 工程信息
project(OpenCVDemosCh8)

include_directories(${CMAKE_SOURCE_DIR}/..)

add_subdirectory(1_findContours)
add_subdirectory(2_FindAndDrawContours)
add_subdirectory(3_convexHull)
add_subdirectory(4_convexHull2)
add_subdirectory(5_minAreaRect)
add_subdirectory(6_minEnclosingCircle)
add_subdirectory(7_approxPolyDP)
add_subdirectory(8_ContourMoment)
add_subdirectory(9_watershed)
add_subdirectory(10_inpaint)
