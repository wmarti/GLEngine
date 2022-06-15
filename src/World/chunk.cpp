#include "chunk.h"


Chunk::Chunk() {
    mesh = new Mesh();
    mesh->generate_mesh();
    mesh->build_face_direction_data();
}


void Chunk::draw(Shader& shader) {

}