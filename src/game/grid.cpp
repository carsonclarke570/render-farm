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
#include "grid.h"

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