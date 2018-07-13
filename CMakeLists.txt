cmake_minimum_required (VERSION 3.2)
project (aruco-generator VERSION 0.1)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/module)

find_package(OpenCV REQUIRED core opencv_imgcodecs opencv_highgui opencv_imgproc opencv_videoio opencv_aruco)
if (NOT OpenCV_FOUND)
    message(FATAL_ERROR "Could not find OpenCV")
endif()

find_package(cxxopts REQUIRED)

set(ARUCO_GENERATOR
    src/generator.cpp)
add_executable(aruco-generator ${ARUCO_GENERATOR})
target_link_libraries(aruco-generator  ${OpenCV_LIBS})
