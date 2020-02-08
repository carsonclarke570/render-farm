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
#ifndef GRID_H
#define GRID_H

#include <stdint.h>


struct Grid {
    uint8_t *cells;
    int x, y, z;

    /**
     *  Constructs a new Grid struct
     * 
     *  @param x   Size of the x dimension
     *  @param y   Size of the y dimension
     *  @param z   Size of the z dimension
     */
    Grid(int x, int y, int z);

    /**
     *  Destroys a Grid struct
     */
    ~Grid();
};


#endif


