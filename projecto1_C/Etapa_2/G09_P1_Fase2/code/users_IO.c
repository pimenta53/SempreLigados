#include "define.h"
#include "users.h"
#include "dados.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

int  print_user(Perfil *user){
	if(!user) {
		printw("Utilizador não exite ou foi apagado\n");
		return 0;
	}
	
	printw("\n------Informação User-------\n");
	printw(" ID %lld\n",user->id);
	printw(" NOME:%s\n",user->nome);
	printw(" CIDADE:%s\n",user->cidade);
	printw(" ESTADO CIVIL:%s\n",user->estado_civil);
	printw(" EMAIL:%s\n",user->email);
	printw(" NIF:%lld\n",user->nif);
	printw("\n----------------------------\n");
	
	return 0;
}

int findByName(char *name){
	
	long long IDname;
	User_h *aux;
	int valid=0;
	IDname=F_hash_nome(name);
	if(!(aux=hash_nome[IDname])) return 0;
	
	while(aux && !valid){
		if(strcmp(aux->user->nome,name)==0 && aux->user->apagado!=1){
		clear();
		print_user(aux->user);
		valid=reposta();
		}
		aux=aux->next;
		
	}
	
	if(!aux || aux->user->apagado==1){
		clear();
		printw("Utilizador não exite ou foi apagado\n");
	}
	
return 1;
}

int pesquisa_nif(long long nif){
		
		Perfil *user=findByNif(nif);
		if(user && user->apagado==0) print_user(user);
		else{
			clear();
			printw("utilizador não existe ou foi apagado");
		}

return 0;
}

int pesquisa_nome(){
	
	char nome[MAXNOME];

	mvprintw(1,0,"Digite o nome:");
	ler_input("nome",nome,MAXNOME,1,0);
	findByName(nome);
	


return 0;
}


int editar(long long nif){
	
	char cidade[MAXCIDADE];
	char email[MAXEMAIL];
	char *estado_civil;
	
	mvprintw(0,0,"Digite a sua cidade:");
	refresh();
	ler_input("cidade",cidade,MAXCIDADE,0,0);
	mvprintw(1,0,"Digite o seu email:");
	refresh();	
	ler_input("email",email,MAXEMAIL,1,0);
	mvprintw(2,0,"Estado civil:\n");
	refresh();
	estado_civil=est_civil();
	editar_perfil(cidade,estado_civil,email,nif);
	
return 0;
}

int criar_user(long long *IdUsers) {
			
	char nome[MAXNOME];
	char cidade[MAXCIDADE];
	char email[MAXEMAIL];
	char *estado_civil;
	long long nif;
	Perfil *user;

	nif=ler_nif();	
	user=findByNif(nif);
	
	
	if(!user){
		echo();
		mvprintw(1,0,"Digite o seu nome:");
		ler_input("nome",nome,MAXNOME,1,0);
		mvprintw(2,0,"Digite a sua cidade:");
		ler_input("cidade",cidade,MAXCIDADE,2,0);
		mvprintw(3,0,"Digite o seu email:");	
		ler_input("email",email,MAXEMAIL,3,0);
		mvprintw(4,0,"Estado civil:\n");
		estado_civil=est_civil();
		noecho();
		inserir_user(IdUsers,nome,cidade,estado_civil,email,nif);
		clear();
		printw("utilizador registado com com sucesso\n");
		getch();
		return 1;
	}
	if(user->apagado==0){
		clear();
		printw("utilizador com este nif já se encontra registado");
		getch();
		return 1;
	}
	if(user->apagado==1){
		clear();
		printw("deseja reactivar a sua conta?\n");
		if(reposta()){
			user->apagado=0;
			clear();
			printw("Conta reactivada com sucesso");
			getch();
			return 1;
		}
	}
	
return 0;
}
