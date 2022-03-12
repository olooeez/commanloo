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

void comando_formatar_remover(char *sequencia, comandos_execucao_t *comandos_execucao) {
	const char sequencia_delimitador = ' ';
	char *nova_sequencia;

	int sequencia_tamanho = strlen(sequencia);

	// Remove o `\n` do final, caso tenha
	if (sequencia[sequencia_tamanho-1] == '\n') {
		sequencia[sequencia_tamanho-1] = '\n';
		sequencia_tamanho--;
	}

	comandos_execucao->acao_index = sequencia[0] - '0';
	comandos_execucao->acao_vezes = sequencia[2] - '0';

	// Termina caso não de para formatar ainda mais. Exemplo: `1-2`
	if (sequencia_tamanho == 3) {
		strcpy(sequencia, "");
		return;
	}

	nova_sequencia = strchr(sequencia, sequencia_delimitador);

	// Copia e formata ela, removendo os extras
	strcpy(sequencia, nova_sequencia);
	memmove(sequencia, sequencia+1, strlen(sequencia));
}
