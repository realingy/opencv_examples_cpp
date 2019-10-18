cmake_minimum_required(VERSION 3.5)

# 工程信息
project(OpenCVDemosCh7)

include_directories(${CMAKE_SOURCE_DIR}/..)

add_subdirectory(1_Canny)
add_subdirectory(2_sobel)
add_subdirectory(3_Laplacian)
add_subdirectory(4_Scharr)
add_subdirectory(5_EdgeDetection)
add_subdirectory(6_HoughLines)
add_subdirectory(7_HoughLinesP)
add_subdirectory(8_EqualizeHist)
add_subdirectory(9_HoughCircles)
add_subdirectory(10_CircleCheck)
add_subdirectory(11_HoughLineTotal)
add_subdirectory(12_remap)
add_subdirectory(13_remap2)
add_subdirectory(14_AffineTransform)
