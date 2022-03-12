CC=gcc
CFLAGS=-Wall -Wextra -O2 -std=c99 -g

OBJ=obj
SRC=src
HDR=include
BIN=bin

SRCS=$(wildcard $(SRC)/*.c)
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))

NAME=$(BIN)/loop_command

all: $(OBJ) $(BIN) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -I $(HDR) -c $< -o $@

$(OBJ):
	mkdir -p $@

$(BIN):
	mkdir -p $@

clean:
	rm -rf $(OBJ) $(BIN)

run: all
	./$(NAME)

docker:
	docker build -t loop-commands .

submit: all
	zip -jr comandos_loop.zip *
