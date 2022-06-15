#pragma once
#include "common.h"

enum Direction : char {
	North,
	East,
	South,
	West,
	Up,
	Down
};

enum MeshDimensions : int {
	ROW_MAX = 15,
	COL_MAX = 15,
	HEIGHT_MAX = 255,
};

class Mesh {
public:
	Mesh();
	void generate_mesh();
	int get_block(short row, short col, short height);
	int get_neighbor(short row, short col, short height, Direction dir);
	void build_face_direction_data();

	// Block information, for now just solid or air...
	std::vector<char> block_data;
	// Position information for each north, east, etc. face.
	std::vector<std::vector<glm::vec3>> direction;

	struct BlockCoordinate {
		int row, col, height;

		BlockCoordinate(int row, int col, int height) {
			this->row = row;
			this->col = col;
			this->height = height;
		}
	};

	BlockCoordinate offsets[6] = {
		BlockCoordinate(-1, 0, 0),
		BlockCoordinate( 0, 1, 0),
		BlockCoordinate( 1, 0, 0),
		BlockCoordinate( 0,-1, 0),
		BlockCoordinate( 0, 0, 1),
		BlockCoordinate( 0, 0,-1)
	};
};
