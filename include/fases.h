#ifndef INCLUDE_FASES_H
#define INCLUDE_FASES_H

#include <stdio.h>

// Definição de algumas regras
#define FASES_QUANTIDADE 3

// Definicao da estrtura de uma função de uma fase
typedef _Bool (*fase_func_t)(void); 

// Definição do objeto das fases
typedef struct {
	fase_func_t func;
	char nome[BUFSIZ];
	char info[BUFSIZ];
} fases_t;

/* Inicia um array dinamico de fases */
void fases_iniciar(fases_t *fases);

/* Mostra a na tela o nome da fase mais uma pequena informação sobre ela */
void fases_mostrar_dados(fases_t fases);

#endif
