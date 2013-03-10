#include "operacoes.h"
//hash nome
long long F_hash_nome(char *nome){
	long long res;
	
	int tam=strlen(nome);
	if(tam<=5 && nome[0]=='Y') return 0;//(nome[tam-2]%10);
	if(tam>5 && tam<=7) return 0;//(((nome[tam-3])%10)*10 +nome[tam-1]+nome[tam-2]+nome[tam-3]+nome[tam-4]);
	if((tam>14 && tam<20) && (nome[tam-2]=='e' || nome[tam-2]=='i'||nome[tam-2]=='o' || nome[tam-2]=='u' )) return 0; //(((((nome[tam-8])%10)*100) +tam +nome[tam-2]));	
	if(tam<=5 && nome[0]!='Y') return 0 ;//tam*10+(nome[1]%10)*1000;
	res = (((nome[1]%10)*1000) + ((nome[tam-7]%10)*100) +((nome[tam-6]%10)*10) + nome[tam-7] + nome[tam-6] + nome[tam-5] + nome[tam-4] + nome[tam-10]%10);
	if (res<0) return (res*(-1));
	return res;
}

//hash nif
long long F_hash_nif(long long nif){
	
	long long n1=nif%10;
	long long n2=nif%2;
	long long n3=nif%9;	
	long long n4=nif%100;
	
	
	if(n1==0 && n2==n3 &&n2==1) return ((n2+1)*3);
	if(n1==1 && (n3<=1 && n3>5)) return(((n3)*10)+n2*2+n3);
	if(n1>=2 && n1<3) return ((n3*100)+(((n2+1)*2)*10)+n1);
	if(n1>=4 && n1<7 && n3<5) return (((n3)*1000)+(n2*53)+(n2*2)+n3*10+n4);
	if(n1>=4 && n1<7 && n3>5) return (((n3+1)*1000)+(n2*100)+(n3*53)+(n3*2)+n2+n4);

	return ((nif%1000)-n3+(n2*100)+n4*100+n3*90);
}

//ler numero NIF
int ler_numero_int(char *string) {

        int i = atoi(string);
        return i;
}
	
//ler numero NIF
long long ler_numero_ll(char *string) {

        char *end;
        long long i = strtoll(string,&end,0);

        if ((*end)!='\0') return -1;
        return i;
}


void check_input(char *s) {
	char *t;
	if ((t=strchr(s,'\n'))==NULL) {
		while (getchar()!='\n');
	}
	else *t='\0';
}

void ler_dados(char *dado, char* input, int dim) {
	char *valid=NULL;

	printf("%s:\n",dado);
	while (valid==NULL) {
		valid=fgets(input,dim,stdin);
		check_input(input);
		if (strcmp("\0",input)==0){
			fprintf(stdout,"Insira %s válido: \n",dado);
			valid=NULL;
		}
	}
}

int resposta() {
	char c=' ';
	while (c!='y' && c!='n') {
		c=fgetc(stdin);
	}
	if (c=='y') return 1;
	return 0;
}


int saveToHash(long long IDnif,long long IDnome,Perfil* userP){
	
	User_h *newUser=malloc(sizeof(User_h));
	User_h **aux;
	long long nif_check=userP->nif;
	int valid=1;

	if(!newUser) {
		fprintf(stderr,"errco ao alocar mem\n"); 
		return 0;
	}
	newUser->user=userP;
	newUser->next=NULL;
	
	//guarda apontador para perfil na tabela de hash caso n exista nenhum utilizador com o mesmo nif
	aux=&hash_nif[IDnif];
	while ((*aux) && valid) {
		if ((*aux)->user->nif!=nif_check) aux=&((*aux)->next);
		else valid=0;
	}
	if (valid) (*aux)=newUser;
	else {
		if ((*aux)->user->apagado==1)  {
			fprintf(stdout,"O utilizador com o NIF %lld foi apagado! Deseja reativar a conta?",(*aux)->user->nif);
			if (resposta()) (*aux)->user->apagado=0;
			free(newUser);
			return 0;
		}
		else fprintf(stdout,"Já existe um utilizador com o mesmo NIF.\n");
		free(newUser);
		return 0;
	}

	//guarda apontador para perfil na tabela de hash dos nomes caso n exista nenhum utilizador com o mesmo nif
	aux=&hash_nome[IDnome];
	while (*aux) {
		aux=&((*aux)->next);
	}
	(*aux)=newUser;
		
	return 1;
}


int inserir_user(long long *IdUsers) {
	
	char nome[MAXNOME];
	char cidade[MAXCIDADE];
	char email[MAXEMAIL];
	char estado_civil[MAXESTADOCIV];
	char nifstr[MAXNIF];
	long long nif=-1;
	int valid=1;
	char *s=NULL;

	Perfil *p=malloc(sizeof(Perfil));

	if (p==NULL) {
		fprintf(stderr,"Memoria insuficiente!\n");
		return -1;
	}
	
	ler_dados("nome",nome,MAXNOME);
	ler_dados("cidade",cidade,MAXCIDADE);	
	ler_dados("estado civil",estado_civil,MAXESTADOCIV);		
	ler_dados("email",email,MAXEMAIL);		

	printf("nif: \n");
	while (nif==-1){
		s=fgets(nifstr,MAXNIF,stdin);
		if (strcmp(nifstr,"\n")==0 || strchr(nifstr,'\n')==NULL) {
			fprintf(stdout,"NIF válido! Insira NIF com máximo de %d digitos.\n",MAXNIF-2);
			valid=0;
		} 
		check_input(nifstr);
		if (valid) {
			nif=ler_numero_ll(nifstr);
			if (nif==-1 && valid) fprintf(stdout,"Insira um NIF válido:\n");
		}
		valid=1;
	}

	strcpy(p->nome,nome);
	strcpy(p->cidade,cidade);
	strcpy(p->estado_civil,estado_civil);
	strcpy(p->email,email);
	p->nif=nif;
	p->id = *IdUsers;
	p->apagado=0;
	
	if (saveToHash(F_hash_nif(nif),F_hash_nome(nome),p)) {
		(*IdUsers)++;
		return 1;
	}
	return 0;
}

int apagar_user (long long nif) {
	long long pos = F_hash_nif(nif);
	
	User_h *user = hash_nif[pos];
	
	while (user!=NULL) {
		if (user->user->nif==nif) {
			user->user->apagado=1;
			return 1;
		}
		user=user->next;
	}
	return 0;
}


int  print_user(Perfil *user){
	if(!user) {
		printf("Utilizador não exite ou foi apagado\n");
		return 0;
	}
	
	printf("\n------Informação User-------\n");
	printf(" %lld\n",user->id);
	printf(" %s\n",user->nome);
	printf(" %s\n",user->cidade);
	printf(" %s\n",user->estado_civil);
	printf(" %s\n",user->email);
	printf(" %lld\n",user->nif);
	printf("\n----------------------------\n");
	printf("\n");
	
	return 0;
}


Perfil *findByNif(long long nif) {
	
	long long IDnif=F_hash_nif(nif);
	
	if(!hash_nif[IDnif]) return NULL;
	User_h *aux=hash_nif[IDnif];
	
	while(aux && (aux->user->nif!=nif)){
		aux=aux->next;
	}
	if(aux && aux->user->apagado==0) return(aux->user);
	return NULL;
}


Perfil *findByName(char *name){
	
	long long IDname;
	User_h *aux;
	int confirm=0;
	
	IDname=F_hash_nome(name);
	if(!(aux=hash_nome[IDname])) return NULL;
	
	while(aux && !confirm){
		if(strcmp((aux->user->nome),name)==0 && aux->user->apagado==0){ 
			print_user(aux->user);
			printf(" É este o utilizador? (y/n)\n");
			confirm=resposta();
		}
		if(confirm) return (aux->user);
		aux=aux->next;
	}
	return NULL;
}


void ler_parametro_f(FILE *fp, int count, int dim, char *parametro) {
        fseek(fp,(long) (count*sizeof(char)),SEEK_SET);
        fgets(parametro,dim,fp);
}

int ler_user_ficheiro(FILE *fp, Perfil **ptr, int count, long long *id) {

        char idstr[MAXUSERSTR], apgdstr[MAXAPAGADO], nifstr[MAXNIF], endstr[END];
	Perfil *p = malloc(sizeof(Perfil));

        ler_parametro_f(fp,count,MAXUSERSTR,idstr);
        count+=MAXUSERSTR;

        ler_parametro_f(fp,count,MAXNIF,nifstr);
        count+=MAXNIF;
        ler_parametro_f(fp,count,MAXNOME,p->nome);
        count+=MAXNOME;
        ler_parametro_f(fp,count,MAXCIDADE,p->cidade);
        count+=MAXCIDADE;
        ler_parametro_f(fp,count,MAXESTADOCIV,p->estado_civil);
        count+=MAXESTADOCIV;
        ler_parametro_f(fp,count,MAXEMAIL,p->email);
        count+=MAXEMAIL;
        ler_parametro_f(fp,count,MAXAPAGADO,apgdstr);
        count+=MAXAPAGADO;
        ler_parametro_f(fp,count,END,endstr);
        count+=END;

        if (strcmp(endstr,".")!=0) {
                fprintf(stderr,"Ficheiro com formato inválido!\n");
		free(p);
                return 0;
        }

        p->id=ler_numero_ll(idstr);
        if (p->id==-1) {
                fprintf(stderr,"Ficheiro com formato inválido!\n");
		free(p);
                return 0;
        }
        p->nif=ler_numero_ll(nifstr);
        if (p->nif==-1) {
                fprintf(stderr,"Ficheiro com formato inválido!\n");
		free(p);
                return 0;
        }
        p->apagado=ler_numero_int(apgdstr);
        if (p->apagado==-1) {
                fprintf(stderr,"Ficheiro com formato inválido!\n");
		free(p);
                return 0;
        }
	p->id=(*id);
	(*ptr)=p;
	(*id)++;

        return count;
}

int carregar_bd(char *input, long long *id) {
	
	int j=0;	
        int count=0;
	int inseriu=1;
	Perfil *p=NULL;
	FILE *fp = fopen(input,"r");
	
	if (fp==NULL) {
		fprintf(stdout,"Impossível abrir ficheiro.\n");
		return 0;
	}
        while (j<2 && inseriu) {
                count=ler_user_ficheiro(fp,&p,count,id);
                if (count) {	printf("conseguir ler\n");
			inseriu=saveToHash(F_hash_nif(p->nif),F_hash_nome(p->nome),p);
                	if (inseriu)	printf("conseguir inserir\n");
		}
                else {
			printf("Erros ao inserir na hash.\n");
			inseriu=0;
		}
                j++;
        }
        fclose(fp);
	if (inseriu==0) {
		fprintf(stdout,"Erros ao ler o ficheiro.\n");
		return 0;
	}
        return 1;
}

void guardar_str(char *str, int dim, FILE *f) {
        int i=0;
        while (i<dim) {
                fputc(str[i],f);
                i++;
        }
}

void converte_ll_str(long long numero, char *numstr) {
        sprintf(numstr,"%lld",numero);
}


void guarda_user(FILE *fw, Perfil *p) {

        char idstr[MAXUSERSTR], apgdstr[MAXAPAGADO], nifstr[MAXNIF];
        char end = '.';

	converte_ll_str(p->id,idstr);
        converte_ll_str(p->nif,nifstr);
        sprintf(apgdstr,"%d",p->apagado);
        guardar_str(idstr,MAXUSERSTR,fw);
        guardar_str(nifstr,MAXNIF,fw);
        guardar_str(p->nome,MAXNOME,fw);
        guardar_str(p->cidade,MAXCIDADE,fw);
        guardar_str(p->estado_civil,MAXESTADOCIV,fw);
        guardar_str(p->email,MAXEMAIL,fw);
        guardar_str(apgdstr,MAXAPAGADO,fw);
        guardar_str(&end,END,fw);
}

int guardar_bd(char *output, long long *id) {
	//gravar_id;
        FILE *fw=fopen(output,"w");
	User_h *lista=NULL;
	int i=0;

        if(!fw){ 
                fprintf(stderr,"Não conseguio criar o ficheiro %s.\n",output);
                return 0;
        }

        while(i<MAXNODES){
		lista=hash_nif[i];
		while (lista) {
			guarda_user(fw,lista->user);
			lista=lista->next;
		}
		i++;
      	}
	fclose(fw);
	return 1;
}


