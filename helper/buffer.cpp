#ifndef HELPER_BUFFER
#define HELPER_BUFFER

#include <GL/glew.h>
#include <vector>
#include <string>
#include <iostream>


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
        name(_name), location(_location), points(ps)
    {
        if (location < 0)
        {
            throw "Invalid Location";
        }
    }

    typedef std::shared_ptr<bind_point> pointer;

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
        std::cout<<_buffer<<std::endl;
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
    shared_ptr<buffer> with_bind_point(bind_point point)
    {
        using std::cout;
        auto s = point.points.size();
        bool match  = true;
        for(int i = 0; i<s; i++) {
            match =  match && (point.points[i] == types[assigned+i]);
        }
        if(!match) {
            throw  points_do_not_match();
            // return shared_from_this();
        }
        glVertexAttribPointer(point.location, 
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

}; // namespace gl

#endif
