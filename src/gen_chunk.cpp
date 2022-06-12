#include "gen_chunk.h"


Chunk::Chunk() {
    mesh = new Mesh();
    mesh->generate_mesh();
}

void Chunk::build_face_data() {
    for (short height = 0; height < 256; height++) {
        for (short row = 0; row < 16; row++) {
            for (short col = 0; col < 16; col++) {
                // If the block in the mesh is 'air', skip it.
                if (mesh->get_block(row, col, height) == 0) {
                    continue;
                }
                // Check neighbors for drawing faces
                for (int i = 0; i < 6; i++) {
                    // If a block has a neighbor that is 'air' in a certain direction, calculate the position of the face.
                    if (mesh->get_neighbor(row, col, height, (Direction)i) == 0) {
                        direction[i].emplace_back(glm::vec3((float)col - 16, (float)height, (float)row - 16));
                    }
                }
            }
        }
    }
}

void Chunk::draw_mesh(Block& block, Shader& shader) {

}

bool Chunk::interior_block(uint32_t row, uint32_t col, uint32_t aisle) {
    if ((row > 1 && col > 1 && aisle > 1) && (row < 16 && col < 16 && aisle < 256)) {
        return true;
    }
    return false;
}

void Chunk::gen_flat_16_16(Block& block, Shader& shader) {

    glm::mat4 model = glm::mat4(1.0f);

    for (uint32_t row = 1; row < 17; row++) {
        for (uint32_t col = 1; col < 17; col++) {
            for (uint32_t ailsle = 1; ailsle < 257; ailsle++) {
                if (!(interior_block(row, col, ailsle))) {
                    model = glm::mat4(1.0f);
                    model = glm::translate(model, glm::vec3((float)col - 8, (float)ailsle - 257, (float)row));
                    model = glm::rotate(
                        model,
                        glm::radians(90.0f),
                        glm::vec3(1.0f, 0.0f, 0.0f));
                    shader.setMat4("model", model);
                    //block.draw();
                }
            }
        }
    }
}