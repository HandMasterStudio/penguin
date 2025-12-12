cmake_minimum_required(VERSION 4.0)
project(penguin)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)    

include_directories(src lib)

add_executable(penguin 
src/main.cpp
src/glad.c
src/window/windowManager.cpp
src/loader/loader.cpp
src/loader/stb_image.cpp
src/core/renderer.cpp
src/shader/shaderCompiler.cpp
src/player/camera.cpp
src/player/player.cpp
)

target_link_libraries(penguin glfw OpenGL::GL)