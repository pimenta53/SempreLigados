#include "define.h" 
//estrutura para saber quais os adjacentes de um nodo. 
//posicao do adjacente no grafo (indice no array pq usamos lista de adjacencias)
//peso da ligação
//apontador para o próximo adajcente
typedef struct adj{
	long int id;
	long long nif;
	int peso;
	struct adj *next;
} Adj;


//grafos para as diferentes relações
//tem o numero de nodos existentes no grafo
//tem apontador para a estrutura Nodo (ver anterior) k tem o indice da tabela de hash k permite aceder ao perfil
//tem apontador para os nodos adjacentes 
typedef struct grafo{
	int ocupados;
	Adj *nodos[MAXNODES];		
} Grafo;

/**
 * A função inserir_ligação irá criar uma ligação entre dois utilizadores, num determinado grafo("estrutura de dados escolhida") que poderá corresponder a familia, amigos ou profissional.
 * Será então criada uma ligação entre dois utilizadores e será atribuido um determinado peso a essa ligação.
 * @param nif1 campo correspondente ao nif de quem queremos criar uma relação, este será util para podermos ter o id do utilizador e aceder imediatamente ao campo correspondente na estrutura de dados.
 * @param nif2 campo correspondente ao nif de quem está a criar a ligação, este será util para podermos ter o id do utilizador e aceder imediatamente ao campo correspondente na estrutura de dados.
 * @param peso É um avaliador da qualidade da relação.
 * @param g estrutura de dados onde se guarda todas as relações de um mesmo tipo.
 * @returns Retorna um inteiro que verifica se conseguiu ou não efectuar a operação.
 */
int inserir_ligacao(long long nif1,long long nif2,int peso,Grafo *g);
/**
 * A função remover irá eleminar a relação entre dois utulizadores, apagando esta definitivamente,
 * Desta forma os dois utilizadores deixam de tar ligados numa determinada relação.
 * @param nif1 campo correspondente ao nif de quem queremos quebrar uma relação, este será util para podermos ter o id do utilizador e aceder imediatamente ao campo correspondente na estrutura de dados.
 * @param nif2 campo correspondente ao nif de quem está a quebrar a ligação, este será util para podermos ter o id do utilizador e aceder imediatamente ao campo correspondente na estrutura de dados.
 * @param relacao É o tipo de relação que se vai eliminar.
 * @param g estrutura de dados onde se guarda todas as relações de um mesmo tipo.
 * @returns Retorna um inteiro que verifica se conseguiu ou não efectuar a operação.
 */
int remover(long nif1, long nif2, char *relacao, Grafo *g);
/**
 * A função relaçoes_remover irá eleminar a relação entre dois utulizadores, apagando esta definitivamente chamando a função "remover".
 * Nesta função é passado o tipo de relaçãoa a remover, e as estruturas correspondetes aos tres tipos de dados.
 * A função vai  decidir em qual das estruturas vai apagar a relação.
 * @param nif1 campo correspondente ao nif de quem queremos quebrar uma relação, este será util para podermos ter o id do utilizador e aceder imediatamente ao campo correspondente na estrutura de dados.
 * @param nif2 campo correspondente ao nif de quem está a quebrar a ligação, este será util para podermos ter o id do utilizador e aceder imediatamente ao campo correspondente na estrutura de dados.
 * @param tipo É o tipo de relação que se vai eliminar.
 * @param f estrutura de dados onde se guarda todas as relações de um mesmo tipo(familia).
 * @param a estrutura de dados onde se guarda todas as relações de um mesmo tipo(amigos).
 * @param p estrutura de dados onde se guarda todas as relações de um mesmo tipo(Proficional).
 * @returns Retorna um inteiro que verifica se conseguiu ou não efectuar a operação.
 */
int relacoes_remover (long nif1, long nif2,char *tipo,Grafo *f,Grafo *a,Grafo *p);
/**
 * A função relaçoes_inserir irá criar umaa relação entre dois utulizadores chamando a função "inserir".
 * Nesta função é passado o tipo de relaçãoa a criar, e as estruturas correspondetes aos tres tipos de dados.
 * A função irá então decidir em qual das estruturas se vai criar a relação.
 * @param nif1 campo correspondente ao nif de quem queremos criar uma relação, este será util para podermos ter o id do utilizador e aceder imediatamente ao campo correspondente na estrutura de dados.
 * @param peso O novo peso da realção
 * @param nif2 campo correspondente ao nif de quem está criar a ligação, este será util para podermos ter o id do utilizador e aceder imediatamente ao campo correspondente na estrutura de dados.
 * @param tipo É o tipo de relação que se vai criar.
 * @param f estrutura de dados onde se guarda todas as relações de um mesmo tipo(familia).
 * @param a estrutura de dados onde se guarda todas as relações de um mesmo tipo(amigos).
 * @param p estrutura de dados onde se guarda todas as relações de um mesmo tipo(Proficional).
 * @returns Retorna um inteiro que verifica se conseguiu ou não efectuar a operação.
 */
int relacoes_inserir (long nif1, long nif2,int peso,char *tipo,Grafo *f,Grafo *a,Grafo *p);
/**
 * A função alterar_relação irá eleminar a relação entre dois utulizadores, apagando esta definitivamente chamando a função "remover" e cria uma nova entre os mesmo utilizadores usando a função inserir ligação.
 * Nesta função é passado o tipo de relação que se quer alterar e que se pertende alterar, e as estruturas correspondetes aos tres tipos de dados para se poderem efectuar as operações.
 * A função vai irá decidir em qual das estruturas vai apagar a relação e criar a nova relação.
 * @param nif1 campo correspondente ao nif de quem queremos alterar uma relação, este será util para podermos ter o id do utilizador e aceder imediatamente ao campo correspondente na estrutura de dados.
 * @param nif2 campo correspondente ao nif de quem está a altera a ligação, este será util para podermos ter o id do utilizador e aceder imediatamente ao campo correspondente na estrutura de dados.
 * @param tipo1 É o tipo de relação que se vai eliminar.
 * @param tipo2 É o tipo de relação que se vai criar.
 * @param peso É o novo peso da relação.
 * @param f estrutura de dados onde se guarda todas as relações de um mesmo tipo(familia).
 * @param a estrutura de dados onde se guarda todas as relações de um mesmo tipo(amigos).
 * @param p estrutura de dados onde se guarda todas as relações de um mesmo tipo(Proficional).
 * @returns Retorna um inteiro que verifica se conseguiu ou não efectuar a operação.
 */
int alterar_relacao(long nif1,long nif2,char *tipo1,char *tipo2,int peso,Grafo *a,Grafo *f,Grafo *p);
/**
 * A função ver_relação mostra os dados de um utilizador ligado a outro e os dadoas da relação.
 * A função irá apenas mostrar uma relação especifica.
 * @param nif É campo correspondente ao nif de quem queremos ver uma relação, este será util para podermos ter o id do utilizador e aceder imediatamente ao campo correspondente na estrutura de dados.
 * @param a Estrutura de dados onde se guarda todas as relações de um mesmo tipo e que vai ser utlizada para consultarmos a relação.
 * @returns Retorna um inteiro que verifica se conseguiu ou não efectuar a operação.
 */
int ver_relacao(long long nif,Grafo *a);
/**
 * A função ver_relacoes mostra todos os utilizadores ligados a um outro, para isso ela vai invocando a função ver_relacao.
 * A função irá mostrar todas as pessoas ligas a um utilizador num tipo especifico de relação.
 * @param nif1 É campo correspondente ao nif de quem queremos ver as relações, este será util para podermos ter o id do utilizador e aceder imediatamente ao campo correspondente na estrutura de dados.
 * @param tipo É o tipo de relação que se pretende ver as pessoas ligadas ao utilizador escolhido.
 * @param f estrutura de dados onde se guarda todas as relações de um mesmo tipo(familia).
 * @param a estrutura de dados onde se guarda todas as relações de um mesmo tipo(amigos).
 * @param p estrutura de dados onde se guarda todas as relações de um mesmo tipo(Proficional).
 * @returns Retorna um inteiro que verifica se conseguiu ou não efectuar a operação.
 */
int ver_relacoes (long nif1,char *tipo,Grafo *f,Grafo *a,Grafo *p);

