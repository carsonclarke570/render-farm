/*
	Version 2012-03-09
	
	A speed-improved simplex noise algorithm for 2D, 3D and 4D in Java.
	
	Based on example code by Stefan Gustavson (stegu@itn.liu.se).
	Optimisations by Peter Eastman (peastman@drizzle.stanford.edu).
	
	This code was placed in the public domain by its original author,
	Stefan Gustavson. You may use it as you see fit, but
	attribution is appreciated.
	
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	
	Copyright 2020 Wesley Dahar
	
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
#include "simplex_noise.h"
#include "mcubes.h"


/**
 * 
 */
void simplex_noise(Grid *grid) {
	
	// To remove the need for index wrapping, double the permutation table length
	short p[512] = {
		151,160,137,91,90,15,
		131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
		190,6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
		88,237,149,56,87,174,20,125,136,171,168,68,175,74,165,71,134,139,48,27,166,
		77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
		102,143,54,65,25,63,161,1,216,80,73,209,76,132,187,208,89,18,169,200,196,
		135,130,116,188,159,86,164,100,109,198,173,186,3,64,52,217,226,250,124,123,
		5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
		223,183,170,213,119,248,152,2,44,154,163,70,221,153,101,155,167,43,172,9,
		129,22,39,253,19,98,108,110,79,113,224,232,178,185,112,104,218,246,97,228,
		251,34,242,193,238,210,144,12,191,179,162,241,81,51,145,235,249,14,239,107,
		49,192,214,31,181,199,106,157,184,84,204,176,115,121,50,45,127,4,150,254,
		138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180
	};
	short perm[512];
	short permMod12[512];
	for (int i = 0; i < 512; i++) {
		perm[i] = p[i & 0xFF];
		permMod12[i] = (short) (perm[i] % 12);
	}
	
	double t0, t1, t2, t3;
	double n0, n1, n2, n3;
	double s;
	double t;
	double x0, y0, z0;
	double x1, y1, z1;
	double x2, y2, z2;
	double x3, y3, z3;
	double grad[12][3] = {
		{  1,  1,  0},
		{ -1,  1,  0},
		{  1, -1,  0},
		{ -1, -1,  0},
		{  1,  0,  1},
		{ -1,  0,  1},
		{  1,  0, -1},
		{ -1,  0, -1},
		{  0,  1,  1},
		{  0, -1,  1},
		{  0,  1, -1},
		{  0, -1, -1}
	};
	int gi0, gi1, gi2, gi3;
	int x, y, z;
	int i, j, k;
	int ii, jj, kk;
	int *ijk12;
	int ijk12s[8][6] = {
		{0, 0, 1, 0, 1, 1}, // zyx
		{0, 1, 0, 0, 1, 1}, // yzx
		{0, 0, 0, 0, 0, 0}, // invalid
		{0, 1, 0, 1, 1, 0}, // yxz
		{0, 0, 1, 1, 0, 1}, // zxy
		{0, 0, 0, 0, 0, 0}, // invalid
		{1, 0, 0, 1, 0, 1}, // xzy
		{1, 0, 0, 1, 1, 0}  // xyz
	};
	int c;
    
	for (c = 0, x = 0; x < grid->x; x++) {
	for (y = 0; y < grid->y; y++) {
	for (z = 0; z < grid->z; z++, c++) {
		
		// Skew the input space to determine which simplex cell we're in
		
		// Very nice and simple skew factor for 3D
		s = (x + y + z) / 3.0;
		ii = (int) (x + s);
		i = i < ii ? ii - 1 : ii;
		jj = (int) (y + s);
		j = j < jj ? jj - 1 : jj;
		kk = (int) (z + s);
		k = k < kk ? kk - 1 : kk;
		t = (i + j + k) / 6.0;
		
		// Unskew the cell origin back to (x,y,z) space
		// The x,y,z distances from the cell origin
		x0 = x - i + t;
		y0 = y - j + t;
		z0 = z - k + t;
		
		// For the 3D case, the simplex shape is a slightly irregular tetrahedron.
		// Determine which simplex we are in.
		
		// Offsets for second and third corners of simplex in (i,j,k) coords.
		ijk12 = ijk12s[
			(x0 >= y0) << 2 |
			(x0 >= z0) << 1 |
			(y0 >= z0)
		];
		
		// A step of (1,0,0) in (i,j,k) means a step of (1-c,-c,-c) in (x,y,z),
		// a step of (0,1,0) in (i,j,k) means a step of (-c,1-c,-c) in (x,y,z), and
		// a step of (0,0,1) in (i,j,k) means a step of (-c,-c,1-c) in (x,y,z), where
		
		// Offsets for second corner in (x,y,z) coords.
		x1 = x0 - ijk12[0] + (1.0 / 6.0);
		y1 = y0 - ijk12[1] + (1.0 / 6.0);
		z1 = z0 - ijk12[2] + (1.0 / 6.0);
		
		// Offsets for third corner in (x,y,z) coords.
		x2 = x0 - ijk12[3] + (1.0 / 3.0);
		y2 = y0 - ijk12[4] + (1.0 / 3.0);
		z2 = z0 - ijk12[5] + (1.0 / 3.0);
		
		// Offsets for last corner in (x,y,z) coords.
		x3 = x0 - 0.5;
		y3 = y0 - 0.5;
		z3 = z0 - 0.5;
		
		// Work out the hashed gradient indices of the four simplex corners
		ii = i & 0xFF;
		jj = j & 0xFF;
		kk = k & 0xFF;
		gi0 = permMod12[ii + perm[jj + perm[kk]]];
		gi1 = permMod12[ii + ijk12[0] + perm[jj + ijk12[1] + perm[kk + ijk12[2]]]];
		gi2 = permMod12[ii + ijk12[3] + perm[jj + ijk12[4] + perm[kk + ijk12[5]]]];
		gi3 = permMod12[ii + 1 + perm[jj + 1 + perm[kk + 1]]];
		
		// Calculate the contribution from the four corners
		t0 = 0.5 - (x0 * x0) - (y0 * y0) - (z0 * z0);
		t1 = 0.5 - (x1 * x1) - (y1 * y1) - (z1 * z1);
		t2 = 0.5 - (x2 * x2) - (y2 * y2) - (z2 * z2);
		t3 = 0.5 - (x3 * x3) - (y3 * y3) - (z3 * z3);
		
		if (t0 < 0) {
			n0 = 0.0;
		} else {
			t0 *= t0;
			n0 = t0 * t0 * (
				(grad[gi0][0] * x0) +
				(grad[gi0][1] * y0) +
				(grad[gi0][2] * z0)
			);
		}
		
		if (t1 < 0) {
			n1 = 0.0;
		} else {
			t1 *= t1;
			n1 = t1 * t1 * (
				(grad[gi1][0] * x1) +
				(grad[gi1][1] * y1) +
				(grad[gi1][2] * z1)
			);
		}
		
		if (t2 < 0) {
			n2 = 0.0;
		} else {
			t2 *= t2;
			n2 = t2 * t2 * (
				(grad[gi2][0] * x2) +
				(grad[gi2][1] * y2) +
				(grad[gi2][2] * z2)
			);
		}
		
		if (t3 < 0) {
			n3 = 0.0;
		} else {
			t3 *= t3;
			n3 = t3 * t3 * (
				(grad[gi3][0] * x3) +
				(grad[gi3][1] * y3) +
				(grad[gi3][2] * z3)
			);
		}
		
		// Add contributions from each corner to get the final noise value.
		// The result is scaled to stay just inside [-1,1]
		grid->m_cells[c] = (32.0 * (n0 + n1 + n2 + n3)) > 0;
	}}}
}
