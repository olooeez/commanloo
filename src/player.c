#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "player.h"
#include "estilo.h"

// Regras do player e do tabuleiro
#define PLAYER_INICIO_LINHA 0
#define PLAYER_INICIO_COLUNA 0

#define OBJETIVO_LINHA 7
#define OBJETIVO_COLUNA 7

/* Função privada para mudar a direção e a posição do player */
static void player_atualizar(player_t *player, acoes_t direcao) {
	switch (direcao) {
	case D:
		if (player->direcao == ESQUERDA) player->direcao = CIMA;
		else if (player->direcao == DIREITA) player->direcao = BAIXO;
		else if (player->direcao == CIMA) player->direcao = DIREITA;
		else if (player->direcao == BAIXO) player->direcao = ESQUERDA;

		break;
	case E:
		if (player->direcao == ESQUERDA) player->direcao = BAIXO;
		else if (player->direcao == DIREITA) player->direcao = CIMA;
		else if (player->direcao == CIMA) player->direcao = ESQUERDA;
		else if (player->direcao == BAIXO) player->direcao = DIREITA;

		break;
	case F:
		if (player->direcao == CIMA) player->proxima_linha--;
		else if (player->direcao == BAIXO) player->proxima_linha++;
		else if (player->direcao == ESQUERDA) player->proxima_coluna--;
		else if (player->direcao == DIREITA) player->proxima_coluna++;

		break;
	case N:
		break;
	}
}

/* Move o player uma casa */
static void player_mover(player_t *player, mapa_t *mapa) {
	if (mapa->tabuleiro[player->proxima_linha][player->proxima_coluna] == OBS) {
		player->proxima_linha = player->linha_atual;
		player->proxima_coluna = player->coluna_atual;
	}

	if (player->proxima_linha >= TABULEIRO_LINHAS) {
		player->proxima_linha = TABULEIRO_LINHAS - 1;
	} else if (player->proxima_linha < 0) {
		player->proxima_linha = 0;
	}

	if (player->proxima_coluna >= TABULEIRO_COLUNAS) {
		player->proxima_coluna = TABULEIRO_COLUNAS - 1;
	} else if (player->proxima_coluna < 0) {
		player->proxima_coluna = 0;
	}

	mapa->tabuleiro[player->linha_atual][player->coluna_atual] = PAT;
	mapa->tabuleiro[player->proxima_linha][player->proxima_coluna] = PLA;

	player->linha_atual = player->proxima_linha;
	player->coluna_atual = player->proxima_coluna;
}

player_t player_iniciar(void) {
	player_t player;

	player.coluna_atual = PLAYER_INICIO_COLUNA;
	player.linha_atual = PLAYER_INICIO_LINHA;
	player.direcao = DIREITA;

	return player;
}

_Bool player_chegou_objetivo(player_t player) {
	if (player.linha_atual >= OBJETIVO_LINHA && player.coluna_atual >= OBJETIVO_COLUNA) {
		return 1;
	}

	return 0;
}

_Bool player_chegou_inicio(player_t player) {
	if (player.linha_atual == PLAYER_INICIO_LINHA && player.coluna_atual == PLAYER_INICIO_COLUNA) {
		return 1;
	}

	return 0;
}

void player_andar(player_t *player, comandos_execucao_t comando, mapa_t *mapa, comandos_t comandos) {
	size_t i, j;

	player->proxima_linha = player->linha_atual;
	player->proxima_coluna = player->coluna_atual;

	acoes_t acao;

	for (i = 0; i < comando.acao_vezes; i++) {
		for (j = 0; j < COMANDO_ACAO_MAXIMO; j++) {
			acao = comandos.acoes[comando.acao_index-1][j];

			player_atualizar(player, acao);
			player_mover(player, mapa);
		}
	}
}

void player_mostrar_direcao(player_t player) {
	char direcao_arte[] = "▼";

	switch (player.direcao) {
	case DIREITA:
		strcpy(direcao_arte, "▶");
		break;
	case ESQUERDA:
		strcpy(direcao_arte, "◀");
		break;
	case CIMA:
		strcpy(direcao_arte, "▲");
		break;
	case BAIXO:
		break;
	}

	printf("\n|@-------------- %sDirecao%s --------------@|\n", COR_AMARELO, ESTILO_RESETAR);
	printf("O player esta com a direcao para P[%s]\n", direcao_arte);
}
