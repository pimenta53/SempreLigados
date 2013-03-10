#include "relacoes.h"
#include "operacoes.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int inserir_ligacao(long long nif1,long long nif2,int peso,Grafo *g){
	
	Perfil *aux1=findByNif(nif1);
	Perfil *aux2=findByNif(nif2);
	
	Adj *novo, *novo2;
	Adj *auxiliar;
	long long id1 = aux1->id;
	long long id2 = aux2->id;
	
	if(!aux1 || !aux2){
		printf(" Impossivel criar ligação, utilizador/s inexistente\n");
		return 0;
	} 
	
	//adicionar num dos utilizadores
	auxiliar = g->nodos[id1];
	
	
	if (g->nodos[id1]==NULL) {
		g->ocupados++;
		novo = malloc(sizeof(Adj));
		novo->id = id2;
		novo->peso = peso;
		novo->nif = nif2;
		novo->next=NULL;
		g->nodos[id1]=novo;
	}
	else {
		if (g->nodos[id1]->id==id2) g->nodos[id1]->peso=peso;
		else {
		while (auxiliar->next!=NULL && auxiliar->id!=id2){
			 auxiliar=auxiliar->next;
			 }
		if (auxiliar->id==id2) auxiliar->peso=peso;
		else {
		novo = malloc(sizeof(Adj));
		novo->id = id2;
		novo->peso = peso;
		novo->nif = nif2;
		novo->next=auxiliar->next;
		auxiliar->next=novo;
		}
		}
	}
		
	//adicionar no outro
	auxiliar = g->nodos[id2];
	
	if (g->nodos[id2]==NULL) {
		g->ocupados++;
		novo2 = malloc(sizeof(Adj));
		novo2->id = id1;
		novo2->peso = peso;
		novo2->nif = nif1;
		novo2->next=NULL;
		g->nodos[id2]=novo2;
	}
	else {
		if (g->nodos[id1]->id==id1) g->nodos[id2]->peso=peso;
		else {
		while (auxiliar->next!=NULL && auxiliar->id!=id1){
			 auxiliar=auxiliar->next;
			 }
		if (auxiliar->id==id1) auxiliar->peso=peso;
		else {
		novo2 = malloc(sizeof(Adj));
		novo2->id = id1;
		novo2->peso = peso;
		novo2->nif = nif1;
		novo2->next=auxiliar->next;
		auxiliar->next=novo2;
		}
		}
	}

	return 1;
}

int remover(long nif1, long nif2, char *relacao, Grafo *g) {
	
	Perfil *p1=findByNif(nif1);
	Perfil *p2=findByNif(nif2);
	if(!p1 || !p2) {
		printf("Utilizador com o este nif não exste\n");
		return 0;}
	
	long id1=p1->id;
	long id2=p2->id;

	Adj **aux1 = &(g->nodos[id1]);
	Adj **aux2 = &(g->nodos[id2]);
	Adj *apagar;
	
	int valid=1;

	while ((*aux1) && (*aux1)->id!=id2) {
		aux1=&((*aux1)->next);
	}
	if ((*aux1)==NULL) {
		fprintf(stdout,"Não existe relacão %s  entre %s e %s.\n",relacao,p1->nome,p2->nome);
		valid=0;
	}
	else {
		apagar=(*aux1);
		(*aux1)=(*aux1)->next;
		free(apagar);
	}
	
	while ((*aux2) && (*aux2)->id!=id1) {
		aux2=&((*aux2)->next);
	}
	if ((*aux2)==NULL) {
		fprintf(stdout,"Não existe relacão %s  entre %s e %s.\n",relacao,p1->nome,p2->nome);
		valid=0;
	}
	else {
		apagar=(*aux2);
		(*aux2)=(*aux2)->next;
		free(apagar);
	}
	if (valid) return 1;
	return 0;
}

int relacoes_remover (long nif1, long nif2,char *tipo,Grafo *f,Grafo *a,Grafo *p){
	
	if(strcmp(tipo,FAM)==0){ 
		remover(nif1,nif2,tipo,f);
		return 0;
	}
	
	if(strcmp(tipo,AMI)==0){ 
		remover(nif1,nif2,tipo,a);
		return 0;
	}
	
	if(strcmp(tipo,PRO)==0){ 
		remover(nif1,nif2,tipo,p);
		return 0;
	}

return 0;
}

int relacoes_inserir (long nif1, long nif2,int peso,char *tipo,Grafo *f,Grafo *a,Grafo *p){
	
	if(strcmp(tipo,FAM)==0){ 
		if(!inserir_ligacao(nif1,nif2,peso,f)){
			printf(" Impossivel criar relação\n");}
	}
	
	if(strcmp(tipo,AMI)==0){ 
		if(!inserir_ligacao(nif1,nif2,peso,a)){
			printf(" Impossivel criar relação\n");}
	}
	
	if(strcmp(tipo,PRO)==0){ 
		if(!inserir_ligacao(nif1,nif2,peso,p)){
			printf(" Impossivel criar relação\n");}
	}
	printf(" Relacao criada\n");

return 0;
}

int alterar_relacao(long nif1,long nif2,char *tipo1,char *tipo2,int peso,Grafo *a,Grafo *f,Grafo *p){

		relacoes_remover(nif1,nif2,tipo1,f,a,p);
		relacoes_inserir(nif1,nif2,peso,tipo2,f,a,p);
		printf(" Relacao alterada \n");
		
return 0;
}
	
int ver_relacao(long long nif,Grafo *g){
	
	long id;
	char c;//para para a impressao de utilizadores
	Perfil *aux=findByNif(nif);
	Adj *aux1;
	
	if (!aux){
		 printf(" a pessoa não existe\n");
		 return 0;
	 }
	 id=aux->id;
	aux1=g->nodos[id]; 
	 while(aux1){
		print_user(findByNif(aux1->nif));
		scanf("%c",&c);
		aux1=aux1->next;
		}
	

return 1;
}

int ver_relacoes (long nif,char *tipo,Grafo *f,Grafo *a,Grafo *p){
	
	char c;
	
	if(strcmp(tipo,"fam")==0){ 
		if(!ver_relacao(nif,f)) printf("Não existe\n");
		else printf("Familiar\n\n");
		scanf("%c",&c);
	}
	
	if(strcmp(tipo,"ami")==0){ 
		if(!ver_relacao(nif,a)) printf("Não existe\n");
		else printf("Amigo\n\n");
		scanf("%c",&c);
	}
	
	if(strcmp(tipo,"pro")==0){ 
		if(!ver_relacao(nif,p)) printf("Não existe\n");
		else printf("proficional\n\n");
		scanf("%c",&c);
	}
	return 0;
}

