#include "relacoes_IO.h"
#include "erro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void apagar_lista(Adj *nodo) {
        Adj* aux;
        while (nodo) {
                aux=nodo;
                nodo=nodo->next;
                free(aux);
        }
}


void limpar_grafos(Grafo *ami, Grafo *fam, Grafo *prof) {

        Info *inf_a, *inf_f, *inf_p;
        Adj *aux;
        int i;

        for(i=0;i<ami->tamanho;i++) {
                inf_a=ami->nodos[i];
                inf_f=fam->nodos[i];
                inf_p=prof->nodos[i];
                if (inf_a) {
                        aux=inf_a->adjacentes;
                        apagar_lista(aux);
                }
                if (inf_f) {
                        aux=inf_f->adjacentes;
                        apagar_lista(aux);
                }
                if (inf_p) {
                        aux=inf_p->adjacentes;
                        apagar_lista(aux);
                }
        }
        ami->tamanho=0;
        free(ami->nodos);
        ami->nodos=NULL;
        fam->tamanho=0;
        free(fam->nodos);
        fam->nodos=NULL;
        prof->tamanho=0;
        free(prof->nodos);
        prof->nodos=NULL;
}


Grafo *selecionar_grafo(char *tipo, Grafo *ami, Grafo *fam, Grafo *prof) {
        if (strcmp("ami",tipo)==0) return ami;
        if (strcmp("fam",tipo)==0) return fam;
        if (strcmp("prof",tipo)==0) return prof;
        return NULL;
}

void inicia_grafos(int tamanho, Grafo *ami,Grafo *fam, Grafo *prof) {
        int i;
        ami->tamanho = fam->tamanho = prof->tamanho = tamanho;
        ami->nodos=malloc(tamanho*sizeof(Info *));
        fam->nodos=malloc(tamanho*sizeof(Info *));
        prof->nodos=malloc(tamanho*sizeof(Info *));
        for (i=0;i<tamanho;i++) {
                ami->nodos[i]=NULL;
                fam->nodos[i]=NULL;
                prof->nodos[i]=NULL;
        }
}

int aumenta_grafos(long long tamanho, Grafo *g) {
        int i;
        Info **new_lista=malloc(tamanho*sizeof(Info *));

        if (new_lista==NULL) {
                return mensagem_de_erro(E_MEM);
        }
        for(i=0; i<(g->tamanho); i++) {
                new_lista[i]=g->nodos[i];
        }
        free(g->nodos);
        g->tamanho=tamanho;
        g->nodos=new_lista;
        return 1;
}

FILE *ler_relc_fich(FILE *fr, long long *nif1, long long *nif2, char *tipo,int *peso, int *valid) {
        size_t result;

        result = fread (nif1,sizeof(long long),1,fr);
        if (result==0) (*valid)=0;
        result = fread (nif2,sizeof(long long),1,fr);
        if (result==0) (*valid)=0;
        result = fread (tipo,sizeof(char),sizeof(tipo),fr);
        if (result==0) (*valid)=0;
        else tipo[result]='\0';
        result = fread (peso,sizeof(int),1,fr);
        if (result==0) (*valid)=0;
        return fr;
}

int ler_relacoes (char *input, Grafo *ami, Grafo *fam, Grafo *prof) {
        FILE *pFile = fopen("relacoes.bin","rb");

        Adj *new;
        Grafo *selecionado=NULL;
        char tipo[MAXTIPOREL];
        long long nif1,nif2;
        int valid=1, peso;

        if(!pFile) {
                return mensagem_de_erro(E_OPEN_FILE);
        }
        while (!feof(pFile) && valid) {
                new=malloc(sizeof(struct adj));
                pFile=ler_relc_fich(pFile,&nif1,&nif2,tipo,&peso,&valid);
                if (valid) {
                        //printf("%lld, %lld, %s, %d\n",nif1,nif2,tipo,peso);
                        selecionado=selecionar_grafo(tipo,ami,fam,prof);
                        if (selecionado) criar_relacao(nif1,nif2,peso,selecionado);
                }
        }
        fclose(pFile);

        return 1;
}


FILE *guardar_relac_fich(FILE *fw, long long nif1, Adj *nodo, char *tipo) {
        fwrite(&nif1,sizeof(long long),1,fw);
        fwrite(&nodo->nif,sizeof(long long),1,fw);
        fwrite(tipo,sizeof(char),sizeof(tipo),fw);
        fwrite(&nodo->peso,sizeof(int),1,fw);
        return fw;
}


FILE *guarda_relacionados(FILE *pFile, long long nif1, Adj *nodo, char *relacao, int *j) {
        char tipo[MAXTIPOREL];
        sprintf(tipo,"%s",relacao);
        while (nodo) {
                pFile=guardar_relac_fich(pFile,nif1,nodo,tipo);
                //printf("%lld, %lld, %s\n",nif1,nodo->nif,tipo);
                nodo=nodo->next;
                (*j)++;
        }
        return pFile;
}

void guardar_relacoes (char *input, Grafo *ami, Grafo *fam, Grafo *prof) {

        Info *inf_a, *inf_f, *inf_p;
        Adj *aux_a, *aux_f, *aux_p;
        int i,j=0;
        FILE *pFile = fopen (input,"wb");

        for(i=0;i<ami->tamanho;i++) {
                inf_a=ami->nodos[i];
                inf_f=fam->nodos[i];
                inf_p=prof->nodos[i];
                if (inf_a) {
                        aux_a=inf_a->adjacentes;
                        if (aux_a!=NULL) pFile=guarda_relacionados(pFile,inf_a->nif,aux_a,"ami",&j);
                }
                if (inf_f) {
                        aux_f=inf_f->adjacentes;
                        if (aux_f!=NULL) pFile=guarda_relacionados(pFile,inf_f->nif,aux_f,"fam",&j);
                }
                if (inf_p) {
                        aux_p=inf_p->adjacentes;
                        if (aux_p!=NULL) pFile=guarda_relacionados(pFile,inf_p->nif,aux_p,"prof",&j);
                }
        }
}
