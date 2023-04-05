CC = gcc
CFLAGS = -Wall -Wextra -O2 -std=c99 -pedantic -fprofile-arcs -ftest-coverage

HDR = include
BIN = bin
SRC = src
OBJ = obj
TEST = test

SRCS := $(wildcard $(SRC)/*.c)
OBJS := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))

TEST_SRCS := $(wildcard $(TEST)/*.c)
TEST_BINS := $(patsubst $(TEST)/%.c, $(TEST)/bin/%, $(TEST_SRCS))

NAME = commanloo
VERSION = 0.1.0

.PHONY: all clean test lint docker submit coverage

all: $(OBJ) $(BIN) $(BIN)/$(NAME)

$(BIN)/$(NAME): main.c $(OBJS)
	@echo "> Generating the executable in $@."
	@$(CC) $(CFLAGS) -I $(HDR) $^ -o $@

$(OBJ):
	@echo "> Creating $@ directory."
	@mkdir -p $@

$(BIN):
	@echo "> Creating $@ directory."
	@mkdir -p $@

$(OBJ)/%.o: $(SRC)/%.c
	@echo "> Generating $@ from $<."
	@$(CC) $(CFLAGS) -I $(HDR) -c $< -o $@

$(TEST)/bin/%: $(TEST)/%.c $(OBJS)
	@echo "> Generating $@ from $<."
	@$(CC) $(CFLAGS) -I $(HDR) $< $(OBJS) -o $@ -lcriterion -lgcov

$(TEST)/bin:
	@echo "> Creating $@ directory."
	@mkdir -p $@

check: $(TEST)/bin $(TEST_BINS)
	@for test in $(TEST_BINS); do echo "> Running test from $$test."; ./$$test; done

coverage: $(TEST)/bin $(TEST_BINS)
	@echo "> Generating code coverage report."
	@rm -f *.gcno *.gcda *.gcov
	@for test in $(TEST_BINS); do echo "> Running test with coverage from $$test."; ./$$test; done
	@echo "> Running gcovr to get the coverage."
	@gcovr --xml-pretty --exclude-unreachable-branches --print-summary -o coverage.xml --root .

clean:
	@echo "> Cleaning the project."
	@$(RM) -rf $(OBJ) $(BIN) $(TEST)/bin *.gcno *.gcda *.gcov $(TEST)/*.gcov

run: all
	@echo "> Running the project in $(BIN)/$(NAME)."
	@./$(BIN)/$(NAME)

registry:
	@echo "> Building a docker image from version $(VERSION)."
	@docker build -t registry.gitlab.com/olooeez/$(NAME):$(VERSION) .
	@echo "> Pushing new docker image verison $(VERSION) to container registry."
	@docker push registry.gitlab.com/olooeez/$(NAME):$(VERSION)
