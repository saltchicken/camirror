cmake_minimum_required(VERSION 3.10)
project(camirror)

# Set C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED COMPONENTS core highgui videoio)

message(STATUS "OpenCV libraries found: ${OpenCV_LIBS}")

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(camirror main.cpp)

target_link_libraries(camirror ${OpenCV_LIBS})
