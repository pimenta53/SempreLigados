#include "operacoes.h" 
#include "relacoes.h"
#include "mensagens.h"
#include <stdlib.h>
#include <string.h>



int menu(){
	printf("Criar registo: 1\n");
	printf("Apagar registo: 2\n");
	printf("Criar relação: 3\n");
	printf("Apagar Relação: 4\n");
	printf("Modificar relação: 5\n");
	printf("Ver relação: 6\n");
	printf("Procurar pessoa por nif: 7\n");
	printf("Procurar pessoa por nome: 8\n");
	printf("Enviar mensagem: 10\n");
	printf("Ver mensagem: 11\n");
	printf("Sair: 0\n");
	printf("\n");
return 0;
}

char* menu_relacoes(){
	int n;
	
	printf("amigo: 1\n");
	printf("familiar: 2\n");
	printf("profissional: 3\n");
	scanf("%d",&n);
	if(n==1) return AMI;
	if(n==2) return FAM;
	if(n==3) return PRO;
return NULL;
}

int executa_comando(int comando,Grafo *f,Grafo *a,Grafo *p,Lista_mensagens *lm,long long *IdUser){
	
	long long nif1,nif2;
	char *tipo;
	char *tipo2;
	int peso;
	char nome[50];
	char mensagem[1024];
	
	if(comando==1){
		inserir_user(IdUser);
	}
	if(comando==2){
		printf("\nDigite o nif do utlizador a apagar\n");
		scanf("%lld",&nif1);
		apagar_user (nif1);
	}
	if(comando==3){
		printf("\nDigite o nif do utlizador a quem quer se ligar\n");
		scanf("%lld",&nif1);
		printf("\nDigite o seu nif\n");
		scanf("%lld",&nif2);
		tipo=menu_relacoes();
		printf("\nDigite o peso da relacao\n");
		scanf("%d",&peso);
		relacoes_inserir (nif1,nif2,peso,tipo,f,a,p);
	}
	if(comando==4){
		printf("\nDigite o nif do utlizador a quem quer cortar a ligação ligar\n");
		scanf("%lld",&nif1);
		printf("\nDigite o seu nif\n");
		scanf("%lld",&nif2);
		tipo=menu_relacoes();
		relacoes_remover (nif1,nif2,tipo,f,a,p);
	}
	if(comando==5){
		printf("\nDigite o nif do utlizador a quem quer se ligar\n");
		scanf("%lld",&nif1);
		printf("\nDigite o seu nif\n");
		scanf("%lld",&nif2);
		tipo=menu_relacoes();
		tipo2=menu_relacoes();
		printf("\nDigite o peso da relacao\n");
		scanf("%d",&peso);
	alterar_relacao(nif1,nif2,tipo,tipo2,peso,a,f,p);
	}
	if(comando==6){
		printf("\nDigite o nif do utlizador a quem quer ver as ligaçpes\n");
		scanf("%lld",&nif1);
		tipo=menu_relacoes();
		ver_relacoes (nif1,tipo,f,a,p);
	}	
	if(comando==7){
		printf("\nDigite o nif do utlizador a procurar\n");
		scanf("%lld",&nif1);
		print_user(findByNif(nif1));
	}
	if(comando==8){
		printf("\nDigite o nome do utlizador a procurar\n");
		scanf("%s",nome);
		print_user(findByName(nome));
	}
	if(comando==10){
		printf("\nDigite o nif do utlizador a quem quer mandar uma mensagem\n");
		scanf("%lld",&nif1);
		printf("\nDigite o seu nif\n");
		scanf("%lld",&nif2);
		printf("digite a sua mensagem\n");
		scanf("%s",mensagem);
		grava_mensagem(nif1,nif2,mensagem,lm);
	}
	if(comando==11){
		printf("\nDigite o nif do utlizador a quem quer ver as mensagens\n");
		scanf("%lld",&nif1);
		print_mensagens(nif1,lm);
	}	
	if(comando==0) exit(1);
			
	
return 0;
}
	
	
	


int main() {

	Grafo *f=malloc(sizeof(Grafo));
	f->ocupados=0;
	Grafo *a=malloc(sizeof(Grafo));
	a->ocupados=0;
	Grafo *p=malloc(sizeof(Grafo));
	p->ocupados=0;
	Lista_mensagens *lm=malloc(sizeof(Lista_mensagens));
	lm->total_utilizadores=0;
	long long idUser=0;
	
	int comando;
	
	//carregar_bd("clientes.csv",&idUser);
	while(1){	
	menu();
	scanf("%d",&comando);
	system("clear");			
	executa_comando(comando,f,a,p,lm,&idUser);
	}
	
	

	
	/*inserir_user(&idUser);
	inserir_user(&idUser);
	int i=0;
	while (i<MAXNODES) {
		if (hash_nif[i]) {
			print_user(hash_nif[i]->user);
		}
		i++;
	}
	guardar_bd("resultado1.csv",&idUser);
	i=0;
	while (i<MAXNODES) {
		hash_nif[i]=NULL;
		hash_nome[i]=NULL;
		i++;
	}
	idUser=0;
	carregar_bd("resultado1.csv",&idUser);
	i=0;
	while (i<MAXNODES) {
		if (hash_nif[i]) {
			print_user(hash_nif[i]->user);
		}
		i++;
	}*/
	
	
	/* printf("errado");
	if (p) printf("%lld\n",p->id);
	apagar_user(findByName("ricardo")->nif);
	printf("%lld\n",findByName("ricardo")->id);*/
	return 0;
}

