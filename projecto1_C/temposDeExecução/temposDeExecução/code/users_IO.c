#include <sys/time.h>
#include "define.h"
#include "users.h"
#include "dados.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

int print_user(Perfil *user){
	
	int row,col;
	
	getmaxyx(stdscr,row,col);
	if(!user) {
		mvprintw(row/2,(col-38)/2,"Utilizador não exite ou foi apagado\n");
		return 0;
	}
	
	mvprintw((row/2)-3,(col-28)/2,"------Informação User-------");
	mvprintw((row/2)-2,(col-28)/2," ID: %lld",user->id);
	mvprintw((row/2)-1,(col-28)/2," NOME:%s",user->nome);
	mvprintw((row/2),(col-28)/2," NIF:%lld",user->nif);
	mvprintw((row/2)+1,(col-28)/2," MORADA:%s",user->cidade);
	mvprintw((row/2)+2,(col-28)/2," ESTADO CIVIL:%s",user->estado_civil);
	mvprintw((row/2)+3,(col-28)/2," EMAIL:%s",user->email);
	mvprintw((row/2)+4,(col-28)/2,"----------------------------");
	move((row/2)+5,(col-28)/2);
	
	return 0;
}


int findByName(char *name){

	long long indice=F_hash_nome(name);
	User_h *aux;
	int confirm=0;
	int row,col;
	/*-----------Declaração-------------*/
		struct timeval t1,t2;
		long sec;
		long usec;
	/*--------------------------------*/
	getmaxyx(stdscr,row,col);
		
	aux=hash_nome[indice];
	if(!aux){
		clear();
		mvprintw(row/2,(col-48)/2,"Utilizador inexistente ou com conta desactivada");
		getch();
	}
	/*------------tempo inicio----------*/
        gettimeofday(&t1,NULL);
	/*--------------------------------*/
	while(aux && !confirm){
		if((strcmp(aux->user->nome,name)==0) && aux->user->apagado==0){
			clear();
			print_user(aux->user);
			confirm=response();
		}
		aux=aux->next;
	}
	/*------------tempo fim-----------*/
        gettimeofday(&t2,NULL);
        sec=(t2.tv_sec)-(t1.tv_sec);
        usec=(t2.tv_usec)-(t1.tv_usec);
        if(usec<0) usec+=1000000;
        FILE *pT = fopen("times.txt","a+");
        fprintf(pT,"pesquisa nome ->%ld s %ld us \n",sec,usec);
        fclose(pT);
	/*--------------------------------*/ 
	if(!confirm ){
		clear();
		mvprintw(row/2,(col-48)/2,"Utilizador inexistente ou com conta desactivada");
		getch();
	}

return 0;	
}

int pesquisa_nif(){
		
		long long nif;
		
		/*-----------Declaração-------------*/
		struct timeval t1,t2;
		long sec;
		long usec;
		/*--------------------------------*/
		
		nif=ler_nif(); 
		/*------------tempo inicio----------*/
        gettimeofday(&t1,NULL);
		/*--------------------------------*/
		Perfil *user=findByNif(nif);
		/*------------tempo fim-----------*/
        gettimeofday(&t2,NULL);
        sec=(t2.tv_sec)-(t1.tv_sec);
        usec=(t2.tv_usec)-(t1.tv_usec);
        if(usec<0) usec+=1000000;
        FILE *pT = fopen("times.txt","a+");
        fprintf(pT,"pesquisar por nif ->%ld s %ld us \n",sec,usec);
        fclose(pT);
		/*--------------------------------*/
		if(user && user->apagado==0){
			print_user(user);
			getch();
		}
		else{
			clear();
			printw("utilizador não existe ou foi apagado");
			getch();
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
		mvprintw(2,0,"Digite o seu email:");	
		ler_input("email",email,MAXEMAIL,2,0);
		mvprintw(3,0,"Digite a sua cidade:");
		ler_input("cidade",cidade,MAXCIDADE,3,0);
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
		if(response()){
			user->apagado=0;
			clear();
			printw("Conta reactivada com sucesso");
			getch();
			return 1;
		}
	}
	
return 0;
}

