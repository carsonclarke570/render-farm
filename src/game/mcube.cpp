#include "mcubes.h"

#include <vector>
#include "tables.h"

Grid::Grid(int xn, int yn, int zn) {
    this->x_len = xn;
    this->y_len = yn;
    this->z_len = zn;

    this->m_cells = new uint8_t**[xn];
    for (int x = 0; x < xn; x++) {
        this->m_cells[x] = new uint8_t*[yn];
        for (int y = 0; y < yn; y++) {
            this->m_cells[x][y] = new uint8_t[zn];
        }
    }
}

Grid::~Grid() {
    for (int x = 0; x < this->x_len; x++) {
        for (int y = 0; y < this->y_len; y++) {
            delete[] this->m_cells[x][y];
        }
        delete[] this->m_cells[x];
    }
    delete[] this->m_cells;
}

Mesh* MarchingCubeGenerator::generate(Grid* cells, int n) {
    
    Mesh* mesh = new Mesh();
    std::vector<Vertex> vertices = std::vector<Vertex>();

    int upper = n - 1;
    int n2 = n * n;
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
                        Vertex v0, v1, v2;

                        v0.position[0] = MC_OFFSETS[MC_TRI_TABLE[index][i]][0] + (float)x;
                        v0.position[1] = MC_OFFSETS[MC_TRI_TABLE[index][i]][1] + (float)y;
                        v0.position[2] = MC_OFFSETS[MC_TRI_TABLE[index][i]][2] + (float)z;

                        v1.position[0] = MC_OFFSETS[MC_TRI_TABLE[index][i+1]][0] + (float)x;
                        v1.position[1] = MC_OFFSETS[MC_TRI_TABLE[index][i+1]][1] + (float)y;
                        v1.position[2] = MC_OFFSETS[MC_TRI_TABLE[index][i+1]][2] + (float)z;

                        v2.position[0] = MC_OFFSETS[MC_TRI_TABLE[index][i+2]][0] + (float)x;
                        v2.position[1] = MC_OFFSETS[MC_TRI_TABLE[index][i+2]][1] + (float)y;
                        v2.position[2] = MC_OFFSETS[MC_TRI_TABLE[index][i+2]][2] + (float)z;

                        vertices.push_back(v0);
                        vertices.push_back(v1);
                        vertices.push_back(v2);
                    }
                }
            }
        }
    }

    mesh_create(mesh, vertices.data(), vertices.size(), nullptr, 0);
    return mesh;
}