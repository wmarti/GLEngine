#pragma once
#include <array>
#include <vector>
#include <random>

#include <glm/glm.hpp>

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
	void generate_mesh();
	void build_face_data();
	int get_block(short row, short col, short height);
	int get_neighbor(short row, short col, short height, Direction dir);


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

	std::array<short, 65536> block_data;
};