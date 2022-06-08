#include "gen_chunk.h"

void Chunk::gen_flat_16_16(Block& block, Shader& shader) {

    glm::mat4 model = glm::mat4(1.0f);

    for (uint32_t row = 1; row < 17; row++) {
        for (uint32_t col = 1; col < 17; col++) {
            model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3((float)col-8, 0.0f, (float)row));
            model = glm::rotate(
                model,
                glm::radians(90.0f),
                glm::vec3(1.0f, 0.0f, 0.0f));
            shader.setMat4("model", model);
            block.draw();
        }
    }
}