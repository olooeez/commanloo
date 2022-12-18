#ifndef INCLUDE_PHASES_H
#define INCLUDE_PHASES_H

#include <stdio.h>

#define PHASES_QUANTITY 3

typedef _Bool (*phase_func_t)(void); 

typedef struct {
	phase_func_t func;
	char name[BUFSIZ];
	char info[BUFSIZ];
} phases_t;

void init_phase(phases_t *phase);
void draw_phase_data(phases_t phase);

#endif
