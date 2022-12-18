#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "interface.h"
#include "style.h"

static void interface_tentativas(size_t tentativas) {
	printf("|@----------- %s%lu° tentativa%s -----------@|\n", PURPLE, tentativas, RESET);
}

void draw_type_scene(map_t map, commands_t commands, player_t player, size_t trys) {
	system("clear||cls");
	interface_tentativas(trys);
	draw_map(map);
	draw_commands(commands);
	draw_player_direction(player);
	draw_input_info();
}

void draw_moving(map_t map, commands_t commands, execution_commands_t command, player_t player) {
	system("clear||cls");
	draw_map(map);
	draw_commands(commands);
	draw_player_direction(player);
	draw_command_info(command);
}

void draw_won_phase(void) {
	system("clear||cls");
	printf("|@--------------- %sParabens, você passou de fase%s -----------------@|\n", GREEN, RESET);
	sleep(2);
	system("clear||cls");
}

void draw_lost_phase(void) {
	system("clear||cls");
	printf("|@--------------- %sInfelizmente, você não passou de fase%s -----------------@|\n", RED, RESET);
	sleep(2);
	system("clear||cls");
}

void draw_lost(void) {
	system("clear||cls");
	printf("|@------------- %sVoce perdeu o jogo%s -------------@|\n", RED, RESET);
	sleep(2);
	system("clear||cls");
	exit(EXIT_FAILURE);
}

void draw_won(void) {
	system("clear||cls");
	printf("|@------------- %sVoce ganhou o jogo%s -------------@|\n", GREEN, RESET);
	sleep(2);
	system("clear||cls");
}
