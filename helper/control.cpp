#include "control.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/glm.hpp"
#include <functional>
#include <iostream>


control::control(int _max_x, int _max_y, int _min_x, int _min_y, glm::mat4 _zero,
                 glm::vec3 _move_x, glm::vec3 _move_y)
        : max_x(_max_x), max_y(_max_y), min_x(_min_x), min_y(_min_y),
          move_x(_move_x), move_y(_move_y), zero(_zero), pos(_zero) {
    x = 0;
    y = 0;
    std::time(&t);
}

void control::set_zero(int _x, int _y) {
    x = _x;
    y = _y;
}

void control::on_error(std::function<void(int, std::string)> func) {
    err_func = std::move(func);
}
using std::cout;
using std::endl;
std::shared_ptr<control> control::move_ver(float d_y) {
    if ((y + d_y > max_y) || (y + d_y < min_y)) {
        err_func(1, "moved_out_of_bounds");
//        cout << "x: " << x << "y: " << y << endl;
        return shared_from_this();
        /* throw moved_out_of_bounds(); */
    }
    auto n = std::make_shared<control>(*this);
    n->y += d_y;
    using std::cout;
    using std::endl;

//    cout << "x: " << x << "y: " << y << endl;
    n->pos = glm::translate(zero, n->y * move_y);
    n->pos = glm::translate(n->pos, n->x * move_x);
    return n;
}

std::shared_ptr<control> control::move_hor(float d_x) {
    if (x + d_x > max_x || x + d_x < min_x) {
        err_func(1, "moved_out_of_bounds");
        cout << "x: " << x << "y: " << y << endl;
        return shared_from_this();
        /* throw moved_out_of_bounds(); */
    }
    using std::cout;
    using std::endl;
    auto n = std::make_shared<control>(*this);
//    cout << "x: " << x << "y: " << y << endl;
    n->x += d_x;
    n->pos = glm::translate(zero, n->y * move_y);
    n->pos = glm::translate(n->pos, n->x * move_x);
    return n;
}

