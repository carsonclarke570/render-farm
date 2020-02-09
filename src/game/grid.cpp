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


Grid::Grid(int x, int y, int z) {
    this->m_cells = new uint8_t[x * y * z];
    this->x = x;
    this->y = y;
    this->z = z;
}


Grid::~Grid() {
    delete[] this->m_cells;
    this->x = 0;
    this->y = 0;
    this->z = 0;
}


int Grid::index(int x, int y, int z) {
	return (x * this->y * this->z) + (y * this->z) + z;
}


