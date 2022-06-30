#include "chunk.h"


Chunk::Chunk() {
    mesh = new Mesh();
    mesh->generate_mesh();
    mesh->generate_face_data();
}


void Chunk::draw(Shader& shader) {

}