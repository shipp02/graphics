#ifndef HELPER_SHADER
#define HELPER_SHADER

#include <memory>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include"./buffer.cpp"
using std::cout;

namespace gl
{

using std::endl;
using std::ifstream;
using std::map;
using std::string;

using error_handler = void (*)(int err, string describe);

string reader(const char *file)
{
    ifstream infile;
    infile.open(file, std::ios::in);
    if (!infile.is_open())
    {
        printf("Failed to read shader\n");
        printf("%s\n", file);
    }
    std::stringstream buffer;
    buffer << infile.rdbuf();
    infile.close();
    string sha = buffer.str();
    return sha;
}

void backgroundColor(float r, float g, float b, float a){
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}

// error_handler error_printer;
void error_printer(int err, string describe)
{
    cout << "Error code: " << err << endl;
    cout << "Error description: " << describe << endl;
}

class shader
{
public:
    shader(GLenum t, string sourceFile)
    {
        type = t;
        auto Ssource = reader(sourceFile.c_str());
        auto source = Ssource.c_str();
        if (source == "")
        {
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
        if (error != GL_TRUE)
        {
            err_describe += "Failed to compile shader" + sourceFile;
            glDeleteShader(_shader);
        }
        char info[512];
        glGetShaderInfoLog(_shader, 512, NULL, info);
        err_describe += info;
    }

    void on_error(error_handler handler)
    {
        if (error != 0)
        {
            handler(error, err_describe);
        }
    }
    // No set so _shader is immutable
    GLuint get()
    {
        return _shader;
    }

    ~shader()
    {
        glDeleteShader(_shader);
    }

private:
    int error = 0;
    string err_describe;
    GLuint _shader;
    GLenum type;
};

class program : public std::enable_shared_from_this<program>
{
public:
    program(string vertexSource, string fragmentSource) : 
        vShader(GL_VERTEX_SHADER, vertexSource), 
        fShader(GL_FRAGMENT_SHADER, fragmentSource)
    {
        _program = glCreateProgram();
        attachShader(vShader);
        attachShader(fShader);
        glLinkProgram(_program);
        // TODO:Better error handlng design
        glGetProgramiv(_program, GL_LINK_STATUS, &error);
        if (error != GL_TRUE)
        {
            err_describe += "Linking failed\n";
        }
        char proInfo[512];
        glGetProgramInfoLog(_program, 512, NULL, proInfo);
        err_describe += proInfo;
    }

    void on_error(error_handler &handler)
    {
        if (error != 0)
        {
            handler(error, err_describe);
        }
    }

    // Returns enabled pointer to input vector
    GLuint attribLocation(string attr)
    {
        auto pos = glGetAttribLocation(_program, attr.c_str());
        glEnableVertexAttribArray(pos);
        return pos;
    }

    bind_point::ptr attribBindPoint(string attr, vector<point_type> ps) 
    {
        auto ptr = std::make_shared<bind_point>(attr, attribLocation(attr), ps);
        binds.insert({attr, ptr});
        return ptr;
    }

    GLint matLocation(string name)
    {
        return glGetUniformLocation(_program, name.c_str());
    }
    void attachShader(shader &s)
    {
        glAttachShader(_program, s.get());
    }
    void use()
    {
        glUseProgram(_program);
    }
    ~program()
    {
        glDeleteProgram(_program);
    }
    std::map<std::string, bind_point::ptr> binds;
private:
    GLuint _program;
    shader vShader;
    shader fShader;
    int error;
    string err_describe;
    // map<string, bind_point> bps;
};

void printErrors(string pos)
{
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR)
    {
        std::cout << "OpenGL error: " << err << " at " + pos << endl;
        cout << gluErrorString(err) << endl;
    }
}
}; // namespace gl

#endif

#ifndef HELPER_VERTICES
#define HELPER_VERTICES
namespace vertices
{

std::vector<GLfloat> cube{
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

    -0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    -0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

    -0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

    0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

    -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f
};

std::vector<float> square {
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
};
}; // namespace vertices

#endif
