#include "block_data.h"

void Mesh::generate_mesh() {
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_int_distribution<> distr(0, 1); // define the range

	for (int height = 0; height < 256; height++) {
		for (int row = 0; row < 16; row++) {
			for (int col = 0; col < 16; col++) {
				int index = (height * 16 * 16) + (row * 16) + col;
				if (height < 1) {
					block_data[index] = 1;
				}
				else {
					block_data[index] = 0;
				}
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