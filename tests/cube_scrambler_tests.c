#include <stdint.h>
#include <stdio.h>

#include "../include/libcube.h"
#include "../src/core/_cube.h"
#include "../src/core/_cube_state.h"
#include "criterion/criterion.h"
#include "criterion/redirect.h"

// suites

TestSuite(scramble);

// tests

Test(scramble, handscramble_results_in_legal_cube) {
  cube_tables_generate();

  cube_t cube = cube_scrambler_get_handscrambled_cube();

  cr_assert(cube_valid_eo(&cube));
  cr_assert(cube_valid_co(&cube));
  cr_assert(cube_valid_permutation(&cube));
}

Test(scramble, scramble_results_in_legal_cube) {
  cube_tables_generate();

  cube_t cube = cube_scrambler_get_scrambled_cube();

  cr_assert(cube_valid_eo(&cube));
  cr_assert(cube_valid_co(&cube));
  cr_assert(cube_valid_permutation(&cube));
}
