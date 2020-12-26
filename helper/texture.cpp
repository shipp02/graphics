//
// Created by Aashay shah on 27/12/2020.
//

#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace gl {
    auto DefaultTexture = tex_parameters{GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR};

    void texture2dBind(GLuint arr) { glBindBuffer(GL_TEXTURE_2D, arr); }
    texture::texture(std::string path, GLenum activeTexture, tex_parameters params) {
        glActiveTexture(activeTexture);
//        gl::genAndBind(_texture, glGenTextures, texture2dBind);
        glGenTextures(1, &_texture);
        texture2dBind(_texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, params.wrap_s);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, params.wrap_t);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, params.max_filter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, params.min_filter);
        GLint width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char *data =
                stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    }

    texture::~texture() {
        glDeleteTextures(1, &_texture);
    }
}