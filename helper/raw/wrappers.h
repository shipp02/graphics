#ifndef OPENGL_WITH_CONAN_RAW_WRAPPER_H
#define OPENGL_WITH_CONAN_RAW_WRAPPER_H

#include "GL/glew.h"
#include <string>

namespace gl::raw {

enum shaders { VERTEX, FRAGMENT };
enum shader_info { TYPE, DELETED, COMPILE, INFO_LOG_LEN, SOURCE_LENGTH };
GLuint CreateShader(shaders type);
void ShaderSource(GLuint shader, const std::string &source);
void CompileShader(GLuint shader);
GLint GetShaderiv(GLuint shader, shader_info kind);
void DeleteShader(GLuint);
GLuint CreateProgram();
void LinkProgram(GLuint program);
void AttachShader(GLuint program, GLuint shader);

class not_a_shader : public std::exception{};
class could_not_compile_shader : public std::exception{
  public:
    explicit could_not_compile_shader(std::string err);

  private:
    std::string error;
};

class could_not_create_program : public std::exception{};
class not_a_program : public std::exception{};
} // namespace gl::raw

#endif
