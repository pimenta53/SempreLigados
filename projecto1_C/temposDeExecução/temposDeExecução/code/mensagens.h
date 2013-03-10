#include "define.h"

typedef struct mensagens {
	char *mensagem;	
	struct mensagens *next;
} Mensagens;
	
typedef struct remetente {
	long long id;
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
	int dimensao;
	Destinatario **L_mensagens;
}Lista_destinatario;









