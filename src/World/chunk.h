#pragma once
#include "common.h"

#include "texture.h"
#include "shader.h"
#include "block_data.h"

enum Chunk_Dimensions : int {
    CHUNK_SIZE = 65536
};

class Chunk {
public:
    Chunk();
    void draw(Shader& shader);
    void build_face_data();

    struct Mesh* mesh;
};