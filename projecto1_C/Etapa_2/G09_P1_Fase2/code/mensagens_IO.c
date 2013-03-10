#include "define.h"
#include "mensagens.h"
#include "users.h"
#include "users_IO.h"
#include "dados.h"
#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>

int print_mensagens(long long nif,Lista_destinatario *ld){
	
	Perfil *user=findByNif(nif);
	long long id;
	char cmd;
	int sair=0;
	
	if(!user){
		printw("Não existe nenhum utilizador com este nif\n");
		getch();
		return 0;
	}
	
	id=user->id;
	
	if(!ld->L_mensagens[id]){
		printw("\nNão tem mensagens\n\n");
		getch();
		return 0;
		}
	
	Remetente *aux_rem=ld->L_mensagens[id]->remetentes;
	Mensagens *aux_msg;
	
	while (aux_rem && !sair){
		aux_msg=aux_rem->msg;
		user = findByNif(aux_rem->nif);
		while(aux_rem->msg!=NULL && !sair){
			printw ("\n-----------------------------------");
			printw ("\n\nEnviadas por pelo utilizador(a) %s\n\n", user->nome);
			printw("%s\n\n",aux_rem->msg->mensagem);
			printw("Sair:q \n");
			printw ("-----------------------------------\n\n");
			cmd=getch();
			clear();
			if(cmd=='q') sair=1;
			aux_rem->msg=aux_rem->msg->next;
		}
	aux_rem->msg=aux_msg;
	aux_rem=aux_rem->next;
	}
	
	
return 1;
}

int escrever_mensagem(long long nif1,Lista_destinatario *ld){
	
	char msg[MAXMSG];
	long long nif2;
	
	
	nif2=ler_nif();	
	echo();	
	printw("Digite a sua mensagem:\n");
	getnstr(msg,MAXMSG-1);
	
	
	if(grava_mensagem(nif1,nif2,msg,ld)){
		clear();
		printw("Mensagem enviada com sucesso");
		getch();
	}
	else{
		clear();
		printw("Impossivel enviar mensagem");
		getch();
	}
	noecho();
return 0;
}

int ver_popular(Lista_destinatario *ld){
	
	Perfil *user=findByNif(ld->nif_popular);
	
	if(user) print_user(user);
	else{
		clear();
		printw("Ainda ninguem recebeu mensagens");
		getch();
	}

return 0;
}
