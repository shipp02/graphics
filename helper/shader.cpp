#include "shader.h"
#include "utils.h"
#include "raw/wrappers.h"
#include <GLFW/glfw3.h>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
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
    using namespace gl::raw;
    gl::printErrors("shader cons: " + sourceFile);
    type = t;
    auto source = reader(sourceFile.c_str());
    // TODO:
    // Lines 48-58 and 88-98 can be refactored to function which
    // accepts a function to create shader/program
    // executes a given function on it with only argument of object
    // checks for errors
    _shader = CreateShader(shaders::VERTEX);
    ShaderSource(_shader, source);
    CompileShader(_shader);
}

void shader::on_error(error_handler handler) {
    if (error != 0) {
        handler(error, err_describe);
    }
}

// No set so _shader is immutable
uint64_t shader::get() const { return _shader; }

shader::~shader() { glDeleteShader(_shader); }

}; // namespace gl
