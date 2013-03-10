#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "define.h"

int ler_numero_int(char *string) {

        int i = atoi(string);
        return i;
}

long long ler_numero_ll(char *string) {

        char *end;
        long long i = strtoll(string,&end,0);

        if ((*end)!='\0') return -1;
        return i;
}

void converte_ll_str(long long numero, char *numstr) {
        sprintf(numstr,"%lld",numero);
}

long long ler_nif(){
	
	char nifstr[MAXNIF];
	long long nif;
	int valid=0;
	
	echo();
	while(!valid){
		mvprintw(0,0,"Digite o nif:");
		getnstr(nifstr,MAXNIF);
		refresh();
		nif=ler_numero_ll(nifstr);
		if(nif==-1 || strlen(nifstr)<1 ){
			clear();
			printw("Nif invalido");
			refresh();
			getch();
		}
		else valid=1;
	}	
	noecho();
return nif;
}

int get_int(int row,int col){
	
	char nstr[4];
	int n;
	int valid=0;
	
	echo();
	while(!valid){
		mvprintw(row,col,"Digite o peso:");
		getnstr(nstr,4);
		refresh();
		n=ler_numero_int(nstr);
		if(n==-1 || strlen(nstr)<1 ){
			printw("Peso invalido\n");
			refresh();
			getch();
		}
		else valid=1;
	}	
	noecho();

return n;
}


void ler_input(char *dado,char* input, int dim,int row,int col) {
	int valid=0;

	refresh();
	echo();
	while (!valid) {
		getnstr(input,dim);
		if (strlen(input)<=1){
			mvprintw(row,col,"Insira %s válido:",dado);
			refresh();
		}
		else valid=1;
	}
	noecho();
}

int response(){
	
	int loop=1;
	char cmd;
	
	printw("Confirmar(y or n)");
	while(loop){
		cmd=getch();
		if(cmd=='y'){
			return 1;
		}
		if(cmd=='n'){
			return 0;
		}
	}

return -1;
}

char* est_civil(){
	
	char cmd;
	
	printw("\tSolteiro:1\n");
	printw("\tCasado:2\n");
	printw("\tViuvo:3\n");
	printw("\tDivorciado:4\n");
	while(1){
		refresh();
		cmd=getch();
		if(cmd=='1') return "solterio";
		if(cmd=='2') return "Casado";
		if(cmd=='3') return "Viuvo";
		if(cmd=='4') return "Divorciado";
	}
return NULL;
}

