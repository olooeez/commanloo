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
    size_t linha_atual, coluna_atual;
    size_t proxima_linha, proxima_coluna;
} player_t;

/* Função que inicia o player com alguns valores por padrão */
player_t player_iniciar(void);

/* Função que diz se o player chegou ao objetivo */
_Bool player_chegou_destino(player_t player);

/* Fazer o player andar com primerio item a fila */
void player_andar_fila(player_t *player, fila_t *fila, mapa_t *mapa, comandos_t comandos);

#endif