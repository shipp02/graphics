//
// Created by Aashay shah on 27/12/2020.
//

#include "bind_point.h"

#include <utility>

// order in ps must be same as required order in the buffer
// 0th element in point_type will be bound to 0, 0+nth points in buffer
// where n is the total number of points in that buffer
// TODO: Add default instances with type X,Y,Z & R,G,B & U,V using static method
namespace gl {
    bind_point::bind_point(std::string _name, GLuint _location, std::vector<point_type> ps)
            : points(std::move(ps)), location(_location), name(std::move(_name)) {
        if (location < 0) {
            throw "Invalid Location";
        }
    }
}