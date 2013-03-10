#include "mensagens_IO.h"

int menu_pesquisa(int row,int col,long long idUser);
int menu_relacao(int row,int col,long long nif,Grafo *g,long long *userID);
int menu_relacoes(int row,int col,long long nif,Grafo *f,Grafo *a,Grafo *p,long long *userID);
int menu_mensagens(int row,int col,long long nif,long long *userID,Lista_destinatario *lm);
int menu_utilizador(int row,int col,long long nif,Grafo *f,Grafo *a,Grafo *p,long long *userID,Lista_destinatario *lm);
int menu_login(int row,int col,Grafo *f,Grafo *a,Grafo *p,long long *userID,Lista_destinatario *lm);
int menu_principal(Grafo *f,Grafo *a,Grafo *p,long long *userID,Lista_destinatario *lm);
