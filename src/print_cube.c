#include "print_cube.h"

// todo: where to put these?

static const char* corners_str_repr[NCORNERS] = {
  "ULB", "UBR", "URF", "UFL",
  "DLF", "DFR", "DRB", "DBL",
};

static const char* edges_str_repr[NEDGES] = {
    "UB", "UR", "UF", "UL",
    "DF", "DR", "DB", "DL",
    "BL", "BR", "FR", "FL",
};

// todo: ugly function. need to rewrite.
void print_cube(cube_t* cube){
  char* cube_str_pattern =
    "      -------\n"
    "      |%c %c %c|\n"
    "      |%c   %c|\n"
    "      |%c %c %c|\n"
    "------------------------\n"
    "|%c %c %c|%c %c %c|%c %c %c|%c %c %c|\n"
    "|%c   %c|%c   %c|%c   %c|%c   %c|\n"
    "|%c %c %c|%c %c %c|%c %c %c|%c %c %c|\n"
    "------------------------\n"
    "      |%c %c %c|\n"
    "      |%c   %c|\n"
    "      |%c %c %c|\n"
    "      -------\n";
  char cs[NCORNERS][3];
  char es[NEDGES][2];

  for (int i = 0; i < NCORNERS; i++){
    int c;

    for (int k = 0; k < NCORNERS; k++){
      if (extract_corner_perm(cube->corners[k]) == i) c = k;
    }
    
    int co = extract_corner_orien(cube->corners[c], UD);

    cs[i][0] = corners_str_repr[c][(0 + 3 - co) % 3];
    cs[i][1] = corners_str_repr[c][(1 + 3 - co) % 3];
    cs[i][2] = corners_str_repr[c][(2 + 3 - co) % 3];
  }

  for (int i = 0; i < NEDGES; i++){
    int e;

    for (int k = 0; k < NEDGES; k++){
      if (extract_edge_perm(cube->edges[k]) == i) e = k;
    }

    for (int j = 0; j < 2; j++){
      es[i][j] = edges_str_repr[e][(extract_edge_orien(cube->edges[e], FB) + j) % 2];
    }
  }

  printf(cube_str_pattern,
                                   cs[0][0], es[0][0], cs[1][0],
                                   es[3][0],           es[1][0],
                                   cs[3][0], es[2][0], cs[2][0],
    cs[0][1], es[3][1], cs[3][2],  cs[3][1], es[2][1], cs[2][2],  cs[2][1], es[1][1], cs[1][2], cs[1][1], es[0][1], cs[0][2],
    es[8][1],           es[11][1], es[11][0],          es[10][0], es[10][1],          es[9][1], es[9][0],           es[8][0],
    cs[7][2], es[7][1], cs[4][1],  cs[4][2], es[4][1], cs[5][1],  cs[5][2], es[5][1], cs[6][1], cs[6][2], es[6][1], cs[7][1],
                                   cs[4][0], es[4][0], cs[5][0],
                                   es[7][0],           es[5][0],
                                   cs[7][0], es[6][0], cs[6][0]
  );
}


int main(int argc, char** argv){
  // gen mtables
  initialize_move_tables();
  gen_move_tables();

  // do a T-perm: R U R' U' R' F R2 U' R' U' R U R' F'
  cube_t cube = cube_create_new_cube();
  printf("initial state:\n");
  print_cube(&cube);

  make_move(&cube, 3*R + 0);
  make_move(&cube, 3*U + 0);
  make_move(&cube, 3*R + 2);
  make_move(&cube, 3*U + 2);
  make_move(&cube, 3*R + 2);
  make_move(&cube, 3*F + 0);
  make_move(&cube, 3*R + 1);
  make_move(&cube, 3*U + 2);
  make_move(&cube, 3*R + 2);
  make_move(&cube, 3*U + 2);
  make_move(&cube, 3*R + 0);
  make_move(&cube, 3*U + 0);
  make_move(&cube, 3*R + 2);
  make_move(&cube, 3*F + 2);
  
  printf("T-perm:\n");
  print_cube(&cube);
}
