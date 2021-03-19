//
// Created by Aashay shah on 26/12/2020.
//

#ifndef OPENGL_WITH_CONAN_SHADER_H
#define OPENGL_WITH_CONAN_SHADER_H

#include <GL/glew.h>
#include <string>
namespace gl {
class shader {
    using error_handler = void (*)(int err, std::string describe);

  public:
    shader(GLenum t, std::string sourceFile);

    void on_error(error_handler handler);

    uint64_t get() const;

    ~shader();

  private:
    int error = 0;
    std::string err_describe;
    GLuint _shader;
    GLenum type;
};
} // namespace gl
#endif // OPENGL_WITH_CONAN_SHADER_H
