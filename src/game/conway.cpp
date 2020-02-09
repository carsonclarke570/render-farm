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


GameOfLife::GameOfLife(int x, int y, int z) {
	this->m_current = new Grid(x, y, z);
	this->m_next = new Grid(x, y, z);
	this->x = x;
	this->y = y;
	this->z = z;
}


GameOfLife::~GameOfLife() {
	delete this->m_current;
	delete this->m_next;
	this->x = 0;
	this->y = 0;
	this->z = 0;
}  


void GameOfLife::populate(int percent) {
	int n = this->x * this->y * this->z;
	int c;
	
	for (c = 0; c < n; c++) {
		this->m_current->m_cells[c] = ((rand() % 100) < percent);
	}
}


void GameOfLife::step() {
	int c, x, y, z;
	int n;
	
	for (c = 0, x = 0; x < this->x; x++) {
		for (y = 0; y < this->y; y++) {
			for (z = 0; z < this->z; z++, c++) {
				n = count_neigbors(x, y, z);
				
				if (this->m_current->m_cells[c]) { // Alive
					this->m_next->m_cells[c] = (n >= CONWAY_SURVIVE_LOW && n <= CONWAY_SURVIVE_HIGH);
				} else {
					this->m_next->m_cells[c] = (n >= CONWAY_BIRTH_LOW && n <= CONWAY_BIRTH_HIGH);
				}
			}
		}
	}

	Grid *temp = this->m_next;
	m_next = m_current;
	m_current = temp;
}


// Private helper functions

int GameOfLife::count_neigbors(int x, int y, int z) {
	int count = -this->m_current->m_cells[this->m_current->index(x, y, z)];
	int i, j, k, in, jn, kn;
	
	for (i = x - 1; i <= x + 1; i++) {
		for (j = y - 1; j <= y + 1; j++) {
			for (k = z - 1; k <= z + 1; k++) {
				wrap_bounds(i, j, k, &in, &jn, &kn);
				count += this->m_current->m_cells[this->m_current->index(in, jn, kn)];
			}
		}
	}
	
	return count;
}


int GameOfLife::wrap_bounds(int x0, int y0, int z0, int *x1, int *y1, int *z1) {
	*x1 = x0 > 0 ? x0 < this->x ? x0 : this->x : 0;
	*y1 = y0 > 0 ? y0 < this->y ? y0 : this->y : 0;
	*z1 = z0 > 0 ? z0 < this->z ? z0 : this->z : 0;
}


