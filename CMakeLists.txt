cmake_minimum_required(VERSION 3.21)
project(VoxEngine)

set(OpenGlLinkers -lglut -lGLU -lGL)
set(CMAKE_CXX_STANDARD 20)

add_executable(VoxEngine)

target_link_libraries(VoxEngine ${OpenGlLinkers})