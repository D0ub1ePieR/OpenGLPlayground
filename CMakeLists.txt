cmake_minimum_required(VERSION 3.16)
project(OpenGLPlayground)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(3rd/glfw)

include_directories(include)
include_directories(3rd/glfw/include)
include_directories(3rd/glad/include)
add_executable(main src/main.cpp)

# link_directories(3rd/glfw/src)
target_link_libraries(main glfw)
# target_link_libraries(main glad)