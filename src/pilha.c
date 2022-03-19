#include <stdlib.h>
#include <stdio.h>

#include "pilha.h"

// Definição dos nós da pilha
typedef struct no_s {
	comandos_execucao_t dados;
	struct no_s *proximo;
} no_t;

// Definição do objeto pilha
struct pilha_s {
	no_t *inicio;
	no_t *fim;
	int quantidade;
};

pilha_t *pilha_iniciar(void) {
	pilha_t *pilha = (pilha_t *) malloc(sizeof(pilha_t));

	if (pilha != NULL) {
		pilha->inicio = NULL;
		pilha->fim = NULL;
		pilha->quantidade = 0;
	}

	return pilha;
}

void pilha_terminar(pilha_t *pilha) {
	if (pilha != NULL) {
		while (pilha->inicio != NULL) {
			no_t *no;

			no = pilha->inicio;
			pilha->inicio = pilha->inicio->proximo;
			free(no);
		}

		free(pilha);
	}
}

pilha_err pilha_consultar(pilha_t *pilha, comandos_execucao_t *dados) {
	if (pilha == NULL) return PILHA_SEM_MEMORIA;
	if (pilha->quantidade == 0) return PILHA_VAZIA;

	*dados = pilha->inicio->dados;

	return PILHA_OK;
}

pilha_err pilha_inserir(pilha_t *pilha, comandos_execucao_t dados) {
	if (pilha == NULL) return PILHA_SEM_MEMORIA;

	no_t *no = (no_t *) malloc(sizeof(no_t));

	if (no == NULL) return PILHA_SEM_MEMORIA;

	no->dados = dados;
	no->proximo = pilha->inicio;

	pilha->inicio = no;
	pilha->quantidade++;

	return PILHA_OK;
}

pilha_err pilha_remover(pilha_t *pilha) {
	if (pilha == NULL) return PILHA_SEM_MEMORIA;
	if (pilha->quantidade == 0) return PILHA_VAZIA;

	no_t *no = pilha->inicio;
	pilha->inicio = pilha->inicio->proximo;

	free(no);
	pilha->quantidade--;

	return PILHA_OK;
}

_Bool pilha_vazia(pilha_t *pilha) {
	return (pilha->quantidade == 0);
}
