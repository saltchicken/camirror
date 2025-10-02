cmake_minimum_required(VERSION 3.10)

project(camirror)

find_package(OpenCV REQUIRED COMPONENTS core highgui videoio)

add_executable(camirror main.cpp)
target_link_libraries(camirror PRIVATE ${OpenCV_LIBS})
