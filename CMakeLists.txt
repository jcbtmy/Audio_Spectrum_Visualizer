cmake_minimum_required(VERSION 3.16)

project(Graphics)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)


add_executable(${PROJECT_NAME} src/main.cpp
                               src/Sphere.cpp
                               src/Sphere.h
                               src/Shader.cpp
                               src/Shader.h
                               src/Window.cpp
                               src/Window.h
                               src/Shape.cpp
                               src/Shape.h
                            )

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(GLEW REQUIRED)


target_link_libraries(${PROJECT_NAME} OpenGL::GL glfw GLEW::GLEW)
