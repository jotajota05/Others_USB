all : cliente servidor

servidor: 	servidor.c
			gcc servidor.c -o servidor
			
cliente: cliente.o
	gcc -lncurses cliente.o -o cliente

cliente.o: cliente.c cliente.h
	gcc -c cliente.c
