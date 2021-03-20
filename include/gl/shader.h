//
// Created by Aashay shah on 26/12/2020.
//

#ifndef OPENGL_WITH_CONAN_SHADER_H
#define OPENGL_WITH_CONAN_SHADER_H

#include "raw/wrappers.h"
#include <GL/glew.h>
#include <string>

namespace gl {
class shader {
    using error_handler = void (*)(int err, std::string describe);

  public:
    shader(gl::raw::shaders t, std::string sourceFile);

    void on_error(error_handler handler);

    GLuint get() const;

    ~shader();

    shader& operator= (const shader& s);
    shader(const shader& s);
    

  private:
    int error = 0;
    /* std::string err_describe; */
    // Use std::unique_ptr to prevent copying.
    GLuint _shader;
    gl::raw::shaders type;
};
} // namespace gl
#endif // OPENGL_WITH_CONAN_SHADER_H
