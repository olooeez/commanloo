#include <stdlib.h>
#include <stdio.h>

#include "fila.h"

// Definição dos nós da fila
typedef struct no_s {
	comandos_execucao_t dados;
	struct no_s *proximo;
} no_t;

// Definição do objeto fila
struct fila_s {
	no_t *inicio;
	no_t *fim;
	int quantidade;
};

fila_t *fila_iniciar(void) {
	fila_t *fila = (fila_t *) malloc(sizeof(fila_t));

	if (fila != NULL) {
		fila->inicio = NULL;
		fila->fim = NULL;
		fila->quantidade = 0;
	}

	return fila;
}

void fila_terminar(fila_t *fila) {
	if (fila != NULL) {

		while (fila->inicio != NULL) {
			no_t *no;

			no = fila->inicio;
			fila->inicio = fila->inicio->proximo;
			free(no);
		}

		free(fila);
	}
}

fila_err fila_consultar(fila_t *fila, comandos_execucao_t *dados) {
	if (fila == NULL) return FILA_SEM_MEMORIA;
	if (fila->quantidade == 0) return FILA_VAZIA;

	*dados = fila->inicio->dados;

	return FILA_OK;
}

fila_err fila_inserir(fila_t *fila, comandos_execucao_t dados) {
	if (fila == NULL) return FILA_SEM_MEMORIA;

	no_t *no = (no_t *) malloc(sizeof(no_t));

	if (no == NULL) return FILA_SEM_MEMORIA;

	no->dados = dados;
	no->proximo = NULL;

	if (fila->fim == NULL) fila->inicio = no;
	else fila->fim->proximo = no;

	fila->fim = no;
	fila->quantidade++;

	return FILA_OK;
}

fila_err fila_remover(fila_t *fila) {
	if (fila == NULL) return FILA_SEM_MEMORIA;
	if (fila->quantidade == 0) return FILA_VAZIA;

	no_t *no = fila->inicio;
	fila->inicio = fila->inicio->proximo;

	if (fila->inicio == NULL) fila->fim = NULL;

	free(no);
	fila->quantidade--;

	return FILA_OK;
}

_Bool fila_vazia(fila_t *fila) {
	return (fila->quantidade == 0);
}
