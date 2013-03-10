#include "mensagens_FILE.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

/*---------- leituras popular ---------*/

int ler_cabecalho(FILE **fr, long long *nif, int *num) {
        size_t result;
        result = fread (nif,sizeof(long long),1,*fr);
        if (result==0) return 0;
        result = fread (num,sizeof(int),1,*fr);
        if (result==0) return 0;
        return 1;
}

int obter_info_popular(long long *nif, int *num) {
	FILE *fp = fopen("mensagens.bin","rb");
	if (fp==NULL) {
			//mensagem_de_erro(E_OPEN);
			return 0;
	}
	if (ler_cabecalho(&fp,nif,num)==0) return 0;
	fclose(fp);
	return 1;
}


/* ------ funcoes ficheiros--------*/

int termina_escrita(FILE *fp) {
	fclose(fp);
	return 0;
}

int rename_fich(char *output, char *old) {
	int result;
	
	result = rename(output,old);
	if ( result != 0 ) {
			perror( "Error renaming file" );
			return 0;
	}
	return 1;
}

FILE *cria_ficheiro(char *nome) {
	FILE *fp= fopen(nome,"wb");
	return fp;
}

/*------------------letitutas de ficheiro-------------*/
int ler_indice(FILE **fr, int *id_fich) {
	size_t result;
    result = fread(id_fich,sizeof(int),1,*fr);
    if (result==0) return 0;
    return 1;
}

int ler_total_dest(FILE **fr, int *count) {
    size_t result;
    result = fread (count,sizeof(int),1,*fr);
	if (result==0) return 0;
    return 1;    
}
	
int cria_destinatario(Destinatario **dst, int total_msg) {
	*dst=malloc(sizeof(Destinatario));
	if (!(*dst)) {
		//mensagme_de_erro(E_MEM);
		return 0;
	}
	(*dst)->total_mensagens=total_msg;
	(*dst)->remetentes=NULL;
	return 1;
}

void cria_remetente(Remetente **rm,long long id, int nm, long long nif) {
	*rm=malloc(sizeof(Remetente));
	if (!rm) {
		//mensagem_de_erro(E_MEM);
		exit(1);
	}
	(*rm)->id=id;
	(*rm)->n_mensagens=nm;
	(*rm)->nif=nif;
	(*rm)->msg=NULL;
	(*rm)->next=NULL;
}

void insere_mensagem_lst(Mensagens *new_msg, Remetente *rm) {
	new_msg->next=rm->msg;
	rm->msg=new_msg;	
}

int ler_msg(FILE **fr, Remetente *rm) {
	Mensagens *new_msg=NULL;
	size_t result;
	
	new_msg=malloc(sizeof(Mensagens)); 
	if (!new_msg) {
		//mensagem_de_erro(E_MEM);
		exit(0);
	}
	new_msg->mensagem=malloc(MAXMSG*sizeof(char));
    result=fread(new_msg->mensagem,sizeof(char),MAXMSG,*fr);
    if (result<MAXMSG) {
		free(new_msg->mensagem);
		free(new_msg);
		return 0;
	}
    new_msg->next=NULL;

    if (result==0) {
		free(new_msg);
		return 0;
	}
	else insere_mensagem_lst(new_msg,rm);
	return 1;
}

void insere_remetente_lst(Remetente *rm, Destinatario *dst) {
	rm->next=dst->remetentes;
	dst->remetentes=rm;
}

int ler_info_dest(FILE **fr, int *total_msg, Destinatario *dst) {
    long long id,nif;
	int nm;
	Remetente *rm=NULL;
	size_t result;

	result=fread(&id,sizeof(long long),1,*fr);
	if (result==0) return 0;
	result=fread(&nm,sizeof(int),1,*fr);
	if (result==0) return 0;
	result=fread(&nif,sizeof(long long),1,*fr);
	if (result==0) return 0;
	
	cria_remetente(&rm,id,nm,nif);
	while (nm) {
		if (ler_msg(fr,rm)==0) return 0;
		nm--;
		(*total_msg)--;
	}
	insere_remetente_lst(rm,dst);
    return 1;
}

Destinatario *ler_dest_fich(FILE **fr, int *id_fich) {
	int total_msg;
	Destinatario *dst=NULL;
	
	if (ler_indice(fr,id_fich)!=0) {
		if (ler_total_dest(fr,&total_msg)!=0) {
			if (cria_destinatario(&dst,total_msg)!=0) {
				while (total_msg) {
					if (ler_info_dest(fr,&total_msg,dst)==0) {
						apagar_destinatario(&dst);
						return NULL;
					}
				}
			}
		}
	}
	return dst;
}

/*-------------- procura destinatario ficheiro------------*/
Destinatario *procura(int id_procurado) {
	FILE *fr = fopen("mensagens.bin","rb");
	int id_fich=-1;
	Destinatario *dst=NULL;
	long long nif;
	int num;

	if (!fr) {
		//mensagem_de_erro(NAO EXISTE);
		return 0;
	}
	
	if (ler_cabecalho(&fr,&nif,&num)==0) return dst;
	do {
		if (dst) apagar_destinatario(&dst);
		dst=ler_dest_fich(&fr,&id_fich);
	} while (dst && id_fich!=id_procurado);
	fclose(fr);
	return dst;
}

/*--------- gravacoes ficheiro -----*/
int guardar_cabecalho(FILE **fw, Lista_destinatario *ld) {
	size_t result;
    result = fwrite(&(ld->nif_popular),sizeof(long long),1,*fw);
    if (result==0) return 0;
    result = fwrite(&(ld->num_mensagens),sizeof(int),1,*fw);
    if (result==0) return 0;
    return 1;
}

int guardar_indice(FILE **fw, int i) {
    size_t result;
    result = fwrite(&i,sizeof(int),1,*fw);
    if (result==0) return 0;
	return 1;
}

int guardar_total_dest(FILE **fw, Destinatario *dt) {
	size_t result;
    result = fwrite(&(dt->total_mensagens),sizeof(int),1,*fw);
    if (result==0) return 0;
    return 1;
}

int guarda_msg(FILE **fw, Mensagens *msgs) {
	size_t result=1;
	while (msgs && result) {
        result=fwrite(msgs->mensagem,sizeof(char),MAXMSG,*fw);
		msgs=msgs->next;
	}
	if (result==0) return 0;
	return 1;  
}

int guardar_info_remet(FILE **fw, Remetente *rm) {
	while (rm) {
        fwrite(&(rm->id),sizeof(long long),1,*fw);
        fwrite(&(rm->n_mensagens),sizeof(int),1,*fw);
        fwrite(&(rm->nif),sizeof(long long),1,*fw);
		if (!guarda_msg(fw,rm->msg)) return 0;
		rm=rm->next;
	}
	return 1;
}

int guarda_dest(FILE **fw, Destinatario *dt, int i) {
	if (dt) {
		if (!guardar_indice(fw,i)) return 0;
		if (!guardar_total_dest(fw,dt)) return 0;
		if (!guardar_info_remet(fw,dt->remetentes)) return 0;
	}
	return 1;
}


void print_dest(Destinatario *dst) {
	Remetente *rm=NULL;
	Mensagens *msg=NULL;
	if (dst) rm=dst->remetentes;
	while (rm) {
        	printf("id: %lld, nm: %d, nif: %lld\n",rm->id,rm->n_mensagens,rm->nif);
		msg=rm->msg;
		while (msg) {
			printf("%s\n",msg->mensagem);
			msg=msg->next;
		}
		rm=rm->next;
	}
}


int guarda_msg_ficheiro(char *output, Lista_destinatario *ld) {	
	FILE *fr = fopen(output,"rb");
	FILE *fw = fopen("aux.bin","wb");
	Destinatario *dst = NULL;
	long long nif;
	int num, i = 0, id_fich = -1;
	
	if (!fr) cria_ficheiro("mensagens.bin");
	else ler_cabecalho(&fr,&nif,&num);
	guardar_cabecalho(&fw,ld);
	
	do {
		while (i<ld->dimensao && !ld->L_mensagens[i]) i++;
		if (fr) {
			do {
				if (dst) apagar_destinatario(&dst);
				dst=ler_dest_fich(&fr,&id_fich);
				if (dst && id_fich<i) {
					guarda_dest(&fw,dst,id_fich);
				}
			} while (dst && id_fich<i);
		}
		if (i<ld->dimensao) {
			guarda_dest(&fw,ld->L_mensagens[i],i); 
		}
		i++;
	} while (dst || i<ld->dimensao);
	if (fr) fclose(fr);
	fclose(fw);
	if(remove(output)!=0) {
		perror("Error deleting file");
		return 0;
	}
	if (rename_fich("aux.bin",output)==0) return 0;
	return 1;
}
