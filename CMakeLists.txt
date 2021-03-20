cmake_minimum_required(VERSION 3.15.0)
project(opengl-with-conan)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)
set(CMAKE_CXX_COMPILER "/usr/local/opt/llvm/bin/clang++")

add_definitions("-std=c++17")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories(include)
include_directories(/usr/local/include)
link_directories(/usr/local/lib)


add_subdirectory(src)

# set(SRC one.cpp ${SRC} ${LIB_SRC} )
# file(COPY models DESTINATION ${CMAKE_BINARY_DIR})
# add_executable(conan1 ${SRC})
# target_link_libraries(conan1 ${CONAN_LIBS})

add_executable(lighting two.cpp )
target_link_libraries(lighting ${CONAN_LIBS})
target_link_libraries(lighting glpp)
target_link_libraries(lighting uvpp)

