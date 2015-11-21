# Compilar todos los programas
all : c_tiempo s_tiempo

# Compilar sock_utils
sock_utils : 
		gcc  sock_utils.c	

# Compilar marzullo
marzullo2 : 
		gcc  marzullo2.c	
			
# Compilar s_tiempo
s_tiempo : 	s_tiempo.c sock_utils.o 
		gcc -g s_tiempo.c -o s_tiempo sock_utils.o

# Compilar c_tiempo
c_tiempo : 	c_tiempo.c sock_utils.o marzullo2.o
		gcc -g c_tiempo.c -o c_tiempo sock_utils.o marzullo2.o


