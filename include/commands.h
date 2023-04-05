#ifndef INCLUDE_COMMANDS_H
#define INCLUDE_COMMANDS_H

#define MINIMUM_COMMANDS 3
#define COMMANDS_MAXIMUM 4
#define MINIMUM_ACTION_COMMAND 2
#define COMMAND_ACTION_MAXIMUM 4

typedef enum {
	N,
	L,
	R,
	F,
} action_t;

typedef struct {
	action_t actions[COMMANDS_MAXIMUM][COMMAND_ACTION_MAXIMUM];
} commands_t;

typedef struct {
	size_t index;
	size_t times;
} execution_commands_t;

commands_t init_commands(void);
void store_input(char *sequence, execution_commands_t *commands);
void draw_commands(commands_t commands);
void draw_command_info(execution_commands_t command);
void draw_input_info(void);

#endif
