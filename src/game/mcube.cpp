#include "mcubes.h"

#include <vector>
#include "tables.h"


Grid::Grid(int x, int y, int z) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->cells = new uint8_t[x * y * z];
}


Grid::~Grid() {
	delete[] this->cells;
}


Mesh* MarchingCubeGenerator::generate(Grid* grid) {
	Mesh* mesh = new Mesh();
	std::vector<Vertex> vertices = std::vector<Vertex>();
	int x, y, z;
	int i, c = 0;
	uint8_t index;
	
	for (z = 0; z < grid->z - 1; z++) {
		for (y = 0; y < grid->y - 1; y++) {
			for (x = 0; x < grid->x - 1; x++) {
				index = 0;
				if (grid->cells[c							   ]) index |= 1;
				if (grid->cells[c + grid->x					   ]) index |= 2;
				if (grid->cells[c + grid->x +			grid->z]) index |= 4;
				if (grid->cells[c +						grid->z]) index |= 8;
				if (grid->cells[c +			  grid->y		   ]) index |= 16;
				if (grid->cells[c + grid->x + grid->y		   ]) index |= 32;
				if (grid->cells[c + grid->x + grid->y + grid->z]) index |= 64;
				if (grid->cells[c +			  grid->y + grid->z]) index |= 128;
				
				if (MC_EDGE_TABLE[index]) {
					for(i = 0; MC_TRI_TABLE[index][i] != -1; i += 3) {
						Vertex v0, v1, v2;
						
						v0.position[0] = MC_OFFSETS[MC_TRI_TABLE[index][i    ]][0] + (float)x;
						v0.position[1] = MC_OFFSETS[MC_TRI_TABLE[index][i    ]][1] + (float)y;
						v0.position[2] = MC_OFFSETS[MC_TRI_TABLE[index][i    ]][2] + (float)z;
						
						v1.position[0] = MC_OFFSETS[MC_TRI_TABLE[index][i + 1]][0] + (float)x;
						v1.position[1] = MC_OFFSETS[MC_TRI_TABLE[index][i + 1]][1] + (float)y;
						v1.position[2] = MC_OFFSETS[MC_TRI_TABLE[index][i + 1]][2] + (float)z;
						
						v2.position[0] = MC_OFFSETS[MC_TRI_TABLE[index][i + 2]][0] + (float)x;
						v2.position[1] = MC_OFFSETS[MC_TRI_TABLE[index][i + 2]][1] + (float)y;
						v2.position[2] = MC_OFFSETS[MC_TRI_TABLE[index][i + 2]][2] + (float)z;
						
						vertices.push_back(v2);
						vertices.push_back(v1);
						vertices.push_back(v0);
					}
				}
				
				// Increment cell index.
				c++;
			}
			
			// Skip last x cell.
			c++;
		}
		
		// Skip last y column.
		c += grid->x;
	}
	
	mesh_create(mesh, vertices.data(), vertices.size(), nullptr, 0);
	return mesh;
}
