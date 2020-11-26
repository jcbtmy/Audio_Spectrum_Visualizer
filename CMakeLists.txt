cmake_minimum_required(VERSION 3.16)

project(Graphics)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)


add_executable(${PROJECT_NAME} src/main.cpp)

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)

target_link_libraries(${PROJECT_NAME} OpenGL::GL glfw)
