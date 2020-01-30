/*
    Copyright 2019 Carson Clarke-Magrab

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

#ifndef MARCHING_CUBES_H
#define MARCHING_CUBES_H

#include "mesh.h"

struct Grid {
    uint8_t*** m_cells;
    int x_len, y_len, z_len;

    /**
     *  Constructs a new Grid struct
     * 
     *  @param xn   Size of the x dimension
     *  @param yn   Size of the y dimension
     *  @param zn   Size of the z dimension
     */
    Grid(int xn, int yn, int zn);

    /**
     *  Destroys a Grid struct
     */
    ~Grid();
};

class MarchingCubeGenerator {
public:
    /**
     *  Uses the marching cube algorithm to convert a three-dimensional array
     *  of boolean cells into a mesh.
     * 
     *  @params cells   A three-dimensional array of cells
     *  @params n       The length of the height, width and length of the array
     * 
     *  @return A newly allocated mesh object generated from marching cubes.
     */
    static Mesh* generate(Grid* cells, int n);
};

#endif