CC=gcc
CFLAGS=-Wall -Wextra -O2 -std=c99 -pedantic -g

OBJ=obj
SRC=src
HDR=include
BIN=bin

SRCS=$(wildcard $(SRC)/*.c)
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))

DIR=$(notdir $(CURDIR))

NAME=comandos_loop

all: $(OBJ) $(BIN) $(NAME)

$(NAME): $(OBJS)
	@echo [CC CFLAGS $^ -o BIN] 
	@$(CC) $(CFLAGS) $^ -o $(BIN)/$@

$(OBJ)/%.o: $(SRC)/%.c
	@echo [CC CFLAGS -c $< -o $@]
	@$(CC) $(CFLAGS) -I $(HDR) -c $< -o $@

$(OBJ):
	@echo [MKDIR $@]
	@mkdir -p $@

$(BIN):
	@echo [MKDIR $@]
	@mkdir -p $@

clean:
	@echo [RM OBJS BIN]
	@$(RM) -rf  $(OBJ) $(BIN)

run: all
	@echo [./BIN]
	@./$(NAME)

docker:
	@echo [DOCKER BUILD]
	@docker build -t $(DIR) .

submit: all
	@echo [ZIP DIR]
	@zip -qqr $(DIR).zip . -x ".git/*" "bin/*" "obj/*" ".gitignore" "LICENSE" "README.md"

lint:
	@echo [CPPCHECK]
	@cppcheck -I include --enable=all --std=c99 --suppressions-list=.cppcheck-suppress --platform=win64 --platform=unix64 $(SRC)
