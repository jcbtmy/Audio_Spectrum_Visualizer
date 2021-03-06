cmake_minimum_required(VERSION 3.16)

project(Graphics)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
Set(CMAKE_CXX_FLAGS "-lm")


add_executable(${PROJECT_NAME} src/main.cpp
                               src/Shader.cpp
                               src/Shader.h
                               src/Window.cpp
                               src/Window.h
                               src/Shape.cpp
                               src/Shape.h
                               src/Controller.cpp
                               src/Controller.h
                               src/Camera.cpp
                               src/Camera.h
                               src/Audio.cpp
                               src/Audio.h
                            )

find_path(AVCODEC_INCLUDE_DIR libavcodec/avcodec.h)
find_library(AVCODEC_LIBRARY avcodec)

find_path(AVUTIL_INCLUDE_DIR libavutil/avutil.h)
find_library(AVUTIL_LIBRARY avutil)

find_path(AVFORMAT_INCLUDE_DIR libavformat/avformat.h)
find_library(AVFORMAT_LIBRARY avformat)

find_path(LIBAO_INCLUDE_DIR ao/ao.h)
find_library(LIBAO_LIBRARY ao)

find_path(FFTW_INCLUDE_DIR fftw.h)
find_library(FFTW_LIBRARY fftw)

find_package(Threads REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)


target_link_libraries(${PROJECT_NAME}  OpenGL::GL
                                       Threads::Threads
                                       glfw
                                       fftw3
                                       GLEW::GLEW 
                                       ${GLM_INCLUDE_DIR} 
                                       ${AVCODEC_LIBRARY}
                                       ${AVUTIL_LIBRARY}
                                       ${AVFORMAT_LIBRARY}
                                       ${LIBAO_LIBRARY}
                                       ${FTTW_LIBRARY}
                                       )
