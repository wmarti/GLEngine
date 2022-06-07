#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "texture.h"
#include "vertices.h"

struct Block {
    Texture* p_top;
    Texture* p_sides;
    Texture* p_bottom;
    Block(Texture* top, Texture* sides, Texture* bottom) {
        p_top = top;
        p_sides = sides;
        p_bottom = bottom;
    }
    void draw() {
        for (int i = 0; i < 7; i++) {
            // top
            if (i == 1) {
                p_top->bind();
            }
            // bottom
            else if (i == 2) {
                p_bottom->bind();
            }
            // sides
            else {
                p_sides->bind();
            }
            glDrawArrays(GL_TRIANGLES, 0, i*6);
        }
    }
};

class Chunk {
    void gen_flat_16_16();
};