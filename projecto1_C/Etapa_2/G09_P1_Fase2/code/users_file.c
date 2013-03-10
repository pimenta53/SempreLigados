#include "define.h"
#include "users.h"
#include "dados.h"
#include "erro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ler_parametro_f(FILE *fp, int count, int dim, char *parametro) {
        fseek(fp,(long) (count*sizeof(char)),SEEK_SET);
        fgets(parametro,dim,fp);
}

int ler_id(FILE *fp, int count, long long *id) {
	char idstr[MAXUSERSTR];
	ler_parametro_f(fp,count,MAXUSERSTR,idstr);
        count+=MAXUSERSTR;
	*id=ler_numero_ll(idstr);
        if (*id==-1) {
                return mensagem_de_erro(E_OPEN_FILE);
        }
	return count;
}

void limpa_hash(long long *id) {
	int i;
	User_h *lista, *aux;
 	
	for(i=0;i<MAXNODES;i++) {
                lista=hash_nome[i];
                while (lista) {
                        aux=lista;
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

int ler_user_ficheiro(FILE *fp, Perfil **ptr, int count) {

        char idstr[MAXUSERSTR], apgdstr[MAXAPAGADO], nifstr[MAXNIF], endstr[END];
        Perfil *p = malloc(sizeof(Perfil));

        ler_parametro_f(fp,count,MAXUSERSTR,idstr);
        count+=MAXUSERSTR;
        ler_parametro_f(fp,count,MAXNIF,nifstr);
        count+=MAXNIF;
        ler_parametro_f(fp,count,MAXNOME,p->nome);
        count+=MAXNOME;
        ler_parametro_f(fp,count,MAXCIDADE,p->cidade);
        count+=MAXCIDADE;
        ler_parametro_f(fp,count,MAXESTADOCIV,p->estado_civil);
        count+=MAXESTADOCIV;
        ler_parametro_f(fp,count,MAXEMAIL,p->email);
        count+=MAXEMAIL;
        ler_parametro_f(fp,count,MAXAPAGADO,apgdstr);
        count+=MAXAPAGADO;
        ler_parametro_f(fp,count,END,endstr);
        count+=END;

       
        if (strcmp(endstr,".")!=0) {
                free(p);
                return mensagem_de_erro(E_OPEN_FILE);
        }

        p->id=ler_numero_ll(idstr);
        if (p->id==-1) {
                free(p);
                return mensagem_de_erro(E_OPEN_FILE);
        }
        p->nif=ler_numero_ll(nifstr);
        if (p->nif==-1) {
                free(p);
                return mensagem_de_erro(E_OPEN_FILE);
        }
        p->apagado=ler_numero_int(apgdstr);
        if (p->apagado==-1) {
                free(p);
                return mensagem_de_erro(E_OPEN_FILE);
        }
        (*ptr)=p;

        return count;
}


int carregar_bd(char *input, long long *id) {

        int j=0;
        int count=0;
        Perfil *p=NULL;
        FILE *fp = fopen(input,"r");
        long long id_aux;

        if (fp==NULL) {
                return 0;
        }

        limpa_hash(id);
        count=ler_id(fp,count,&id_aux);
        if (count == 0) return 0;
        while (j<id_aux && count) {
                count=ler_user_ficheiro(fp,&p,count);
                if (count) saveToHash(F_hash_nif(p->nif),F_hash_nome(p->nome),p,id);
                else limpa_hash(id);
                j++;
        }
        fclose(fp);
        if (count==0) return 0;
        return 1;
}


void guarda_user(FILE *fw, Perfil *p) {

        char idstr[MAXUSERSTR], apgdstr[MAXAPAGADO], nifstr[MAXNIF];
        char end = '.';

	converte_ll_str(p->id,idstr);
        converte_ll_str(p->nif,nifstr);
        sprintf(apgdstr,"%d",p->apagado);
        guardar_str(idstr,MAXUSERSTR,fw);
        guardar_str(nifstr,MAXNIF,fw);
        guardar_str(p->nome,MAXNOME,fw);
        guardar_str(p->cidade,MAXCIDADE,fw);
        guardar_str(p->estado_civil,MAXESTADOCIV,fw);
        guardar_str(p->email,MAXEMAIL,fw);
        guardar_str(apgdstr,MAXAPAGADO,fw);
        guardar_str(&end,END,fw);
}

int guardar_bd(char *output, long long *id) {
	//gravar_id;
        FILE *fw=fopen(output,"w+");
	User_h **lista=NULL;
	char idstr[MAXUSERSTR];
	int i=0;

        if(!fw){ 
                return mensagem_de_erro(E_CREATE_FILE);
        }

	converte_ll_str(*id,idstr);
        guardar_str(idstr,MAXUSERSTR,fw);

        while(i<MAXNODES){
		lista=&hash_nome[i];
		while (*lista) {
			guarda_user(fw,(*lista)->user);
			lista=&((*lista)->next);
		}
		i++;
      	}
	fclose(fw);
	return 1;
}


