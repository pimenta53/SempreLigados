#include "users_IO.h"
#include "define.h"
#include "relacoes.h"
#include "dados.h"
#include "users.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

int relacoes_inserir (long long nif,Grafo *g){
	
	long long nif2;
	int peso;
	int result;
	
	nif2=ler_nif();	
	peso=get_int(2,0);
	
	if(nif2==nif){
		clear();
		printw("impossivel criar ligação consigo mesmo");
		getch();
		return 0;
	}

	result = criar_relacao(nif,nif2,peso,g);
	if (result==1) {
		 printw("\nRelação criada com sucesso");
		 getch();
	}
	else{
		if (result==-1) {
			printw("\nUser não registado\n");
			getch();}	
		else {
			printw("\nJá existe relacao entre users\n");
			getch();
		}	
	}
	return 0;
}

int relacoes_apagar (long long nif,Grafo *g){
	
	long long nif2;
	int result;
	
	nif2=ler_nif();
	if(nif2==nif){
		clear();
		printw("impossivel apagar ligação consigo mesmo");
		getch();
		return 0;
	}			
	
	result = remover_relacao(nif,nif2,g);
	if (result==1) {
		 printw("\nRelação apagada com sucesso");
		 getch();}
	else {
		if (result==0) {
			printw("\nImpossivel apagar. Não existe ligação entre voces\n");
			getch();
		}
		else {
			printw("\nEste user não está registado\n");
			getch();
		}
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
		 printw("Utilizador não possui ligações deste tipo ou naõ existe\n");
		 getch();
		 return 0;
	 }
	 id=aux->id;
	 inf=g->nodos[id];
	 if (inf!=NULL) { 
		if (!inf->adjacentes) {
			clear();
			printw("Não possui relações\n");
			getch();
			return 0;
		}
		aux1=inf->adjacentes;
		while(aux1 && !sair){
			clear();
			printw("Ligação com peso %d ao utilizador:",aux1->peso);
			print_user(findByNif(aux1->nif));
			printw("Sair:q\n");
			cmd=getch();
			if(cmd=='q') sair=1;
			aux1=aux1->next;
		}
	}
	else {
		clear();
		printw("Não possui relações\n");
		getch();
		return 0;
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

int relacoes_modificar (long long nif,Grafo *rm, Grafo *new, long long *id_max){
	
	long long nif2;
	int peso;
	
	nif2=ler_nif();
	peso=get_int(2,0);
	if(nif2==nif){
		clear();
		printw("impossivel alterar ligação consigo mesmo");
		getch();
		return 0;
	}			
	
	if(alterar_relacao(id_max,nif,nif2,peso,rm,new)){
		 printw("\nRelação alterada com sucesso");
		 getch();}
	else {
		 printw("\nImpossivel alterar relação");
		 getch();}

return 1;
}

int caminho_mais_curto(long long userID, long long nif, Grafo *g) {
	
	long long nif2;
	int result;
	long long path[userID], i=0;
	int a=1;
	
	nif2=ler_nif();
	if(nif2==nif){
		clear();
		printw("Impossivel. Este é o seu nif");
		getch();
		return 0;
	}			
	
	result = procura_caminho_curto(userID,nif,nif2,path,g);
	if (result==1) {
		while (1){
			if (a==1){
				printw("{");
				a=2;
				}
			printw("%s",(findByNif(path[i]))->nome);
			i++;
			if (path[i]==-1 && i!=userID) {
				printw("}");
				break;
				}
			printw(" -> ");
		}
		getch();
    }
	else {
		if (result==0) {
			printw("Não existe ligação entre voces\n");
			getch();
		}
		else {
			printw("\nEste user não está registado\n");
			getch();
		}
	}
	return 1;
}

int procura_distanciados(long long userID, long long nif, Grafo *g) {
	int dist=0;
	int usrs[userID],i;
	long long id;
	Perfil *aux=findByNif(nif);
	
	if (!aux) {
		 clear();
		 printw("\n Erro. Utilizador não encontrado.\n");
		 getch();
		 return 0;
	}
	id=aux->id;
	dist=get_int(2,0);

	for(i=0;i<userID;i++) {
		usrs[i]=0;
    }
    if (distancia_d(id,usrs,dist,g)) {
		i=0;
		printw("\nPessoas a uma distancia %d, de si:\n\n",dist);
		while (i<userID){
			if (usrs[i]!=0) printw("%s \n",(findByNif(g->nodos[i]->nif))->nome);
			i++;
		}
		getch();
		return 1;
	}	
	printw("\nNão existem pessoas à distancia %d, de si:\n\n",dist);
	getch();
	return 0;
}

int procura_distanciados_geral(long long userID, long long nif, Grafo *a, Grafo *f, Grafo *p) {
	int dist=0;
	int usrs[userID],i;
	long long id;
	Perfil *aux=findByNif(nif);
	int res_a, res_b, res_c;
	
	clear();
	if (!aux) {
		 printw("\n Erro. Utilizador não encontrado.\n");
		 getch();
		 return 0;
	}
	id=aux->id;
	dist=get_int(2,0);

	for(i=0;i<userID;i++) {
		usrs[i]=0;
    }
    
    res_a=distancia_d(id,usrs,dist,a);
    res_b=distancia_d(id,usrs,dist,f);
    res_c=distancia_d(id,usrs,dist,p);
    
    
    if (res_a || res_b || res_c) {
		i=0;
		printw("\nPessoas a uma distancia %d, de si:\n\n",dist);
		while (i<userID){
			if (usrs[i]!=0) {
				if (a->nodos[i]) printw("%lld,",a->nodos[i]->nif);
				else {
					if (f->nodos[i]) printw("%lld,",f->nodos[i]->nif);
					else printw("%lld,",p->nodos[i]->nif);
				}
			}	
			i++;
		}
		getch();
		return 1;
	}	
	printw("\nNão existem pessoas à distancia %d, de si:\n\n",dist);
	getch();
	return 0;
}
