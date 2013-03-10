#include "relacoes_FILE.h"
#include "define.h"
#include "users.h"
#include "users_file.h"
#include "menus.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>


int main(){
	
	
	Grafo ami, fam, prof;
	Lista_destinatario *lm=malloc(sizeof(Lista_destinatario));
	lm->num_mensagens=0;
	long long  userID=0;
	
	carregar_bd("resultado.csv",&userID);
	inicia_grafos(100,&ami,&fam,&prof);
	ler_relacoes("relacoes.bin",&ami,&fam,&prof);
	menu_principal(&ami,&fam,&prof,&userID,lm);

return 0;	
}

