//
// Created by Aashay shah on 27/12/2020.
//
/*
 * Each bind type will have an appropriate pointer to the data it holds in the GPU
 * For example:  
 * mat_bind will hold refrences to glm::mat or glm::vecs
 * TODO: ALso rename mat_bind to uniform_bind.
 * attrib_bind will hold refrence to the buffer it points. 
 * TODO: Add fields to attrib_bind to show what kind of bind it is.
 * Fields include: size, type, stride
 * This will have a 
 */
#ifndef OPENGL_WITH_CONAN_BIND_POINT_H
#define OPENGL_WITH_CONAN_BIND_POINT_H

#include <stdexcept>
#include <string>
#include <vector>
#include <gl/raw/opengl.h>

namespace gl {
enum point_type { Red, Green, Blue, X, Y, Z, U, V };
extern std::vector<point_type> RGB;
extern std::vector<point_type> XYZ;
extern std::vector<point_type> UV;

class bind_point {
  public:
    bind_point(std::string _name, uint64_t _location, std::vector<point_type> ps);

    using ptr = std::shared_ptr<bind_point>;

    std::vector<point_type> points;
    int location;
//    std::function<GLint(std::string, int)> get;
    /* virtual GLint get(GLuint program, std::string name) = 0; */

  private:
    std::string name;
};


/* class mat_bind : public bind_point {
    mat_bind(GLuint program, const std::string& name);
    GLint get(GLuint program, std::string name) override;
};

class attrib_bind :public bind_point {
  public:
    attrib_bind(GLuint program, const std::string& name);
    GLint get(GLuint program, std::string name) override;
}; */
} // namespace gl

#endif // OPENGL_WITH_CONAN_BIND_POINT_H
