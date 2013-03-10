sempreLigados:operacoes.o relacoes.o main.o mensagens.o
	gcc -Wall -gd -o sempreLigados operacoes.o relacoes.o mensagens.o main.o 
operacoes.o:operacoes.c estruturas.h
	gcc -Wall -c operacoes.c 
relacoes.o:relacoes.c relacoes.h operacoes.h
	gcc -Wall -c relacoes.c
mensagens.o:mensagens.c mensagens.h operacoes.h
	gcc -Wall -c mensagens.c
main.o:main.c operacoes.h  relacoes.h mensagens.h
	gcc -Wall -c main.c
clean:
	rm *.o
