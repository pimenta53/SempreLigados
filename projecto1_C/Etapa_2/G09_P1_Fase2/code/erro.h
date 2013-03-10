#define E_NO_NIF                         0 /**     Não existe o nif                        **/
#define E_NO_SEND                        1 /**     Não é possivel enviar para o próprio    **/
#define E_NO_USER                        2 /**     Não existem mensagens                   **/
#define E_MEM                            4 /**     Memória insuficiente                    **/
#define E_INVALIDE_TYPE                  5 /**     Formato do ficheiro invalido            **/
#define E_OPEN_FILE                      6 /**     Erro a abrir ficheiro                   **/
#define E_CREATE_FILE                    7 /**     Erro a criar ficheiro                   **/

/**
* Reporta o erro escrevendo uma mensagem no standard error
* @param erro_num O número do erro que vem da tabela de erros. Usar SEMPRE o define e não o valor numérico para maior legibilidade.
*/
int mensagem_de_erro(int erro_num);

