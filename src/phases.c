#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "commands.h"
#include "map.h"

#include "queue.h"
#include "heap.h"
#include "player.h"
#include "interface.h"
#include "phases.h"

static bool phase_1(void) {
	size_t trys = 1;

	char sequence[BUFSIZ];

	map_t map, map_reset;
	player_t player;
	commands_t commands;
	execution_commands_t command;

	map = init_map();
	map_reset = map;

	while (true) {
		map = map_reset;

		player = init_player();
		commands = init_commands();

		queue_t *queue = init_queue();

		draw_type_scene(map, commands, player, trys);
		(void) *fgets(sequence, BUFSIZ, stdin);

		while (strlen(sequence) != 0) {
			store_input(sequence, &command);
			printf("%ld, %ld\n", command.index, command.times);
			insert_queue(queue, command);
		}

		while (!is_queue_empty(queue)) {
			consult_queue(queue, &command);
			move_player(&player, command, &map, commands);
			remove_queue(queue);

			draw_moving(map, commands, command, player);
		}

		if (player_reached_goal(player)) {
			draw_won_phase();
			break;
		}

		draw_lost_phase();
		trys++;

		if (trys == 4) return 0;

		end_queue(queue);
	}

	return 1;
}

static bool phase_2(void) {
	size_t trys = 1;

	char sequence[BUFSIZ];

	map_t map, map_reset;
	player_t player;
	commands_t commands;
	execution_commands_t command;

	map = init_map();
	map_reset = map;

	while (true) {
		map = map_reset;

		player = init_player();
		commands = init_commands();

		heap_t *heap = init_heap();

		draw_type_scene(map, commands, player, trys);
		(void) *fgets(sequence, BUFSIZ, stdin);

		while (strlen(sequence) != 0) {
			store_input(sequence, &command);
			insert_heap(heap, command);
		}

		while (!is_heap_empty(heap)) {
			consult_heap(heap, &command);
			move_player(&player, command, &map, commands);
			remove_heap(heap);

			draw_moving(map, commands, command, player);
		}

		if (player_reached_goal(player)) {
			draw_won_phase();
			break;
		}

		draw_lost_phase();
		trys++;

		if (trys == 4) return 0;

		end_heap(heap);
	}

	return 1;
}

static bool phase_3(void) {
	size_t trys = 1;

	char sequence[BUFSIZ];

	map_t map, map_reset;
	player_t player, player_reset;
	commands_t commands;
	execution_commands_t command;

	map = init_map();
	map_reset = map;

	heap_t *out;

	while (true) {
		map = map_reset;

		player = init_player();
		commands = init_commands();

		queue_t *in = init_queue();

		draw_type_scene(map, commands, player, trys);
		(void) *fgets(sequence, BUFSIZ, stdin);

		while (strlen(sequence) != 0) {
			store_input(sequence, &command);
			insert_queue(in, command);
		}

		while (!is_queue_empty(in)) {
			consult_queue(in, &command);
			move_player(&player, command, &map, commands);
			remove_queue(in);

			draw_moving(map, commands, command, player);
		}

		if (player_reached_goal(player)) {
			map_reset = map;
			player_reset = player;

			while (true) {
				map = map_reset;
				player = player_reset;

				out = init_heap();
				commands = init_commands();

				draw_type_scene(map, commands, player, trys);
				(void) *fgets(sequence, BUFSIZ, stdin);

				while (strlen(sequence) != 0) {
					store_input(sequence, &command);
					insert_heap(out, command);
				}

				while (!is_heap_empty(out)) {
					consult_heap(out, &command);
					move_player(&player, command, &map, commands);
					remove_heap(out);

					draw_moving(map, commands, command, player);
				}

				if (player_arrived_start(player)) {
					draw_won_phase();
					return 1;
				}

				draw_lost_phase();
				trys++;

				if (trys == 4) return 0;

				end_heap(out);
			}
		}

		draw_lost_phase();
		trys++;

		if (trys == 4) return 0;

		end_queue(in);
	}

	return 1;
}

static phases_t defined_phases[PHASES_QUANTITY] = {
	{phase_1, "First phase (using queues)", "Get to the objective (O) using queue"},
	{phase_2, "Second phase (using heaps)", "Get to the objective (O) using heaps"},
	{phase_3, "Third phase (Using queues/heaps)", "Get to the objective (O) using queue and go back to the beginning using the heap"},
};

void init_phase(phases_t *phase) {
	size_t i;

	for (i = 0; i < PHASES_QUANTITY; i++) {
		phase[i] = defined_phases[i];
	}
}

void draw_phase_data(phases_t phase) {
	printf("> %s\n", phase.name);
	printf("> Mission: %s\n", phase.info);
}
