#ifndef INCLUDE_MAPA_H
#define INCLUDE_MAPA_H

#define MINIMUM_OBSTACLES 6
#define MAXIMUM_OBSTACLES 14

#define OBSTACLES_MINIMUM_SIZE 2
#define OBSTACLES_MAXIMUM_SIZE 3

#define OBSTACLES_POSSIBLE_DIRECTIONS 2

#define BOARD_ROWS 8
#define BOARD_COLUMNS 8

typedef enum {
	PAT,
	PLA,
	OBJ,
	OBS,
} board_t;

typedef struct {
	board_t board[BOARD_ROWS][BOARD_COLUMNS];
} map_t;

map_t init_map(void);
void draw_map(map_t map);

#endif
