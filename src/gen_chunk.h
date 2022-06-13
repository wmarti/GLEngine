#pragma once

#include <vector>
#include <array>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "texture.h"
#include "vertices.h"
#include "shader.h"
#include "block_data.h"

enum Chunk_Dimensions : int {
    CHUNK_SIZE = 65536
};

struct Block_Type {
    Texture* top;
    Texture* sides;
    Texture* bottom;
};

struct Block {
    Texture* top;
    Texture* sides;
    Texture* bottom;
    Block(Texture* top, Texture* sides, Texture* bottom) {
        this->top = top;
        this->sides = sides;
        this->bottom = bottom;
    }

    void draw_face(Direction dir, glm::vec3 face_position) {

    }
    void draw_cube(glm::vec3 cube_position) {
        for (int i = 0; i < 6; i++) {
            draw_face((Direction)i, cube_position);
        }
    }

    void draw_face(Direction dir) {
        // If dir == North, bind texture, etc...
        glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(sizeof(GLuint) * 6 * dir), 1);
    }
};

struct Vertex {
    glm::vec3 Position;
    glm::vec3 TexCoords;
};

class Chunk {
public:
    Chunk();
    void gen_flat_16_16(Block& block, Shader& shader);
    bool interior_block(uint32_t row, uint32_t col, uint32_t aisle);
    void draw_mesh(Block& block, Shader& shader);
    void build_face_data();

    Mesh* mesh;
    // Position information for each north, east, etc. face.
    std::vector<std::vector<glm::vec3>> direction;
};