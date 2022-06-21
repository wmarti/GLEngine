#include "texture_atlas.h"

TextureAtlas::TextureAtlas(const char* filepath) {
	// OpenGL has texture coordinates with (0, 0) on bottom
	stbi_set_flip_vertically_on_load(true);
	image = stbi_load(filepath, &width, &height, &channels, STBI_rgb_alpha);
	assert(image != NULL);

    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);

    glBindTexture(GL_TEXTURE_2D_ARRAY, texture);

    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA,
        16, 16,       // width, height
        256,            // Image count
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE, nullptr);

    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);

    tile.resize(16 * 16 * 4);

    int tileSizeX = 16 * 4;
    int rowLen = 16 * tileSizeX;
    for (int row = 0; row < 16; row++) {
        for (int col = 0; col < 16; col++) {
            int index = (row * rowLen * 16) + col * tileSizeX;
            unsigned char* tile_ptr = image + index;
            for (int r = 0; r < 16; r++) {
                std::copy(
                    tile_ptr + (r * rowLen),
                    tile_ptr + (r * rowLen + tileSizeX),
                    tile.begin() + r * tileSizeX);
            }
            int depth = (row * 16) + col;
            glTexSubImage3D(GL_TEXTURE_2D_ARRAY,
                0,              // Mipmap number
                0, 0, depth,    // x, y, z offsets
                16, 16, 1,      // width, height, depth
                GL_RGBA, GL_UNSIGNED_BYTE, tile.data());
        }
    }
    stbi_image_free(image);
}

void TextureAtlas::Bind() {
    glBindTexture(GL_TEXTURE_2D_ARRAY, texture);
}