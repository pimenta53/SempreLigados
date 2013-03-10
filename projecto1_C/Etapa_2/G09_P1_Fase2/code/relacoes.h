#include "define.h"
//estrutura para saber quais os adjacentes de um nodo. 
//posicao do adjacente no grafo (indice no array pq usamos lista de adjacencias)
//peso da ligação
//apontador para o próximo adajcente
typedef struct adj{
        long long id;
        long long nif;
        int peso;
        struct adj *next;
} Adj;


typedef struct info {
        long long nif;
        Adj *adjacentes;
} Info;

//grafos para as diferentes relações
//tem o numero de nodos existentes no grafo
//tem apontador para a estrutura Nodo (ver anterior) k tem o indice da tabela de hash k permite aceder ao perfil
//tem apontador para os nodos adjacentes 
typedef struct grafo{
        int tamanho;
        Info **nodos;
} Grafo;


Grafo *selecionar_grafo(char *tipo, Grafo *ami, Grafo *fam, Grafo *prof);
int inserir_relacao(long long id_origem, long long id_destino, long long nif_destino, int peso, Grafo *g);
int inserir_info_user(long long id, long long nif, Info **inf);
int criar_relacao(long long nif1, long long nif2, int peso, Grafo *g);
int remover_relacao(long long nif1, long long nif2, Grafo *g);
int alterar_relacao(long long nif1,long long nif2,int peso,Grafo *rm,Grafo *new);


