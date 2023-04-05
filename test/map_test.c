#include <criterion/criterion.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "map.h"

Test(map, init_map) {
    map_t map = init_map();

    bool player_found = false;
    bool objective_found = false;
    for (size_t i = 0; i < BOARD_ROWS; i++) {
        for (size_t j = 0; j < BOARD_COLUMNS; j++) {
            if (map.board[i][j] == PLA) {
                player_found = true;
            } else if (map.board[i][j] == OBJ) {
                objective_found = true;
            }
        }
    }

    cr_assert(player_found);
    cr_assert(objective_found);

    size_t obstacle_count = 0;
    for (size_t i = 0; i < BOARD_ROWS; i++) {
        for (size_t j = 0; j < BOARD_COLUMNS; j++) {
            if (map.board[i][j] == OBS) {
                obstacle_count++;
            }
        }
    }

    cr_assert(obstacle_count >= MINIMUM_OBSTACLES);
    cr_assert(obstacle_count <= MAXIMUM_OBSTACLES);
}
