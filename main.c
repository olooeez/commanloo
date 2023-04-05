#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "include/phases.h"
#include "include/interface.h"

int main(void) {
	size_t i;
	phases_t phases[PHASES_QUANTITY];
	
	init_phase(phases);

	for (i = 0; i < PHASES_QUANTITY; i++) {
		draw_phase_data(phases[i]);

		if (!phases[i].func()) {
			draw_lost();
		}
	}

	draw_won();
	return 0;
}
