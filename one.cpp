#include <stdio.h>
#include <iostream>
#include <math.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "buffer.cpp"
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

int main(){
    // -------------------------------- INIT ------------------------------- //

    // Init GLFW
    auto window = gl::mkWindowContextCurrent(800, 600);
    glfwSetKeyCallback(window, key_call);


    gl::program p1("shaders/model.1.vert","shaders/model.1.frag");
    p1.use();
    gl::printErrors("before loop 4");


    GLuint vao, vbo;
    gl::printErrors("before loop 3");
    gl::genAndBind(vao, glGenVertexArrays, glBindVertexArray);
    auto p_Pos = p1.attribBindPoint("Pos", vector<point_type>{
        point_type::X,
        point_type::Y,
        point_type::Z
    });
    gl::printErrors("before loop 2");
    auto p_fColor = p1.attribBindPoint("fColor", vector<point_type> {
        point_type::Red,
        point_type::Green,
        point_type::Blue
    });

    auto p_fTexCoords = p1.attribBindPoint("fTexCoords", vector<point_type> {
        point_type::U,
        point_type::V
    });

    auto b = std::make_shared<gl::buffer>(glGenBuffers, gl::arrayBufferBind, 
            vertices::cube, vector<gl::point_type> {
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
    cout<<"Not yet.."<<std::endl;

    auto modelMatPos = p1.matLocation("model");
    auto model = glm::mat4(1.0f);
//    model = glm::rotate(model, glm::radians(25.0f), glm::vec3(0.0f,1.0f,0.0f));

    auto viewMatPos = p1.matLocation("view");
    auto view = glm::lookAt(
        glm::vec3(0.0f, 0.0f, 3.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );
    glUniformMatrix4fv(viewMatPos, 1, GL_FALSE, glm::value_ptr(view));

    auto projMatPos = p1.matLocation("projection");
    glm::mat4 proj = glm::perspective(glm::radians(75.0f), 800.0f / 600.0f, 0.1f, 10.0f);
    glUniformMatrix4fv(projMatPos, 1, GL_FALSE, glm::value_ptr(proj));

    gl::texture("models/8_Bit_Mario.png");


    gl::printErrors("before loop");

    while(!glfwWindowShouldClose(window)){
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        p1.use();
        glBindVertexArray(vao);

        glDrawArrays(GL_TRIANGLES, 0, 36);
//        model = glm::rotate(model, glm::radians(10.0f), glm::vec3(0.0f,0.0f,1.0f));
        glUniformMatrix4fv(modelMatPos, 1, GL_FALSE, glm::value_ptr(model));

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    gl::printErrors("end");

    glfwDestroyWindow(window);
    glfwTerminate();
}
