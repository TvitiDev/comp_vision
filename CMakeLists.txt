cmake_minimum_required(VERSION 3.8)
project(ComputerVision)

set(CMAKE_CXX_STANDARD 17)
set(OpenCV_DIR /home/vadim/project/opencv-3.3.1/cmake-build-debug)

set(OpenCV_FOUND 1)
find_package(OpenCV REQUIRED)

set(SOURCE_FILES main.cpp Image.cpp Image.h Filters.cpp Filters.h Kernels.cpp Kernels.h Pyramids.cpp Pyramids.h)

add_executable(ComputerVision ${SOURCE_FILES})
target_link_libraries(ComputerVision ${OpenCV_LIBS})