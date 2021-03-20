#include "gl/shader.h"
#include "gl/raw/wrappers.h"
#include "gl/utils.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
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

shader::shader(gl::raw::shaders t, std::string sourceFile) {
    gl::printErrors("shader cons" + sourceFile);
    type = t;
    auto Ssource = reader(sourceFile.c_str());
    auto source = Ssource.c_str();
    if (source == "") {
        /* err_describe += "Read error: \n" + sourceFile; */
        throw std::runtime_error("Could not read file.");
    }
    // TODO:
    // Lines 48-58 and 88-98 can be refactored to function which
    // accepts a function to create shader/program
    // executes a given function on it with only argument of object
    // checks for errors
    using namespace gl::raw;
    _shader = CreateShader(t);
    ShaderSource(_shader, Ssource);
    CompileShader(_shader);
}
shader& shader::operator= (const shader& s) {
    std::cout<<"shader Copy op"<<std::endl;
    type = s.type;
    _shader = s._shader;
    return *this;
}

shader::shader(const shader& s) {
    std::cout<<"shader Copy cons"<<std::endl;
    type = s.type;
    _shader = s._shader;
}

void shader::on_error(error_handler handler) {
    if (error != 0) {
        /* handler(error, err_describe); */
    }
}

// No set so _shader is immutable
GLuint shader::get() const { return _shader; }

shader::~shader() { glDeleteShader(_shader); }

}; // namespace gl
