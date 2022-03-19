#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "fases.h"
#include "interface.h"

int main(void) {
	size_t i;
	fases_t fases[FASES_QUANTIDADE];
	
	fases_iniciar(fases);

	for (i = 0; i < FASES_QUANTIDADE; i++) {
		fases_mostrar_dados(fases[i]);

		if (!fases[i].func()) {
			interface_perdeu();
		}
	}

	interface_ganhou();
	return 0;
}
