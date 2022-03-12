#ifndef INCLUDE_MAPA_H
#define INCLUDE_MAPA_H

// Algumas regras do tabuleiro
#define TABULEIRO_LINHAS 8
#define TABULEIRO_COLUNAS 8

// Objetos que podem cobrir o mapa
typedef enum {
	PAT,
	PLA,
	OBJ,
	OBS,
} tabuleiro_t;

// Definição do tipo do mapa
typedef struct {
	tabuleiro_t tabuleiro[TABULEIRO_LINHAS][TABULEIRO_COLUNAS];
} mapa_t;

/* Inicia o map com objetos aleatorios */
mapa_t mapa_iniciar(void);

#endif
