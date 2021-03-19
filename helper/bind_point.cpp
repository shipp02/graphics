//
// Created by Aashay shah on 27/12/2020.
//

#include "bind_point.h"

#include <stdexcept>
#include <utility>
#include <vector>

// order in ps must be same as required order in the buffer
// 0th element in point_type will be bound to 0, 0+nth points in buffer
// where n is the total number of points in that buffer
namespace gl {
bind_point::bind_point(std::string _name, uint64_t _location,
                       std::vector<point_type> ps)
    : points(std::move(ps)), location(_location), name(std::move(_name)) {
    if (location < 0) {
        throw std::invalid_argument(name + " location must not be less than 0");
    }
}

using std::vector;
auto RGB = vector<point_type>{Red, Green, Blue};
auto XYZ = vector<point_type>{X, Y, Z};
auto UV = vector<point_type>{U, V};

/* GLint mat_bind::get(GLuint program, std::string name) {
    location = glGetUniformLocation(program, name.c_str());
    return location;
}
mat_bind::mat_bind(GLuint program, const std::string &name)
    : bind_point(name, glGetUniformLocation(program, name.c_str()),
                 std::vector<point_type>{}) {}

GLint attrib_bind::get(GLuint program, std::string name) {
    location = glGetAttribLocation(program, name.c_str());
    glEnableVertexAttribArray(location);
    return location;
}
attrib_bind::attrib_bind(GLuint program, const std::string &name)
    : bind_point(name, glGetAttribLocation(program, name.c_str()), std::vector<point_type>{}){
    glEnableVertexAttribArray(location);
} */
} // namespace gl
