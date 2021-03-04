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
} // namespace uv