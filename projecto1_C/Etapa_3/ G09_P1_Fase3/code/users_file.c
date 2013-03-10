#include "define.h"
#include "users.h"
#include "dados.h"
#include "erro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void limpa_hash(long long *id) {
	int i;
	User_h *lista, *aux;
 	
	for(i=0;i<MAXNODES;i++) {
                lista=hash_nome[i];
                while (lista) {
                        aux=lista;
                        free(aux->user);//apaga o user na hash do nome, na do nif já vai estar apagado
                        lista=lista->next;
                        free(aux);
                }
                hash_nome[i]=NULL;
                lista=hash_nif[i];
                while (lista) {
                        aux=lista;
                        lista=lista->next;
                        free(aux);
                }
                hash_nif[i]=NULL;
        }
        (*id)=0;
}

FILE *ler_user_ficheiro(FILE *fr, int *valid,long long *id) {
        size_t result;

		Perfil *p=malloc(sizeof(Perfil));
        
        result = fread (&(p)->id,sizeof(long long),1,fr);
        if (result==0) (*valid)=0;
		result = fread (&(p)->nif,sizeof(long long),1,fr);
        if (result==0) (*valid)=0;
        result = fread ((p)->nome,sizeof(char),MAXNOME,fr);
        if (result==0) (*valid)=0;
        result = fread ((p)->cidade,sizeof(char),MAXCIDADE,fr);
        if (result==0) (*valid)=0;
        result = fread ((p)->estado_civil,sizeof(char),MAXESTADOCIV,fr);
        if (result==0) (*valid)=0;
        result = fread ((p)->email,sizeof(char),MAXEMAIL,fr);
        if (result==0) (*valid)=0;
		result = fread (&(p)->apagado,sizeof(int),1,fr);
        if (result==0) (*valid)=0;
        if (*valid) saveToHash(F_hash_nif(p->nif),F_hash_nome(p->nome),p,id);
        else free(p);

		return fr;
}

int carregar_bd(char *input, long long *id) {

        FILE *fp = fopen(input,"rb");
        long long id_aux;
        int j=0;
        int valid=1;

        if (fp==NULL) {
			return mensagem_de_erro(E_OPEN_FILE);
		}
       
        limpa_hash(id);
        fread(&id_aux,sizeof(long long),1,fp);
        while (j<id_aux && valid) {
				fp=ler_user_ficheiro(fp,&valid,id);
                j++;
		}
		if (!valid) {
			limpa_hash(id);
			return 0;
		}
        fclose(fp);
        return 1;
}

FILE *guarda_user(FILE *fw,Perfil *p) {
	        
        fwrite(&(p->id),sizeof(long long),1,fw);
        fwrite(&(p->nif),sizeof(long long),1,fw);
        fwrite((p->nome),sizeof(char),MAXNOME,fw);
        fwrite((p->cidade),sizeof(char),MAXCIDADE,fw);
        fwrite((p->estado_civil),sizeof(char),MAXESTADOCIV,fw);
        fwrite((p->email),sizeof(char),MAXEMAIL,fw);
        fwrite(&(p->apagado),sizeof(int),1,fw);
        return fw;
}


int guardar_bd(char *output, long long *id) {
	
	User_h *lista=NULL;
	int i=0;

	FILE *fw=fopen(output,"wb+");
	if(!fw){ 
		return mensagem_de_erro(E_CREATE_FILE);
	}
	
	fwrite(id,sizeof(long long),1,fw); // guarda o ultimo id
	while(i<MAXNODES){
		lista=hash_nome[i];
		while (lista) {
                fw=guarda_user(fw,lista->user);
                lista=lista->next;
		}
		i++;
	}
	fclose(fw);
	return 1;
}

