//
// Created by Aashay shah on 27/12/2020.
//

#ifndef OPENGL_WITH_CONAN_CONTROL_H
#define OPENGL_WITH_CONAN_CONTROL_H

#include <glm/glm.hpp>
#include <functional>
#include <string>
#include <memory>

class control : public std::enable_shared_from_this<control> {
public:
    control(int _max_x, int _max_y, int _min_x, int _min_y, glm::mat4 _zero,
            glm::vec3 _move_x, glm::vec3 _move_y);

    control();

    control(const control &c);

    void set_zero(int _x, int _y);

    void on_error(std::function<void(int, std::string)> func);

    std::vector<control> move_ver(float d_y, int split = 1);

    std::vector<control> move_hor(float d_x, int split = 1);

    glm::mat4 pos;
private:
    float x, y;
    const int max_x, min_x, max_y, min_y;
    const glm::vec3 move_x, move_y;
    const glm::mat4 zero;
    std::function<void(int, std::string)> err_func;
    std::time_t t;
};


#endif //OPENGL_WITH_CONAN_CONTROL_H
