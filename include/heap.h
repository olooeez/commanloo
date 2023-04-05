#ifndef INCLUDE_HEAP_H
#define INCLUDE_HEAP_H

#include <stdbool.h>

#include "node.h"

typedef enum {
	HEAP_OK,
	HEAP_NO_MEMORY,
	HEAP_EMPTY,
} heap_err;

typedef struct heap_s {
	node_t *begin;
	node_t *end;
	int quantity;
} heap_t;

heap_t *init_heap(void);
void end_heap(heap_t *heap);
heap_err consult_heap(heap_t *heap, execution_commands_t *data);
heap_err insert_heap(heap_t *heap, execution_commands_t data);
heap_err remove_heap(heap_t *heap);
bool is_heap_empty(heap_t *heap);

#endif
