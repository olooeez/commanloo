#include <stdlib.h>
#include <stdio.h>

#include "heap.h"

heap_t *init_heap(void) {
	heap_t *heap = (heap_t *) malloc(sizeof(heap_t));

	if (heap != NULL) {
		heap->begin = NULL;
		heap->end = NULL;
		heap->quantity = 0;
	}

	return heap;
}

void end_heap(heap_t *heap) {
	if (heap != NULL) {
		while (heap->begin != NULL) {
			node_t *node;

			node = heap->begin;
			heap->begin = heap->begin->next;
			free(node);
		}

		free(heap);
	}
}

heap_err consult_heap(heap_t *heap, execution_commands_t *data) {
	if (heap == NULL) return HEAP_NO_MEMORY;
	if (heap->quantity == 0) return HEAP_EMPTY;

	*data = heap->begin->data;

	return HEAP_OK;
}

heap_err insert_heap(heap_t *heap, execution_commands_t data) {
	if (heap == NULL) return HEAP_NO_MEMORY;

	node_t *node = (node_t *) malloc(sizeof(node_t));

	if (node == NULL) return HEAP_NO_MEMORY;

	node->data = data;
	node->next = heap->begin;

	heap->begin = node;
	heap->quantity++;

	return HEAP_OK;
}

heap_err remove_heap(heap_t *heap) {
	if (heap == NULL) return HEAP_NO_MEMORY;
	if (heap->quantity == 0) return HEAP_EMPTY;

	node_t *node = heap->begin;
	heap->begin = heap->begin->next;

	free(node);
	heap->quantity--;

	return HEAP_OK;
}

bool is_heap_empty(heap_t *heap) {
	return (heap->quantity == 0);
}
