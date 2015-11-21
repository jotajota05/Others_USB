/*
Proyecto 2 Redes de Computadores I
Servidores Concurrentes  TCP (Procesos) y UDP (Hilos de Ejecucion)

Grupo 11
Jessica Perez 05-38724
Juan Garcia 05-38207
*/

//Librerias necesarias para el funcionamiento del Servidor
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <ctype.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h> 
#include <pthread.h>

//Librerias implementadas para el funcionamiento del Servidor
#include "sock_utils.h"

/* Tipo de dato para los hilos usados en el servidor con protocolo UDP */
/* Contiene todas las variables necesarias por los hilos para ejecutar  */
/* la funcion de envio de paquetes */
typedef struct {
  int sock, longt_emisor;
  char *buf, *calidad;
  struct sockaddr_in emisor;
} infoThread;

/* Funcion que toma los parametros de la entrada de comandos y los almacena en variables. */
/* Recibe el arreglo de paramtros del main, el tamano del mismo, y las variables */
/* Puerto, calidad y protocolo */ 
void tomarParametros(int argc,char *argv[],int *puerto,char **calidad,char **protocolo) {
  int c;
  char subStr[2];

  //Se verifica la cantidad de parametros
  if (argc != 6) error("Parametros incompletos o incorrectos");

  opterr = 0;
     
  //El siguiente codigo administra los parametros y los almacena en variables
  while ((c = getopt (argc, argv, "p:c:tu")) != -1)
    switch (c) {
    case 'p':
      substring(0,1,optarg,subStr,sizeof(subStr));
      if (!strcmp(subStr,"-")) error("Ingrese el numero de puerto luego de -p");
      *puerto = atoi(optarg);
      break;
    case 'c':
      substring(0,1,optarg,subStr,sizeof(subStr));
      if (!strcmp(subStr,"-")) error("Ingrese el Nombre o direccion del servidor luego de -s");
      *calidad = optarg;
      break;
    case 't':
      *protocolo = "-t";
      break;
    case 'u':
      *protocolo = "-u";
      break;
    case '?':
      error("Opcion invalida");
      break;
    default:
      abort();
      break;
    }
}

//Funcion para matar los procesos hijos que quedan zombies al finalizar su tarea en el servidor TCP
void matarZombies() { 
  while (waitpid(-1, NULL, WNOHANG) > 0); 
} 

/* Funcion que ejecutan los hilos creados en el servidor UDP */
/* Recibe la estructura que contiene todas las variables necesarias */
/* para que el hijo ejecute el envio de paquetes al cliente */
void *sendUDP(void *data) {
  infoThread *th;
  th = (infoThread *)data;
  infoThread t = *th;
  double tiempo = time(NULL);
  sprintf(t.buf,"%d%f",(atoi(t.calidad) - 1),tiempo);
  int n = sendto(t.sock,t.buf,256,0,(struct sockaddr *)&(t.emisor),sizeof(struct sockaddr_in));
  if (n < 0) error("Al hacer sendto en hilo UDP");
  printf("Peticion Otorgada = %s\n",t.buf);
  printf("Calidad Otorgada = %s\n",t.calidad);
  pthread_exit(0);
}

/* Funcion Principal del programa */
int main (int argc, char *argv[]) {

  //Declaracion de las variables del servidor
  struct sockaddr_in direccion, servidor, emisor;
  infoThread *structThread = (infoThread *)malloc(sizeof(infoThread));
  socklen_t longDireccion = sizeof(struct sockaddr_in);
  pid_t pidHijoServ;
  char *protocolo, buf[1024], subStr[2], *calidad;
  int  i, c, puerto, sock, longt, longt_emisor, conexion, countProc, status, fdThread;  
  double tiempo;
  pthread_t threadUDP;

  //Se toman los parametros de entrada y se almacenan en variables
  tomarParametros(argc,argv,&puerto,&calidad,&protocolo);

  ////////////////////////////////////////////////////////////
  //////////////Se realiza la conexion por TCP////////////////
  ///////////////////////////////////////////////////////////

  if (!strcmp(protocolo,"-t")) {
 
    //Se crea el socket de comunicacion entre el servidor y el cliente
    if ((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0) error("Al crear Socket -  TCP");
    
    //Se establecen los campos de direccion del socket, el dominio y el puerto.
    direccion.sin_family = AF_INET;
    direccion.sin_port = htons(puerto);
    memset(&direccion.sin_addr, 0, sizeof(direccion.sin_addr));

    //Se asocia el socket al puerto bien conocido del servidor
    if (bind(sock, (struct sockaddr *)&direccion, longDireccion)) error("Al asociar la direccion al Socket - TCP");

    //El servidor empieza a escuchar por llamadas desde un emisor
    while (listen(sock, 5) >= 0) {
      
      //Se procede a matar cualquier proceso zombie existente
      signal(SIGCHLD, matarZombies);
      
      //Comienzan a recibirse las solicitudes del emisor, y se procede a aceptar la conexion
      if ((conexion = accept(sock, (struct sockaddr *) &direccion, &longDireccion)) >= 0) {

	//////////////////////////////////////
	//////Aqui se maneja la peticion//////

	//Creamos el proceso hijo para que maneje la peticion
	switch (fork()) {
	case -1 :       //En caso de error al crear el hijo

	  error("Al crear el proceso para atender la Peticion");

	case 0:        //Codigo que ejecutara el hijo

	  bzero(buf,256);
	  
	  while (recv(conexion,buf,1024,0)) {    //Mientras se reciban datos en el socket se aceptan peticiones
	    printf("Peticion Recibida - TCP: %s\n",buf);
	    tiempo = time(NULL);
	    sprintf(buf,"%f",tiempo);
	    
	    send(conexion,buf,256,0);     //Se envia la hora al cliente
	    printf("Peticion Otorgada = %s\n",buf);
	    
	    send(conexion,calidad,256,0);   //Se envia la calidad del servidor al cliente
	    printf("Calidad Otorgada = %s\n",calidad);
	    bzero(buf,256);
	  }
	  exit(0);

	default:    //Codigo que ejecuta el Padre
	  continue;
	}
	
	///////////////////////////////////
      
      } else error("No se pudo aceptar la Conexion");        
    
    }
    
    ////////////////////////////////////////////////////////////
    //////////////Se realiza la conexion por UDP////////////////
    ///////////////////////////////////////////////////////////
    
  } else if (!strcmp(protocolo,"-u")) {

    //Se crea el socket de comunicacion
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) error("Error al crear el socket!");

    longt = sizeof(servidor);
    bzero(&servidor,longt);

    //Inicializamos las variables de la estructura del servidor, el dominio, la direccion y el puerto
    servidor.sin_family = AF_INET;
    servidor.sin_addr.s_addr = INADDR_ANY;
    servidor.sin_port = htons(puerto);

    //Establecemos la conexion con el puerto conocido, para comenzar la conexion
    if (bind(sock,(struct sockaddr *)&servidor,longt) < 0) error("Al hacer binding");

    longt_emisor = sizeof(struct sockaddr_in);

    int count = 0;
    
    //Se inicia el ciclo para escuchar peticiones
    while (1) {
 
      ///////////////////////////////////////////////////
      //////Aqui se responde la peticion con sendto//////

      //Se escucha una peticion del cliente
      recvfrom(sock,buf,1024,0,(struct sockaddr *)&emisor,&longt_emisor);
      
      //Se procede a inicializar las variables de la estructura
      //que contiene la informacion para la ejecucion del hilo
      structThread->sock = sock;   //El socket de comunicacion
      structThread->longt_emisor = longt_emisor;    //La longitud del emisor
      structThread->calidad = calidad;    //La calidad del servidor
      structThread->emisor.sin_family = emisor.sin_family;   //El dominio del servidor
      structThread->emisor.sin_addr.s_addr = emisor.sin_addr.s_addr;   //Las direcciones del servidor
      structThread->emisor.sin_port = emisor.sin_port;   //El puerto de comunicacion
      *structThread->emisor.sin_zero = *emisor.sin_zero;
      structThread->buf = buf;   //El bufer de comunicacion

      //Se recibio la peticion y se procede a crear el hilo de ejecucion
      //para enviar los paquetes de respuesta.
      printf("Peticion Recibida - UDP: %s\n",buf);
      fdThread = pthread_create(&threadUDP,NULL,sendUDP,(void *)structThread);
  
      /////////////////////////////////////////////////

    }

  }
  
  //Se cierra la conexion del Socket
  close(sock);

  return 0;

}
