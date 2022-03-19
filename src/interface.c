#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "interface.h"
#include "estilo.h"

/* Mostra o contador de tentativas */
static void interface_tentativas(size_t tentativas) {
	printf("|@----------- %s%lu° tentativa%s -----------@|\n", COR_MAGENTA, tentativas, ESTILO_RESETAR);
}

void interface_digitar(mapa_t mapa, comandos_t comandos, player_t player, size_t tentativas) {
	system("clear||cls");
	interface_tentativas(tentativas);
	mapa_mostrar_tabuleiro(mapa);
	comandos_interface_comandos(comandos);
	player_mostrar_direcao(player);
	comandos_interface_sequencia();
}

void interface_movimento(mapa_t mapa, comandos_t comandos, comandos_execucao_t comando, player_t player) {
	system("clear||cls");
	mapa_mostrar_tabuleiro(mapa);
	comandos_interface_comandos(comandos);
	player_mostrar_direcao(player);
	comandos_interface_dados_comando(comando);
}

void interface_passou_fase(void) {
	system("clear||cls");
	printf("|@--------------- %sParabens, você passou de fase%s -----------------@|\n", COR_VERDE, ESTILO_RESETAR);
	sleep(2);
	system("clear||cls");
}

void interface_nao_passou_fase(void) {
	system("clear||cls");
	printf("|@--------------- %sInfelizmente, você não passou de fase%s -----------------@|\n", COR_VERMELHO, ESTILO_RESETAR);
	sleep(2);
	system("clear||cls");
}

void interface_perdeu(void) {
	system("clear||cls");
	printf("|@------------- %sVoce perdeu o jogo%s -------------@|\n", COR_VERMELHO, ESTILO_RESETAR);
	sleep(2);
	system("clear||cls");
	exit(EXIT_FAILURE);
}

void interface_ganhou(void) {
	system("clear||cls");
	printf("|@------------- %sVoce ganhou o jogo%s -------------@|\n", COR_VERDE, ESTILO_RESETAR);
	sleep(2);
	system("clear||cls");
}
