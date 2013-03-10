#include "erro.h"
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
	Lista_destinatario *lm;
	long long  userID=0;
	
	carregar_bd("users.bin",&userID);
	if (inicia_mensagens(userID,&lm)==0) return 0;
	
	initscr();
	noecho();
	keypad(stdscr, TRUE);
	cbreak();
	start_color();
	init_pair(5, COLOR_BLUE, COLOR_BLACK);
	attrset(COLOR_PAIR(5));
	attron(A_BOLD );
	
	inicia_grafos(userID,&ami,&fam,&prof);
	ler_relacoes("relacoes.bin",&ami,&fam,&prof);
	menu_principal(&ami,&fam,&prof,&userID,lm);
	guardar_relacoes("relacoes.bin",&ami,&fam,&prof);
	guardar_bd("users.bin",&userID);
	guarda_msg_ficheiro("mensagens.bin",lm);
	limpar_grafos(&ami,&fam,&prof);
	limpa_hash(&userID);
	limpa_mensagens(lm);
	endwin();

	return 0;	
}

