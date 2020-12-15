cmake_minimum_required(VERSION 3.15.0)
project(opengl-with-conan)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)
set(CMAKE_CXX_COMPILER "/usr/local/Cellar/llvm/10.0.1_2/bin/clang++")

add_definitions("-std=c++11")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories(helper)
set(SRC one.cpp ${SRC})
file(COPY models DESTINATION ${CMAKE_BINARY_DIR})
add_executable(conan1 ${SRC})
target_link_libraries(conan1 ${CONAN_LIBS})

