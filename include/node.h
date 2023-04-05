#ifndef INCLUDE_NODE_H
#define INCLUDE_NODE_H

#include "commands.h"

typedef struct node_s {
	execution_commands_t data;
	struct node_s *next;
} node_t;

#endif
