//
// Created by Aashay shah on 26/12/2020.
//

#ifndef OPENGL_WITH_CONAN_PROGRAM_H
#define OPENGL_WITH_CONAN_PROGRAM_H


#include <memory>
#include "shader.h"
#include <map>
#include "buffer.h"
#include <string>
#include <GL/glew.h>

namespace gl {
    class program : public std::enable_shared_from_this<program> {
        using error_handler = void (*)(int err, std::string describe);
    public:
        program(std::string vertexFile, std::string fragmentFile);

        void attachShader(gl::shader &s) const;

        void on_error(error_handler &handler);

        GLuint attribLocation(std::string attr) const;

        gl::bind_point::ptr attribBindPoint(std::string attr, std::vector<gl::point_type> ps);

        GLint matLocation(std::string name) const;

        void use() const;

        ~program();

        std::map<std::string, gl::bind_point::ptr> binds;
    private:
        gl::shader vShader;
        gl::shader fShader;
        GLuint _program;
        int error{};
        std::string err_describe;
        error_handler err_func{};
    };
};

#endif //OPENGL_WITH_CONAN_PROGRAM_H
