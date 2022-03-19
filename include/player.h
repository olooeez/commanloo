#ifndef INCLUDE_PLAYER_H
#define INCLUDE_PLAYER_H

#include "mapa.h"
#include "fila.h"
#include "pilha.h"

// Direções que o player pode tomar
typedef enum {
	ESQUERDA,
	DIREITA,
	CIMA,
	BAIXO,
} direcao_t;

// Erros comuns durante o movimento do jogador
typedef enum {
	PLAYER_OK,
	PLAYER_ATINGIU_OBJETIVO,
} player_err;

// Objeto do player
typedef struct {
	direcao_t direcao;
	int linha_atual, coluna_atual;
	int proxima_linha, proxima_coluna;
} player_t;

/* Inicia o player com alguns valores por padrão */
player_t player_iniciar(void);

/* Diz se o player chegou no objetivo */
_Bool player_chegou_objetivo(player_t player);

/* Diz se o player chegou no inicio */
_Bool player_chegou_inicio(player_t player);

/* Fazer o player andar com primerio item a fila */
void player_andar(player_t *player, comandos_execucao_t comando, mapa_t *mapa, comandos_t comandos);

/* Mostra a direção do player */
void player_mostrar_direcao(player_t player);

#endif
