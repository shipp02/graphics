#include "shader.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <cstdio>
#include <string>

using std::cout;

namespace gl {



    std::string reader(const char *file) {
        std::ifstream infile;
        infile.open(file, std::ios::in);
        if (!infile.is_open()) {
            printf("Failed to read shader\n");
            printf("%s\n", file);
        }
        std::stringstream buffer;
        buffer << infile.rdbuf();
        infile.close();
        std::string sha = buffer.str();
        return sha;
    }


    void error_printer(int err, std::string &describe) {
        cout << "Error code: " << err << std::endl;
        cout << "Error description: " << describe << std::endl;
    }

    shader::shader(GLenum t, std::string sourceFile) {
        type = t;
        auto Ssource = reader(sourceFile.c_str());
        auto source = Ssource.c_str();
        if (source == "") {
            err_describe += "Read error: \n" + sourceFile;
        }
        // TODO:
        // Lines 48-58 and 88-98 can be refactored to function which
        // accepts a function to create shader/program
        // executes a given function on it with only argument of object
        // checks for errors
        _shader = glCreateShader(type);
        glShaderSource(_shader, 1, &source, 0);
        glCompileShader(_shader);
        glGetShaderiv(_shader, GL_COMPILE_STATUS, &error);
        // TODO: Better design for handling error
        if (error != GL_TRUE) {
            err_describe += "Failed to compile shader" + sourceFile;
            glDeleteShader(_shader);
        }
        char info[512];
        glGetShaderInfoLog(_shader, 512, NULL, info);
        err_describe += info;
    }

    void shader::on_error(error_handler handler) {
        if (error != 0) {
            handler(error, err_describe);
        }
    }

    // No set so _shader is immutable
    GLuint shader::get() const { return _shader; }

    shader::~shader() { glDeleteShader(_shader); }

}; // namespace gl



