add_subdirectory(raw)

set(GL_LIB_SRC ${GL_LIB_SRC} bind_point.cpp  board.cpp 
    buffer.cpp  context.cpp control.cpp program.cpp 
    shader.cpp texture.cpp thread_pool.cpp 
    utils.cpp vao.cpp PARENT_SCOPE)

add_library(glpp ${GL_LIB_SRC} bind_point.cpp board.cpp 
    buffer.cpp context.cpp control.cpp program.cpp 
    shader.cpp texture.cpp thread_pool.cpp 
    utils.cpp vao.cpp )

# helper/uv/loop.cpp helper/uv/loop.h helper/raw/wrappers.cpp helper/raw/wrappers.h)

# bind_point.cpp bind_point.h board.cpp board.h buffer.cpp buffer.h context.cpp control.cpp control.h program.cpp program.h shader.cpp shader.h texture.cpp texture.h thread_pool.cpp thread_pool.h utils.cpp utils.h vao.cpp vao.h
