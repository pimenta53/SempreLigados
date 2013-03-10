#include "define.h"
#include "relacoes.h"
#include "dados.h"
#include "users.h"
#include "users_IO.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

int relacoes_inserir (long long nif,Grafo *g){
	
	
	long long nif2;
	int peso;
	
	nif2=ler_nif();	
	peso=get_int(2,0);
	
	if(nif2==nif){
		clear();
		printw("impossivel criar ligação consigo mesmo");
		getch();
		return 0;
	}

	if((criar_relacao(nif,nif2,peso,g))){
		 printw("\nRelação criada com sucesso");
		 getch();}
	else{
		 printw("\nImpossivel criar ligação\n");
		getch();}
		
		
return 0;
}

int relacoes_apagar (long long nif,Grafo *g){
	
	long long nif2;
	
	
	nif2=ler_nif();
	if(nif2==nif){
		clear();
		printw("impossivel apagar ligação consigo mesmo");
		getch();
		return 0;
	}			
	
	if(remover_relacao(nif,nif2,g)){
		 printw("\nRelação apagada com sucesso");
		 getch();}
	else {
		printw("\nImpossivel apagar ligação, utilizadore(s) inexistente(s)\n");
		getch();
	}
return 0;
}

int ver_relacao(long long nif,Grafo *g){
	
	long long id;
	Perfil *aux=findByNif(nif);
	Info *inf;
	Adj *aux1;
	int sair=0;
	char cmd;
	
	if (!aux){
		 clear();
		 printw("\n a pessoa não existe ou não possui ligações\n");
		 getch();
		 return 0;
	 }
	 id=aux->id;
	 inf=g->nodos[id];
	 if (inf!=NULL) { 
		aux1=inf->adjacentes;
		while(aux1 && !sair){
			clear();
			printw("Sair:q\n");
			printw("Ligação com peso %d ao utilizador:",aux1->peso);
			print_user(findByNif(aux1->nif));
			cmd=getch();
			if(cmd=='q') sair=1;
			aux1=aux1->next;
		}
	}
	return 1;
}

int relacao_distancia(long long nif,Grafo *g,int peso){
	
	long long id;
	Perfil *aux=findByNif(nif);
	Info *inf;
	Adj *aux1;
	int sair=0;
	char cmd;
	
	if (!aux){
		 clear();
		 printw("\n a pessoa não existe ou não possui ligações\n");
		 getch();
		 return 0;
	 }
	 id=aux->id;
	 inf=g->nodos[id];
	 if (inf!=NULL) {
		aux1=inf->adjacentes; 
		if (aux1!=NULL) {
			while(aux1 && !sair){
				if(aux1->peso==peso){
					clear();
					printw("Sair:q\n");
					printw("Ligação com peso %d ao utilizador:",aux1->peso);
					print_user(findByNif(aux1->nif));
					cmd=getch();
					if(cmd=='q') sair=1;
				}
				aux1=aux1->next;
			}
		}
		else printw("\n não possui ligações\n");
	}
	
	return 1;
}

