#ifndef INCLUDE_PILHA_H
#define INCLUDE_PILHA_H

#include "comandos.h"

// Difinição de alguns erros que podem acontecer na pilha
typedef enum {
	PILHA_OK,
	PILHA_SEM_MEMORIA,
	PILHA_VAZIA,
} pilha_err;

typedef struct pilha_s pilha_t;

/* Inicia a pilha com valores padrões */
pilha_t *pilha_iniciar(void);

/* Termina a pilha, limpando ela no processo */
void pilha_terminar(pilha_t *pilha);

/* Armazena o elemento do inicio da pilha no dados */
pilha_err pilha_consultar(pilha_t *pilha, comandos_execucao_t *dados);

/* Inseri um novo elemento na pilha */
pilha_err pilha_inserir(pilha_t *pilha, comandos_execucao_t dados);

/* Remove o primeiro elemento (último) da pilha */
pilha_err pilha_remover(pilha_t *pilha);

/* Verifica se a pilha é vazia */
_Bool pilha_vazia(pilha_t *pilha);

#endif
