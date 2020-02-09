cmake_minimum_required(VERSION 3.0)
project(dodecahedron)

file(GLOB SOURCES *.cpp)
add_executable(dodecahedron ${SOURCES})
target_link_libraries(dodecahedron pthread)
