#include "define.h"

typedef struct mensagens {
	char mensagem[1025];	
	struct mensagens *next;
} Mensagens;
	
typedef struct remetente {
	int id;
	int n_mensagens;
	long long nif;
	Mensagens *msg;
	struct remetente *next;
}Remetente;

typedef struct lista_mensagens{
	int total_utilizadores;
	Remetente *L_mensagens[MAXNODES];
}Lista_mensagens;

/**
 * A função grava_mensagem irá guardar as mensagems de cada utilizador para um destinatario, criando uma lista de mensagens que cada utilizador recebeu.
 * @param nif1 campo correspondente ao nif de quem vamos mandar a mensagem.
 * @param nif2 campo correspondente ao nif de quem está a mandar a mensagem.
 * @param mensagem mensagem que se pretend enviar.
 * @param lm estrutura de dados onde se guarda todas as mensagens de todos os utilizadores.
 * @returns Retorna um inteiro que verifica se conseguiu ou não efectuar a operação.
 */
int grava_mensagem(long long nif1,long long nif2,char *mensagem,Lista_mensagens *lm);
/**
 * A função print_mensagens é responsavel por imprimir todas as mensagens dos diferentes destinatarios de um utilizador.
 * @param nif campo correspondente ao nif que vai ser utlizado para encontrar o id do utilizador atrves da função "findByNif"
 * @param lm estrutura de dados onde vamos ver as mensagens de cada utilizador para depois podermos imprimilas.
 * @returns Retorna um inteiro que verifica se conseguiu ou não efectuar a operação.
 */
int print_mensagens(long long nif,Lista_mensagens *lm);
