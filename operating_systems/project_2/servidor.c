/*		servidor.c
 *		"CHAT" Proyecto 2 Sistemas de Operacion I CI-3825
 * 
 *      Copyright 2008 	
 * 		Juan J Garcia 05-38207
 * 		
 */
 
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>

struct cliente {
   char nombre[21], estado[30];
   int fdRead, fdWrite, posicion;
};

//DECLARACION DE VARIABLES
char *pathServidor, *mensaje, *lectura;
struct cliente listaClientes[100],conversa[100][2];
int fdServ, clientes, i, pipePorLeer;
fd_set pipesLectura, pipesEscritura;
struct timeval tiempo;

//FUNCION QUE LEE UNA LINEA DEL PIPE, RETORNA 0 SI SE LEE UNA LINEA NULL
//Y RETORNA 1 EN CASO DE QUE LA LECTURA SEA SATISFACTORIA
readLine(int fd, char *str) {
   int n;
   do {
      n = read(fd, str, 1);
   }
   while(n > 0 && &(*str++) != NULL);

   return(n > 0);
}

//FUNCION QUE ESCRIBE UNA LINEA EN EL PIPE
writeLine(int fd, char *str) {
   int n;
   do {
      n = write(fd, str, 1);
   }
   while(n > 0 && &(*str++) != NULL);
}

struct cliente *findCliente(char *nombre,int fdRead,int fdWrite) {
   int i;
   for (i = 0 ; i < 100 ; i++) {
      if (strcmp(nombre,listaClientes[i].nombre) == 0 || 
          listaClientes[i].fdRead == fdRead || listaClientes[i].fdWrite == fdWrite)
         return &listaClientes[i];
      else return NULL;
   }
};

/* """NOTA""": El orden en que los clientes escriben en el pipe de conexion es,
 * primero el nombre, luego el pipe de escritura del cliente (lectura 
 * del servidor) y por ultimo el pipe de lectura del cliente (escritura
 * del servidor)
 */

int main(int argc, char* arg[])
{
   //SE CREA EL PIPE DE CONEXIONES NUEVAS
   pathServidor = malloc(100);
   mensaje = malloc(1000);
   lectura = malloc(1000);
   if (arg[1] == NULL) strcat(pathServidor,"/tmp/servidor05-38207");
   else strcat(pathServidor,arg[1]);
   unlink(pathServidor);
   mknod(pathServidor,S_IFIFO,0);
   fdServ = open(pathServidor,O_RDONLY); 

   //EMPIEZA EL CICLO DE TRABAJO DEL SERVIDOR
   FD_ZERO(&pipesLectura);
   FD_ZERO(&pipesEscritura);
   clientes = 0;
   tiempo.tv_sec = 0;
   tiempo.tv_usec = 1000;
   while (1) {
      
      //SE HACE SELECT DE LOS DESCRIPTORES DE ENTRADA
      if (select(fdServ + 1,&pipesLectura,NULL,NULL,&tiempo) == -1) {
         perror("select");
         exit(1);
      }
      for ( i = 0 ; i <= fdServ ; i++) {
         if (FD_ISSET(i,&pipesLectura)) {
            while (readLine(i,mensaje)) {
               if (*strchr(mensaje,"-quien") == *mensaje) {
      
               } else if (*strchr(mensaje,"-escribir") == *mensaje) {
                     conversa[(*findCliente(NULL,i,-1)).posicion][0] = *findCliente(NULL,i,-1);
                     conversa[(*findCliente(NULL,i,-1)).posicion][1] = *findCliente(strchr(mensaje," "),-1,-1);
               } else if (*strchr(mensaje,"-estoy") == *mensaje) {
                  *(*findCliente(NULL,i,-1)).estado = *strchr(mensaje," ");
               } else if (*strchr(mensaje,"-enviar") == *mensaje) {
                  
               } else if (*strchr(mensaje,"-salir") == *mensaje) {
                  if (FD_ISSET((*findCliente(NULL,i,-1)).fdRead,&pipesLectura))
                     FD_CLR((*findCliente(NULL,i,-1)).fdRead,&pipesLectura);
                  if (FD_ISSET((*findCliente(NULL,i,-1)).fdWrite,&pipesEscritura))
                     FD_CLR((*findCliente(NULL,i,-1)).fdWrite,&pipesEscritura);
                  close((*findCliente(NULL,i,-1)).fdRead);
                  close((*findCliente(NULL,i,-1)).fdWrite);
                  listaClientes[(*findCliente(NULL,i,-1)).posicion] = listaClientes[clientes];
               } else {
                  
               }
            }
         }
      }
      
      //SE VERIFICA SI HAY NUEVAS CONEXIONES Y LAS AGREGA EN LA LISTA DE PIPES DE CLIENTES
      pipePorLeer = 0;
      while (1) {
         if (pipePorLeer == 0) clientes++;
         if (pipePorLeer >= 3) {
            pipePorLeer = 0;
            continue;
         }
         if (readLine(fdServ,lectura)) {
            printf("%s\n",lectura);
            if (pipePorLeer == 0) {
               strcat(listaClientes[clientes].nombre,lectura);
               listaClientes[clientes].posicion = clientes;
            } else if (pipePorLeer == 1) {
               listaClientes[clientes].fdRead = open(lectura,O_RDONLY);
               FD_SET(listaClientes[clientes].fdRead,&pipesLectura);
            } else if (pipePorLeer == 2) {
               listaClientes[clientes].fdWrite = open(lectura,O_WRONLY);
               FD_SET(listaClientes[clientes].fdWrite,&pipesEscritura);
            }
            pipePorLeer++;
         }
         else {
            clientes--;
            break;
         }
      }
   }
   close(fdServ);
   exit(0);
}
