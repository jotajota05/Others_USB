/*		cliente.c
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
#include <ncurses.h>

#define ALTO 5 // Alto de la ventana 2
#define LINES_MIN 10 // Alto m�nimo que debe tener el terminal
#define COLS_MIN 25 // Ancho m�nimo que debe tener el terminal
#define TECLA_RETURN 0xD
#define TAM 2048 // Tama�o de buffer

struct cliente {
   char nombre[21], estado[30];
   int fdRead, fdWrite;
};

//DECLARACION DE VARIABLES
char *pathServidor, *pathEntrada, *pathSalida, *mensaje, *escritura;
int fdServ, i;
struct cliente usuario;
WINDOW *ventana1, *ventana2;

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

/* Mueve el cursor al punto de inserci�n actual de la ventana 2. */
void enfocarVentana2() {
    int y, x;
    getyx(ventana2, y, x);
    wmove(ventana2, y, x);
    wrefresh(ventana2);
}

/* Borra el contenido de la ventana 2 y ubica el cursor en la esquina 
 * superior izquierda de esta ventana.
 */
void limpiarVentana2() {
    wclear(ventana2);
    mvwhline(ventana2, 0, 0, 0, 20); // Dibujar la l�nea horizontal
    wmove(ventana2, 1, 0);
    wrefresh(ventana2);
}

int main(int argc, char* arg[])
{
   //SE ABRE EL PIPE DE CONEXIONES NUEVAS
   pathServidor = malloc(100);
   mensaje = malloc(1000);
   if (strcmp(arg[1],"-p") == 0) strcat(pathServidor,arg[1]);
   else strcat(pathServidor,"/tmp/servidor05-38207");
   fdServ = open(pathServidor,O_WRONLY);
   
   //SE CREAN LOS DOS PIPES DEL CLIENTE Y SE ABREN
   pathEntrada = malloc(100);
   pathSalida = malloc(100);
   strcat(pathEntrada,"pipeEntrada");
   strcat(pathSalida,"pipeSalida");
   if (strcmp(arg[1],"-p") == 0) {
      strcat(pathEntrada,arg[3]);
      strcat(pathSalida,arg[3]);
      strcat(usuario.nombre,arg[3]);
   } else {
      strcat(pathEntrada,arg[1]);
      strcat(pathSalida,arg[1]);
      strcat(usuario.nombre,arg[1]);
   }
   usuario.fdRead = open(pathEntrada,S_IFIFO,0);
   usuario.fdWrite = open(pathSalida,S_IFIFO,0);
   
   //SE ESCRIBE LA INFORMACION DEL CLIENTE EN EL PIPE DE CONEXIONES NUEVAS
   escritura = malloc(100);
   for (i = 0 ; i < 3 ; i++) {
      switch (i) {
         case 0: writeLine(fdServ,usuario.nombre);break;
         case 1: writeLine(fdServ,pathSalida);break;
         case 2: writeLine(fdServ,pathEntrada);break;
      }
   }
   
   //SE INICIA EL PROCESO CON LAS VENTANAS
   if (LINES < LINES_MIN || COLS < COLS_MIN) {
        endwin(); // Restaurar la operaci�n del terminal a modo normal
        printf("El terminal es muy peque�o para correr este programa.\n");
        exit(0);
    }
   
   int alto1 = LINES - ALTO; // Alto de la ventana 1
    ventana1 = newwin(alto1, 0, 0, 0); // Crear la ventana 1
    ventana2 = newwin(ALTO, 0, alto1, 0); // Crear la ventana 2
    scrollok(ventana1, TRUE); //Activar el corrimiento autom�tico en la ventana 1
    scrollok(ventana2, TRUE);
    limpiarVentana2(); // Dibujar la l�nea horizontal
    
    while(1) {
        char buffer[TAM];
        wgetnstr(ventana2, buffer, TAM); // Leer una l�nea de la entrada
        if (strcmp(buffer, "-salir") == 0) {
            break;
        }
        wprintw(ventana1, "usuario: %s\n", buffer);
        wrefresh(ventana1);
        limpiarVentana2();
    }
   
   exit(0);
}

/**
* uid_t uid = getuid();
struct passwd* usuario = getpwuid(uid);
n_usuario = usuario -> pw_name;
* */
