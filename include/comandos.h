#ifndef INCLUDE_COMANDOS_H
#define INCLUDE_COMANDOS_H

// Algumas regras para os comandos
#define COMANDOS_MINIMO 3
#define COMANDOS_MAXIMO 4
#define COMANDO_ACAO_MINIMO 2
#define COMANDO_ACAO_MAXIMO 4

// Ação para os comandos
typedef enum {
	N,
	E,
	D,
	F,
} acoes_t;

// Definição do tipo de ações
typedef struct {
	acoes_t acoes[COMANDOS_MAXIMO][COMANDO_ACAO_MAXIMO];
} comandos_t;

// Definição do tipo que vai ser armazenado nas estrutura de dados
typedef struct {
	size_t acao_index;
	size_t acao_vezes;
} comandos_execucao_t;

/* Inicia os comandos aleatoriamente */
comandos_t comandos_iniciar(void);

/* Recebe uma sequencia de comandos do stdin, os formata e remove eles */
void comando_formatar_remover(char *sequencia, comandos_execucao_t *comandos_execucao);

/* Atrapalha todos os comandos */
void comando_atrapalha(acoes_t comandos[COMANDOS_MAXIMO][COMANDO_ACAO_MAXIMO]);

#endif
