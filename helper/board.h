//
// Created by Aashay shah on 7/2/2021.
//

#ifndef OPENGL_WITH_CONAN_BOARD_H
#define OPENGL_WITH_CONAN_BOARD_H


#include <memory>
#include <vector>
#include "glm/fwd.hpp"
#include "program.h"
#include "buffer.h"
#include "control.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

struct board {
    std::shared_ptr<gl::program> p;
    std::shared_ptr<gl::buffer> b;
    const glm::mat4 base;
    const glm::vec3 hTrans;
    const glm::vec3 vTrans;
    GLuint vao;
    GLint model_mat_pos;
  std::vector<glm::mat4> board_pos;
};

board createAndBindBoard();

void drawBoard(const board &brd);

std::vector<glm::mat4> make_grid(glm::mat4 base, glm::vec3 hTrans, glm::vec3 vTrans,  int x, int y);

class space_invaders {
public:
    std::shared_ptr<control> player;
    std::vector<control> aliens;
    
};

control move_side(int distance);
control move_vertical(int distance);
control move(glm::vec2 dir);


#endif //OPENGL_WITH_CONAN_BOARD_H
