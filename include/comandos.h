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
void comandos_formatar_remover(char *sequencia, comandos_execucao_t *comandos_execucao);

/* Mostra os comandos formatado para o stdout */
void comandos_interface_comandos(comandos_t comandos);

/* Mostra os dados do comando para o stdout */
void comandos_interface_dados_comando(comandos_execucao_t comando);

/* Mostra a informação na hora de por a sequncia de comandos */
void comandos_interface_sequencia(void);

#endif
