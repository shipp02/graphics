#ifndef OPENGL_WITH_CONAN_UV_LOOP_H
#define OPENGL_WITH_CONAN_UV_LOOP_H

#include "uv.h"
#include <iostream>
#include <memory>
#include <uv.h>
#include<string>
#include <vector>

namespace uv
{

template<typename T>
class pin {
public:
    explicit pin(T pinned) : obj(new T(pinned)){
        should_delete = false;
        is_owner =  true;
    }
    explicit pin(std::unique_ptr<T> pinned) : obj(new T(*pinned)){
        should_delete = false;
        is_owner =  true;
    }

    ~pin() {
        if((!should_delete) && is_owner) {
            return;
        } else if (is_owner){
        std::cout<<"Deleted pin" <<std::endl;
        delete obj;
        }
    }

    pin(const pin& other) {
        should_delete = false;
        is_owner = true;
        obj = other.obj;
    }

    pin& operator= (const pin& other) {
        should_delete = false;
        is_owner = false;
        obj = other.obj;
    }

    void close () {
        should_delete = true;
    }

    pin(pin && other)  noexcept {
        should_delete = other.should_delete;
        other.should_delete  = false;
        other.is_owner = false;
        is_owner =  true;
        obj = std::move(other.obj);
        other.obj = nullptr;
    }

    pin& operator= (pin && other)  noexcept {
        should_delete = other.should_delete;
        other.should_delete = false;
        other.is_owner = false;
        is_owner = true;
        obj = std::move(other.obj);
        other.obj = nullptr;
    }

    T& operator* () {
        return *obj;
    }


private:
    T* obj;
    bool should_delete;
    bool is_owner;

};

template<typename T>
struct back_data {
    // return true to stop the timer.
    std::function<bool(T&, uv_timer_t*)> f;
    pin<T> init;
    bool stop;
};

template<typename T>
void time_back(uv_timer_t * t) {
    auto back = static_cast<back_data<T>*>(t->data);
    auto stop = back->f(*back->init, t);
    if(stop) {
        uv_timer_stop(t);
    }
}


template<typename T>
class handle {
public:
    handle(uv_timer_t *t, pin<T> x) : data(std::move(x)) , h(t){
    }

    T& operator* () {
        return *data;
    }

    void stop() {
        std::cout<<"Stopped"<<std::endl;
        auto back = static_cast<back_data<T>*>(h->data);
        back->stop =  true;
        /* uv_timer_stop(h); */
        delete h;
    }

    uv_timer_t *h;

private:
    int times;
    pin<T> data;

};


class loop
{
    public:
    loop();
    ~loop();
    template<typename T>
    handle<T> timer(uint64_t repeat, std::function<bool(T&, uv_timer_t*)> func, std::unique_ptr<T> init) {
        auto timer = new uv_timer_t;
        auto b_data = new back_data<T> {
            .f = func,
            .init = pin<T>(std::move(init)),
            .stop = false
        };
        timer-> data = static_cast<void*>(b_data);
        uv_timer_init(t, timer);
        uv_timer_start(timer, time_back<T>, 0, repeat);
        return handle<T>(timer, b_data->init);
    }
    void run();
    void stop();
    private:
        uv_loop_t *t;
        uv_idle_t *idler;
        bool should_stop;
};

} // namespace uv

#endif
