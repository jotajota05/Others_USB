# Compilar todos los programas
all : c_tiempo s_tiempo

# Compilar sock_utils
sock_utils : 
		gcc  sock_utils.c	

# Compilar leer
leer :
		gcc leer.c		

# Compilar marzullo
marzullo : 
		gcc  marzullo.c	

# Compilar s_tiempo
s_tiempo : 	s_tiempo.c sock_utils.o 
		gcc -lpthread -g s_tiempo.c -o s_tiempo sock_utils.o

# Compilar c_tiempo
c_tiempo : 	c_tiempo.c sock_utils.o marzullo.o leer.o
		gcc -lpthread -g c_tiempo.c -o c_tiempo sock_utils.o marzullo.o leer.o


