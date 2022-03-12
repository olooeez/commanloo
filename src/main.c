#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "comandos.h"
#include "mapa.h"
#include "estilo.h"
#include "pilha.h"
#include "fila.h"
#include "player.h"
#include "interface.h"

/* Primeira fase do jogo */
_Bool fase_1(void) {
	size_t tentativas = 1;

	while (1) {
		char sequencia[BUFSIZ];

		mapa_t mapa = mapa_iniciar();
		player_t player = player_iniciar();
		comandos_t comandos = comandos_iniciar();

		fila_t *fila = fila_iniciar();

		comandos_execucao_t comando;

		interface_tentativas(tentativas);
		interface_digitar(mapa, comandos, player);
		fgets(sequencia, BUFSIZ, stdin);

		// Escreve a sequencia na fila
		while (strlen(sequencia) != 0) {
			comando_formatar_remover(sequencia, &comando);
			fila_inserir(fila, comando);
		}

		while (!fila_vazia(fila)) {
			player_andar_fila(&player, fila, &mapa, comandos);
			fila_consultar(fila, &comando);
			fila_remover(fila);

			system("cls||clear");

			interface_movimento(mapa, comandos, comando, player);
		}

		if (player_chegou_destino(player)) {
			interface_passou_fase();
			break;
		} else {
			interface_fracasso();
			tentativas++;
		}

		if (tentativas == 4) return 0;

		fila_terminar(fila);
	}

	return 1;
}

int main(void) {
	if (!fase_1()) {
		interface_fracasso();
		exit(EXIT_FAILURE);
	}

	// Aqui vai a função da fase 2 e 3

	interface_ganhou();
	return 0;
}
