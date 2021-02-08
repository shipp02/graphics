#include "buffer.h"
#include "context.cpp"
#include "control.h"
#include "program.h"
#include "texture.h"
#include "utils.h"
#include "board.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <ostream>
#include <string>

std::shared_ptr<control> player_c = nullptr;

void key_call(GLFWwindow *window, int character, int /*b*/, int action, int /*d*/) {
    using namespace std;

    if (action != GLFW_PRESS) {
        return;
    }

    if (character == GLFW_KEY_Q) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    } else if (character == GLFW_KEY_UP) {
        /* cout<<"UP"<<endl; */
        player_c->move_ver(1.0f);
    } else if (character == GLFW_KEY_DOWN) {
        /* cout<<"DOWN"<<endl; */
        player_c->move_ver(-1.0f);
    } else if (character == GLFW_KEY_RIGHT) {
        /* cout<<"RIGHT"<<endl; */
        player_c->move_hor(1.0f);
    } else if (character == GLFW_KEY_LEFT) {
        /* cout<<"LEFT"<<endl; */
        player_c->move_hor(-1.0f);
    }
}

int SCR_WIDTH = 800;
int SCR_HEIGHT = 600;
using gl::point_type;
using std::vector;


void move_err(int x, std::string y) {
    std::cout << "error: " << x << std::endl;
    std::cout << y << std::endl;
}

int main() {

    // Init GLFW
    auto window = gl::mkWindowContextCurrent(SCR_WIDTH, SCR_HEIGHT);
    glfwSetKeyCallback(window, key_call);

    auto brd = createAndBindBoard();

    player_c = std::make_unique<control>(9, 0, 0, -9, brd.base, glm::vec3(1.2f, 0.0f, 0.0f),
                                         -glm::vec3(0.0f, -1.2f, 0.0f));
    player_c->on_error(move_err);

    gl::program player("shaders/model.1.vert", "shaders/model.1.frag");
    player.use();
    GLuint vao;
    gl::genAndBind(vao, glGenVertexArrays, glBindVertexArray);

    auto player_Pos = player.attribBindPoint(
            "Pos", vector<point_type>{point_type::X, point_type::Y, point_type::Z});
    gl::printErrors("before loop 2");

    auto player_fColor = player.attribBindPoint(
            "fColor",
            vector<point_type>{point_type::Red, point_type::Green, point_type::Blue});

    auto player_fTexCoords = player.attribBindPoint(
            "fTexCoords", vector<point_type>{point_type::U, point_type::V});

    auto b = std::make_shared<gl::buffer>(
            vertices::square,
            vector<gl::point_type>{
                    point_type::X,
                    point_type::Y,
                    point_type::Z,
                    point_type::Red,
                    point_type::Green,
                    point_type::Blue,
                    point_type::U,
                    point_type::V,
            })
            ->with_bind_point(player_Pos)
            ->with_bind_point(player_fColor)
            ->with_bind_point(player_fTexCoords);

    /* auto cfg  = gl::read_config("player.cfg"); */
    /* cout << cfg.far << " " << cfg.near << " " << cfg.fov << std::endl; */

    auto viewMatPos = player.matLocation("view");
    auto view =
            glm::lookAt(glm::vec3(0.0f, 0.0f, 8.0f), glm::vec3(0.0f, 0.0f, 0.0f),
                        glm::vec3(0.0f, 1.0f, 0.0f));
    glUniformMatrix4fv(viewMatPos, 1, GL_FALSE, glm::value_ptr(view));

    auto projMatPos = player.matLocation("projection");
    glm::mat4 proj =
            glm::perspective(glm::radians(75.0f), 800.0f / 600.0f, 0.1f, 10.0f);
    glUniformMatrix4fv(projMatPos, 1, GL_FALSE, glm::value_ptr(proj));

    auto modelMatPos = player.matLocation("model");
    glUniformMatrix4fv(modelMatPos, 1, GL_FALSE, glm::value_ptr(player_c->pos));
    gl::texture tex("models/8_Bit_Mario.png");

    gl::printErrors("before loop");
    gl::backgroundColor(0.807, 0.823, 0.909, 1.0);
    gl::printErrors("before function");
    drawBoard(brd);

    gl::printErrors("before loop.");
    player.use();
    glUniformMatrix4fv(modelMatPos, 1, GL_FALSE, glm::value_ptr(player_c->pos));
    glBindVertexArray(vao);

    gl::printErrors("before loop..");
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glfwSwapBuffers(window);
    glfwPollEvents();

    while (!glfwWindowShouldClose(window)) {
        gl::backgroundColor(0.807, 0.823, 0.909, 1.0);
        drawBoard(brd);
        player.use();
        glBindVertexArray(vao);
        glUniformMatrix4fv(modelMatPos, 1, GL_FALSE, glm::value_ptr(player_c->pos));
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    gl::printErrors("end");

    glfwDestroyWindow(window);
    glfwTerminate();
}
