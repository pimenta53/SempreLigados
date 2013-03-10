#include "define.h"
#include "erro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas.h"

//hash nome
long long F_hash_nome(char *nome){
	long long res;
	
	int tam=strlen(nome);
	if(tam<=5 && nome[0]=='Y') return 0;//(nome[tam-2]%10);
	if(tam>5 && tam<=7) return 0;//(((nome[tam-3])%10)*10 +nome[tam-1]+nome[tam-2]+nome[tam-3]+nome[tam-4]);
	if((tam>14 && tam<20) && (nome[tam-2]=='e' || nome[tam-2]=='i'||nome[tam-2]=='o' || nome[tam-2]=='u' )) return 0; //(((((nome[tam-8])%10)*100) +tam +nome[tam-2]));	
	if(tam<=5 && nome[0]!='Y') return 0 ;//tam*10+(nome[1]%10)*1000;
	res = (((nome[1]%10)*1000) + ((nome[tam-7]%10)*100) +((nome[tam-6]%10)*10) + nome[tam-7] + nome[tam-6] + nome[tam-5] + nome[tam-4] + nome[tam-10]%10);
	if (res<0) return (res*(-1));
	return 0;
}

//hash nif
long long F_hash_nif(long long nif){
	
	long long n1=nif%10;
	long long n2=nif%2;
	long long n3=nif%9;	
	long long n4=nif%100;
	
	
	if(n1==0 && n2==n3 &&n2==1) return ((n2+1)*3);
	if(n1==1 && (n3<=1 && n3>5)) return(((n3)*10)+n2*2+n3);
	if(n1>=2 && n1<3) return ((n3*100)+(((n2+1)*2)*10)+n1);
	if(n1>=4 && n1<7 && n3<5) return (((n3)*1000)+(n2*53)+(n2*2)+n3*10+n4);
	if(n1>=4 && n1<7 && n3>5) return (((n3+1)*1000)+(n2*100)+(n3*53)+(n3*2)+n2+n4);

	return ((nif%1000)-n3+(n2*100)+n4*100+n3*90);
	return (nif%10000);
}



int saveToHash(long long hash_nif_code,long long hash_nome_code,Perfil* new_entry, long long *id){

        User_h *name_entry=malloc(sizeof(User_h));
        User_h *nif_entry=malloc(sizeof(User_h));
        User_h **aux;
        int valid=1;

        if(!name_entry || !nif_entry) {
                fprintf(stderr,"errco ao alocar mem\n");
                return 0;
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


