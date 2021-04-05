#include "uv/loop.h"
#include "glm/fwd.hpp"
#include "uv.h"
#include <functional>
#include <memory>
#include <stdint.h>
#include <sys/types.h>
#include <thread>

namespace uv
{
loop::loop()
{
    t = new uv_loop_t;
    idler = new uv_idle_t;
    should_stop = false;
    uv_loop_init(t);
    uv_idle_init(t, idler);
    idler->data = static_cast<void*>(&should_stop);
    uv_idle_start(idler, [](uv_idle_t *cb){
        auto should_stop = static_cast<bool*>(cb->data);
        if(*should_stop) {
            uv_stop(cb->loop);
        }
    });
}

loop::~loop()
{
    should_stop = true;
    uv_loop_close(t);
    delete t;
}
void loop::run() {
    uv_run(t, UV_RUN_DEFAULT);
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(300ms);
    uv_stop(t);
}

void loop::stop() {
    std::cout<<"Loop stopped"<<std::endl;
    uv_stop(t);
}


template class handle<int>;
template class handle<uint>;
/* template class handle<glm::mat4>; */
/* template class handle<glm::vec3>; */
template class handle<std::string>;
template handle<int> loop::timer<int>(uint64_t, std::function<void(int&, uv_timer_t*)>, std::unique_ptr<int>);
template handle<std::string> loop::timer<std::string>(uint64_t, std::function<void(std::string&, uv_timer_t*)>, std::unique_ptr<std::string>);
} // namespace uv
