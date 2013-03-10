#include "define.h" 

//contem os dados de um perfil
typedef struct perfil{
	long long id;
	char nome[MAXNOME];
	long long nif;
	char cidade[MAXCIDADE];
	char estado_civil[MAXESTADOCIV];
	char email[MAXEMAIL];
	int apagado;
} Perfil;

typedef struct user_hash{
	Perfil *user;
	struct user_hash *next;
}User_h;

//Tabela de hash com apontadores para Perfis
//tabela para pesquisa por nome e nif
User_h *hash_nome[MAXNODES];
User_h *hash_nif[MAXNODES];

