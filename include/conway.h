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
#ifndef CONWAY_H
#define CONWAY_H

#include <stdlib.h>
#include <stdio.h>

#include "grid.h"


#define CONWAY_SURVIVE_LOW  (0)
#define CONWAY_SURVIVE_HIGH (26)
#define CONWAY_BIRTH_LOW    (1)
#define CONWAY_BIRTH_HIGH   (26)

class GameOfLife {
private:
    Grid *m_next;

    int count_neigbors(int x, int y, int z);
    void wrap_bounds(int x0, int y0, int z0, int *x1, int *y1, int *z1);
public:
    Grid *m_current;
    int x;
	int y;
	int z;

    /**
     * Construct a new Game Of Life object
     * 
     * @param x_len     Length of the x dimension
     * @param y_len     Length of the y dimension
     * @param z_len     Length of the z dimension
     */
    GameOfLife(int x, int y, int z);
    
    /**
     * Destroy the Game Of Life object
     */
    ~GameOfLife();

    /**
     *  Creates a new Grid object and populates it with living cells. 
     * 
     *  @param percent   Percent of the cells to fill in the range [0:100]  
     */
    void populate(int percent);

    /**
     *  Applies the given rule represented by:
     *      [A A A A B B B B C C C C D D D D]
     *      - Live cells remain living if they have between A and B neighbors
     *      - Dead cells become alive  if they have between C and D neighnors
     * 
     *  @param rule     Rule for the system
     */
    void step();
};


#endif


