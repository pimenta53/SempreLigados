#include <stdio.h>
#include "erro.h"
#include <ncurses.h>
#include <string.h>

typedef struct erro {
        char *err_code;
        char *mensagem;
} ERRO;

static ERRO erro[] = {
        {"E_NO_NIF",                    "Nif enexistente"},
        {"E_NO_SEND",                   "Não é possivel enviar para o próprio"},
       	{"E_NO_USER",                 	"Utilizador não existe"},
        {"E_NO_MSG",                    "Não tem mensagens"},       
		{"E_MEM",                   	"Memória insuficiente"},
        {"E_INVALIDE_TYPE",             "Formato do ficheiro inválido"},
        {"E_OPEN_FILE",            	"Erro ao abrir ficheiro"},
        {"E_CREATE_FILE",               "Erro ao criar ficheiro"},
};

/**
* Reporta o erro escrevendo uma mensagem no standard error
* @param erro_num O número do erro que vem da tabela de erros. Usar SEMPRE o define e não o valor numérico para maior legibilidade.
*/
int mensagem_de_erro(int erro_num) {
		
		int row,col;
		
		getmaxyx(stdscr,row,col);
		clear();
		mvprintw(row/2,(col-strlen(erro[erro_num].mensagem))/2,"%s", erro[erro_num].mensagem);
		getch();
		def_prog_mode();
		endwin();
		(void) fprintf(stderr, "%s\n", erro[erro_num].mensagem);
        reset_prog_mode();
        return erro_num;
}

