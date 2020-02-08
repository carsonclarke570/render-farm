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

#include "conway.h"

GameOfLife::GameOfLife(int x_len, int y_len, int z_len) {
    this->m_current = new Grid(x_len, y_len, z_len);
    this->m_next = new Grid(x_len, y_len, z_len);
}


GameOfLife::~GameOfLife() {
    delete this->m_current;
    delete this->m_next;
}  

void GameOfLife::populate(int percent) {
    for (int x = 0; x < this->m_next->x_len; x++) {
        for (int y = 0; y < this->m_next->y_len; y++) {
            for (int z = 0; z < this->m_next->z_len; z++) {
                this->m_current->m_cells[x][y][z] = ((rand() % 100) < percent);
            }
        }
    }
}

void GameOfLife::step() {
    int c;
    for (int x = 0; x < this->m_next->x_len; x++) {
        for (int y = 0; y < this->m_next->y_len; y++) {
            for (int z = 0; z < this->m_next->z_len; z++) {
                c = count_neigbors(x, y, z);
                if (this->m_current->m_cells[x][y][z]) { // Alive
                    this->m_next->m_cells[x][y][z] = (c >= CONWAY_SURVIVE_LOW && c <= CONWAY_SURVIVE_HIGH);
                } else {
                    this->m_next->m_cells[x][y][z] = (c >= CONWAY_BIRTH_LOW && c <= CONWAY_BIRTH_HIGH);
                }
            }
        }
    }

    Grid* temp = this->m_next;
    m_next = m_current;
    m_current = temp;
}


// Private helper functions

int GameOfLife::count_neigbors(int x, int y, int z) {
    int count = 0;
    int in, jn, kn;
    for (int i = x - 1; i <= x + 1; i++) {
        for (int j = y - 1; j <= y + 1; j++) {
            for (int k = z - 1; k <= z + 1; k++) {
                if (i == x && j == y && k == z) continue;
                in = wrap_bounds(i, this->m_next->x_len);
                jn = wrap_bounds(j, this->m_next->y_len);
                kn = wrap_bounds(k, this->m_next->z_len);
                if (this->m_current->m_cells[in][jn][kn]) {
                    count++;
                }
            }
        }
    }
    return count;
}

int GameOfLife::wrap_bounds(int n, int max) {
    if (n == max) {
        return 0;
    } 
    if (n == -1) {
        return max - 1;
    }
    return n;
} 