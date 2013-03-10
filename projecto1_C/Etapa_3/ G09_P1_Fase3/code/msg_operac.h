#ifndef _MENSAGENS_FILE_H_
#define _MENSAGENS_FILE_H_
   #include "mensagens_FILE.h"
#endif

#ifndef _MENSAGENS_H_
#define _MENSAGENS_H_
   #include "mensagens.h"
#endif

Destinatario **cria_lista_msg(long long userID);
int act_tam_list_msg(long long userID, Lista_destinatario *lm);
int inicia_mensagens(long long userID, Lista_destinatario **lm);
void limpa_mensagens(Lista_destinatario *ld);
