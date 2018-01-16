cmake_minimum_required (VERSION 2.8.11)

project (cooking-helper)

find_package(OpenCV REQUIRED core imgproc highgui objdetect calib3d)

include_directories(src/)
add_definitions("-Wall -std=c++14")

include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(cooking-helper src/main.cpp src/util.h src/util.cpp)
target_link_libraries(cooking-helper ${OpenCV_LIBS})
file(COPY ./assets DESTINATION ${CMAKE_BINARY_DIR})
