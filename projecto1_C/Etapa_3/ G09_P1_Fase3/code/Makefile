sempreLigados: dados.o users.o users_IO.o users_file.o relacoes.o relacoes_IO.o msg_operac.o mensagens_IO.o mensagens_FILE.o menus.o relacoes_FILE.o erro.o main.o
	gcc -Wall -o sempreLigados dados.o users.o users_IO.o users_file.o relacoes.o relacoes_IO.o msg_operac.o mensagens_IO.o mensagens_FILE.o relacoes_FILE.o menus.o erro.o main.o  -lncurses
dados.o:dados.c dados.h define.h
	gcc -c -g -Wall dados.c 
users.o:users.c users.h define.h estruturas.h erro.h
	gcc -c -g -Wall users.c 
users_IO.o:users_IO.c users_IO.h define.h estruturas.h users.h dados.h
	gcc -c -g -Wall users_IO.c
users_file.o:users_file.c users_file.h define.h estruturas.h users.h dados.h erro.h
	gcc -c -g -Wall users_file.c 
relacoes.o:relacoes.c relacoes.h define.h users.h erro.h
	gcc -c -g -Wall relacoes.c 
relacoes_FILE.o: relacoes_FILE.c relacoes_FILE.h relacoes.h erro.h
	gcc -c -g -Wall relacoes_FILE.c
relacoes_IO.o:relacoes_IO.c relacoes_IO.h define.h dados.h relacoes.h users_IO.h
	gcc -c -g -Wall relacoes_IO.c  
msg_operac.o:msg_operac.c msg_operac.h mensagens.h define.h users.h erro.h
	gcc -g -c -Wall msg_operac.c
mensagens_IO.o:mensagens_IO.c mensagens_IO.h msg_operac.h mensagens.h define.h users.h dados.h
	gcc -g -c -Wall mensagens_IO.c
mensagens_FILE.o: mensagens_FILE.c mensagens_FILE.h mensagens.h define.h
	gcc -g -c -Wall mensagens_FILE.c
menus.o:menus.c define.h dados.h users_IO.h relacoes_IO.h mensagens_IO.h users_file.h mensagens.h users.h
	gcc -c -g -Wall menus.c
erro.o: erro.c erro.h
	gcc -c -g -Wall erro.c
main.o:main.c define.h dados.h users_IO.h relacoes_IO.h users_file.h mensagens.h users.h menus.h
	gcc -c -g -Wall main.c
clean:
	rm *.o
