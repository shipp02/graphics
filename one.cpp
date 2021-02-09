#include "bind_point.h"
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

struct _key_state {
    int speed;
    int key;
  int max_speed = 5;
};

static auto key_state = _key_state{};

void key_call(GLFWwindow *window, int character, int /*b*/, int action, int /*d*/) {
    using namespace std;

//    if (action != GLFW_PRESS) {
//        return;
//    }
    if(action == GLFW_RELEASE) {
      key_state.key = -1;
      key_state.speed = 0;
    } else if (action == GLFW_PRESS) {
      key_state.speed = 1;
        key_state.key = character;
    } else if (action == GLFW_REPEAT && key_state.speed <= key_state.max_speed) {
      key_state.speed++;
    }
#define SPEED(state) state.speed * 1.0f

    if (character == GLFW_KEY_Q) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    } else if (character == GLFW_KEY_UP) {
        /* cout<<"UP"<<endl; */
      player_c->move_ver(SPEED(key_state));
    } else if (character == GLFW_KEY_DOWN) {
        /* cout<<"DOWN"<<endl; */
      player_c->move_ver(-SPEED(key_state));
    } else if (character == GLFW_KEY_RIGHT) {
        /* cout<<"RIGHT"<<endl; */
      player_c->move_hor(SPEED(key_state));
    } else if (character == GLFW_KEY_LEFT) {
        /* cout<<"LEFT"<<endl; */
      player_c->move_hor(-SPEED(key_state));
    }
}

const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 600;


void move_err(int x, std::string y) {
    std::cout << "error: " << x << std::endl;
    std::cout << y << std::endl;
}

int main() {

    // Init GLFW
    auto window = gl::mkWindowContextCurrent(SCR_WIDTH, SCR_HEIGHT);
    glfwSetKeyCallback(window, key_call);

    auto brd = createAndBindBoard();
    // To edge for x: -8.2,8.2
    // To edge for y: -6,6
    auto player_base = glm::translate(glm::mat4(1.0f), glm::vec3(8.20f, -4.0f, 0.0f));

    player_c = std::make_unique<control>(9, 0, -136, 0, player_base,
                                         glm::vec3(0.12f, 0.0f, 0.0f),
                                         -glm::vec3(0.0f, -0.12f, 0.0f));
    player_c->on_error(move_err);

    gl::program::ptr player = std::make_shared<gl::program>("shaders/model.1.vert", "shaders/model.1.frag");
    player->use();
    GLuint vao;
    gl::genAndBind(vao, glGenVertexArrays, glBindVertexArray);

    auto b = gl::StandardBuffer(vertices::square)
            ->with_bind_point(player, "Pos", gl::XYZ)
            ->with_bind_point(player, "fColor", gl::RGB)
            ->with_bind_point(player, "fTexCoords", gl::UV);


    auto viewMatPos = player->matLocation("view");
    auto view =
            glm::lookAt(glm::vec3(0.0f, 0.0f, 8.0f), glm::vec3(0.0f, 0.0f, 0.0f),
                        glm::vec3(0.0f, 1.0f, 0.0f));
    glUniformMatrix4fv(viewMatPos, 1, GL_FALSE, glm::value_ptr(view));

    auto projMatPos = player->matLocation("projection");
    glm::mat4 proj =
            glm::perspective(glm::radians(75.0f), SCR_WIDTH / (float) SCR_HEIGHT, 0.1f, 10.0f);
    glUniformMatrix4fv(projMatPos, 1, GL_FALSE, glm::value_ptr(proj));

    auto modelMatPos = player->matLocation("model");
    glUniformMatrix4fv(modelMatPos, 1, GL_FALSE, glm::value_ptr(player_c->pos));
    gl::texture tex("models/8_Bit_Mario.png");

    gl::backgroundColor(0.807, 0.823, 0.909, 1.0);
    drawBoard(brd);

    gl::printErrors("before loop.");
    player->use();
    glUniformMatrix4fv(modelMatPos, 1, GL_FALSE, glm::value_ptr(player_c->pos));
    glBindVertexArray(vao);

    gl::printErrors("before loop..");
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glfwSwapBuffers(window);
    glfwPollEvents();

    while (!glfwWindowShouldClose(window)) {
        gl::backgroundColor(0.807, 0.823, 0.909, 1.0);
        drawBoard(brd);
        player->use();
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
