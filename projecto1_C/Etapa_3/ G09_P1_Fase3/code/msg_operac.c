#include "msg_operac.h"
#include "define.h"
#include "users.h"
#include "erro.h"
#include <stdio.h>
#include <stdlib.h>

Destinatario **cria_lista_msg(long long userID) {
        Destinatario **lst_msg;
        int tamanho=(2*userID);
        int i;

        lst_msg=malloc(tamanho*sizeof(Destinatario*));
        if (lst_msg==NULL) {
                mensagem_de_erro(E_MEM);
                return NULL;
        }
        for (i=0;i<tamanho;i++) lst_msg[i]=NULL;
        return lst_msg;
}

int act_tam_list_msg(long long userID, Lista_destinatario *lm) {
        Destinatario **aux;
        int tamanho = (2*userID);
        int i,j;

        aux=malloc(tamanho*sizeof(Destinatario*));
        if (aux==NULL) {
                mensagem_de_erro(E_MEM);
                return 0;
        }
        for (i = 0; i < lm->dimensao; i++) aux[i] = lm->L_mensagens[i];
        for (j = i; j < tamanho; j++) aux[j] = NULL;

        free(lm->L_mensagens);
        lm->L_mensagens=aux;
        lm->dimensao = tamanho;
        return 1;
}

int inicia_mensagens(long long userID, Lista_destinatario **lm) {

		long long nif;
		int num_msg;
		
        *lm=malloc(sizeof(Lista_destinatario));
        if (!(*lm)) return 0;
        if (obter_info_popular(&nif,&num_msg)==0) {
			(*lm)->nif_popular=-1;
			(*lm)->num_mensagens=0;
		}
		else {
			(*lm)->nif_popular=nif;
			(*lm)->num_mensagens=num_msg;
		}
        (*lm)->L_mensagens=cria_lista_msg(userID);
        if ((*lm)->L_mensagens==NULL) return 0;

        (*lm)->dimensao=(userID);
        return 1;
}

void apagar_destinatario(Destinatario **dst) {
	Remetente *rm, *rm_aux;
	Mensagens *msg, *msg_aux;

	if (*dst) {
		rm=(*dst)->remetentes;
		while (rm) {
			rm_aux=rm;
			rm=rm->next;
			msg=rm_aux->msg;
			while (msg) {
				msg_aux=msg;
				msg=msg->next;
				free(msg_aux->mensagem);
				free(msg_aux);
			}
			free(rm_aux);
		}
		free(*dst);
		(*dst)=NULL;
	}
}

void limpa_mensagens(Lista_destinatario *ld) {
	int i;
	for (i=0;i<ld->dimensao;i++) {
		if (ld->L_mensagens[i]!=NULL) apagar_destinatario(&(ld->L_mensagens[i]));
	}
	free(ld->L_mensagens);
	free(ld);
}
