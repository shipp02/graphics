#ifndef OPENGL_WITH_CONAN_UV_LOOP_H
#define OPENGL_WITH_CONAN_UV_LOOP_H

#include <iostream>
#include <memory>
#include <uv.h>
#include<string>

namespace uv
{

template<typename T>
class pin {
public:
    pin(T pinned) : obj(new T(pinned)){
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

    pin(pin && other) {
        should_delete = other.should_delete;
        other.should_delete  = false;
        other.is_owner = false;
        is_owner =  true;
        obj = std::move(other.obj);
        other.obj = nullptr;
    }

    pin& operator= (pin && other) {
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
    std::function<void(T&, uv_timer_t*)> f;
    pin<T> init;
};

template<typename T>
void time_back(uv_timer_t * t) {
    auto back = static_cast<back_data<T>*>(t->data);
    back->f(*back->init, t);
}

class loop
{
    public:
    loop();
    ~loop();
    template<typename T>
    uv_timer_t* timer(uint64_t repeat, std::function<void(T&, uv_timer_t*)> func, std::unique_ptr<T> init) {
        auto timer = new uv_timer_t;
        auto b_data = new back_data<T> {
            .f = func,
            .init = pin<T>(std::move(init))
        };
        timer-> data = static_cast<void*>(b_data);
        uv_timer_init(t, timer);
        uv_timer_start(timer, time_back<T>, 0, repeat);
        return timer;
    }
    void run();
    private:
        uv_loop_t *t;
};

}; // namespace uv

#endif
