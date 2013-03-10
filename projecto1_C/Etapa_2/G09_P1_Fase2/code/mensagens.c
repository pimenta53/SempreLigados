#include "define.h"
#include "mensagens.h"
#include "users.h"
#include "erro.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int mais_popular (int total_msg, long long n_nif, Lista_destinatario *ld){
	if (total_msg>(ld->num_mensagens)) {
		ld->num_mensagens = total_msg;
		ld->nif_popular = n_nif;
		}
	return 1;
	}

int grava_mensagem(long long nif2,long long nif1,char *mensagem,Lista_destinatario *ld){
	
	Perfil *user1=findByNif(nif1);
	Perfil *user2=findByNif(nif2);
	long long id1;
	long long id2;
	
	
	if(!user1 || !user2){
		return mensagem_de_erro(E_NO_NIF);
		}
		
	if (nif1==nif2) {
		return mensagem_de_erro(E_NO_NIF);
		}
	
	Mensagens *mensagem1=malloc(sizeof(Mensagens));
	strcpy(mensagem1->mensagem,mensagem);
	mensagem1->next=NULL;
	
	
	id1=user2->id;
	id2=user1->id;
	
	
	if (!(ld->L_mensagens[id2])) {
		Destinatario *dest = malloc(sizeof(Destinatario));
		dest->total_mensagens = 0;
		dest->remetentes = NULL;
		ld->L_mensagens[id2]=dest;
		}
	
	(ld->L_mensagens[id2]->total_mensagens)++;
	
	mais_popular (ld->L_mensagens[id2]->total_mensagens, user1->nif, ld);
	
	
	Remetente *aux_remetente=ld->L_mensagens[id2]->remetentes;
	Remetente *aux_ant=ld->L_mensagens[id2]->remetentes;
	
	while ((ld->L_mensagens[id2]->remetentes)!=NULL) {
		aux_ant=ld->L_mensagens[id2]->remetentes;
		if ((ld->L_mensagens[id2]->remetentes->id) == id1) break;
		ld->L_mensagens[id2]->remetentes = ld->L_mensagens[id2]->remetentes->next;
	}
	
	
	if (ld->L_mensagens[id2]->remetentes==NULL) {
		Remetente *rem = malloc(sizeof(Remetente));
		rem->id=id1;
		rem->n_mensagens=1;
		rem->nif = nif2;
		rem->msg = mensagem1;
		rem->next=NULL;
		ld->L_mensagens[id2]->remetentes = aux_ant;
		if ((ld->L_mensagens[id2]->remetentes)==NULL) ld->L_mensagens[id2]->remetentes = rem;
		else  {
			ld->L_mensagens[id2]->remetentes->next = rem;
			ld->L_mensagens[id2]->remetentes=aux_remetente;
		}
		return 1;
		}
		
	if ((ld->L_mensagens[id2]->remetentes->n_mensagens)>19) {
		Mensagens *m_aux = ld->L_mensagens[id2]->remetentes->msg;
		ld->L_mensagens[id2]->remetentes->msg = ld->L_mensagens[id2]->remetentes->msg->next;
		free(m_aux);
		(ld->L_mensagens[id2]->remetentes->n_mensagens)--;
		}
	
	Mensagens *auxiliar = ld->L_mensagens[id2]->remetentes->msg;
	
	while (ld->L_mensagens[id2]->remetentes->msg->next!=NULL) {
		ld->L_mensagens[id2]->remetentes->msg=ld->L_mensagens[id2]->remetentes->msg->next;
	}
	
	
	ld->L_mensagens[id2]->remetentes->msg->next = mensagem1;
	
	(ld->L_mensagens[id2]->remetentes->n_mensagens)++;
	
	ld->L_mensagens[id2]->remetentes->msg=auxiliar;
	
	ld->L_mensagens[id2]->remetentes=aux_remetente;
		
return 1;
}
	
