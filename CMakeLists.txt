cmake_minimum_required(VERSION 3.16)
project(penguin)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)    
add_subdirectory(lib/glfw)
add_subdirectory(lib/glm)

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
src/shader/lightManager.cpp
)

target_include_directories(penguin PUBLIC 
src
lib
shader
lib/glfw/include
)

target_link_libraries(penguin PUBLIC glfw OpenGL::GL)