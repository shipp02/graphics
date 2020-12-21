#ifndef HELPER_CONTROL
#define HELPER_CONTROL
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "glm/glm.hpp"


class  control {
public:
    glm::mat4 pos;
    class moved_out_of_bounds{};

    control(int _max_x, int _max_y, int _min_x, int _min_y, glm::mat4 _zero, glm::vec3 _move_x, glm::vec3 _move_y) :
        max_x(_max_x), max_y(_max_y), min_x(_min_x), min_y(_min_y), move_x(_move_x), move_y(_move_x), zero(_zero)
    {
        x = 0;
        y = 0;
    }
    void move_ver(float d_y) {
        if((y+d_y > max_y) || (y+d_y < min_y)){
            throw moved_out_of_bounds();
        }
        y += d_y;
        pos = glm::translate(zero, y*move_y);
        pos = glm::translate(pos, x*move_x);
    }

    void move_hor(float d_x) {
        if((x+d_x > max_x) || (x+d_x < min_x)){
            throw moved_out_of_bounds();
        }
        x += d_x;
        pos = glm::translate(zero, y*move_y);
        pos = glm::translate(pos, x*move_x);
    }
private:
    float x,y;
    const int max_x, min_x,max_y, min_y;
    const glm::vec3 move_x, move_y;
    const glm::mat4 zero;

};

#endif
