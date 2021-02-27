
#include "bind_point.h"
#include "buffer.h"
#include "context.cpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/scalar_constants.hpp"
#include "glm/fwd.hpp"
#include "glm/trigonometric.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "program.h"
#include "utils.h"
#include <memory>
#include "GLFW/glfw3.h"

int main() {
    auto window = gl::mkWindowContextCurrent(800, 600);
    auto box = std::make_shared<gl::program>("shaders/lighting_ch1.vert", "shaders/lighting_ch1.frag");
    gl::printErrors("box program");
    box->use();
    GLuint vao;
    gl::genAndBind(vao, glGenVertexArrays, glBindVertexArray);
    auto buf_box = std::make_shared<gl::buffer>(vertices::normal_cube, std::vector<gl::point_type> {
	gl::X,
	  gl::Y,
	  gl::Z,
	  gl::Red,
	  gl::Green,
	  gl::Blue})
        ->with_bind_point(box, "Pos", gl::XYZ)
      ->with_bind_point(box, "fNormal", gl::RGB);
    gl::printErrors("box buffers");

    glm::mat4 base(1.0f);
    auto rotate = glm::rotate(base, 3.14f/2, glm::vec3(0.0f, 1.0f, 0.0f));
    auto viewMatPos = box->matLocation("view");
    auto view =
            glm::lookAt(glm::vec3(0.0f, 0.0f, 8.0f), glm::vec3(0.0f, 0.0f, 0.0f),
                        glm::vec3(0.0f, 1.0f, 0.0f));
    glUniformMatrix4fv(viewMatPos, 1, GL_FALSE, glm::value_ptr(view));
    gl::printErrors("box matrixes");

    auto projMatPos = box->matLocation("projection");
    glm::mat4 proj =
            glm::perspective(glm::radians(75.0f), 800/ (float) 600, 0.1f, 10.0f);
    glUniformMatrix4fv(projMatPos, 1, GL_FALSE, glm::value_ptr(proj));

    auto modelMatPos = box->matLocation("model");
    glUniformMatrix4fv(modelMatPos, 1, GL_FALSE, glm::value_ptr(rotate));
    gl::printErrors("box matrixes.");

    auto lightColor = glGetUniformLocation(box->get(), "lightColor");
    glUniform3f(lightColor, 1.0f, 1.0, 1.0f);

    auto Color  = glGetUniformLocation(box->get(), "Color");
    glUniform3f(Color, 1.0f, 0.7f, 0.7f);

    // Lights.
    auto light = std::make_shared<gl::program>("shaders/lights.vert", "shaders/lights.frag");
    gl::printErrors("box program");

    light->use();
    GLuint light_vao;
    gl::genAndBind(light_vao, glGenVertexArrays, glBindVertexArray);
    auto buf_light = gl::StandardBuffer(vertices::cube)
      ->with_bind_point(box, "Pos", gl::XYZ);
    gl::printErrors("box buffers");

    glm::mat4 light_base(1.0f);
    light_base  =  glm::translate(light_base, glm::vec3(0.5f, 0.0f, 0.0f));
    auto rotate_light =
        glm::rotate(base, 3.14f / 2, glm::vec3(1.0f, 0.0f, 1.0f));
    rotate_light = glm::translate(rotate_light, glm::vec3(1.0f, 0.0f, 1.5f));
    auto light_viewMatPos = light->matLocation("view");
    auto light_view =
            glm::lookAt(glm::vec3(0.0f, 0.0f, 8.0f), glm::vec3(0.0f, 0.0f, 0.0f),
                        glm::vec3(0.0f, 1.0f, 0.0f));
    glUniformMatrix4fv(light_viewMatPos, 1, GL_FALSE, glm::value_ptr(view));
    gl::printErrors("box matrixes");

    auto light_projMatPos = light->matLocation("projection");
    glm::mat4 light_proj =
            glm::perspective(glm::radians(75.0f), 800/ (float) 600, 0.1f, 10.0f);
    glUniformMatrix4fv(light_projMatPos, 1, GL_FALSE, glm::value_ptr(light_proj));

    auto light_modelMatPos = light->matLocation("model");
    glUniformMatrix4fv(light_modelMatPos, 1, GL_FALSE, glm::value_ptr(rotate_light));
    gl::printErrors("box matrixes.");

    auto last = glfwGetTime();
    while(!glfwWindowShouldClose(window)) {
        gl::backgroundColor(0.807, 0.823, 0.909, 1.0);
	
	box->use();
	glBindVertexArray(vao);
        if(glfwGetTime() - last > 1) {
            last = glfwGetTime();
            rotate = glm::rotate(rotate, glm::radians(15.0f), glm::vec3(0.0f, 0.0f, 1.0f));

        }
	glUniformMatrix4fv(modelMatPos, 1, GL_FALSE, glm::value_ptr(rotate));
	glUniform3f(lightColor, 1.0f, 0.5f, 0.5f);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        light->use();
	glBindVertexArray(light_vao);
    glUniformMatrix4fv(light_modelMatPos, 1, GL_FALSE, glm::value_ptr(rotate_light));
	glDrawArrays(GL_TRIANGLES, 0, 36);
	
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}