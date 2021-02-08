//
// Created by Aashay shah on 7/2/2021.
//

#include "board.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "glm/common.hpp"
#include "glm/vec2.hpp"
#include "glm/vec4.hpp"
#include "utils.h"

using std::vector;


board createAndBindBoard() {
    auto p1 = std::make_shared<gl::program>("shaders/model.1.vert",
                                            "shaders/board.1.frag");
    p1->use();
    gl::printErrors("before loop 4");
    GLuint vao;
    gl::printErrors("before loop 3");
    gl::genAndBind(vao, glGenVertexArrays, glBindVertexArray);

    auto p_Pos = p1->attribBindPoint(
            "Pos", vector < gl::point_type > {gl::point_type::X, gl::point_type::Y, gl::point_type::Z});

    gl::printErrors("before loop 2");

    auto p_fColor = p1->attribBindPoint(
            "fColor",
            vector < gl::point_type > {gl::point_type::Red, gl::point_type::Green, gl::point_type::Blue});

    auto p_fTexCoords = p1->attribBindPoint(
            "fTexCoords", vector < gl::point_type > {gl::point_type::U, gl::point_type::V});

    auto b = std::make_shared<gl::buffer>(
            vertices::square,
            vector < gl::point_type > {
                    gl::point_type::X,
                    gl::point_type::Y,
                    gl::point_type::Z,
                    gl::point_type::Red,
                    gl::point_type::Green,
                    gl::point_type::Blue,
                    gl::point_type::U,
                    gl::point_type::V,
            })
            ->with_bind_point(p_Pos)
            ->with_bind_point(p_fColor)
            ->with_bind_point(p_fTexCoords);
    /* cout<<"Not yet.."<<std::endl; */
    const auto baseModel =
            glm::translate(glm::mat4(1.0f), glm::vec3(-8.00f, 5.0f, 0.0f));
    auto viewMatPos = p1->matLocation("view");
    auto view =
            glm::lookAt(glm::vec3(0.0f, 0.0f, 8.0f), glm::vec3(0.0f, 0.0f, 0.0f),
                        glm::vec3(0.0f, 1.0f, 0.0f));
    glUniformMatrix4fv(viewMatPos, 1, GL_FALSE, glm::value_ptr(view));

    auto projMatPos = p1->matLocation("projection");
    glm::mat4 proj =
            glm::perspective(glm::radians(75.0f), 800.0f / 600.0f, 0.1f, 10.0f);
    glUniformMatrix4fv(projMatPos, 1, GL_FALSE, glm::value_ptr(proj));

    const auto brd = make_grid(baseModel, glm::vec3(1.2f, 0.0f, 0.0f),
				glm::vec3(0.0f, -1.2f, 0.0f), 10, 1);

    return board{p1,
                 b,
                 baseModel,
                 glm::vec3(1.2f, 0.0f, 0.0f),
                 glm::vec3(0.0f, -1.2f, 0.0f),
                 vao,
                 p1->matLocation("model"),
    brd};
}

std::vector<glm::mat4> make_board(glm::mat4 base, glm::vec3 hTrans, glm::vec3 vTrans, int x, int y) {
  std::vector<glm::mat4> pos(x*y);
  for (float i  = 0;i<y;i++){
    for(float j = 0; j<x;j++){
      pos[i*x+j] =  glm::translate(base, hTrans* j + vTrans*i);
    }
  }
  return pos;
}

void drawBoard(const board &brd) {
    brd.p->use();
    gl::printErrors("In function..");
    glBindVertexArray(brd.vao);
    gl::printErrors("In function");

    for (auto it = brd.board_pos.begin(); it != brd.board_pos.end(); ++it){
      glDrawArrays(GL_TRIANGLES, 0, 6);
      glUniformMatrix4fv(brd.model_mat_pos, 1, GL_FALSE, glm::value_ptr(*it));
    }
}

