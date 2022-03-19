#ifndef INCLUDE_FILA_H
#define INCLUDE_FILA_H

#include "comandos.h"

// Difinição de alguns erros que podem acontecer na fila
typedef enum {
	FILA_OK,
	FILA_SEM_MEMORIA,
	FILA_VAZIA,
} fila_err;

typedef struct fila_s fila_t;

/* Inicia a fila com os valores padrões */
fila_t *fila_iniciar(void);

/* Termina a fila, limpando ela no processo */
void fila_terminar(fila_t *fila);

/* Armazena o elemento do inicio da fila no dados */
fila_err fila_consultar(fila_t *fila, comandos_execucao_t *dados);

/* Inseri um novo elemento na fila */
fila_err fila_inserir(fila_t *fila, comandos_execucao_t dados);

/* Remove o primeiro elemento da fila */
fila_err fila_remover(fila_t *fila);

/* Ve se a fila está vazia */
_Bool fila_vazia(fila_t *fila);

#endif
