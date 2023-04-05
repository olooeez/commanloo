#ifndef INCLUDE_QUEUE_H
#define INCLUDE_QUEUE_H

#include <stdbool.h>

#include "node.h"

typedef enum {
	QUEUE_OK,
	QUEUE_NO_MEMORY,
	QUEUE_EMPTY,
} queue_err;

typedef struct queue_s {
	node_t *begin;
	node_t *end;
	int quantity;
} queue_t;

queue_t *init_queue(void);
void end_queue(queue_t *queue);
queue_err consult_queue(queue_t *queue, execution_commands_t *data);
queue_err insert_queue(queue_t *queue, execution_commands_t data);
queue_err remove_queue(queue_t *queue);
bool is_queue_empty(queue_t *queue);

#endif
