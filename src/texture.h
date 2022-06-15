#pragma once
#include "common.h"

class Texture {
public:
    unsigned int texture;
    int width, height, channels;
    unsigned char* image;
    Texture(const char* filepath);
    Texture();
    void bind();
};
