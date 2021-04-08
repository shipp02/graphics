#include "uv.h"
#include <gl/context.h>

int main() {
    auto win = gl::mkWindowContextCurrent(800, 600);
    uv_run(uv_default_loop(), UV_RUN_DEFAULT);
}
