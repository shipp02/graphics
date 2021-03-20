//
// Created by Aashay shah on 27/12/2020.
//

// Maybe add a config object to be optionally provided  by the vao to control some
// values in with_bind_point.

#ifndef OPENGL_WITH_CONAN_BUFFER_H
#define OPENGL_WITH_CONAN_BUFFER_H

#include "bind_point.h"
#include "program.h"
#include <cstddef>
#include <functional>
#include <string>
#include <vector>
namespace gl {
// This assumes that the points are laid out in a array of structures fashion.
// The points are arranged in order of which they need to be accesed.
// So to send XYZ and RGB insted of adding an array of XYZ and another of RGB
// The the array of points are in an array of XYZRGB order.
class buffer : public std::enable_shared_from_this<buffer> {
  public:
    buffer();
    buffer(std::vector<float> &points, std::vector<point_type> _types);
    ~buffer();

    using ptr = std::shared_ptr<buffer>;
    ptr with_bind_point(bind_point::ptr point);

    ptr with_bind_point(const program::ptr &p, std::string name,
                        std::vector<point_type> ps);

    ptr set_data(std::vector<float> &_points, std::vector<point_type> &_types);

    // Buffer conifg object not used currnetly since it is not needed.
    // API Idea:
    // There will be a method/in-constructor which will take a lambda
    // which is passed the default config. It will modify and return
    // the struct which is set to the default struct for that instance.
    struct config {
        GLboolean normalized;
        GLenum type;
        std::function<size_t(int)> size;
    };

  private:
    GLuint _buffer;
    std::vector<float> points;
    std::vector<point_type> types;
    uint32_t assigned;
    void save_to_gpu();
};
buffer::ptr StandardBuffer(std::vector<float> &points);
} // namespace gl

#endif // OPENGL_WITH_CONAN_BUFFER_H
