#ifndef INCLUDE_MAPA_H
#define INCLUDE_MAPA_H

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
