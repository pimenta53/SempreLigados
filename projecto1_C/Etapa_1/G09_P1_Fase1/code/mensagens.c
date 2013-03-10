#include "mensagens.h"
#include "operacoes.h"
#include "relacoes.h"
#include <stdio.h>
#include <stdlib.h>


int grava_mensagem(long long nif1,long long nif2,char *mensagem,Lista_mensagens *lm){
	//mensagem para o nif2 do nif1
	//inserir á cabeça
	
	Perfil *user1=findByNif(nif1);
	Perfil *user2=findByNif(nif2);
	long long id1;
	long long id2;
	Remetente *dest;
	Remetente *remetente_aux;
	
	Mensagens *mensagem1=malloc(sizeof(Mensagens));
	strcpy(mensagem1->mensagem,mensagem);
	mensagem1->next=NULL;
	
	if(!user1 || !user2){
		printf("NIF/s inexistentes \n");
		return 0;}
		
	id1=user2->id;
	id2=user1->id;
		
	
	if(!lm->L_mensagens[id2]) {
		lm->total_utilizadores++;
		dest=malloc(sizeof(Remetente));
		dest->id=id1;
		dest->n_mensagens=0;
		dest->nif=nif2;
		dest->msg=mensagem1;
		dest->next=NULL;
		lm->L_mensagens[id2]=dest;
	} 
	
	remetente_aux=lm->L_mensagens[id2];
	
	while(remetente_aux && remetente_aux->id!=id1){
		remetente_aux=remetente_aux->next;
	}
	
	if(!remetente_aux ){
		dest=malloc(sizeof(Remetente));
		dest->id=id1;
		dest->n_mensagens=0;
		dest->nif=nif2;
		dest->msg=mensagem1;
		dest->next=NULL;
		remetente_aux=dest;}
	else{
		mensagem1->next=remetente_aux->msg;
		remetente_aux->msg=mensagem1;
	}
	
return 0;
}
	
//falta ainda um ciclo
int print_mensagens(long long nif,Lista_mensagens *lm){
	
	Perfil *user=findByNif(nif);
	long long id;
	if(!user){
		printf("Não existe nenhum utilizador com este nif\n");
		return 0;
	}
	
	id=user->id;
	
	if(!lm->L_mensagens[id]){
		printf(" Não tem mensagens\n");
		return 0;}
		
	while(lm->L_mensagens[id]->msg){
		printf("%s\n",lm->L_mensagens[id]->msg->mensagem);
		lm->L_mensagens[id]->msg=lm->L_mensagens[id]->msg->next;
	}
return 0;
}
