#include <GL/glew.h>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>
#include "bind_point.h"
#include "buffer.h"
#include "utils.h"


namespace gl {


    using std::string;
    using std::vector;


    void arrayBufferBind(GLuint arr) { glBindBuffer(GL_ARRAY_BUFFER, arr); }


//enum point_type {
//  Red,
//  Green,
//  Blue,
//  X,
//  Y,
//  Z,
//  U,
//  V
//
//};
    using std::shared_ptr;


#define FLOAT_SIZE(x) x * sizeof(float)


    buffer::buffer() { genAndBind(_buffer, glGenBuffers, gl::arrayBufferBind); };

    buffer::buffer(vector<float> &_points,
                   vector<point_type> _types)
            : points(_points), types(std::move(_types)) {
        genAndBind(_buffer, glGenBuffers, gl::arrayBufferBind);
        /* std::cout<<_buffer<<std::endl; */
        assigned = 0;
        save_to_gpu();
    }

    buffer::~buffer() {
        glDeleteBuffers(1, &_buffer);
    }

    buffer::ptr buffer::set_data(vector<float> &_points,
                                 vector<point_type> &_types) {
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
    buffer::ptr buffer::with_bind_point(bind_point::ptr point) {
        using std::cout;
        auto s = point->points.size();
        bool match = true;
        for (int i = 0; i < s; i++) {
            match = match && (point->points[i] == types[assigned + i]);
        }
        if (!match) {
            throw points_do_not_match();
            // return shared_from_this();
        }
        glVertexAttribPointer(point->location, s, GL_FLOAT, GL_FALSE,
                              FLOAT_SIZE(types.size()),
                              (void *) (FLOAT_SIZE(assigned)));
        assigned += s;
        return shared_from_this();
    }


    void buffer::save_to_gpu() {
        glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(float), &points[0],
                     GL_STATIC_DRAW);
    }

    buffer::ptr buffer::with_bind_point(const program::ptr& p, string name, std::vector<point_type> ps) {
        using std::cout;
        auto point = p->attribBindPoint(std::move(name), ps);
        with_bind_point(point);
        return shared_from_this();
    }

    buffer::ptr StandardBuffer(std::vector<float> &points) {
    return std::make_shared<buffer>(points, vector<gl::point_type>{
                    point_type::X,
                    point_type::Y,
                    point_type::Z,
                    point_type::Red,
                    point_type::Green,
                    point_type::Blue,
                    point_type::U,
                    point_type::V,
      });
  }
			     


}; // namespace gl

#ifndef HELPER_VERTICES
#define HELPER_VERTICES

#include <vector>
; // namespace vertices

#endif
