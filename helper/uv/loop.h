#ifndef OPENGL_WITH_CONAN_UV_LOOP_H
#define OPENGL_WITH_CONAN_UV_LOOP_H

#include <uv.h>
#include<string>

namespace uv
{
template<typename T>
struct back_data {
    std::function<void(T*, uv_timer_t*)> f;
    T* init;
};

template<typename T>
void time_back(uv_timer_t * t) {
    auto back = static_cast<back_data<T>*>(t->data);
    back->f(back->init, t);
}

class loop
{
    public:
    loop();
    ~loop();
    template<typename T>
    uv_timer_t* timer(uint64_t repeat, std::function<void(T*, uv_timer_t*)> func, T* init) {
        auto timer = new uv_timer_t;
        auto b_data = new back_data<T> {
            .f = func,
            .init = init
        };
        timer-> data = static_cast<void*>(b_data);
        uv_timer_init(t, timer);
        uv_timer_start(timer, time_back<T>, 0, repeat);
        return timer;
    }
    private:
        uv_loop_t *t;
};

}; // namespace uv

#endif
