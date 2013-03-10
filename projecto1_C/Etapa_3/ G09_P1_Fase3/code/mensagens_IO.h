#ifndef _MENSAGENS_FILE_H_
#define _MENSAGENS_FILE_H_
   #include "mensagens_FILE.h"
#endif

#ifndef _MENSAGENS_H_
#define _MENSAGENS_H_
   #include "mensagens.h"
#endif

#ifndef _MSG_H_
#define _MSG_H_
   #include "msg_operac.h"
#endif

#ifndef _USERS_IO_H_
#define _USERS_IO_H_
   #include "users_IO.h"
#endif

int print_mensagens(long long userID,long long nif,Lista_destinatario *ld);
int escrever_mensagem(long long userID, long long nif1,Lista_destinatario *ld);
int ver_popular(Lista_destinatario *ld);
