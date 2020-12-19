#include <stdio.h>
#include <iostream>
#include <math.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <stdio.h>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "buffer.cpp"
#include "glm/detail/qualifier.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "shader.cpp"
// #include "buffer.cpp"
#include "context.cpp"

// Too may errors not building

void key_call(GLFWwindow* window, int character, int b, int c, int d){

    glfwSetWindowShouldClose(window, GLFW_TRUE);

}
int SCR_WIDTH = 800;
int SCR_HEIGHT = 600;
using std::vector;
using gl::point_type;

#define FLOAT_SIZE(x) x*sizeof(float)

struct board {
    std::shared_ptr<gl::program> p;
    std::shared_ptr<gl::buffer> b;
    vector<gl::bind_point> binds;
    const glm::mat4 base;
    const glm::vec3 hTrans;
    const glm::vec3 vTrans;
    GLuint vao;
    GLint model_mat_pos;
};

board createAndBindBoard() {
    auto p1 = std::make_shared<gl::program>("shaders/model.1.vert", "shaders/board.1.frag");
    p1->use();
    gl::printErrors("before loop 4");
    GLuint vao;
    gl::printErrors("before loop 3");
    gl::genAndBind(vao, glGenVertexArrays, glBindVertexArray);
    auto p_Pos = p1->attribBindPoint("Pos", vector<point_type>{
        point_type::X,
        point_type::Y,
        point_type::Z
    });
    gl::printErrors("before loop 2");
    auto p_fColor = p1->attribBindPoint("fColor", vector<point_type> {
        point_type::Red,
        point_type::Green,
        point_type::Blue
    });

    auto p_fTexCoords = p1->attribBindPoint("fTexCoords", vector<point_type> {
        point_type::U,
        point_type::V
    });

    auto b = std::make_shared<gl::buffer>(glGenBuffers, gl::arrayBufferBind, 
            vertices::square, vector<gl::point_type> {
        point_type::X,
        point_type::Y,
        point_type::Z,
        point_type::Red,
        point_type::Green,
        point_type::Blue,
        point_type::U,
        point_type::V,
    })
    ->with_bind_point(p_Pos)
    ->with_bind_point(p_fColor)
    ->with_bind_point(p_fTexCoords);
    /* cout<<"Not yet.."<<std::endl; */
    const auto baseModel = glm::translate(glm::mat4(1.0f), glm::vec3(-8.00f, 5.0f, 0.0f));
    auto viewMatPos = p1->matLocation("view");
    auto view = glm::lookAt(
        glm::vec3(0.0f, 0.0f, 8.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );
    glUniformMatrix4fv(viewMatPos, 1, GL_FALSE, glm::value_ptr(view));

    auto projMatPos = p1->matLocation("projection");
    glm::mat4 proj = glm::perspective(glm::radians(75.0f), 800.0f / 600.0f, 0.1f, 10.0f);
    glUniformMatrix4fv(projMatPos, 1, GL_FALSE, glm::value_ptr(proj));

    return board {
        p1,
        b,
        vector<gl::bind_point> {
            p_Pos,
            p_fColor,
            p_fTexCoords
        },
        baseModel,
        glm::vec3(1.2f, 0.0f, 0.0f),
        glm::vec3(0.0f, -1.2f, 0.0f),
        vao,
        p1->matLocation("model")
    };

}

void drawBoard(board brd) {
    brd.p->use();
    gl::printErrors("In function..");
    glBindVertexArray(brd.vao);
    gl::printErrors("In function");

    auto vModel = brd.base;
    auto model = brd.base;
    for (int j = 0; j<10; j++) {
    
        for(int i = 0;i<9;i++) {
            glDrawArrays(GL_TRIANGLES, 0, 6);
            model = glm::translate(model, brd.hTrans);
            glUniformMatrix4fv(brd.model_mat_pos, 1, GL_FALSE, glm::value_ptr(model));
        }
        model = glm::translate(vModel, brd.vTrans);
        vModel =  model;
    }
    model = brd.base;
    vModel = brd.base;
}

int main(){
    // -------------------------------- INIT ------------------------------- //

    // Init GLFW
    auto window = gl::mkWindowContextCurrent(800, 600);
    glfwSetKeyCallback(window, key_call);

    auto brd = createAndBindBoard();


    gl::program player("shaders/model.1.vert", "shaders/model.1.frag");
    player.use();
    GLuint vao;
    gl::genAndBind(vao, glGenVertexArrays, glBindVertexArray);
    auto player_Pos = player.attribBindPoint("Pos", vector<point_type>{
        point_type::X,
        point_type::Y,
        point_type::Z
    });
    gl::printErrors("before loop 2");
    auto player_fColor = player.attribBindPoint("fColor", vector<point_type> {
        point_type::Red,
        point_type::Green,
        point_type::Blue
    });
    auto player_fTexCoords = player.attribBindPoint("fTexCoords", vector<point_type> {
        point_type::U,
        point_type::V
    });
    auto b = std::make_shared<gl::buffer>(glGenBuffers, gl::arrayBufferBind, 
            vertices::square, vector<gl::point_type> {
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

    auto viewMatPos = player.matLocation("view");
    auto view = glm::lookAt(
        glm::vec3(0.0f, 0.0f, 8.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );
    glUniformMatrix4fv(viewMatPos, 1, GL_FALSE, glm::value_ptr(view));

    auto projMatPos = player.matLocation("projection");
    glm::mat4 proj = glm::perspective(glm::radians(75.0f), 800.0f / 600.0f, 0.1f, 10.0f);
    glUniformMatrix4fv(projMatPos, 1, GL_FALSE, glm::value_ptr(proj));

    auto modelMatPos = player.matLocation("model");
    auto m = glm::mat4(1.0f);
    glUniformMatrix4fv(modelMatPos, 1, GL_FALSE, glm::value_ptr(m));
    gl::texture("models/8_Bit_Mario.png");


    gl::printErrors("before loop");
    gl::backgroundColor(0.807, 0.823, 0.909, 1.0);
    gl::printErrors("before function");
    drawBoard(brd);

    gl::printErrors("before loop.");
    player.use();
    glBindVertexArray(vao);

    gl::printErrors("before loop..");
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glfwSwapBuffers(window);
    glfwPollEvents();

    while(!glfwWindowShouldClose(window)){
        gl::backgroundColor(0.807, 0.823, 0.909, 1.0);
        drawBoard(brd);
        player.use();
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    gl::printErrors("end");

    glfwDestroyWindow(window);
    glfwTerminate();
}
