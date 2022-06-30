#include "block_data.h"
#include "block_data.h"

Mesh::Mesh() {
	// Reserve space for block face and direction data upon construction of a mesh.
	block_data.resize(65536);
	direction.resize(6);
	texture_index.resize(65536);
}

void Mesh::generate_mesh() {
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_int_distribution<> distr(0, 1); // define the range
	std::uniform_int_distribution<> distr_tex(0, 3); 
	for (int height = 0; height < 256; height++) {
		for (int row = 0; row < 16; row++) {
			for (int col = 0; col < 16; col++) {
				int index = (height * 16 * 16) + (row * 16) + col;
				block_data[index] = distr(gen);
				texture_index[index] = distr_tex(gen);
			}
		}
	}
}

void Mesh::build_face_direction_data(short row, short col, short height) {
	glm::mat4 model = glm::mat4(1.0f);
	// If the block in the mesh is 'air', skip it.
	if (get_block(row, col, height) == 0) {
		return;
	}
	// Check neighbors for drawing faces
	for (int i = 0; i < 6; i++) {
		model = glm::mat4(1.0f);
		model = glm::translate(glm::mat4(1.0), glm::vec3((float)col, (float)height, (float)row));
		// If a block has a neighbor that is 'air' in a certain direction, we want to draw it,
		// so calculate the position of the face.
		if (get_neighbor(row, col, height, (Direction)i) == 0) {
			direction[i].emplace_back(glm::vec3((float)col, (float)height - 256, (float)row));
		}
	}
}

void Mesh::generate_face_data() {
	for (short height = 0; height < 256; height++) {
		for (short row = 0; row < 16; row++) {
			for (short col = 0; col < 16; col++) {
				build_face_direction_data(row, col, height);

			}
		}
	}
}

int Mesh::get_block(short row, short col, short height) {
	return block_data[(height * (short)16 * (short)16) + (row * (short)16) + col];
}

int Mesh::get_neighbor(short row, short col, short height, Direction dir) {
	BlockCoordinate offset_to_check = offsets[dir];
	BlockCoordinate neighbor_coord = BlockCoordinate(row + offset_to_check.row,
														col + offset_to_check.col,
														height + offset_to_check.height);

	if (neighbor_coord.row < 0 || neighbor_coord.row > ROW_MAX || neighbor_coord.col < 0 || neighbor_coord.col > COL_MAX || neighbor_coord.height < 0 || neighbor_coord.height > HEIGHT_MAX) {
		return 0;
	}
	else {
		return get_block(neighbor_coord.row, neighbor_coord.col, neighbor_coord.height);
	}
}