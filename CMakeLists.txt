cmake_minimum_required(VERSION 3.16)
project(OpenGLPlayground)

set(CMAKE_CXX_STANDARD 20)

# glad
add_library(glad 3rd/glad/src/glad.c)
target_include_directories(glad PUBLIC 3rd/glad/include)

# glfw
add_subdirectory(3rd/glfw)

include_directories(include)
include_directories(3rd/glfw/include)
add_executable(main src/main.cpp)
add_executable(EBO_demo src/EBO_demo.cpp)
target_link_libraries(main glfw glad)
target_link_libraries(EBO_demo glfw glad)
