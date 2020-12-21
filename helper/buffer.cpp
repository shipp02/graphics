#ifndef HELPER_BUFFER
#define HELPER_BUFFER

#include <GL/glew.h>
#include <memory>
#include <vector>
#include <string>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


namespace gl
{

using std::string;
using std::vector;

using binder = void (*)(GLuint array);
using generator = void (*)(GLsizei n, GLuint *array);

void genAndBind(GLuint &gen, generator g, binder b)
{
    g(1, &gen);
    b(gen);
}

void arrayBufferBind(GLuint arr)
{
    glBindBuffer(GL_ARRAY_BUFFER, arr);
}

void texture2dBind (GLuint arr) 
{
    glBindBuffer(GL_TEXTURE_2D, arr);
}

enum point_type
{
    Red,
    Green,
    Blue,
    X,
    Y,
    Z,
    U,
    V

};

class buffer;
// order in ps must be same as required order in the buffer
// 0th element in point_type will be bound to 0, 0+nth points in buffer
// where n is the total number of points in that buffer
// TODO: Add default instances with type X,Y,Z & R,G,B & U,V using static method
class bind_point
{
public:
    bind_point(string _name, GLuint _location, vector<point_type> ps) : 
          points(ps), location(_location), name(_name)
    {
        if (location < 0)
        {
            throw "Invalid Location";
        }
    }

    using ptr = std::shared_ptr<bind_point>;

    static ptr bind_XYZ(string _name, GLuint _location) {
        return std::make_shared<bind_point>(_name, _location, vector<point_type>{
                X,
                Y,
                Z
        });
    }

    void bind_vertex(buffer &b) {
    }
    vector<point_type> points;
    GLuint location;

private:
    string name;
};

#define FLOAT_SIZE(x) x*sizeof(float)

using std::shared_ptr;
class buffer : public std::enable_shared_from_this<buffer>
{
public:
    buffer(generator &g, binder &b)
    {
        genAndBind(_buffer, g, b);
    };

    buffer(generator g, binder b, 
        vector<float> &_points, vector<point_type> _types) 
    : points(_points), types(_types)
    {
        genAndBind(_buffer, g, b);
        /* std::cout<<_buffer<<std::endl; */
        assigned = 0;
        save_to_gpu();
    };


    ~buffer()
    {
        glDeleteBuffers(1, &_buffer);
        std::cout<<"Deleted"<<std::endl;
    }

    shared_ptr<buffer> set_data(vector<float> &_points, vector<point_type> &_types)
    {
        points = _points;
        types = _types;
        save_to_gpu();
        return shared_from_this();
    }

    class points_do_not_match {
    };
    // TODO: THis will bind the first few points on the bind_point with
    // with those on buffer provided their types match
    // Add check to prevent assignment of more than given number of points
    shared_ptr<buffer> with_bind_point(bind_point::ptr point)
    {
        using std::cout;
        auto s = point->points.size();
        bool match  = true;
        for(int i = 0; i<s; i++) {
            match =  match && (point->points[i] == types[assigned+i]);
        }
        if(!match) {
            throw  points_do_not_match();
            // return shared_from_this();
        }
        glVertexAttribPointer(point->location, 
                s, 
                GL_FLOAT, GL_FALSE, 
                FLOAT_SIZE(types.size()),
                (void*) (FLOAT_SIZE(assigned)));
        assigned += s;
        return shared_from_this();
    }


private:
    GLuint _buffer;
    vector<float> points;
    vector<point_type> types;
    uint32_t assigned;

    void save_to_gpu() {
        glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(float), &points[0], GL_STATIC_DRAW);
    }
};

struct TexParameters {
    GLenum wrap_s;
    GLenum wrap_t;
    GLenum min_filter;
    GLenum max_filter;
};

auto DefaultTexture = TexParameters {
    GL_REPEAT,
    GL_REPEAT,
    GL_LINEAR,
    GL_LINEAR
};

class texture : public std::enable_shared_from_this<texture> {
public:
    using pointer = std::shared_ptr<texture>;

    texture(string path, 
            GLenum activeTexture = GL_TEXTURE0,
            TexParameters params = DefaultTexture) {
        glActiveTexture(activeTexture);
        gl::genAndBind(_texture, glGenTextures, texture2dBind);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, params.wrap_s);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, params.wrap_t);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, params.max_filter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, params.min_filter);
        GLint width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    }


    ~texture() {
        glDeleteTextures(1, &_texture);
    }

private:
    GLuint _texture;
    vector<GLbyte> data;
};

}; // namespace gl

#endif
