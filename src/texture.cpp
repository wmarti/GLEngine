#include "texture.h"

Texture::Texture(const char* filepath) {
    // OpenGL has texture coordinates with (0, 0) on bottom
    stbi_set_flip_vertically_on_load(true);
    image = stbi_load(filepath, &width, &height, &channels, STBI_rgb_alpha);
    assert(image != NULL);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // No interpolation
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    stbi_image_free(image);
}

void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, texture);
}