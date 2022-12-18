CC=gcc
CFLAGS=-Wall -Wextra -O2 -std=c99 -pedantic -g

OBJ=obj
SRC=src
HDR=include
BIN=bin

SRCS=$(wildcard $(SRC)/*.c)
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))

DIR=$(notdir $(CURDIR))

NAME=commanloo

all: $(OBJ) $(BIN) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -I $(HDR) -c $< -o $@

$(OBJ):
	mkdir -p $@

$(BIN):
	mkdir -p $@

clean:
	$(RM) -rf  $(OBJ) $(BIN)

run: all
	./$(NAME)

docker:
	docker build -t $(DIR) .

submit: all
	zip -qqr $(DIR).zip . -x ".git/*" "bin/*" "obj/*" ".gitignore" "LICENSE" "README.md"

lint:
	cppcheck -I include --enable=all --std=c99 --suppressions-list=.cppcheck-suppress --platform=win64 --platform=unix64 $(SRC)
