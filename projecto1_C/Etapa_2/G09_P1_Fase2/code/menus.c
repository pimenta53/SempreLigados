#include "define.h"
#include "users.h"
#include "users_file.h"
#include "relacoes_FILE.h"
#include "users_IO.h"
#include "dados.h"
#include "mensagens_IO.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

int menu_pesquisa(int row,int col,long long *userID){

	char cmd;
	long long nif;
	
	while(1){
		clear();
		mvprintw(row-4,0,"Por nif:1");
		mvprintw(row-3,0,"Por nome:2");
		mvprintw(row-2,0,"Voltar atras:0");
		mvprintw(row-1,0,"Sair:9");
		refresh();
		cmd=getch();
		if(cmd=='0') return 0;
		if(cmd=='9'){
			endwin();
			guardar_bd("resultado.csv",userID);
			limpa_hash(userID);
			exit(0); 
		}
		if(cmd=='1'){
			nif=ler_nif();
			clear();
			pesquisa_nif(nif);
			getch();
		}
		if(cmd=='2'){
			clear();
			pesquisa_nome();
			getch();
		}
	}
	
return 0;
}


int menu_relacao(int row,int col,long long nif,Grafo *g,long long *userID){
	
	char cmd;
	
	
	while(1){
		clear();
		mvprintw(row-7,0,"Nova relão:1");
		mvprintw(row-6,0,"Apagar relação:2");
		mvprintw(row-5,0,"Ver pessoas ligadas a si:3");
		mvprintw(row-4,0,"Ver pessoas ligadas a outra pessoa:4");
		mvprintw(row-3,0,"Ver pessoas ligadas a uma certa distancia:5");
		mvprintw(row-2,0,"Voltar atras:0");
		mvprintw(row-1,0,"Sair:9");
		refresh();
		cmd=getch();
		if(cmd=='0') return 0;
		if(cmd=='9'){
			endwin();
			guardar_bd("resultado.csv",userID);
			limpa_hash(userID);
			exit(0);
		}
		if(cmd=='1'){
			clear();
			relacoes_inserir (nif,g);
			clear();
		}
		if(cmd=='2'){
			clear();
			relacoes_apagar(nif,g);
			clear();
		}
		if(cmd=='3'){
			clear();
			ver_relacao(nif,g);
		}
		if(cmd=='4'){
			clear();
			ver_relacao(ler_nif(),g);
		}
		if(cmd=='5'){
			clear();
			relacao_distancia(nif,g,get_int());
		}
	}
return 0;
}


int menu_relacoes(int row,int col,long long nif,Grafo *f,Grafo *a,Grafo *p,long long *userID){
	char cmd;
	
	
	while(1){
		clear();
		mvprintw(row-6,0,"Relações de amizade:1");
		mvprintw(row-5,0,"Relações familiares:2");
		mvprintw(row-4,0,"Relaçoes profissionais:3");//não sabia onde meter isto, como tá relacionado com as msg veio paki
		mvprintw(row-3,0,"Alterar relação:4");
		mvprintw(row-2,0,"Voltar atras:0");
		mvprintw(row-1,0,"Sair:9");
		refresh();
		cmd=getch();
		if(cmd=='0') return 0;
		if(cmd=='9'){
			endwin();
			guardar_relacoes("relacoes.bin",a,f,p);
			guardar_bd("resultado.csv",userID);
			limpar_grafos(a,f,p);
			limpa_hash(userID);
			exit(0); // e falta gravar
		}
		if(cmd=='1'){
			menu_relacao(row,col,nif,a,userID); // passar grafo correspondente
		}
		if(cmd=='2'){
			menu_relacao(row,col,nif,f,userID); // passar grafo correspondente
		}
		if(cmd=='3'){
			menu_relacao(row,col,nif,p,userID); // passar grafo correspondente
		}
		if(cmd=='4'){
			// alterar grafo
		}
	}
return 0;
}




int menu_mensagens(int row,int col,long long nif,long long *userID,Lista_destinatario *lm){
	char cmd;
	
	
	while(1){
		clear();
		mvprintw(row-5,0,"Ver mensagens recebidas:1");
		mvprintw(row-4,0,"Enviar mensagem:2");
		mvprintw(row-3,0,"Ver utilizador mais popular:3");//não sabia onde meter isto, como tá relacionado com as msg veio paki
		mvprintw(row-2,0,"Voltar atras:0");
		mvprintw(row-1,0,"Sair:9");
		refresh();
		cmd=getch();
		if(cmd=='0') return 0;
		if(cmd=='9'){
			endwin();
			guardar_bd("resultado.csv",userID);
			limpa_hash(userID);
			exit(0); // e falta gravar
		}
		if(cmd=='1'){
			clear();
			print_mensagens(nif,lm);
		}
		if(cmd=='2'){
			clear();
			escrever_mensagem(nif,lm);
		}
		if(cmd=='3'){
			clear();
			ver_popular(lm);
		}
	}
return 0;
}
	


int menu_utilizador(int row,int col,long long nif,Grafo *f,Grafo *a,Grafo *p,long long *userID,Lista_destinatario *lm){
	


	char cmd;
	
	
	while(1){
		clear();
		mvprintw(row-7,0,"Procurar pessoa:1");
		mvprintw(row-6,0,"Relações:2");
		mvprintw(row-5,0,"Mensagens:3");
		mvprintw(row-4,0,"Apagar conta:4");
		mvprintw(row-3,0,"Editar conta:5");
		mvprintw(row-2,0,"Voltar atras:0");
		mvprintw(row-1,0,"Sair:9");
		refresh();
		cmd=getch();
		if(cmd=='0') return 0;
		if(cmd=='9'){
			endwin();
			guardar_relacoes("relacoes.bin",a,f,p);
			guardar_bd("resultado.csv",userID);
			limpar_grafos(a,f,p);
			limpa_hash(userID);
			exit(0); // e falta gravar
		}
		if(cmd=='1'){
			clear();
			menu_pesquisa(row,col,userID);  // por a sacar outro nif numa função
		}
		if(cmd=='2'){
			menu_relacoes(row,col,nif,f,a,p,userID);
		}
		if(cmd=='3'){
			menu_mensagens(row,col,nif,userID,lm);
		}
		if(cmd=='4'){
			apagar_user(nif);
			clear();
			printw("Utilizador apagado");
			getch();
			return 0;
		}
		if(cmd=='5'){
			clear();
			editar(nif);
		}
	}
return 0;
}

int menu_login(int row,int col,Grafo *f,Grafo *a,Grafo *p,long long *userID,Lista_destinatario *lm){
	

	int login=1;
	char cmd;
	long long nif;
	Perfil *user;
	
		
	while(login){
		clear();
		mvprintw(row-2,0,"Voltar atras:0");
		mvprintw(row-1,0,"Sair:9");
		mvprintw((row-3),0,"Efetuar login:1");
		refresh();
		cmd=getch();
		if(cmd=='0') return 0;
		if(cmd=='9'){
			endwin();
			guardar_relacoes("relacoes.bin",a,f,p);
			guardar_bd("resultado.csv",userID);
			limpar_grafos(a,f,p);
			limpa_hash(userID);
		}
		if(cmd=='1'){
			nif=ler_nif();
			user=findByNif(nif);
			if(user && user->apagado==0) login=0;
			else {
				printw("Ainda não está registado");
				getch();
				}
		}
	}
	

	
	
	clear();
	mvprintw((row/2)-2,col/2,"Login efectuado com sucesso");
	getch();
	clear();
	menu_utilizador(row,col,nif,f,a,p,userID,lm);
	
	
return 0;
}

int menu_principal(Grafo *a,Grafo *f,Grafo *p,long long *userID,Lista_destinatario *lm){

	int row,col;
	char cmd;
	
	initscr();
	noecho();
	cbreak();
	start_color();
	init_pair(5, COLOR_WHITE, COLOR_BLACK);
	attrset(COLOR_PAIR(5));
	
	
	while(1){
		getmaxyx(stdscr,row,col);
		clear();
		mvprintw((row/2)-2,col/2,"Login:1");
		mvprintw((row/2),col/2,"Registar:2");
		mvprintw((row/2)+2,col/2,"Sair:0");
		refresh();
		cmd=getch();
		if(cmd == '1') {
			clear();
			menu_login(row,col,f,a,p,userID,lm);}
		if(cmd =='2' ) {
			clear();
			criar_user(userID);}
		if(cmd == '0'){
			endwin();
			guardar_relacoes("relacoes.bin",a,f,p);
			guardar_bd("resultado.csv",userID);
			limpar_grafos(a,f,p);
			limpa_hash(userID);
			exit(0);
		}
	}


return 0;
}
