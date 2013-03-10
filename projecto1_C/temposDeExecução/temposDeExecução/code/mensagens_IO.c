#include <sys/time.h>
#include "mensagens_IO.h"
#include "define.h"
#include "users.h"
#include "dados.h"
#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int print_mensagens(long long userID,long long nif,Lista_destinatario *ld){
	
	Perfil *user=findByNif(nif);
	Destinatario *dst=NULL;
	long long id;
	char cmd;
	int sair=0;
	
	if(!user){
		printw("Não existe nenhum utilizador com este nif\n");
		getch();
		return 0;
	}
	
	id=user->id;
	if (id>ld->dimensao) act_tam_list_msg(userID,ld);
	if(!ld->L_mensagens[id]){
		dst=procura(id);
		if (dst) ld->L_mensagens[id]=dst;
		else {
			printw("\nNão tem mensagens %p\n\n",ld->L_mensagens[id]);
			getch();
			return 0;
		}
	}
	
	Remetente *aux_rem=ld->L_mensagens[id]->remetentes;
	Mensagens *aux_msg;
	
	while (aux_rem && !sair){
		aux_msg=aux_rem->msg;
		user = findByNif(aux_rem->nif);
		while(aux_rem->msg!=NULL && !sair){
			printw ("\n-----------------------------------");
			printw ("\n\nEnviadas por pelo utilizador(a) %s\n\n", user->nome);
			printw("%s\n\n",aux_rem->msg->mensagem);
			printw("Sair:q \n");
			printw ("-----------------------------------\n\n");
			cmd=getch();
			clear();
			if(cmd=='q') sair=1;
			aux_rem->msg=aux_rem->msg->next;
		}
	aux_rem->msg=aux_msg;
	aux_rem=aux_rem->next;
	}
	return 1;
}

int act_mais_popular (int total_msg, long long n_nif, Lista_destinatario *ld){
	if (total_msg>(ld->num_mensagens)) {
		ld->num_mensagens = total_msg;
		ld->nif_popular = n_nif;
	}
	return 1;
}

int grava_mensagem(long long nif2,long long nif1,char *mensagem,Lista_destinatario *ld, long long userID){
	Perfil *user1=findByNif(nif1);
	Perfil *user2=findByNif(nif2);
	long long id1;
	long long id2;
	Destinatario *dest=NULL;
	
	/*-----------Declaração-------------*/
		struct timeval t1,t2;
		long sec;
		long usec;
	/*--------------------------------*/
	/*------------tempo inicio----------*/
        gettimeofday(&t1,NULL);
	/*--------------------------------*/
	if(!user1 || !user2){
		return mensagem_de_erro(E_NO_NIF);
		}
		
	if (nif1==nif2) {
		return mensagem_de_erro(E_NO_NIF);
	}
	
	Mensagens *mensagem1=malloc(sizeof(Mensagens));
	mensagem1->mensagem=malloc(MAXMSG*sizeof(char));
	strcpy(mensagem1->mensagem,mensagem);
	mensagem1->next=NULL;
	
	id1=user2->id;
	id2=user1->id;
	if (id2>ld->dimensao) act_tam_list_msg(userID,ld);
	
	if (!(ld->L_mensagens[id2])) {
		dest=procura(id2);
		if (dest) ld->L_mensagens[id2]=dest;
		else {
			dest = malloc(sizeof(Destinatario));
			dest->total_mensagens = 0;
			dest->remetentes = NULL;
			ld->L_mensagens[id2]=dest;
		}
	}
	
	(ld->L_mensagens[id2]->total_mensagens)++;

	act_mais_popular (ld->L_mensagens[id2]->total_mensagens, user1->nif, ld);
	
	
	Remetente *aux_remetente=ld->L_mensagens[id2]->remetentes;
	Remetente *aux_ant=ld->L_mensagens[id2]->remetentes;
	
	while ((ld->L_mensagens[id2]->remetentes)!=NULL) {
		aux_ant=ld->L_mensagens[id2]->remetentes;
		if ((ld->L_mensagens[id2]->remetentes->id) == id1) break;
		ld->L_mensagens[id2]->remetentes = ld->L_mensagens[id2]->remetentes->next;
	}
	
	
	if (ld->L_mensagens[id2]->remetentes==NULL) {
		Remetente *rem = malloc(sizeof(Remetente));
		rem->id=id1;
		rem->n_mensagens=1;
		rem->nif = nif2;
		rem->msg = mensagem1;
		rem->next=NULL;
		ld->L_mensagens[id2]->remetentes = aux_ant;
		if ((ld->L_mensagens[id2]->remetentes)==NULL) ld->L_mensagens[id2]->remetentes = rem;
		else  {
			ld->L_mensagens[id2]->remetentes->next = rem;
			ld->L_mensagens[id2]->remetentes=aux_remetente;
		}
		
		/*------------tempo fim-----------*/
        gettimeofday(&t2,NULL);
        sec=(t2.tv_sec)-(t1.tv_sec);
        usec=(t2.tv_usec)-(t1.tv_usec);
        if(usec<0) usec+=1000000;
        FILE *pT = fopen("times.txt","a+");
        fprintf(pT,"mensagens ->%ld s %ld us \n",sec,usec);
        fclose(pT);
		/*--------------------------------*/

		return 1;
	}
		
	if ((ld->L_mensagens[id2]->remetentes->n_mensagens)>19) {
		Mensagens *m_aux = ld->L_mensagens[id2]->remetentes->msg;
		ld->L_mensagens[id2]->remetentes->msg = ld->L_mensagens[id2]->remetentes->msg->next;
		free(m_aux);
		(ld->L_mensagens[id2]->remetentes->n_mensagens)--;
	}
	
	Mensagens *auxiliar = ld->L_mensagens[id2]->remetentes->msg;
	
	while (ld->L_mensagens[id2]->remetentes->msg->next!=NULL) {
		ld->L_mensagens[id2]->remetentes->msg=ld->L_mensagens[id2]->remetentes->msg->next;
	}
	
	ld->L_mensagens[id2]->remetentes->msg->next = mensagem1;
	(ld->L_mensagens[id2]->remetentes->n_mensagens)++;
	ld->L_mensagens[id2]->remetentes->msg=auxiliar;
	ld->L_mensagens[id2]->remetentes=aux_remetente;
	
		/*------------tempo fim-----------*/
        gettimeofday(&t2,NULL);
        sec=(t2.tv_sec)-(t1.tv_sec);
        usec=(t2.tv_usec)-(t1.tv_usec);
        if(usec<0) usec+=1000000;
        FILE *pT = fopen("times.txt","a+");
        fprintf(pT,"mensagens ->%ld s %ld us \n",sec,usec);
        fclose(pT);
		/*--------------------------------*/

	return 1;
}

int escrever_mensagem(long long userID, long long nif1,Lista_destinatario *ld){
	
	char msg[MAXMSG];
	long long nif2;
	
	nif2=ler_nif();	
	echo();	
	printw("Digite a sua mensagem:\n");
	getnstr(msg,MAXMSG-1);
	
	if(grava_mensagem(nif1,nif2,msg,ld,userID)){
		clear();
		printw("Mensagem enviada com sucesso");
		getch();
	}
	else{
		clear();
		printw("Impossivel enviar mensagem");
		getch();
	}
	noecho();
	return 0;
}

int ver_popular(Lista_destinatario *ld){
	Perfil *user=findByNif(ld->nif_popular);
	if(user) {
		print_user(user);
		printw("");
		printw("TEM: %d mensagens.\n",ld->num_mensagens);
		getch();
	}
	else{
		clear();
		printw("Ainda ninguem recebeu mensagens");
		getch();
	}

return 0;
}

