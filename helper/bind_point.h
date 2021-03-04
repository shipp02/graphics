//
// Created by Aashay shah on 27/12/2020.
//

#ifndef OPENGL_WITH_CONAN_BIND_POINT_H
#define OPENGL_WITH_CONAN_BIND_POINT_H

#include <GL/glew.h>
#include <string>
#include <vector>

namespace gl {
enum point_type { Red, Green, Blue, X, Y, Z, U, V };
extern std::vector<point_type> RGB;
extern std::vector<point_type> XYZ;
extern std::vector<point_type> UV;

class bind_point {
  public:
    bind_point(std::string _name, GLuint _location, std::vector<point_type> ps);

    using ptr = std::shared_ptr<bind_point>;
    std::vector<point_type> points;
    GLuint location;

  private:
    std::string name;
};
} // namespace gl

#endif // OPENGL_WITH_CONAN_BIND_POINT_H
