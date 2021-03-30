#include "gl/bind_point.h"
#include "gl/buffer.h"
#include "gl/context.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/trigonometric.hpp"
#include "gl/program.h"
#include "gl/texture.h"
#include "gl/utils.h"
#include "uv/loop.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <memory>
#include "GLFW/glfw3.h"

void err_handle(int num, std::string str) {
    std::cout << "Error code:" << num << std::endl;
    std::cout << str << std::endl;
}

void SetUniformVec3(gl::program::ptr p, std::string name, glm::vec3 vector) {
    glUniform3fv(p->matLocation(name), 1, glm::value_ptr(vector));
}
struct material {
    glm::vec3 ambientVec;
    glm::vec3 diffuseVec;
    glm::vec3 specularVec;
    float shiny;
    int ambient;
    int diffuse;
    int specular;
    int shinyP;
};

void setFloat(uint prog, std::string s, float f) {
    glUniform1f(glGetUniformLocation(prog, s.c_str()), f);
}

material make_material(std::shared_ptr<gl::program> program) {
    return material{.ambientVec = glm::vec3(1.0f, 0.5f, 0.31f),
                    .diffuseVec = glm::vec3(1.0f, 0.5f, 0.31f),
                    .specularVec = glm::vec3(0.5f, 0.5f, 0.5f),
                    .shiny = 32.0f,
                    /* .ambient = program->matLocation("material.ambient"), */
                    .diffuse = program->matLocation("material.diffuse"),
                    .specular = program->matLocation("material.specular"),
                    .shinyP = program->matLocation("material.shiny")};
}

int main() {
    auto window = gl::mkWindowContextCurrent(800, 600);
    auto box = std::make_shared<gl::program>("shaders/lighting_ch1.vert",
                                             "shaders/lighting_ch1.frag");
    gl::printErrors("box program");
    box->use();
    std::cout<<"Program created"<<std::endl;

    GLuint vao;
    gl::genAndBind(vao, glGenVertexArrays, glBindVertexArray);
    auto buf_box = std::make_shared<gl::buffer>(
                       vertices::textured_cube,
                       std::vector<gl::point_type>{gl::X, gl::Y, gl::Z, 
                                                   gl::Red, gl::Green, gl::Blue,
                                                   gl::U, gl::V})
                       ->with_bind_point(box, "Pos", gl::XYZ)
                       ->with_bind_point(box, "fNormal", gl::RGB)
                       ->with_bind_point(box, "fTexCoords", gl::UV);
    std::cout<<"Here"<<std::endl;
    gl::printErrors("box buffers");

    glm::mat4 base(1.0f);
    base = glm::translate(base, glm::vec3(0.0f, -0.7f, 2.5f));
    auto rotate =
        glm::rotate(base, glm::radians(45.0f), glm::vec3(1.0f, 0.1f, 0.0f));    
    auto modelMatPos = box->matLocation("model");
    glUniformMatrix4fv(modelMatPos, 1, GL_FALSE, glm::value_ptr(rotate));
    gl::printErrors("box matrixes.");
    

    auto viewMatPos = box->matLocation("view");
    auto view =
        glm::lookAt(glm::vec3(0.0f, 0.0f, 4.0f), glm::vec3(0.0f, 0.0f, 0.0f),
                    glm::vec3(0.0f, 1.0f, 0.0f));
    glUniformMatrix4fv(viewMatPos, 1, GL_FALSE, glm::value_ptr(view));
    gl::printErrors("box matrixes");

    auto projMatPos = box->matLocation("projection");
    glm::mat4 proj =
        glm::perspective(glm::radians(75.0f), 800 / (float)600, 0.1f, 10.0f);
    glUniformMatrix4fv(projMatPos, 1, GL_FALSE, glm::value_ptr(proj));



    auto lightColor = glGetUniformLocation(box->get(), "lightColor");
    glUniform3f(lightColor, 1.0f, 1.0f, 1.0f);

    auto lightPosLoc = glGetUniformLocation(box->get(), "light.Pos");

    setFloat(box->get(), "light.constant", 1.0f);
    setFloat(box->get(), "light.linear", 0.014f);
    setFloat(box->get(), "light.quad", 0.007f);
    //    auto Color = glGetUniformLocation(box->get(), "Color");
    //    glUniform3f(Color, 1.0f, 0.5f, 0.31f);


    // --------------- Textures -----------------//
    // Create the texture for diffuse maps
    const auto box_material = make_material(box);
    const auto diff_tex = gl::texture("models/cube_diffuse_map.png");
    const auto spec_tex =
        gl::texture("models/cube_specular_map.png", GL_TEXTURE1);
    glUniform1i(box_material.diffuse, 0);
    glUniform1i(box_material.specular, 1);    

    auto eyePos = glGetUniformLocation(box->get(), "viewPos");
    glUniform3fv(eyePos, 1, glm::value_ptr(glm::vec3(0.0f, 0.0f, 4.0f)));
    gl::printErrors("before set all material matrices");
    glUniform1f(box_material.shinyP, box_material.shiny);

    SetUniformVec3(box, "light.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
    SetUniformVec3(box, "light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
    SetUniformVec3(box, "light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
    gl::printErrors("set all material matrices");

    //-----------------Lights------------------//
    //
    // Setting up the ligth shaders.
    // Lights.
    auto light = std::make_shared<gl::program>("shaders/lights.vert",
                                               "shaders/lights.frag");
    gl::printErrors("box program");

    light->use();
    //    light->on_error(err_handle);
    GLuint light_vao;
    gl::genAndBind(light_vao, glGenVertexArrays, glBindVertexArray);
    auto buf_light = gl::StandardBuffer(vertices::cube)
                         ->with_bind_point(light, "Pos", gl::XYZ);
    gl::printErrors("box buffers");

    glm::mat4 light_base(1.0f);
    glm::vec3 lightPos(1.0f, 2.0f, 1.0f);
    light_base = glm::translate(light_base, lightPos);
    //    auto rotate_light =
    //            glm::rotate(base, 3.14f / 2, glm::vec3(1.0f, 0.0f, 1.0f));
    //    rotate_light = glm::translate(rotate_light, glm::vec3(1.0f,
    //    0.0f, 1.5f));
    auto light_viewMatPos = light->matLocation("view");
    glUniformMatrix4fv(light_viewMatPos, 1, GL_FALSE, glm::value_ptr(view));
    gl::printErrors("box matrixes");

    auto light_projMatPos = light->matLocation("projection");
    glUniformMatrix4fv(light_projMatPos, 1, GL_FALSE, glm::value_ptr(proj));

    auto light_modelMatPos = light->matLocation("model");
    glUniformMatrix4fv(light_modelMatPos, 1, GL_FALSE,
                       glm::value_ptr(light_base));
    gl::printErrors("box matrixes.");

    auto last = glfwGetTime();
    uv::loop l;
    l.timer<glm::mat4>(
        200,
        [](glm::mat4 &m, uv_timer_t * /*e*/) {
            /* lightPos = lightPos + glm::vec3(0.1f, 0.1f, 0.0f); */
            m = glm::translate(m, glm::vec3(0.1f, 0.1f, 0.0f));
            std::cout << "Hey guys" << std::endl;
            /* m = new glm::mat4(x); */
        },
        std::make_unique<glm::mat4>(glm::mat4(light_base))
    );
    /* l.run(); */
    while (!glfwWindowShouldClose(window)) {

        gl::backgroundColor(1.000f, 0.823f, 0.909f, 1.0);

        if (glfwGetTime() - last > 1) {
            last = glfwGetTime();
            //            rotate = glm::rotate(rotate,
            //            glm::radians(15.0f), glm::vec3(0.0f,
            //            0.0f, 1.0f));
            lightPos = lightPos + glm::vec3(0.0f, 0.0f, 0.2f);
            light_base =
                glm::translate(light_base, glm::vec3(0.0f, 0.0f, 0.2f));
        }

        box->use();
        glBindVertexArray(vao);
        glUniform3fv(lightPosLoc, 1, glm::value_ptr(lightPos) );
        glDrawArrays(GL_TRIANGLES, 0, 36);

        gl::printErrors("Before light draw");
        light->use();
        glBindVertexArray(light_vao);
        glUniformMatrix4fv(light_modelMatPos, 1, GL_FALSE,
                           glm::value_ptr(light_base));
        glDrawArrays(GL_TRIANGLES, 0, 36);
        gl::printErrors("After light draw");

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
