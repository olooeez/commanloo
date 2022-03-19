#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#include "comandos.h"
#include "estilo.h"

// Definição de todos os possíveis comandos
acoes_t acoes[][COMANDOS_MAXIMO][COMANDO_ACAO_MAXIMO] = {
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

comandos_t comandos_iniciar(void) {
	comandos_t comandos;
	size_t tamanho_comandos, acao_aleatoria, i, j;

	srand(time(NULL));

	tamanho_comandos = (sizeof(acoes) / sizeof(acoes_t)) / (COMANDOS_MAXIMO * COMANDO_ACAO_MAXIMO);
	acao_aleatoria = (rand() % tamanho_comandos);

	// Vai escrevendo novos comandos aleatorios no `comandos`
	for (i = 0; i < COMANDOS_MAXIMO; i++) {
		for (j = 0; j < COMANDO_ACAO_MAXIMO; j++) {
			comandos.acoes[i][j] = acoes[acao_aleatoria][i][j];
		}
	}

	return comandos;
}

void comandos_formatar_remover(char *sequencia, comandos_execucao_t *comandos_execucao) {
	const char sequencia_delimitador = ' ';
	char *nova_sequencia;

	int sequencia_tamanho = strlen(sequencia), info_parse_tamanho = 3;

	// Remove o `\n` do final, caso tenha
	if (sequencia[sequencia_tamanho-1] == '\n' || sequencia[sequencia_tamanho-1] == ' ') {
		sequencia[sequencia_tamanho-1] = '\n';
		sequencia_tamanho--;
	}

	comandos_execucao->acao_index = sequencia[0] - '0';
	comandos_execucao->acao_vezes = sequencia[2] - '0';

	// Termina caso não de para formatar ainda mais. Exemplo: `1-2`
	if (sequencia_tamanho == info_parse_tamanho) {
		strcpy(sequencia, "");
		return;
	}

	nova_sequencia = strchr(sequencia, sequencia_delimitador);

	// Copia e formata ela, removendo os extras
	strcpy(sequencia, nova_sequencia);
	memmove(sequencia, sequencia+1, strlen(sequencia));
}

void comandos_interface_comandos(comandos_t comandos) {
	int i, j;

	printf("\n|@---- %sComandos%s ----@|\n", COR_AZUL, ESTILO_RESETAR);
	for (i = 0; i < COMANDOS_MAXIMO; i++) {
		puts("|--------------------|");

		if (comandos.acoes[i][0] != N) printf("%d -> ", i + 1); // Indicador do comando

		for (j = 0; j < COMANDO_ACAO_MAXIMO; j++) {
			switch(comandos.acoes[i][j]) {
			case F:
				printf("| %sF%s ", COR_VERDE, ESTILO_RESETAR);
				break;
			case E:
				printf("| %sE%s ", COR_AZUL, ESTILO_RESETAR);
				break;
			case D:
				printf("| %sD%s ", COR_AMARELO, ESTILO_RESETAR);
				break;
			case N:
				continue;
			}
		}

		if (comandos.acoes[i][0] != N) printf("|\n"); // Fecha de maneira formatada
	}

	puts("|--------------------|");
}

void comandos_interface_dados_comando(comandos_execucao_t comando) {
	printf("\n|@------------- %sInformações do movimento%s -------------@|\n", COR_CIANO, ESTILO_RESETAR);
	printf("%s|@----->%s Comandos: %lu\n", COR_VERDE, ESTILO_RESETAR, comando.acao_index);
	printf("%s|@----->%s Numero de vezes executado: %lu\n", COR_AMARELO, ESTILO_RESETAR, comando.acao_vezes);
	puts("Aperte a tecla enter para continar...");
	getc(stdin);
}

void comandos_interface_sequencia(void) {
	printf("\n|@---------------------- %sSequencia%s ----------------------@|\n", COR_VERDE, ESTILO_RESETAR);
	puts("Deve ser escrito no modelo: numero_comando-vezes_executado");
	puts("Exemplo: 1-2 3-1 1-1 ...");
	puts("OBS: A sequencia nao pode ter espacos no inico ou final, somente para separ os comandos");
	printf("\nDigite a sequencia de comandos: ");
}
