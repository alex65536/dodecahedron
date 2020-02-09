cmake_minimum_required(VERSION 3.0)
project(dodecahedron)

include(CheckLanguage)

file(GLOB SOURCES *.cpp)

check_language(RC)
if(CMAKE_RC_COMPILER)
    list(APPEND SOURCES logo.rc)
endif()

add_executable(dodecahedron ${SOURCES})
target_link_libraries(dodecahedron pthread)
