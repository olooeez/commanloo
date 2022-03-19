#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "comandos.h"
#include "mapa.h"
#include "estilo.h"
#include "pilha.h"
#include "fila.h"
#include "player.h"
#include "interface.h"
#include "fases.h"

static _Bool fase_1(void) {
	size_t tentativas = 1;

	char sequencia[BUFSIZ];

	mapa_t mapa, mapa_reset;
	player_t player;
	comandos_t comandos;
	comandos_execucao_t comando;

	mapa = mapa_iniciar();
	mapa_reset = mapa;

	while (1) {
		mapa = mapa_reset;

		player = player_iniciar();
		comandos = comandos_iniciar();

		fila_t *fila = fila_iniciar();

		interface_digitar(mapa, comandos, player, tentativas);
		fgets(sequencia, BUFSIZ, stdin);

		// Escreve a sequencia na fila
		while (strlen(sequencia) != 0) {
			comandos_formatar_remover(sequencia, &comando);
			fila_inserir(fila, comando);
		}

		while (!fila_vazia(fila)) {
			fila_consultar(fila, &comando);
			player_andar(&player, comando, &mapa, comandos);
			fila_remover(fila);

			interface_movimento(mapa, comandos, comando, player);
		}

		if (player_chegou_objetivo(player)) {
			interface_passou_fase();
			break;
		}

		interface_nao_passou_fase();
		tentativas++;

		if (tentativas == 4) return 0;

		fila_terminar(fila);
	}

	return 1;
}

static _Bool fase_2(void) {
	size_t tentativas = 1;

	char sequencia[BUFSIZ];

	mapa_t mapa, mapa_reset;
	player_t player;
	comandos_t comandos;
	comandos_execucao_t comando;

	mapa = mapa_iniciar();
	mapa_reset = mapa;

	while (1) {
		mapa = mapa_reset;

		player = player_iniciar();
		comandos = comandos_iniciar();

		pilha_t *pilha = pilha_iniciar();

		interface_digitar(mapa, comandos, player, tentativas);
		fgets(sequencia, BUFSIZ, stdin);

		while (strlen(sequencia) != 0) {
			comandos_formatar_remover(sequencia, &comando);
			pilha_inserir(pilha, comando);
		}

		while (!pilha_vazia(pilha)) {
			pilha_consultar(pilha, &comando);
			player_andar(&player, comando, &mapa, comandos);
			pilha_remover(pilha);

			interface_movimento(mapa, comandos, comando, player);
		}

		if (player_chegou_objetivo(player)) {
			interface_passou_fase();
			break;
		}

		interface_nao_passou_fase();
		tentativas++;

		if (tentativas == 4) return 0;

		pilha_terminar(pilha);
	}

	return 1;
}

static _Bool fase_3(void) {
	size_t tentativas = 1;

	char sequencia[BUFSIZ];

	mapa_t mapa, mapa_reset;
	player_t player, player_reset;
	comandos_t comandos;
	comandos_execucao_t comando;

	mapa = mapa_iniciar();
	mapa_reset = mapa;

	pilha_t *volta;

	while (1) {
		mapa = mapa_reset;

		player = player_iniciar();
		comandos = comandos_iniciar();

		fila_t *ida = fila_iniciar();

		interface_digitar(mapa, comandos, player, tentativas);
		fgets(sequencia, BUFSIZ, stdin);

		while (strlen(sequencia) != 0) {
			comandos_formatar_remover(sequencia, &comando);
			fila_inserir(ida, comando);
		}

		while (!fila_vazia(ida)) {
			fila_consultar(ida, &comando);
			player_andar(&player, comando, &mapa, comandos);
			fila_remover(ida);

			interface_movimento(mapa, comandos, comando, player);
		}

		if (player_chegou_objetivo(player)) {
			mapa_reset = mapa;
			player_reset = player;

			while (1) {
				mapa = mapa_reset;
				player = player_reset;

				volta = pilha_iniciar();
				comandos = comandos_iniciar();

				interface_digitar(mapa, comandos, player, tentativas);
				fgets(sequencia, BUFSIZ, stdin);

				while (strlen(sequencia) != 0) {
					comandos_formatar_remover(sequencia, &comando);
					pilha_inserir(volta, comando);
				}

				while (!pilha_vazia(volta)) {
					pilha_consultar(volta, &comando);
					player_andar(&player, comando, &mapa, comandos);
					pilha_remover(volta);

					interface_movimento(mapa, comandos, comando, player);
				}

				if (player_chegou_inicio(player)) {
					interface_passou_fase();
					return 1;
				}

				interface_nao_passou_fase();
				tentativas++;

				if (tentativas == 4) return 0;

				pilha_terminar(volta);
			}
		}

		interface_nao_passou_fase();
		tentativas++;

		if (tentativas == 4) return 0;

		fila_terminar(ida);
	}

	return 1;
}

static fases_t fases_definidas[FASES_QUANTIDADE] = {
	{fase_1, "Primeira fase [Usando filas]", "Chegue ao objetivo (O) usando fila"},
	{fase_2, "Segunda fase [Usando pilhas]", "Chegue ao objetivo (O) usando pilha"},
	{fase_3, "Terceira fase [Usando filas/pilhas]", "Chegue ao objetivo (O) usando fila e volte ao inicio usando pilha"},
};

void fases_iniciar(fases_t *fases) {
	size_t i;

	for (i = 0; i < FASES_QUANTIDADE; i++) {
		fases[i] = fases_definidas[i];
	}
}

void fases_mostrar_dados(fases_t fase) {
	system("clear||cls");
	printf("|@----------- %s%s%s -----------@|\n", COR_VERMELHO, fase.nome, ESTILO_RESETAR);
	printf("\n|@---> Missao: %s\n", fase.info);
	puts("|@---> Aperte a tecla enter para continuar...");
	getc(stdin);
	system("clear||cls");
}
