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
}

void control::set_zero(int _x, int _y) {
    x = _x;
    y = _y;
}

void control::on_error(std::function<void(int, std::string)> func) {
    err_func = std::move(func);
}

void control::move_ver(float d_y) {
    if ((y + d_y > max_y) || (y + d_y < min_y)) {
        err_func(1, "moved_out_of_bounds");
        return;
        /* throw moved_out_of_bounds(); */
    }
    y += d_y;
    using std::cout;
    using std::endl;

    cout << "x: " << x << "y: " << y << endl;
    pos = glm::translate(zero, y * move_y);
    pos = glm::translate(pos, x * move_x);
}

void control::move_hor(float d_x) {
    if (x + d_x > max_x || x + d_x < min_x) {
        err_func(1, "moved_out_of_bounds");
        return;
        /* throw moved_out_of_bounds(); */
    }
    using std::cout;
    using std::endl;

    cout << "x: " << x << "y: " << y << endl;
    x += d_x;
    pos = glm::translate(zero, y * move_y);
    pos = glm::translate(pos, x * move_x);
}

