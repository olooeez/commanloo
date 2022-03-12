#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "mapa.h"
#include "estilo.h"

#define OBSTACULOS_MINIMO 6
#define OBSTACULOS_MAXIMO 8

#define OBSTACULOS_TAMANHO_MINIMO 2
#define OBSTACULOS_TAMANHO_MAXIMO 3

#define OBSTACULO_POSSIVEIS_DIRECOES 2

// Definição de todos os possíveis tabuleiros
tabuleiro_t tabuleiros[][TABULEIRO_LINHAS][TABULEIRO_COLUNAS] = {
	{
		{PLA, PAT, PAT, PAT, PAT, PAT, PAT, PAT},
		{PAT, OBS, PAT, PAT, PAT, PAT, PAT, PAT},
		{PAT, OBS, PAT, OBS, OBS, PAT, PAT, OBS},
		{PAT, PAT, PAT, PAT, PAT, PAT, PAT, OBS},
		{PAT, PAT, PAT, PAT, PAT, PAT, PAT, PAT},
		{PAT, PAT, PAT, PAT, OBS, OBS, OBS, PAT},
		{OBS, PAT, PAT, PAT, PAT, PAT, PAT, PAT},
		{OBS, PAT, PAT, OBS, OBS, PAT, PAT, OBJ}
	}
};

mapa_t mapa_iniciar(void) {
	size_t tamanho_tabuleiro, tabuleiro_aleatorio, i, j;

	mapa_t mapa;

	srand(time(NULL));

	tamanho_tabuleiro = (sizeof(tabuleiros) / sizeof(tabuleiro_t)) / (TABULEIRO_LINHAS *TABULEIRO_COLUNAS);
	tabuleiro_aleatorio = (rand() % tamanho_tabuleiro);

	// Escreve um novo tabuleiro aleatorio no já fornecido
	for (i = 0; i < TABULEIRO_LINHAS; i++) {
		for (j = 0; j < TABULEIRO_COLUNAS; j++) {
			mapa.tabuleiro[i][j] = tabuleiros[tabuleiro_aleatorio][i][j];
		}
	}

	return mapa;
}
