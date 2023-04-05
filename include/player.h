#ifndef INCLUDE_PLAYER_H
#define INCLUDE_PLAYER_H

#include <stdbool.h>

#include "map.h"
#include "queue.h"
#include "heap.h"

#define PLAYER_START_LINE 0
#define PLAYER_START_COLUMN 0

#define OBJECTIVE_LINE 7
#define OBJECTIVE_COLUMN 7

typedef enum {
	LEFT,
	RIGHT,
	UP,
	DOWN,
} direction_t;

typedef enum {
	PLAYER_OK,
	PLAYER_ACHIEVED_OBJECTIVE,
} player_err;

typedef struct {
	direction_t direction;
	int current_line, current_column;
	int next_line, next_column;
} player_t;

player_t init_player(void);
bool player_reached_goal(player_t player);
bool player_arrived_start(player_t player);
void move_player(player_t *player, execution_commands_t command, map_t *map, commands_t commands);
void draw_player_direction(player_t player);

#endif
