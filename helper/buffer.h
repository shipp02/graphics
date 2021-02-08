//
// Created by Aashay shah on 27/12/2020.
//

#ifndef OPENGL_WITH_CONAN_BUFFER_H
#define OPENGL_WITH_CONAN_BUFFER_H

#include "bind_point.h"
#include "program.h"
#include <vector>
#include <string>
namespace gl {
    class buffer : public std::enable_shared_from_this<buffer> {
    public:
        buffer();
        buffer(std::vector<float> &points, std::vector<point_type> _types);
        ~buffer();

        using ptr = std::shared_ptr<buffer>;
        ptr with_bind_point(bind_point::ptr point);

        ptr with_bind_point(const program::ptr&  p, std::string name, std::vector<point_type> ps);

        ptr set_data(std::vector<float> &_points,
                     std::vector<point_type> &_types);

    private:
        GLuint _buffer;
        std::vector<float> points;
        std::vector<point_type> types;
        uint32_t assigned;
        void save_to_gpu();

    };
  buffer::ptr StandardBuffer(std::vector<float> &points);
}

#endif //OPENGL_WITH_CONAN_BUFFER_H
