#include "estruturas.h" 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/**
 * Função reponsavel por gerar um indice para a tabela de hash_nome
 * O indice gerado esperace que seja o mais aleatorio possivel entre 0 e 10000 de forma a ter um bom desempenho na tabela de hash
 * para isso a função tem varias condições de geração de numeros
 * @param nome atraves desta string vai se gerar o indicie para a tabela de hash_nome
 * @return retorna o indice para a tabela.
 */
long long F_hash_nome(char *nome);
/**
 * Função reponsavel por gerar um indice para a tabela de hash_nif
 * O indice gerado esperace que seja o mais aleatorio possivel entre 0 e 10000 de forma a ter um bom desempenho na tabela de hash
 * para isso a função tem varias condições de geração de numeros
 * @param nif gera-se o indice atraves deste long long
 * @return retorna o indice para a tabela.
 */
long long F_hash_nif(long long nif);
/**
 * Função reponsavel por tranformar uma string em numero
 * @param string String que contem o numero
 * @return retorna o numero como int.
 */
int ler_numero_int(char *string);
/**
 * Função reponsavel por tranformar uma string em numero
 * @param string String que contem o numero
 * @return retorna o numero como long long.
 */
long long ler_numero_ll(char *string);
/**
 * Função auxiliar que verefica se o input é correcto.
 */
void check_input(char *s);
/**
 * Função auxiliar que le os dados introduzidos pelo utilizador.
 */
void ler_dados(char *dado, char* input, int dim);
/**
 * Função que recebe uma resposta do utilizador com yes ou no.
 * @return um interio de vereficação se a operação correu bem.
 */
int resposta();
/**
 * A função responsavel por colocar o perfil do utilizador criado na estrutura de dados(na tabela de hash_nome e tabela de hash_nif).
 * Ela regista o perfil nas posições que lhe são fornecidas através do IDnif e do IDnome.
 * @param IDnif indice para a tabela de hash_nif
 * @param IDnome indice para a tabela de hash_nome
 * @param userP perfil de tilizador a guardar
 * @return um interio de vereficação se a operação correu bem.
 */
int saveToHash(long long IDnif,long long IDnome,Perfil* userP);
/**
 * Esta função recolhe os dados do utilizador que pretende criar o seu perfil na estrutura.
 * Esta função usa a saveToHash para inserir o perfil nas tabelas de hash.
 * @param IdUsers Recebe o id do ultimo registo e incrementa-o
 * @return retorna um inteiro de controlo da operação.
 */
int inserir_user(long long *IdUsers);
/**
 * Acede ao campo apagado de um perfil e marca com 1, que torna este utilizador apagado para as operações futuras.
 * @param nif Através do nif podemos chegar ao perfil, através da função findByNif e alterar o mesmo
 * @return o Um inteiro de verificação da operação
 */
int apagar_user (long long nif);
/**
 * Função que imprime os dados do perfil de um utilizador.
 * @param user Contem o perfil a imprimir
 * @return o Um inteiro de verificação da operação
 */
int print_user(Perfil *user);
/**
 * Função responsavel por encontrar um perfil atraves de um numero passado como argumento.
 * @param nif Nif do perfil que se pretende encontrar.
 * @return o Perfil procurado
 */
Perfil *findByNif(long long nif);
/**
 * Função responsavel por encontrar um perfil atraves de um nome passado como argumento.
 * Como existe a possibilidade de existir algumas pessoas com o mesmo nome é pedido uma confirmação de utilizador
 * @param name Nome do perfil que se pretende encontrar.
 * @return o Perfil procurado
 */
Perfil *findByName(char *name);
/**
 * Função auxiliar, resposavel por ler os varios parametros do ficheiro de base de dados.
 * @param fp ficheiro da base de dados , de onde vão ser lidos os dados.
 * @param dim dimensao do parametro a ler
 * @param parametro a ler
 * @param count controlo do numero de parametros.
 */
void ler_parametro_f(FILE *fp, int count, int dim, char *parametro);
/**
 * Função que le os dados todos de um utilizador e os coloca num perfil de um user
 * @param fp ficheiro de base de dados de onde é retirado os dados
 * @param ptr perfil que recebe os parametros
 * @param id id a atribuir ao novos registos
 * @param count controlo de de leitura
 * @return Interio de vereficação.
 */
int ler_user_ficheiro(FILE *fp, Perfil **ptr, int count, long long *id);
/**
 * Função que é invocada com o intuito de carregar toda a informação sobre os utilizadores para a estrutura de dados.
 * @param input nome do ficheiro onde se vai carregar a informação
 * @param id Este é chamado para a funçõa para ser guardada a referencia ao ultimo id atribuido.
 * @return Retorna um interio que verefica se a operação correu bem.
 */
int carregar_bd(char *input, long long *id);
/**
 * Função reponsavel por tranformar um numero em string
 * @param numero É o numero que se prentede tranforma em string
 * @param numstr string que vai ficar com o numero
 * @return retorna um inteiro que verifica se correu bem.
 */
void converte_ll_str(long long numero, char *numstr);
/**
 * Função que é invocada com o intuito de guardar a informação relativa a um utilizador
 * A informação vai ser guardada num ficheiro que irá servir de base de dados
 * @param fw ficheiro onde se vai guardar a informação
 * @param p Perfil que se prentede guardar.
 * @return Retorna um interio que verefica se a operação correu bem.
 */
void guarda_user(FILE *fw, Perfil *p);
/**
 * Função que é invocada com o intuito de guardar toda a informação sobre os utilizadores para que possa ser utilizada novamente.
 * A informação vai ser guardada num ficheiro que irá servir de base de dados
 * @param output nome do ficheiro onde se vai guardar a informação
 * @param id Este é chamada para a funçõa para ser guardado no ficheiro como um elemento á parte, pois será utilizado como referencia ao ultimo id atribuido.
 * @return Retorna um interio que verefica se a operação correu bem.
 */
int guardar_bd(char *output, long long *id);

