#include "../include/libcube.h"
#include "../src/utils.h"
#include "../src/_cube.h"
#include "criterion/criterion.h"
#include "criterion/redirect.h"
#include <stdint.h>
#include <stdio.h>

// suites

TestSuite(cube_info);

// tests

Test(cube_info, is_solved){
    cube_t cube = cube_create_new_cube();
    cr_assert(cube_state_is_solved(&cube));
}

Test(cube_info, is_solved_after_moves){
    cube_t cube = cube_create_new_cube();
    cube_movetables_generate();
    cube_move_apply_move(&cube, R1);
    cube_move_apply_move(&cube, L1);
    cube_move_apply_move(&cube, R3);
    cube_move_apply_move(&cube, L3);
    cr_assert(cube_state_is_solved(&cube));
}

Test(cube_info, is_not_solved_eo){
    cube_t cube = cube_create_new_cube();
    update_edge_orien(&cube.edges[0], 1, 1, 1);
    cr_assert_not(cube_state_is_solved(&cube));
}

Test(cube_info, is_not_solved_co){
    cube_t cube = cube_create_new_cube();
    update_corner_orien(&cube.corners[0], 1, 1, 1);
    cr_assert_not(cube_state_is_solved(&cube));
}

Test(cube_info, is_not_solved_ep){
    cube_t cube = cube_create_new_cube();
    update_edge_perm(&cube.edges[0], 1);
    cr_assert_not(cube_state_is_solved(&cube));
}

Test(cube_info, is_not_solved_cp){
    cube_t cube = cube_create_new_cube();
    update_corner_perm(&cube.corners[0], 1);
    cr_assert_not(cube_state_is_solved(&cube));
}

Test(cube_info, is_dr){
    cube_t cube = cube_create_new_cube();
    cube_movetables_generate();

    cr_assert(cube_state_is_dr(&cube));
    cr_assert(cube_state_is_dr_FB(&cube));
    cr_assert(cube_state_is_dr_LR(&cube));
    cr_assert(cube_state_is_dr_UD(&cube));

    cube_move_apply_move(&cube, R1);
    cube_move_apply_move(&cube, L1);

    cr_assert(cube_state_is_dr(&cube));
    cr_assert_not(cube_state_is_dr_FB(&cube));
    cr_assert(cube_state_is_dr_LR(&cube));
    cr_assert_not(cube_state_is_dr_UD(&cube));

    cube = cube_create_new_cube();
    cube_move_apply_move(&cube, U1);
    cube_move_apply_move(&cube, D1);

    cr_assert(cube_state_is_dr(&cube));
    cr_assert_not(cube_state_is_dr_FB(&cube));
    cr_assert_not(cube_state_is_dr_LR(&cube));
    cr_assert(cube_state_is_dr_UD(&cube));

    cube = cube_create_new_cube();
    cube_move_apply_move(&cube, F1);
    cube_move_apply_move(&cube, B1);

    cr_assert(cube_state_is_dr(&cube));
    cr_assert(cube_state_is_dr_FB(&cube));
    cr_assert_not(cube_state_is_dr_LR(&cube));
    cr_assert_not(cube_state_is_dr_UD(&cube));
}

Test(cube_info, is_eo){
    cube_t cube = cube_create_new_cube();
    cube_movetables_generate();

    cr_assert(cube_state_is_eo(&cube));
    cr_assert(cube_state_is_eo_FB(&cube));
    cr_assert(cube_state_is_eo_LR(&cube));
    cr_assert(cube_state_is_eo_UD(&cube));

    cube_move_apply_move(&cube, R1);
    cube_move_apply_move(&cube, L1);

    cr_assert(cube_state_is_eo(&cube));
    cr_assert(cube_state_is_eo_FB(&cube));
    cr_assert_not(cube_state_is_eo_LR(&cube));
    cr_assert(cube_state_is_eo_UD(&cube));

    cube = cube_create_new_cube();
    cube_move_apply_move(&cube, U1);
    cube_move_apply_move(&cube, D1);

    cr_assert(cube_state_is_eo(&cube));
    cr_assert(cube_state_is_eo_FB(&cube));
    cr_assert(cube_state_is_eo_LR(&cube));
    cr_assert_not(cube_state_is_eo_UD(&cube));

    cube = cube_create_new_cube();
    cube_move_apply_move(&cube, F1);
    cube_move_apply_move(&cube, B1);

    cr_assert(cube_state_is_eo(&cube));
    cr_assert_not(cube_state_is_eo_FB(&cube));
    cr_assert(cube_state_is_eo_LR(&cube));
    cr_assert(cube_state_is_eo_UD(&cube));

    cube = cube_create_new_cube();
    cube_move_apply_move(&cube, L1);
    cube_move_apply_move(&cube, U1);

    cr_assert(cube_state_is_eo(&cube));
    cr_assert(cube_state_is_eo_FB(&cube));
    cr_assert_not(cube_state_is_eo_LR(&cube));
    cr_assert_not(cube_state_is_eo_UD(&cube));
}

Test(cube_info, is_co){
    cube_t cube = cube_create_new_cube();
    cube_movetables_generate();

    cr_assert(cube_state_is_co(&cube));
    cr_assert(cube_state_is_co_FB(&cube));
    cr_assert(cube_state_is_co_LR(&cube));
    cr_assert(cube_state_is_co_UD(&cube));

    cube_move_apply_move(&cube, R1);
    cube_move_apply_move(&cube, L1);

    cr_assert(cube_state_is_co(&cube));
    cr_assert_not(cube_state_is_co_FB(&cube));
    cr_assert(cube_state_is_co_LR(&cube));
    cr_assert_not(cube_state_is_co_UD(&cube));

    cube = cube_create_new_cube();
    cube_move_apply_move(&cube, U1);
    cube_move_apply_move(&cube, D1);

    cr_assert(cube_state_is_co(&cube));
    cr_assert_not(cube_state_is_co_FB(&cube));
    cr_assert_not(cube_state_is_co_LR(&cube));
    cr_assert(cube_state_is_co_UD(&cube));

    cube = cube_create_new_cube();
    cube_move_apply_move(&cube, F1);
    cube_move_apply_move(&cube, B1);

    cr_assert(cube_state_is_co(&cube));
    cr_assert(cube_state_is_co_FB(&cube));
    cr_assert_not(cube_state_is_co_LR(&cube));
    cr_assert_not(cube_state_is_co_UD(&cube));

    cube = cube_create_new_cube();
    cube_move_apply_move(&cube, L1);
    cube_move_apply_move(&cube, U1);

    cr_assert_not(cube_state_is_co(&cube));
    cr_assert_not(cube_state_is_co_FB(&cube));
    cr_assert_not(cube_state_is_co_LR(&cube));
    cr_assert_not(cube_state_is_co_UD(&cube));
}
