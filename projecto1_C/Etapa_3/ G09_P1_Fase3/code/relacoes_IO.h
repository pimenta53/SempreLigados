#include "relacoes.h"

#ifndef _USERS_IO_H_
#define _USERS_IO_H_
   #include "users_IO.h"
#endif

int relacoes_inserir (long long nif,Grafo *g);
int relacoes_apagar (long long nif,Grafo *g);
int ver_relacao(long long nif,Grafo *g);
int relacao_distancia(long long nif,Grafo *g,int peso);
int relacoes_modificar (long long nif,Grafo *rm, Grafo *new, long long *id_max);
int caminho_mais_curto(long long userID, long long nif, Grafo *g);
int procura_distanciados(long long userID, long long nif, Grafo *g);
int procura_distanciados_geral(long long userID, long long nif, Grafo *a, Grafo *f, Grafo *p);
