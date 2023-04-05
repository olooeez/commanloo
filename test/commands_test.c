#include <criterion/criterion.h>

#include "commands.h"

Test(commands, init_commands) {
    commands_t commands = init_commands();

    int count_F = 0, count_E = 0, count_D = 0;

    for (int i = 0; i < COMMANDS_MAXIMUM; i++) {
        for (int j = 0; j < COMMAND_ACTION_MAXIMUM; j++) {
            if (commands.actions[i][j] == F) count_F++;
            if (commands.actions[i][j] == L) count_E++;
            if (commands.actions[i][j] == R) count_D++;
        }
    }

    cr_assert(count_F > 0);
    cr_assert(count_E > 0);
    cr_assert(count_D > 0);
}

Test(commands, store_input) {
    execution_commands_t commands;

    char sequence[100] = "1-2 3-1 1-1";
    store_input(sequence, &commands);

    cr_assert(commands.index == 1);
    cr_assert(commands.times == 2);

    store_input(sequence, &commands);
    cr_assert(commands.index == 3);
    cr_assert(commands.times == 1);

    store_input(sequence, &commands);
    cr_assert(commands.index == 1);
    cr_assert(commands.times == 1);
}
