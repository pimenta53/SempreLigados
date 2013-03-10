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

typedef struct destinatario {
	int total_mensagens;
	Remetente *remetentes;
	} Destinatario;

typedef struct lista_destinatario{
	long long nif_popular;
	int num_mensagens;
	Destinatario *L_mensagens[MAXNODES];
}Lista_destinatario;

/**
 * A função mais_popular irá testar, cada vez que e enviada uma nova mensagem, se o utilizador que a recebeu tem mais mensagens do que o utilizador mais popular, caso tenha, este será o novo utilizador mais popular.
 * @param total_msg campo correspondente ao total de mensagens recebidas pelo utilizador que recebeu a mensagem.
 * @param n_nif campo correspondente ao nif do utilizador que recebeu a mensagem.
 * @param lm estrutura de dados onde se guarda todas as mensagens de todos os utilizadores.
 * @returns Retorna um inteiro que verifica se conseguiu ou não efectuar a operação.
 */
int mais_popular (int total_msg, long long n_nif, Lista_destinatario *ld);
/**
 * A função grava_mensagem irá guardar as mensagems de cada utilizador para um destinatario, criando uma lista de mensagens que cada utilizador recebeu.
 * @param nif1 campo correspondente ao nif de quem vamos mandar a mensagem.
 * @param nif2 campo correspondente ao nif de quem está a mandar a mensagem.
 * @param mensagem mensagem que se pretend enviar.
 * @param lm estrutura de dados onde se guarda todas as mensagens de todos os utilizadores.
 * @returns Retorna um inteiro que verifica se conseguiu ou não efectuar a operação.
 */
int grava_mensagem(long long nif1,long long nif2,char *mensagem,Lista_destinatario *ld);
