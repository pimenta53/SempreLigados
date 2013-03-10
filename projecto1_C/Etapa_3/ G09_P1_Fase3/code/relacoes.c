#include "define.h" 
#include "relacoes.h"
#include "users.h"
#include "erro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void procura_nodos(int *encontrei, int *state, int *usr, int distancia, int acomulada, int sr, Grafo *g) {
	Adj *nodo;
	
	if (g->nodos[sr]) nodo=g->nodos[sr]->adjacentes;
	while (nodo) {
		if (state[nodo->id]==0) {
			state[nodo->id]=1;
			if (acomulada+nodo->peso <= distancia) {
				if (usr[nodo->id]==0 && acomulada+nodo->peso == distancia) {
					usr[nodo->id]=1;
					*encontrei=1;
				}
				procura_nodos(encontrei,state,usr,distancia,acomulada+nodo->peso,nodo->id,g);
			}
		}
		nodo=nodo->next;
	}
}
			
int distancia_d(long long id, int *usr, int distancia, Grafo *g) {
	int *state = malloc(g->tamanho*sizeof(int));
	int acomulada=0, i;
	int encontrei=0;

    for(i=0; i<g->tamanho; i++) {
		state[i]=0;
    }
	state[id]=1;
	procura_nodos(&encontrei,state,usr,distancia,acomulada,id,g);
	free(state);
	return encontrei;
}


void pesquisa_dijkstra(long long sr,long long ds,long long *path, Grafo *g) {

	struct node *state= malloc(g->tamanho*sizeof(struct node));
	int no_nodes=g->tamanho, INFTY=10000;
 	int i,k,min;
 	struct node *p;
	Adj *aux=NULL;

 	for(p=&state[0];p<&state[no_nodes];p++) {
		p->pre= -1;
 	  	p->length=INFTY;
 	   	p->label=tent;
 	}
 	state[ds].length=0; 
 	state[ds].label=perm; 
 	k=ds; 
 	
 	do { 	
		if (g->nodos[k]!=NULL) aux=g->nodos[k]->adjacentes;
		while (aux) {
			if(state[aux->id].label==tent) {	
 				if((state[k].length + aux->peso) < state[aux->id].length){
					state[aux->id].pre = k;
 			       	state[aux->id].length = state[k].length + aux->peso;
 		        }
			}
			aux=aux->next;
		}
        k=0;
        min=INFTY;
 	    for(i=0;i<no_nodes;i++) {
				if(state[i].label==tent && state[i].length<min) {	
					min=state[i].length;
					k=i;
				}
 	    }
		state[k].label=perm;
 	} while(k!=sr);
 
 	i=0;
 	k=sr;
 	do {
		path[i++]=g->nodos[k]->nif;
		k=state[k].pre;
	} while(k>=0);
 	path[i]=k;
}


int procura_caminho_curto(long long userID, long long nif1,long long nif2, long long *path, Grafo *g) {
	Perfil *p1=findByNif(nif1);
    Perfil *p2=findByNif(nif2);
    int i;

    if(p1==NULL || p2==NULL){
		return -1;
    } 

    for(i=0;i<10;i++) {
		path[i]=-2;
	}

    pesquisa_dijkstra(p1->id,p2->id,path,g);
    if (path[1]==-1) return 0;
    return 1;
}

int act_tamanho_array(long long *UserId, Grafo *ami,Grafo *fam,Grafo *prof){
	long long tamanho = (*UserId) + 100;
	Info **aux_ami=malloc(tamanho*sizeof(Info));
	Info **aux_fam=malloc(tamanho*sizeof(Info));
	Info **aux_prof=malloc(tamanho*sizeof(Info));
	long long i, j;
	
	for(i=0;i<(*UserId);i++){
		aux_ami[i]=ami->nodos[i];
		aux_fam[i]=fam->nodos[i];
		aux_prof[i]=prof->nodos[i];
	}
	for(j=(*UserId);j<tamanho;j++){
		aux_ami[j]=NULL;
		aux_fam[j]=NULL;
		aux_prof[j]=NULL;
	}
	free(ami->nodos);
	ami->nodos = aux_ami;
	ami->tamanho = tamanho;
	free(fam->nodos);
	fam->nodos = aux_fam;
	fam->tamanho = tamanho;
	free(prof->nodos);
	prof->nodos = aux_prof;
	prof->tamanho = tamanho;

return 1;
}


int inserir_relacao(long long id_origem, long long id_destino, long long nif_destino, int peso, Grafo *g) {
        Adj *nodo = malloc(sizeof(struct adj));
        nodo->id=id_destino;
        nodo->nif = nif_destino;
        nodo->peso=peso;
        nodo->next=NULL;
        int valid=1;

        Adj **aux = &(g->nodos[id_origem]->adjacentes);

        while (*aux) {
                if ((*aux)->id==nodo->id) valid=0;
                aux=&((*aux)->next);
        }
        if (valid==0) {
			free(nodo);
			return 0;
		}
        else (*aux)=nodo;

        return 1;

}

int inserir_info_user(long long id, long long nif, Info **inf) {
        (*inf) = malloc(sizeof(struct info));
        if ((*inf)==NULL) {
                return mensagem_de_erro(E_MEM);
        }
        (*inf)->nif=nif;
        (*inf)->adjacentes=NULL;
        return 1;
}

int criar_relacao(long long nif1, long long nif2, int peso, Grafo *g){

        Perfil *p1=findByNif(nif1);
        Perfil *p2=findByNif(nif2);

        if(p1==NULL || p2==NULL){
                return -1;
        } 

        if (g->nodos[p1->id]==NULL) {
                if (inserir_info_user(p1->id,nif1,&(g->nodos[p1->id]))==0) return 0;
        }
        if (g->nodos[p2->id]==NULL) {
                if (inserir_info_user(p2->id,nif2,&(g->nodos[p2->id]))==0) return 0;
        }
        if (inserir_relacao(p1->id,p2->id,nif2,peso,g)) {
                if (inserir_relacao(p2->id,p1->id,nif1,peso,g)) {
                        return 1;
                }
        }
        return 0;
}


int remove_nodos(Adj **lista, long long nif2) {
        int found=0;
        Adj *aux;
        while (*lista && !found) {
                if ((*lista)->nif==nif2) found=1;
                else lista=&((*lista)->next);
        }
        if (found) {
                aux=(*lista);
                (*lista)=(*lista)->next;
                free(aux);
                return 1;
        }
        return 0;
}


int remover_relacao(long long nif1, long long nif2, Grafo *g) {
	
	Perfil *p1=findByNif(nif1);
    Perfil *p2=findByNif(nif2);
    Info *inf1, *inf2;

    if (p1==NULL || p2==NULL) {
		return 0;
    }
    inf1=g->nodos[p1->id];
    inf2=g->nodos[p2->id];
	if (inf1==NULL || inf2==NULL) {
		return 0;
    }
	if (remove_nodos(&(inf1->adjacentes),nif2)) {
		remove_nodos(&(inf2->adjacentes),nif1);
    }
    else return 0;
return 1;

}

int alterar_relacao(long long *user_max,long long nif1,long long nif2,int peso,Grafo *rm,Grafo *new){

        if(!remover_relacao(nif1,nif2,rm)) return 0;
        if(!criar_relacao(nif1,nif2,peso,new)) return 0;

        return 1;
}
