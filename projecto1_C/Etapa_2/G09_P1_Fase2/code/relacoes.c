#include "define.h" 
#include "relacoes.h"
#include "users.h"
#include "erro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        if (valid==0) free(nodo);
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
                return mensagem_de_erro(E_NO_NIF );
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
                return mensagem_de_erro(E_NO_NIF);
        }
        inf1=g->nodos[p1->id];
        inf2=g->nodos[p2->id];
        if (inf1==NULL || inf2==NULL) {
                return mensagem_de_erro(E_NO_NIF);
        }
        if (remove_nodos(&(inf1->adjacentes),nif2)) {
                remove_nodos(&(inf2->adjacentes),nif1);
        }
        else return 0;
return 1;

}

int alterar_relacao(long long nif1,long long nif2,int peso,Grafo *rm,Grafo *new){

        if(!remover_relacao(nif1,nif2,rm)) return 0;
        if(!criar_relacao(nif1,nif2,peso,new)) return 0;

        return 0;
}
