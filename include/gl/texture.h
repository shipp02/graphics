//
// Created by Aashay shah on 27/12/2020.
//

#ifndef OPENGL_WITH_CONAN_TEXTURE_H
#define OPENGL_WITH_CONAN_TEXTURE_H

#include <gl/raw/opengl.h>
#include <string>
#include <vector>

namespace gl {

struct tex_parameters {
    GLenum wrap_s;
    GLenum wrap_t;
    GLenum min_filter;
    GLenum max_filter;
};

extern tex_parameters DefaultTexture;

class texture {
  public:
    explicit texture(std::string path, GLenum activeTexture = GL_TEXTURE0,
                     tex_parameters params = DefaultTexture);
    ~texture();

  private:
    GLuint _texture;
    std::vector<GLbyte> data;
};
} // namespace gl

#endif // OPENGL_WITH_CONAN_TEXTURE_H
