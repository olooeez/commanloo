#ifndef INCLUDE_INTERFACE_H
#define INCLUDE_INTERFACE_H

#include "mapa.h"
#include "comandos.h"
#include "player.h"

/* Mostra o tabuleiro, comandos, direção e o espaço para digitar a sequencia */
void interface_digitar(mapa_t mapa, comandos_t comandos, player_t player, size_t tentativas);

/* Mostra o tabuleiro, comandos, direção, qual comando foi executado e quantas vezes */
void interface_movimento(mapa_t mapa, comandos_t comandos, comandos_execucao_t comando, player_t player);

/* Mostra uma menssagem de que não passou de fase */
void interface_fracasso(void);

/* Mostra uma menssagem de que se passou de fase */
void interface_passou_fase(void);

/* Mostra que o player perdeu */
void interface_perdeu(void);

/* Mostra que o player ganhou */
void interface_ganhou(void);

#endif
