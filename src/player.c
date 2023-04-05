#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "player.h"

static void player_update(player_t *player, action_t direction) {
	switch (direction) {
	case R:
		if (player->direction == LEFT) player->direction = UP;
		else if (player->direction == RIGHT) player->direction = DOWN;
		else if (player->direction == UP) player->direction = RIGHT;
		else if (player->direction == DOWN) player->direction = LEFT;

		break;
	case L:
		if (player->direction == LEFT) player->direction = DOWN;
		else if (player->direction == RIGHT) player->direction = UP;
		else if (player->direction == UP) player->direction = LEFT;
		else if (player->direction == DOWN) player->direction = RIGHT;

		break;
	case F:
		if (player->direction == UP) player->next_line--;
		else if (player->direction == DOWN) player->next_line++;
		else if (player->direction == LEFT) player->next_column--;
		else if (player->direction == RIGHT) player->next_column++;

		break;
	case N:
		break;
	}
}

static void player_move(player_t *player, map_t *mapa) {
	if (mapa->board[player->next_line][player->next_column] == OBS) {
		player->next_line = player->current_line;
		player->next_column = player->current_column;
	}

	if (player->next_line >= BOARD_ROWS) {
		player->next_line = BOARD_ROWS - 1;
	} else if (player->next_line < 0) {
		player->next_line = 0;
	}

	if (player->next_column >= BOARD_COLUMNS) {
		player->next_column = BOARD_COLUMNS - 1;
	} else if (player->next_column < 0) {
		player->next_column = 0;
	}

	mapa->board[player->current_line][player->current_column] = PAT;
	mapa->board[player->next_line][player->next_column] = PLA;

	player->current_line = player->next_line;
	player->current_column = player->next_column;
}

player_t init_player(void) {
	player_t player;

	player.current_column = PLAYER_START_COLUMN;
	player.current_line = PLAYER_START_LINE;
	player.direction = RIGHT;

	return player;
}

bool player_reached_goal(player_t player) {
	if (player.current_line >= OBJECTIVE_LINE && player.current_column >= OBJECTIVE_COLUMN) {
		return 1;
	}

	return 0;
}

bool player_arrived_start(player_t player) {
	if (player.current_line == PLAYER_START_LINE && player.current_column == PLAYER_START_COLUMN) {
		return 1;
	}

	return 0;
}

void move_player(player_t *player, execution_commands_t command, map_t *map, commands_t commands) {
	size_t i, j;

	player->next_line = player->current_line;
	player->next_column = player->current_column;

	action_t action;

	for (i = 0; i < command.times; i++) {
		for (j = 0; j < COMMAND_ACTION_MAXIMUM; j++) {
			action = commands.actions[command.index-1][j];

			player_update(player, action);
			player_move(player, map);
		}
	}
}

void draw_player_direction(player_t player) {
	char direction_art[] = "▼";

	switch (player.direction) {
	case RIGHT:
		strcpy(direction_art, "▶");
		break;
	case LEFT:
		strcpy(direction_art, "◀");
		break;
	case UP:
		strcpy(direction_art, "▲");
		break;
	case DOWN:
		break;
	}

	printf("> The player is headed to %s\n", direction_art);
}
