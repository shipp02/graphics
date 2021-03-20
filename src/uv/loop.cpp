#include "uv/loop.h"

namespace uv
{
loop::loop()
{
    t = new uv_loop_t;
    uv_loop_init(t);
}
loop::~loop()
{
    uv_loop_close(t);
    delete t;
}
void loop::run() {
    uv_run(t, UV_RUN_DEFAULT);
}
} // namespace uv
