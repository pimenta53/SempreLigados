sempreLigados: dados.o users.o users_IO.o users_file.o relacoes.o relacoes_IO.o mensagens.o mensagens_IO.o menus.o relacoes_FILE.o erro.o main.o 
	gcc -Wall -gd -o sempreLigados dados.o users.o users_IO.o users_file.o relacoes.o relacoes_IO.o mensagens.o mensagens_IO.o relacoes_FILE.o menus.o erro.o main.o  -lncurses
dados.o:dados.c dados.h define.h
	gcc -c -Wall dados.c 
users.o:users.c users.h define.h estruturas.h erro.h
	gcc -c -Wall users.c 
users_IO.o:users_IO.c users_IO.h define.h estruturas.h users.h dados.h
	gcc -c -Wall users_IO.c
users_file.o:users_file.c users_file.h define.h estruturas.h users.h dados.h erro.h
	gcc -c -Wall users_file.c 
relacoes.o:relacoes.c relacoes.h define.h users.h erro.h
	gcc -c -Wall relacoes.c 
relacoes_FILE.o: relacoes_FILE.c relacoes_FILE.h relacoes.h erro.h
	gcc -c -Wall relacoes_FILE.c
relacoes_IO.o:relacoes_IO.c relacoes_IO.h define.h dados.h relacoes.h users_IO.h
	gcc -c -Wall relacoes_IO.c  
mensagens.o:mensagens.c mensagens.h define.h users.h erro.h
	gcc -c -Wall mensagens.c
mensagens_IO.o:mensagens_IO.c mensagens_IO.h mensagens.h define.h users.h dados.h
	gcc -c -Wall mensagens_IO.c
menus.o:menus.c define.h dados.h users_IO.h relacoes_IO.h mensagens_IO.h users_file.h mensagens.h users.h
	gcc -c -Wall menus.c
erro.o: erro.c erro.h
	gcc -c -Wall erro.c
main.o:main.c define.h dados.h users_IO.h relacoes_IO.h users_file.h mensagens.h users.h menus.h
	gcc -c -Wall main.c
clean:
	rm *.o
