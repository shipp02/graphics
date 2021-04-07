#include "uv.h"
#include <gl/context.h>
#include <iostream>

int main() {
    auto win = gl::mkWindowContextCurrent(800, 600);
    std::cout<<"Window Created\n";
    uv_run(uv_default_loop(), UV_RUN_DEFAULT);
}
