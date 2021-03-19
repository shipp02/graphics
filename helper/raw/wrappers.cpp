#include "wrappers.h"
#include <map>

namespace gl::raw {

namespace _ {
void CheckShader(GLuint shader) {
    if (!glIsShader(shader)) {
        throw not_a_shader();
    }
}
} // namespace _
std::map<shaders, GLenum> shader_type_map{
    {shaders::FRAGMENT, GL_FRAGMENT_SHADER},
    {shaders::VERTEX, GL_VERTEX_SHADER}};

GLuint CreateShader(shaders type) {
    return glCreateShader(shader_type_map[type]);
}

void ShaderSource(GLuint shader, const std::string &source) {
    if (!glIsShader(shader)) {
        throw not_a_shader();
    }
    _::CheckShader(shader);
    const GLchar *c_src = source.c_str();
    glShaderSource(shader, 1, &c_src, 0);
}

void CompileShader(GLuint shader) {
    _::CheckShader(shader);
    glCompileShader(shader);
    if (GetShaderiv(shader, COMPILE) != GL_TRUE) {
        int len = GetShaderiv(shader, INFO_LOG_LEN);
        GLchar c[len];
        glGetShaderInfoLog(shader, len, NULL, c);
        throw could_not_compile_shader(std::string(c));
    }
}
std::map<gl::raw::shader_info, GLenum> shader_info_map{
    {shader_info::COMPILE, GL_COMPILE_STATUS},
    {shader_info::TYPE, GL_SHADER_TYPE},
    {shader_info::DELETED, GL_DELETE_STATUS},
    {shader_info::INFO_LOG_LEN, GL_INFO_LOG_LENGTH},
    {shader_info::SOURCE_LENGTH, GL_SHADER_SOURCE_LENGTH}};

GLint GetShaderiv(GLuint shader, shader_info kind) {
    _::CheckShader(shader);
    GLint resp;
    glGetShaderiv(shader, shader_info_map[kind], &resp);
    return resp;
}

void DeleteShader(GLuint shader) {
    glDeleteShader(shader);
    glGetError();
}

GLuint CreateProgram() {
    auto x = glCreateProgram();
    if (x == 0) {
        throw could_not_create_program();
    }
    return x;
}

void LinkProgram(GLuint program) {
    if (!glIsProgram(program)) {
        throw not_a_program();
    }
    glLinkProgram(program);
}

void AttachShader(GLuint program, GLuint shader) {
    glAttachShader(program, shader);
    auto err = glGetError();
    if (err == GL_NO_ERROR) {
        return;
    } else if (!glIsProgram(program)) {
        throw not_a_program();
    } else if (!glIsShader(shader)) {
        throw not_a_shader();
    }
}

could_not_compile_shader::could_not_compile_shader(std::string err)
    : error(std::move(err)) {}
} // namespace gl::raw
