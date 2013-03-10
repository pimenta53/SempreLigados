#include "mensagens.h"

/**
 * A função print_mensagens é responsavel por imprimir todas as mensagens dos diferentes destinatarios de um utilizador.
 * @param nif campo correspondente ao nif que vai ser utlizado para encontrar o id do utilizador atrves da função "findByNif"
 * @param lm estrutura de dados onde vamos ver as mensagens de cada utilizador para depois podermos imprimilas.
 * @returns Retorna um inteiro que verifica se conseguiu ou não efectuar a operação.
 */
int print_mensagens(long long nif,Lista_destinatario *ld);
int escrever_mensagem(long long nif1,Lista_destinatario *ld);
int ver_popular(Lista_destinatario *ld);
