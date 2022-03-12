#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "interface.h"
#include "estilo.h"

/* Mostra o tabuleiro formatado para o stdout */
static void interface_tabuleiro(mapa_t mapa) {
	int i, j;

    printf("\n|@--------- %sTabuleiro%s ---------@|\n", COR_VERMELHO, ESTILO_RESETAR);
	for (i = 0; i < TABULEIRO_LINHAS; i++) {
		puts("|---|---|---|---|---|---|---|---|"); // Separador

		for (j = 0; j < TABULEIRO_COLUNAS; j++) {
			switch (mapa.tabuleiro[i][j]) {
			case PLA:
				printf("| %sP%s ", COR_MAGENTA, ESTILO_RESETAR);
				break;
			case OBJ:
				printf("| %sO%s ", COR_VERDE, ESTILO_RESETAR);
				break;
			case OBS:
				printf("| %sX%s ", COR_VERMELHO, ESTILO_RESETAR);
				break;
			case PAT:
				printf("|   ");
			}
		}

		printf("|\n"); // Fechar as ações
	}

	puts("|---|---|---|---|---|---|---|---|"); // Fechar o tabuleiro
}

/* Mostra os comandos formatado para o stdout */
static void interface_comandos(comandos_t comandos) {
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

/* Mostra uma menssagem de digito para sequencia */
static void interface_sequencia(void) {
	printf("\n|@---------------------- %sSequencia%s ----------------------@|\n", COR_AMARELO, ESTILO_RESETAR);
    printf("%sDeve ser escrito no modelo: numero_comando-vezes_executado%s\n", ESTILO_NEGRITO, ESTILO_RESETAR);
    printf("%sExemplo%s: 1-2 3-1 1-1 ...\n", ESTILO_NEGRITO, ESTILO_RESETAR);
    printf("\nDigite a %ssequencia de comandos%s para chegar no objetivo `%sO%s`: ", ESTILO_SUBLINHADO, ESTILO_RESETAR, COR_VERDE, ESTILO_RESETAR);
}

/* Mostra os dados do comando */
static void interface_dados_comando(comandos_execucao_t comando) {
	printf("\n|@------------- %sInformações do movimento%s -------------@|\n", COR_CIANO, ESTILO_RESETAR);
    printf("%s|@----->%s Comandos: %ld\n", COR_VERDE, ESTILO_RESETAR, comando.acao_index);
    printf("%s|@----->%s Numero de vezes executado: %ld\n", COR_AMARELO, ESTILO_RESETAR, comando.acao_vezes);
    printf("\n%sAperte a tecla Enter...%s\n", ESTILO_NEGRITO, ESTILO_RESETAR);
    getc(stdin);
}

/* Mostrar a direção do player */
static void interface_direcao_player(player_t player) {
    char seta[] = "▲";

    switch (player.direcao) {
    case BAIXO:
        strcpy(seta, "▼");
        break;
    case ESQUERDA:
        strcpy(seta, "◀");
        break;
    case DIREITA:
        strcpy(seta, "▶");
    case CIMA:
        break;
    }

	printf("\n|@--------------- %sDirecao%s ---------------@|\n", COR_VERDE, ESTILO_RESETAR);
    printf("A direção que o player está olhando é P[%s]\n", seta);
}

void interface_digitar(mapa_t mapa, comandos_t comandos, player_t player) {
	interface_tabuleiro(mapa);
	interface_comandos(comandos);
	interface_direcao_player(player);
	interface_sequencia();
}

void interface_movimento(mapa_t mapa, comandos_t comandos, comandos_execucao_t comando, player_t player) {
	interface_tabuleiro(mapa);
	interface_comandos(comandos);
	interface_direcao_player(player);
	interface_dados_comando(comando);
}

void interface_passou_fase(void) {
    system("cls||clear");
    printf("|@--------------- %sParabens, você passou de fase%s -----------------@|\n", COR_VERDE, ESTILO_RESETAR);
	sleep(2);
	system("cls||clear");
}

void interface_fracasso(void) {
    system("cls||clear");
    printf("|@--------------- %sInfelizmente, você não passou de fase%s -----------------@|\n", COR_VERMELHO, ESTILO_RESETAR);
	sleep(2);
	system("cls||clear");
}

void interface_tentativas(int tentativas) {
    printf("|@----------- %s%d° tentativa%s -----------@|\n", COR_MAGENTA, tentativas, ESTILO_RESETAR);
}

void interface_perdeu(void) {
	system("cls||clear");
	printf("|@------------- %sVoce perdeu o jogo%s -------------@|\n", COR_VERMELHO, ESTILO_RESETAR);
	sleep(2);
	system("cls||clear");
}

void interface_ganhou(void) {
	system("cls||clear");
	printf("|@------------- %sVoce ganhou o jogo%s -------------@|\n", COR_VERDE, ESTILO_RESETAR);
	sleep(2);
	system("cls||clear");	
}