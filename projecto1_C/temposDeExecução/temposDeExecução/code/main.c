#include <sys/time.h>
#include "erro.h"
#include "relacoes_FILE.h"
#include "define.h"
#include "users.h"
#include "users_file.h"
#include "menus.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

void imprime(){
	
	int i;User_h *lista;
	/*-----------Declaração-------------*/
		struct timeval t1,t2;
		long sec;
		long usec;
	/*--------------------------------*/
	
	/*------------tempo inicio----------*/
        gettimeofday(&t1,NULL);
	/*--------------------------------*/
	for(i=0;i<MAXNODES;i++) {
		lista=hash_nif[i];
		while (lista) {
			printf(" ID: %lld",lista->user->id);
			printf(" NOME:%s",lista->user->nome);
			printf(" NIF:%lld",lista->user->nif);
			printf(" MORADA:%s",lista->user->cidade);
			printf(" ESTADO CIVIL:%s",lista->user->estado_civil);
			printf(" EMAIL:%s",lista->user->email);
		lista=lista->next;
        }
	}
	/*------------tempo fim-----------*/
        gettimeofday(&t2,NULL);
        sec=(t2.tv_sec)-(t1.tv_sec);
        usec=(t2.tv_usec)-(t1.tv_usec);
        if(usec<0) usec+=1000000;
        FILE *pT = fopen("times.txt","a+");
        fprintf(pT,"imprimir ->%ld s %ld us \n",sec,usec);
        fclose(pT);
	/*--------------------------------*/

}


void percorre(){
	
	int i;User_h *lista;
	/*-----------Declaração-------------*/
		struct timeval t1,t2;
		long sec;
		long usec;
	/*--------------------------------*/
	
	/*------------tempo inicio----------*/
        gettimeofday(&t1,NULL);
	/*--------------------------------*/
	for(i=0;i<MAXNODES;i++) {
		lista=hash_nif[i];
		while (lista) {
		lista=lista->next;
        }
	}
	/*------------tempo fim-----------*/
        gettimeofday(&t2,NULL);
        sec=(t2.tv_sec)-(t1.tv_sec);
        usec=(t2.tv_usec)-(t1.tv_usec);
        if(usec<0) usec+=1000000;
        FILE *pT = fopen("times.txt","a+");
        fprintf(pT,"percorre ->%ld s %ld us \n",sec,usec);
        fclose(pT);
	/*--------------------------------*/

}

int main(){
	
	Grafo ami, fam, prof;
	Lista_destinatario *lm;
	long long  userID=0;
	
	carregar_bd("users.bin",&userID);
	percorre();
	imprime();
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

