#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "player.h"

// Regras do player e do tabuleiro
#define PLAYER_INICIO_LINHA 0
#define PLAYER_INICIO_COLUNA 0

#define OBJETIVO_LINHA 7
#define OBJETIVO_COLUNA 7

/* Função privada para mudar a direção do player quando houver algum movimento */
static void player_mudar_direcao(player_t *player, acoes_t direcao) {
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
    case N:
    case F:
        break;
    }
}

player_t player_iniciar(void) {
    player_t player;

    player.coluna_atual = PLAYER_INICIO_COLUNA;
    player.linha_atual = PLAYER_INICIO_LINHA;
    player.direcao = DIREITA;

    return player;
}

_Bool player_chegou_destino(player_t player) {
    if (player.linha_atual >= OBJETIVO_LINHA && player.proxima_coluna >= OBJETIVO_COLUNA) {
        return 1;
    }

    return 0;
}

/* Função que diz se o player vai bater em um obstaculo */
static _Bool player_vai_bater_obstaculo(player_t player, mapa_t mapa) {
    if (mapa.tabuleiro[player.proxima_linha][player.proxima_coluna] == OBS) {
        return 1;
    }

    return 0;
}

/* Função que diz se o player vai chegar ao objetivo */
static _Bool player_vai_chegar_objetivo(player_t player) {
    if (player.proxima_linha >= OBJETIVO_LINHA && player.proxima_coluna >= OBJETIVO_COLUNA) {
        return 1;
    }

    return 0;
}

void player_andar_fila(player_t *player, fila_t *fila, mapa_t *mapa, comandos_t comandos) {
    size_t i, j;

    player->proxima_linha = player->linha_atual;
    player->proxima_coluna = player->coluna_atual;

    comandos_execucao_t dados;
    acoes_t comando;

    fila_consultar(fila, &dados);

    for (i = 0; i < dados.acao_vezes; i++) {
        for (j = 0; j < COMANDO_ACAO_MAXIMO; j++) {
            comando = comandos.acoes[dados.acao_index-1][j];

            player_mudar_direcao(player, comando);

            if (comando == F) {
                if (player->direcao == CIMA) player->proxima_linha--;
                else if (player->direcao == BAIXO) player->proxima_linha++;
                else if (player->direcao == ESQUERDA) player->proxima_coluna--;
                else if (player->direcao == DIREITA) player->proxima_coluna++;
            }
        }
    }

    if (player_vai_bater_obstaculo(*player, *mapa)) {
        return;
    }

    if (player_vai_chegar_objetivo(*player)) {
        mapa->tabuleiro[OBJETIVO_LINHA][OBJETIVO_COLUNA] = PLA;
    } else {
        mapa->tabuleiro[player->proxima_linha][player->proxima_coluna] = PLA;
    }

    mapa->tabuleiro[player->linha_atual][player->coluna_atual] = PAT;

    player->linha_atual = player->proxima_linha;
    player->coluna_atual = player->proxima_coluna;
}