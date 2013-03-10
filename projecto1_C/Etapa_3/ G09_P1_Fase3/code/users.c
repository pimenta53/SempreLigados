#include "define.h"
#include "erro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas.h"

//hash nome
long long F_hash_nome(char *name){
	
	long long index=0,i=1;
	int aux=0,aux2,total=0,len=strlen(name);
	

	while(*name || i<1000000000){
		total+=(*name);
		index+=((*name)%10)*i;
		i*=10;
		name++;
	}
	
	aux=(len%10)*10;
	aux2=((index/10000)%10)*100;
	total=(total%10)*1000;
	return (index%10)+aux+total+aux2;
}


//hash nif
long long F_hash_nif(long long nif){
	
	long long index;
	int aux,aux2;
	long long i=10,aux3=1,total=0;
	
	aux=((nif%10000)/1000)*10;
	aux2=((nif%1000)/100)*100;
	
	while(aux3!=0){
		aux3=nif/i;
		i*=10;
		total+=aux3;
	}
	aux3=(total%10)*1000;
	index=(nif%10)+aux+aux2+aux3;
		
	return index;
}



int saveToHash(long long hash_nif_code,long long hash_nome_code,Perfil* new_entry, long long *id){

        User_h *name_entry=malloc(sizeof(User_h));
        User_h *nif_entry=malloc(sizeof(User_h));
        User_h **aux;
        int valid=1;

        if(!name_entry || !nif_entry) {
                return mensagem_de_erro(E_MEM);
        }

        name_entry->user=nif_entry->user=new_entry;
        name_entry->next=nif_entry->next=NULL;

        //guarda apontador para perfil na tabela de hash caso n exista nenhum utilizador com o mesmo nif
        aux=&hash_nif[hash_nif_code];
        while ((*aux) && valid) {
                if ((*aux)->user->nif==new_entry->nif) valid=0;
                else aux=&((*aux)->next);
        }
        if (valid) {
                (*aux)=nif_entry;

                aux=&hash_nome[hash_nome_code];
                name_entry->next=(*aux);
                hash_nome[hash_nome_code]=name_entry;
        }
        else {
                if ((*aux)->user->apagado==1)  {
                        //user apagado
                        (*aux)->user->apagado=0;
                        free(new_entry);
                        return 0;
                }
                //fprintf(stdout,"Já existe um utilizador com o mesmo NIF.\n");
                free(new_entry);
                return 0;
        }
        (*id)++;
        return 1;
}




int inserir_user(long long *IdUsers,char *nome,char *cidade,char *estado_civil,char *email,long long nif) {
	
	Perfil *p=malloc(sizeof(Perfil));

	if (p==NULL) {
		return mensagem_de_erro(E_NO_NIF);
	}
	
	strcpy(p->nome,nome);
	strcpy(p->cidade,cidade);
	strcpy(p->estado_civil,estado_civil);
	strcpy(p->email,email);
	p->nif=nif;
	p->id = *IdUsers;
	p->apagado=0;

	if (saveToHash(F_hash_nif(nif),F_hash_nome(nome),p,IdUsers)) return 1;

return 0;
}

int apagar_user (long long nif) {
	long long pos = F_hash_nif(nif);
	
	User_h *user = hash_nif[pos];
	
	while (user!=NULL) {
		if (user->user->nif==nif) {
			user->user->apagado=1;
			return 1;
		}
		user=user->next;
	}
	return 0;
}

Perfil *findByNif(long long nif) {
	
	long long IDnif=F_hash_nif(nif);
	
	if(!hash_nif[IDnif]) return NULL;
	User_h *aux=hash_nif[IDnif];
	
	while(aux && (aux->user->nif!=nif)){
		aux=aux->next;
	}
	if(aux) return(aux->user);
	return NULL;
}


int editar_perfil(char *cidade,char *estado_civil,char *email,long long nif){
	
	Perfil *user=findByNif(nif);
	
	if(!user) return mensagem_de_erro(E_NO_NIF);
	strcpy(user->cidade,cidade);
	strcpy(user->estado_civil,estado_civil);
	strcpy(user->email,email);

return 1;
}


