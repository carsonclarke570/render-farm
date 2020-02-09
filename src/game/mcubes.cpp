/*
    Copyright 2020 Carson Clarke-Magrab

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/
#include "mcubes.h"

#include <vector>
#include "tables.h"


Mesh* MarchingCubeGenerator::generate(Grid* grid) {
	Mesh* mesh = new Mesh();
	std::vector<Vertex> vertices = std::vector<Vertex>();
    Vertex v0, v1, v2;
    vec3 norm, q, r;
	int x, y, z;
	int i, c = 0;
	uint8_t index;
	
	for (c = 0, z = 0; z < grid->z - 1; z++) {
		for (y = 0; y < grid->y - 1; y++) {
			for (x = 0; x < grid->x - 1; x++, c++) {
				index = 0;
				if (grid->m_cells[c                              ]) index |= 1;
				if (grid->m_cells[c + grid->x                    ]) index |= 2;
				if (grid->m_cells[c + grid->x +           grid->z]) index |= 4;
				if (grid->m_cells[c +                     grid->z]) index |= 8;
				if (grid->m_cells[c +           grid->y          ]) index |= 16;
				if (grid->m_cells[c + grid->x + grid->y          ]) index |= 32;
				if (grid->m_cells[c + grid->x + grid->y + grid->z]) index |= 64;
				if (grid->m_cells[c +           grid->y + grid->z]) index |= 128;
				
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
						
                        // Normal calculation
                        vec3_sub(v1.position, v0.position, q);
                        vec3_sub(v2.position, v0.position, r);
                        vec3_cross(q, r, norm);
                        memcpy(v0.normal, norm, sizeof(vec3));
                        memcpy(v1.normal, norm, sizeof(vec3));
                        memcpy(v2.normal, norm, sizeof(vec3));
						
						vertices.push_back(v2);
						vertices.push_back(v1);
						vertices.push_back(v0);
					}
				}
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


