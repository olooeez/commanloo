#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "map.h"
#include "style.h"

#define MINIMUM_OBSTACLES 6
#define MAXIMUM_OBSTACLES 8

#define OBSTACLES_MINIMUM_SIZE 2
#define OBSTACLES_MAXIMUM_SIZE 3

#define OBSTACLES_POSSIBLE_DIRECTIONS 2

board_t boards[][BOARD_ROWS][BOARD_COLUMNS] = {
	{
		{PLA, PAT, PAT, PAT, PAT, PAT, PAT, PAT},
		{PAT, PAT, PAT, PAT, PAT, PAT, PAT, PAT},
		{OBS, OBS, PAT, OBS, OBS, PAT, PAT, OBS},
		{PAT, PAT, PAT, PAT, PAT, PAT, PAT, OBS},
		{PAT, OBS, PAT, PAT, PAT, PAT, OBS, PAT},
		{PAT, OBS, PAT, OBS, OBS, PAT, OBS, PAT},
		{PAT, PAT, PAT, PAT, PAT, PAT, PAT, PAT},
		{PAT, PAT, PAT, OBS, OBS, PAT, PAT, OBJ}
	},
	{
		{PLA, PAT, PAT, PAT, PAT, PAT, PAT, PAT},
		{PAT, PAT, PAT, PAT, PAT, OBS, PAT, PAT},
		{PAT, PAT, PAT, PAT, PAT, OBS, PAT, PAT},
		{PAT, PAT, OBS, OBS, PAT, OBS, PAT, PAT},
		{PAT, PAT, PAT, PAT, PAT, PAT, PAT, PAT},
		{PAT, PAT, PAT, PAT, OBS, OBS, PAT, PAT},
		{PAT, OBS, OBS, PAT, PAT, PAT, PAT, PAT},
		{PAT, PAT, PAT, PAT, PAT, PAT, PAT, OBJ}
	}
};

map_t init_map(void) {
	size_t board_size, random_board, i, j;

	map_t map;

	srand(time(NULL));

	board_size = (sizeof(boards) / sizeof(board_t)) / (BOARD_ROWS *BOARD_COLUMNS);
	random_board = (rand() % board_size);

	for (i = 0; i < BOARD_ROWS; i++) {
		for (j = 0; j < BOARD_COLUMNS; j++) {
			map.board[i][j] = boards[random_board][i][j];
		}
	}

	return map;
}

void draw_map(map_t map) {
	size_t i, j;

	printf("\n|@--------- %sTabuleiro%s ---------@|\n", RED, RESET);
	for (i = 0; i < BOARD_ROWS; i++) {
		puts("|---|---|---|---|---|---|---|---|");

		for (j = 0; j < BOARD_COLUMNS; j++) {
			switch (map.board[i][j]) {
			case PLA:
				printf("| %sP%s ", PURPLE, RESET);
				break;
			case OBJ:
				printf("| %sO%s ", GREEN, RESET);
				break;
			case OBS:
				printf("| %sX%s ", RED, RESET);
				break;
			case PAT:
				printf("|   ");
			}
		}

		printf("|\n");
	}

	puts("|---|---|---|---|---|---|---|---|");
}
