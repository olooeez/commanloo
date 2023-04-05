#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#include "commands.h"

action_t actions[][COMMANDS_MAXIMUM][COMMAND_ACTION_MAXIMUM] = {
	{
		{F, F, F},
		{L, F},
		{R, F},
		{F, L}
	},
	{
		{F, F, F, F},
		{L, R, F},
		{F, R},
		{L, F},
	},
	{
		{F, R},
		{R, F},
		{F, F, L, R},
	},
	{
		{F, F, R},
		{F, F, L},
		{R, L, F},
		{L, R, F},
	}
};

commands_t init_commands(void) {
	commands_t commands;
	size_t tamanho_comandos, acao_aleatoria, i, j;

	srand(time(NULL));

	tamanho_comandos = (sizeof(actions) / sizeof(action_t)) / (COMMANDS_MAXIMUM * COMMAND_ACTION_MAXIMUM);
	acao_aleatoria = (rand() % tamanho_comandos);

	for (i = 0; i < COMMANDS_MAXIMUM; i++) {
		for (j = 0; j < COMMAND_ACTION_MAXIMUM; j++) {
			commands.actions[i][j] = actions[acao_aleatoria][i][j];
		}
	}

	return commands;
}

void store_input(char *sequence, execution_commands_t *commands) {
	const char delimiter = ' ';
	char *new_sequence;

	int sequence_size = strlen(sequence), info_size = 3;

	if (sequence[sequence_size-1] == '\n' || sequence[sequence_size-1] == ' ') {
		sequence[sequence_size-1] = '\n';
		sequence_size--;
	}

	commands->index= sequence[0] - '0';
	commands->times = sequence[2] - '0';

	if (sequence_size == info_size) {
		strcpy(sequence, "");
		return;
	}

	new_sequence = strchr(sequence, delimiter);

	strcpy(sequence, new_sequence);
	memmove(sequence, sequence+1, strlen(sequence));
}

void draw_commands(commands_t commands) {
	puts("> List of commands:");

	for (int i = 0; i < COMMANDS_MAXIMUM; i++) {
		puts("|--------------------|");

		if (commands.actions[i][0] != N) printf("%d -> ", i + 1);

		for (int j = 0; j < COMMAND_ACTION_MAXIMUM; j++) {
			switch(commands.actions[i][j]) {
			case F:
				printf("| F ");
				break;
			case L:
				printf("| E ");
				break;
			case R:
				printf("| D ");
				break;
			case N:
				continue;
			}
		}

		if (commands.actions[i][0] != N) printf("|\n");
	}

	puts("|--------------------|");
}

void draw_command_info(execution_commands_t command) {
	puts("> Movement information:");
	printf("> Command: %ld\n", command.index);
	printf("> Times: %ld\n", command.times);
}

void draw_input_info(void) {
	puts("> It should be written in the model: number_command-times_executed");
	printf("• Enter the command sequence (e.g 1-2 3-1 1-1): ");
}
