cmake_minimum_required(VERSION 3.15.0)
project(opengl-with-conan)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)
set(CMAKE_CXX_COMPILER "/usr/local/opt/llvm/bin/clang++")

add_definitions("-std=c++17")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(LIB_SRC helper/program.cpp helper/program.h helper/shader.h helper/shader.cpp helper/buffer.h helper/buffer.cpp helper/bind_point.cpp helper/bind_point.h helper/texture.cpp helper/texture.h helper/utils.h helper/utils.cpp
        helper/control.cpp helper/control.h helper/board.cpp helper/board.h helper/thread_pool.cpp helper/thread_pool.h helper/uv/loop.cpp helper/uv/loop.h)
include_directories(helper)
include_directories(/usr/local/include)
link_directories(/usr/local/lib)
set(SRC one.cpp ${SRC} ${LIB_SRC})
file(COPY models DESTINATION ${CMAKE_BINARY_DIR})
add_executable(conan1 ${SRC})
target_link_libraries(conan1 ${CONAN_LIBS})

add_executable(lighting ${LIB_SRC} two.cpp)
target_link_libraries(lighting ${CONAN_LIBS})
target_link_libraries(lighting uv)
