#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "interface.h"

static void interface_tentativas(size_t tentativas) {
	printf("> You are on your %ldnd attempt.\n", tentativas);
}

void draw_type_scene(map_t map, commands_t commands, player_t player, size_t trys) {
	interface_tentativas(trys);
	draw_map(map);
	draw_commands(commands);
	draw_player_direction(player);
	draw_input_info();
}

void draw_moving(map_t map, commands_t commands, execution_commands_t command, player_t player) {
	draw_map(map);
	draw_commands(commands);
	draw_player_direction(player);
	draw_command_info(command);
}

void draw_won_phase(void) {
	puts("> Congratulations, you passed the stage.");
}

void draw_lost_phase(void) {
	puts("> Unfortunately you didn't pass the stage.");
}

void draw_lost(void) {
	puts("You lost the game!");
	exit(EXIT_FAILURE);
}

void draw_won(void) {
	puts("You won the game");
}
