#include <stdlib.h>
#include <stdio.h>

#include "queue.h"

typedef struct node_s {
	execution_commands_t data;
	struct node_s *next;
} node_t;

struct queue_s {
	node_t *begin;
	node_t *end;
	int quantity;
};

queue_t *init_queue(void) {
	queue_t *queue = (queue_t *) malloc(sizeof(queue_t));

	if (queue != NULL) {
		queue->begin = NULL;
		queue->end = NULL;
		queue->quantity = 0;
	}

	return queue;
}

void end_queue(queue_t *queue) {
	if (queue != NULL) {
		while (queue->begin != NULL) {
			node_t *node;

			node = queue->begin;
			queue->begin = queue->begin->next;
			free(node);
		}

		free(queue);
	}
}

queue_err consult_queue(queue_t *queue, execution_commands_t *data) {
	if (queue == NULL) return QUEUE_NO_MEMORY;
	if (queue->quantity == 0) return QUEUE_EMPTY;

	*data = queue->begin->data;

	return QUEUE_OK;
}

queue_err insert_queue(queue_t *queue, execution_commands_t data) {
	if (queue == NULL) return QUEUE_NO_MEMORY;

	node_t *node = (node_t *) malloc(sizeof(node_t));

	if (node == NULL) return QUEUE_NO_MEMORY;

	node->data = data;
	node->next = NULL;

	if (queue->end == NULL) queue->begin = node;
	else queue->end->next = node;

	queue->end = node;
	queue->quantity++;

	return QUEUE_OK;
}

queue_err remove_queue(queue_t *queue) {
	if (queue == NULL) return QUEUE_NO_MEMORY;
	if (queue->quantity == 0) return QUEUE_EMPTY;

	node_t *node = queue->begin;
	queue->begin = queue->begin->next;

	if (queue->begin == NULL) queue->end = NULL;

	free(node);
	queue->quantity--;

	return QUEUE_OK;
}

bool is_queue_empty(queue_t *queue) {
	return (queue->quantity == 0);
}
