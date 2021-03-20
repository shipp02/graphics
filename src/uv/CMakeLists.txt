set(UV_LIB_SRC loop.cpp PARENT_SCOPE)

add_library(uvpp loop.cpp )
target_link_libraries(uvpp uv)

