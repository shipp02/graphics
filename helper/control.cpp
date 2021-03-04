#include "control.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "glm/glm.hpp"
#include <functional>
#include <iostream>
#include <vector>

control::control(int _max_x, int _max_y, int _min_x, int _min_y,
                 glm::mat4 _zero, glm::vec3 _move_x, glm::vec3 _move_y)
    : max_x(_max_x), max_y(_max_y), min_x(_min_x), min_y(_min_y),
      move_x(_move_x), move_y(_move_y), zero(_zero), pos(_zero) {
    x = 0;
    y = 0;
    std::time(&t);
}

control::control()
    : max_x(0), max_y(0), min_x(0), min_y(0), move_x(glm::vec3(1.0f)),
      move_y(glm::vec3(1.0f)), zero(0) {}

control::control(const control &c)
    : max_x(c.max_x), max_y(c.max_y), min_x(c.min_x), min_y(c.min_y),
      zero(c.zero), move_x(c.move_x), move_y(c.move_y) {}

void control::set_zero(int _x, int _y) {
    x = _x;
    y = _y;
}

void control::on_error(std::function<void(int, std::string)> func) {
    err_func = std::move(func);
}
using std::cout;
using std::endl;
std::vector<control> control::move_ver(float d_y, int split) {
    if ((y + d_y > max_y) || (y + d_y < min_y)) {
        err_func(1, "moved_out_of_bounds");
        //        cout << "x: " << x << "y: " << y << endl;
        return std::vector<control>(0);
        /* throw moved_out_of_bounds(); */
    }
    std::vector<control> ctrl(split);
    auto d_y_per = d_y / split;
    const auto pos_x = glm::translate(zero, x * move_x);
    ////    This indexing is safe since we initialized
    ////     it to the size that we are going to index into it
    for (int i = 0; i < split; ++i) {
        auto n = *this;
        n.y += d_y_per * (i + 1);
        n.pos = glm::translate(pos_x, n.y * move_y);
    }
    //    auto n = std::make_shared<control>(*this);
    //    n->y += d_y;
    //    using std::cout;
    //    using std::endl;
    //
    //    cout << "x: " << x << "y: " << y << endl;
    //    n->pos = glm::translate(zero, n->y * move_y);
    //    n->pos = glm::translate(n->pos, n->x * move_x);
    return ctrl;
}

std::vector<control> control::move_hor(float d_x, int split) {
    if (x + d_x > max_x || x + d_x < min_x) {
        err_func(1, "moved_out_of_bounds");
        cout << "x: " << x << "y: " << y << endl;
        return std::vector<control>(0);
        /* throw moved_out_of_bounds(); */
    }
    using std::cout;
    using std::endl;
    std::vector<control> ctrl(split);
    auto d_x_per = d_x / split;
    const auto pos_y = glm::translate(zero, y * move_y);
    for (int i = 0; i < split; ++i) {
        auto n = *this;
        n.y += d_x_per * (i + 1);
        n.pos = glm::translate(pos_y, n.x * move_x);
    }
    //    auto n = std::make_shared<control>(*this);
    //    cout << "x: " << x << "y: " << y << endl;
    //    n->x += d_x;
    //    n->pos = glm::translate(zero, n->y * move_y);
    //    n->pos = glm::translate(n->pos, n->x * move_x);
    return ctrl;
}
