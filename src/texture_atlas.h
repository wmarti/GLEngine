#include "common.h"

struct TextureAtlas {
public:	
	TextureAtlas(const char* filepath);
	void Bind();

	unsigned int texture;
	unsigned char* image;
	int width;
	int height;
	int channels;
	
	int tilesX = 16;
	int tilesY = 16;
	int imageCount = 256;

	std::vector<unsigned char> tile;

	GLint internalFormat = GL_RGB8;
	GLenum imageFormat = GL_RGBA;

};