#include <criterion/criterion.h>

#include "player.h"

Test(player, init_player) {
    player_t player = init_player();
    cr_assert_eq(player.current_column, PLAYER_START_COLUMN);
    cr_assert_eq(player.current_line, PLAYER_START_LINE);
    cr_assert_eq(player.direction, RIGHT);
}

Test(player_reached_goal, player_has_reached_goal) {
    player_t player = { .current_line = OBJECTIVE_LINE, .current_column = OBJECTIVE_COLUMN };

    bool result = player_reached_goal(player);
    cr_assert_eq(result, true);
}

Test(player_reached_goal, player_has_not_reached_goal_yet) {
    player_t player = { .current_line = OBJECTIVE_LINE - 1, .current_column = OBJECTIVE_COLUMN - 1 };

    bool result = player_reached_goal(player);
    cr_assert_eq(result, false);
}

Test(player_arrived_start, player_not_at_start) {
    player_t player = {RIGHT, 1, 1, 0, 0};

    bool result = player_arrived_start(player);
    cr_assert_not(result);
}

Test(player_arrived_start, player_at_start) {
    player_t player = {RIGHT, PLAYER_START_LINE, PLAYER_START_COLUMN, 0, 0};

    bool result = player_arrived_start(player);
    cr_assert(result);
}
