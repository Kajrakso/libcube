#ifndef _SOLVERS_H_
#define _SOLVERS_H_

#include "../core/cube.h"
#include "../core/move.h"
#include "../core/tables.h"

/* Solve a cube. Returns an array of moves */
int* cube_solvers_solve_cube(cube_t* cube, size_t* solution_length);


#endif // _SOLVERS_H_
