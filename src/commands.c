#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#include "commands.h"
#include "style.h"

action_t actions[][COMMANDS_MAXIMUM][COMMAND_ACTION_MAXIMUM] = {
	{
		{F, F, F},
		{E, F},
		{D, F},
		{F, E}
	},
	{
		{F, F, F, F},
		{E, D, F},
		{F, D},
		{E, F},
	},
	{
		{F, D},
		{D, F},
		{F, F, E, D},
	},
	{
		{F, F, D},
		{F, F, E},
		{D, E, F},
		{E, D, F},
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
	commands->index = sequence[2] - '0';

	if (sequence_size == info_size) {
		strcpy(sequence, "");
		return;
	}

	new_sequence = strchr(sequence, delimiter);

	strcpy(sequence, new_sequence);
	memmove(sequence, sequence+1, strlen(sequence));
}

void draw_commands(commands_t commands) {
	printf("\n|@---- %sComandos%s ----@|\n", BLUE, RESET);

	for (int i = 0; i < COMMANDS_MAXIMUM; i++) {
		puts("|--------------------|");

		if (commands.actions[i][0] != N) printf("%d -> ", i + 1);

		for (int j = 0; j < COMMAND_ACTION_MAXIMUM; j++) {
			switch(commands.actions[i][j]) {
			case F:
				printf("| %sF%s ", GREEN, RESET);
				break;
			case E:
				printf("| %sE%s ", BLUE, RESET);
				break;
			case D:
				printf("| %sD%s ", YELLOW, RESET);
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
	printf("\n|@------------- %sInformações do movimento%s -------------@|\n", CYAN, RESET);
	printf("%s|@----->%s Comandos: %lu\n", GREEN, RESET, command.index);
	printf("%s|@----->%s Numero de vezes executado: %lu\n", YELLOW, RESET, command.times);
	puts("Aperte a tecla enter para continar...");
	getc(stdin);
}

void draw_input_info(void) {
	printf("\n|@---------------------- %sSequencia%s ----------------------@|\n", GREEN, RESET);
	puts("Deve ser escrito no modelo: numero_comando-vezes_executado");
	puts("Exemplo: 1-2 3-1 1-1 ...");
	puts("OBS: A sequencia nao pode ter espacos no inico ou final, somente para separ os comandos");
	printf("\nDigite a sequencia de comandos: ");
}
