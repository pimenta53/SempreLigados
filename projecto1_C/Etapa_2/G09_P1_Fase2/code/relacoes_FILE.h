#include "relacoes_IO.h"
#include <stdio.h>

int ler_relacoes (char *input, Grafo *ami, Grafo *fam, Grafo *prof);
void inicia_grafos(int tamanho, Grafo *ami,Grafo *fam, Grafo *prof);
int aumenta_grafos(long long tamanho, Grafo *g);
FILE *ler_relc_fich(FILE *fr, long long *nif1, long long *nif2, char *tipo,int *peso, int *valid);
Grafo *selecionar_grafo(char *tipo, Grafo *ami, Grafo *fam, Grafo *prof);
FILE *guardar_relac_fich(FILE *fw, long long nif1, Adj *nodo, char *tipo);
FILE *guarda_relacionados(FILE *pFile, long long nif1, Adj *nodo, char *relacao, int *j);
void guardar_relacoes (char *input, Grafo *ami, Grafo *fam, Grafo *prof);
void limpar_grafos(Grafo *ami, Grafo *fam, Grafo *prof);
