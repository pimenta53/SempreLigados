#ifndef _ERRO_H_
#define _ERRO_H_
   #include "erro.h"
#endif

#ifndef _MENSAGENS_H_
#define _MENSAGENS_H_
   #include "mensagens.h"
#endif

void limpa_mensagens(Lista_destinatario *ld);
int obter_info_popular(long long *nif, int *num);
Destinatario *procura(int id_procurado);
int guarda_msg_ficheiro(char *output, Lista_destinatario *ld);
void apagar_destinatario(Destinatario **dst);
