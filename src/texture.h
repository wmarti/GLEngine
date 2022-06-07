#pragma once
#include "stb_image.h"
#include <assert.h>
#include <glad/glad.h>
class Texture {
public:
    unsigned int texture;
    int width, height, channels;
    unsigned char* image;
    Texture(const char* filepath);
    Texture();
    void bind();
};
