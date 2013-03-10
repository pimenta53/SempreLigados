#include "estruturas.h"
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

int saveToHash(long long hash_nif_code,long long hash_nome_code,Perfil* new_entry, long long *id);
/**
 * Esta função recolhe os dados do utilizador que pretende criar o seu perfil na estrutura.
 * Esta função usa a saveToHash para inserir o perfil nas tabelas de hash.
 * @param IdUsers Recebe o id do ultimo registo e incrementa-o
 * @return retorna um inteiro de controlo da operação.
 */
int inserir_user(long long *IdUsers,char *nome,char *cidade,char *estado_civil,char *email,long long nif);
/**
 * Acede ao campo apagado de um perfil e marca com 1, que torna este utilizador apagado para as operações futuras.
 * @param nif Através do nif podemos chegar ao perfil, através da função findByNif e alterar o mesmo
 * @return o Um inteiro de verificação da operação
 */
int apagar_user (long long nif);
/**
 * Função responsavel por encontrar um perfil atraves de um numero passado como argumento.
 * @param nif Nif do perfil que se pretende encontrar.
 * @return o Perfil procurado
 */
Perfil *findByNif(long long nif);


int editar_perfil(char *cidade,char *estado_civil,char *email,long long nif);

