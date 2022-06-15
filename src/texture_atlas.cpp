#include "texture_atlas.h"

TextureAtlas::TextureAtlas(const char* filepath) {
	// OpenGL has texture coordinates with (0, 0) on bottom
	stbi_set_flip_vertically_on_load(true);
	image = stbi_load(filepath, &width, &height, &channels, STBI_rgb_alpha);
	assert(image != NULL);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D_ARRAY, texture);

	glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, internalFormat,
		width, height, imageCount, 0,
		imageFormat, GL_UNSIGNED_BYTE, nullptr);

	tile.resize(width * height * channels);
	int tileSizeX = width * channels;
	int rowLen = tilesX * tileSizeX;

    for (int iy = 0; iy < tilesY; ++iy)
    {
        for (int ix = 0; ix < tilesX; ++ix)
        {
            unsigned char* ptr = image + iy * rowLen + ix * tileSizeX;
            for (int row = 0; row < tilesX; ++row)
                std::copy(ptr + row * rowLen, ptr + row * rowLen + tileSizeX,
                    tile.begin() + row * tileSizeX);


            int i = iy * tilesX + ix;
            glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0,
                0, 0, i,
                width, height, 1,
                imageFormat, GL_UNSIGNED_BYTE, tile.data());
        }
    }
    stbi_image_free(image);
}

void TextureAtlas::Bind() {
    glBindTexture(GL_TEXTURE_2D_ARRAY, texture);
}