#include "define.h"
#include "users.h"
#include "users_file.h"
#include "relacoes_FILE.h"
#include "dados.h"
#include "mensagens_IO.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void logo(int row,int col,char *menu){
		mvprintw((row/2)-4,(col-32)/2,"#################################\n");
		mvprintw((row/2)-3,(col-32)/2,"#################################\n");
		if(menu) mvprintw((row/2)-2,(col-strlen(menu)-8)/2,"**  %s  **\n",menu);
		else mvprintw((row/2)-2,(col-32)/2,"->        SEMPRE LIGADOS       <-\n");
		mvprintw((row/2)-1,(col-32)/2,"#################################\n");
		mvprintw((row/2),(col-32)/2,"#################################\n");
}

int menu_pesquisa(long long *userID){

	char cmd;
	int row,col;
	
	while(1){
		clear();
		getmaxyx(stdscr,row,col);
		logo(row,col,"PESQUISA");
		mvprintw(row-3,0,"Por nif:1");
		mvprintw(row-2,0,"Por nome:2");
		mvprintw(row-1,0,"Voltar atras:0");
		refresh();
		cmd=getch();
		switch (cmd) {
			case ('1'): 
				clear();
				pesquisa_nif();			
				break;
			case ('2'): 
				clear();
				pesquisa_nome();	
				break;
			case ('0'): 
				return 0;		
				break;
		}
	}	
return 0;
}

int menu_alterar_relacao(long long nif,Grafo *f,Grafo *a,Grafo *p, long long *userID){
	char cmd;
	int row,col,n=1;
	
	Grafo *rm=NULL;
	Grafo *new=NULL;
	
	while(n<3){
		clear();
		getmaxyx(stdscr,row,col);
		if (n==1) logo(row,col,"RELACAO A ALTERAR");
		if (n==2) logo(row,col,"NOVA RELACAO");
		mvprintw(row-4,0,"Relações de amizade:1");
		mvprintw(row-3,0,"Relações familiares:2");
		mvprintw(row-2,0,"Relaçoes profissionais:3");
		mvprintw(row-1,0,"Voltar atras:0");
		refresh();
		cmd=getch();
			switch (cmd) {
			case ('1'): 
				if (n==1) rm = a;
				if (n==2) new = a;
				n++;
				break;
			case ('2'): 
				if (n==1) rm = f;
				if (n==2) new = f;
				n++;
				break;
			case('3'):
				if (n==1) rm = p;
				if (n==2) new = p;
				n++;
				break;
			case ('0'): 
				return 0;		
				break;
		}
	}
	clear();
	if(!relacoes_modificar (nif, rm, new, userID)){
		mvprintw(row/2,(col-38)/2,"não possui a relação que prentende mudar");
		getch();
	}
return 1;	
	
}

int menu_relacao(long long nif,Grafo *g,long long *userID,char *relacao){
	
	char cmd;
	int row,col;
	
	while(1){
		clear();
		getmaxyx(stdscr,row,col);
		logo(row,col,relacao);
		mvprintw(row-7,0,"Nova relação:1");
		mvprintw(row-6,0,"Apagar relação:2");
		mvprintw(row-5,0,"Ver pessoas ligadas a si:3");
		mvprintw(row-4,0,"Ver pessoas ligadas a outra pessoa:4");
		mvprintw(row-3,0,"Ver pessoas ligadas a uma certa distancia:5");
		mvprintw(row-2,0,"Ver distancia mais curta a outra pessoa:6");
		mvprintw(row-1,0,"Voltar atras:0");
		refresh();
		cmd=getch();
		switch (cmd) {
			case ('1'): 
				clear();
				relacoes_inserir(nif,g);
				clear();			
				break;
			case ('2'): 
				clear();
				relacoes_apagar(nif,g);
				break;
			case ('3'): 
				clear();
				ver_relacao(nif,g);
				break;
			case ('4'):
				clear();
				ver_relacao(ler_nif(),g);
				break;
			case('5'):
				clear();
				procura_distanciados((*userID),nif,g);
				break;
			case('6'):
				clear();
				caminho_mais_curto((*userID),nif,g);
				break;
			case('0'):
				return 0;
				break;		
		}
	}
return 0;
}


int menu_relacoes(long long nif,Grafo *f,Grafo *a,Grafo *p,long long *userID){
	char cmd;
	int row,col;
	
	while(1){
		clear();
		getmaxyx(stdscr,row,col);
		logo(row,col,"RELACOES");
		mvprintw(row-6,0,"Relações de amizade:1");
		mvprintw(row-5,0,"Relações familiares:2");
		mvprintw(row-4,0,"Relaçoes profissionais:3");//não sabia onde meter isto, como tá relacionado com as msg veio paki
		mvprintw(row-3,0,"Alterar relação:4");
		mvprintw(row-2,0,"Ver pessoas ligadas a uma certa distancia:5");
		mvprintw(row-1,0,"Voltar atras:0");
		refresh();
		cmd=getch();
			switch (cmd) {
			case ('1'): 
				menu_relacao(nif,a,userID,"AMIGOS"); // passar grafo correspondente	
				break;
			case ('2'): 
				menu_relacao(nif,f,userID,"FAMILIA"); // passar grafo correspondente
				break;
			case('3'):
				menu_relacao(nif,p,userID,"COLEGAS DE PROFISSAO"); // passar grafo correspondente
			case('4'):
				menu_alterar_relacao(nif,f,a,p,userID);
			case('5'):
				procura_distanciados_geral(*userID,nif,a,f,p);	
				break;
			case ('0'): 
				return 0;		
				break;
		}
	}
	return 0;
}




int menu_mensagens(long long nif,long long *userID,Lista_destinatario *lm){
	char cmd;
	int row,col;
	
	while(1){
		clear();
		getmaxyx(stdscr,row,col);
		logo(row,col,"MENSAGENS");
		mvprintw(row-4,0,"Ver mensagens recebidas:1");
		mvprintw(row-3,0,"Enviar mensagem:2");
		mvprintw(row-2,0,"Ver utilizador mais popular:3");//não sabia onde meter isto, como tá relacionado com as msg veio paki
		mvprintw(row-1,0,"Voltar atras:0");
		refresh();
		cmd=getch();
		switch (cmd) {
			case ('1'): 
				clear();
				print_mensagens(*userID,nif,lm);			
				break;
			case ('2'): 
				clear();
				escrever_mensagem(*userID,nif,lm);	
				break;
			case('3'):
				clear();
				ver_popular(lm);
				break;
			case ('0'): 
				return 0;		
				break;
		}
	}

return 0;
}
	


int menu_utilizador(long long nif,Grafo *f,Grafo *a,Grafo *p,long long *userID,Lista_destinatario *lm){
	
	int row,col;
	char cmd;
	char *nome=findByNif(nif)->nome;
		
	while(1){
		getmaxyx(stdscr,row,col);
		clear();
		logo(row,col,nome);
		mvprintw(row-7,0,"Procurar pessoa:1");
		mvprintw(row-6,0,"Relações:2");
		mvprintw(row-5,0,"Mensagens:3");
		mvprintw(row-4,0,"Apagar conta:4");
		mvprintw(row-3,0,"Editar conta:5");
		mvprintw(row-2,0,"Gravar:6");
		mvprintw(row-1,0,"Sair:0");
		refresh();
		cmd=getch();
		switch (cmd) {
			case ('1'): 
				clear();
				menu_pesquisa(userID);			
				break;
			case ('2'): 
				act_tamanho_array(userID,a,f,p);
				menu_relacoes(nif,f,a,p,userID);
				break;
			case ('3'): 
				menu_mensagens(nif,userID,lm);
				break;
			case ('4'):
				apagar_user(nif);
				clear();
				mvprintw(row/2,(col-20)/2,"Utilizador apagado");
				getch();
				return 0;
				break;
			case('5'):
				clear();
				editar(nif);
				break;
			case('6'):
				guardar_relacoes("relacoes.bin",a,f,p);
				guardar_bd("users.bin",userID);
				guarda_msg_ficheiro("mensagens.bin",lm);
				break;
			case('0'):
				return 0;
				break;		
		}		
	}
return 0;
}

int menu_login(Grafo *f,Grafo *a,Grafo *p,long long *userID,Lista_destinatario *lm){
	
	int login=1;
	int row,col;
	char cmd;
	long long nif;
	Perfil *user;
	
		
	while(login){
		getmaxyx(stdscr,row,col);
		clear();
		logo(row,col,"LOGIN");
		mvprintw((row)-2,0,"Efetuar login:1");
		mvprintw((row)-1,0,"Sair:0");
		refresh();
		cmd=getch();
		if(cmd=='0') return 0;
		if(cmd=='1'){
			nif=ler_nif();
			user=findByNif(nif);
			if(user && user->apagado==0) login=0;
			else {
				clear();
				mvprintw(row/2,(col-15)/2,"Ainda não está registado");
				getch();
				}
		}
	}
	
	
	clear();
	mvprintw((row/2)-2,(col-15)/2,"Login efectuado com sucesso");
	getch();
	clear();
	menu_utilizador(nif,f,a,p,userID,lm);
	
	
return 0;
}

int menu_principal(Grafo *a,Grafo *f,Grafo *p,long long *userID,Lista_destinatario *lm){

	int row,col;
	char cmd;
	
	while(1){
		getmaxyx(stdscr,row,col);
		clear();
		logo(row,col,NULL);
		mvprintw((row)-3,0,"Login:1");
		mvprintw((row)-2,0,"Registar:2");
		mvprintw((row)-1,0,"Sair:0");
		refresh();
		cmd=getch();
		switch (cmd) {
			case ('1'): 
				clear();
				menu_login(f,a,p,userID,lm);			
				break;
			case ('2'): 
				clear();
				criar_user(userID);			
				break;
			case ('0'): 
				endwin();
				return 0;		
				break;
		}
	}
	return 0;
}

