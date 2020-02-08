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

Mesh* MarchingCubeGenerator::generate(Grid* cells, int n) {
    
    Mesh* mesh = new Mesh();
    std::vector<Vertex> vertices = std::vector<Vertex>();

    Vertex v0, v1, v2;
    vec3 norm, q, r;

    int upper = n - 1;
    for (int z = 0; z < upper; z++) {
        for (int y = 0; y < upper; y++) {
            for (int x = 0; x < upper; x++) {
                uint8_t index = 0;
                if (cells->m_cells[x][y][z]) index |= 1;
                if (cells->m_cells[x+1][y][z]) index |= 2;
                if (cells->m_cells[x+1][y][z+1]) index |= 4;
                if (cells->m_cells[x][y][z+1]) index |= 8;
                if (cells->m_cells[x][y+1][z]) index |= 16;
                if (cells->m_cells[x+1][y+1][z]) index |= 32;
                if (cells->m_cells[x+1][y+1][z+1]) index |= 64;
                if (cells->m_cells[x][y+1][z+1]) index |= 128;

                if (MC_EDGE_TABLE[index]) {
                    for(int i = 0; MC_TRI_TABLE[index][i] != -1; i += 3) {

                        // Position calculation
                        v0.position[0] = MC_OFFSETS[MC_TRI_TABLE[index][i]][0] + (float)x;
                        v0.position[1] = MC_OFFSETS[MC_TRI_TABLE[index][i]][1] + (float)y;
                        v0.position[2] = MC_OFFSETS[MC_TRI_TABLE[index][i]][2] + (float)z;

                        v1.position[0] = MC_OFFSETS[MC_TRI_TABLE[index][i+1]][0] + (float)x;
                        v1.position[1] = MC_OFFSETS[MC_TRI_TABLE[index][i+1]][1] + (float)y;
                        v1.position[2] = MC_OFFSETS[MC_TRI_TABLE[index][i+1]][2] + (float)z;

                        v2.position[0] = MC_OFFSETS[MC_TRI_TABLE[index][i+2]][0] + (float)x;
                        v2.position[1] = MC_OFFSETS[MC_TRI_TABLE[index][i+2]][1] + (float)y;
                        v2.position[2] = MC_OFFSETS[MC_TRI_TABLE[index][i+2]][2] + (float)z;

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
        }
    }

    mesh_create(mesh, vertices.data(), vertices.size(), nullptr, 0);
    return mesh;
}