#ifndef INCLUDE_INTERFACE_H
#define INCLUDE_INTERFACE_H

#include "map.h"
#include "commands.h"
#include "player.h"

void draw_type_scene(map_t map, commands_t commands, player_t player, size_t trys);
void draw_moving(map_t map, commands_t commands, execution_commands_t command, player_t player);
void draw_lost_phase(void);
void draw_won_phase(void);
void draw_lost(void);
void draw_won(void);

#endif
