#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netdb.h>
#include <ctype.h>

#include "sock_utils.h"
#include "marzullo2.h"

int main (int argc, char *argv[]) {

  struct sockaddr_in direccion, servidor, emisor;
  struct in_addr direccion_host;
  struct hostent *host;
  socklen_t longDireccion = sizeof(struct sockaddr_in);
  int sock, longt, n, longt_emisor, conexion, tiempo_tcp, tiempo_udp, j, k, puerto, num_preg, opcion_ene, c, a;
  char buffer[256], *protocolo, *serv, subStr[2];
  int it;
  int i;
  int tj,desface,primera,ultima;
  int hora;
  struct Par * par = malloc(sizeof(struct Par));
  char *prim = malloc(256);
  char *inter = malloc(256);

  //Se revisa que los parametros esten completos
  if (argc != 8 && argc != 9) error("Parametros incompletos o incorrectos");

  opterr = 0;
  opcion_ene = 0;
     
  //El siguiente codigo administra los parametros y los almacena en variables
  while ((c = getopt (argc, argv, "s:p:v:tun")) != -1)
    switch (c) {
    case 's':
      substring(0,1,optarg,subStr,sizeof(subStr));
      if (!strcmp(subStr,"-")) error("Ingrese el Nombre o direccion del servidor luego de -s");
      serv = optarg;
      break;
    case 'p':
      substring(0,1,optarg,subStr,sizeof(subStr));
      if (!strcmp(subStr,"-")) error("Ingrese el numero de puerto luego de -p");
      puerto = atoi(optarg);
      break;
    case 'v':
      substring(0,1,optarg,subStr,sizeof(subStr));
      if (!strcmp(subStr,"-")) error("Ingrese el numero de preguntas luego de -v");
      num_preg = atoi(optarg);
      break;
    case 't':
      protocolo = "-t";
      break;
    case 'u':
      protocolo = "-u";
      break;
    case 'n':
      opcion_ene = 1;
      break;
    case '?':
      error("Opcion invalida");
      break;
    default:
      abort();
      break;
    }

  //Se declara la lista en donde se guardaran las intervalos para Marzullo
  struct Intervalos* lista = malloc(num_preg*2*sizeof(struct Intervalos));

  ////////////////////////////////////////////////////////////
  //////////////Se realiza la conexion por TCP////////////////
  ///////////////////////////////////////////////////////////

  if (!strcmp(protocolo,"-t")) {
      
    //Se intenta convertir el argumento en una direccion, para luego buscar el host, si no, se busca por nombre
    if (inet_aton(serv, &direccion_host))
      host = gethostbyaddr((char *)&direccion_host, sizeof(direccion_host), AF_INET);
    else
      host = gethostbyname(serv);

    if (!host) {
      herror("Error al buscar el Host");
      exit(1);
    }
	
    //Se crea el socket de comunicacion
    if(( sock = socket(PF_INET, SOCK_STREAM, 0)) < 0) error("Error al crear el Socket");
    
    direccion.sin_family = AF_INET;
    direccion.sin_port = htons(puerto);
    
    //Se Toma la primera direccion IP asociada a este hostname
    memcpy(&direccion.sin_addr, host->h_addr_list[0], sizeof(direccion.sin_addr));

    //Se conecta al servidor mediante el socket creado
    conexion = connect(sock, (struct sockaddr *)&direccion, sizeof(direccion));
    if (conexion < 0) error("Error al conectar con el socket");

    ////////////////////////////////////
    //////Aqui se hace la peticion//////
    {
      ////Aca empieza marzullo////
      it = num_preg;
      i = 0;
      a = 0;

      //En cada peticion se van guardando los valores, antes y despues de la peticion
      for(i= 0; i < it ; i++) {
	if (i==0) primera = time(NULL);  	
	lista[a].offset  = time(NULL);
	lista[a].type = -1;

	{
	  //Se realizan las peticiones
	  bzero(buffer,256);
	  send(sock,"Dame la hora!", 256,0);
	  recv(sock,buffer,256,0);
	  printf("Tiempo = %f\n",atof(buffer));

	}
	a++;
	lista[a].offset = time(NULL);
	if ( i == it-1) ultima = lista[a].offset;
	lista[a].type = 1;

	//Comienza la Normalizacion
	desface = (primera-lista[a-1].offset);
	tj = lista[a].offset - desface;
	lista[a-1].offset = atof(buffer) +(tj-primera)/2;
	lista[a].offset = atof(buffer) -(tj-primera)/2;
	a++;
      }     
      
      //Aqui llamamos la funcion de MArzullo
      par = Marzullo(it,lista);
      printf("El intervalo es: %d - %d\n", par->a , par->b);
      hora = (ultima-primera) + ((par->b - par->a)/2) + par->a;
      
      //Dependiendo de la opcion n, se elige la accion a tomar
      if (opcion_ene) {
	strcat(prim,"date --date='@");
      } else {	
	strcat(prim,"date --set='@");
      }
      sprintf(inter,"%i",hora);
      strcat(prim,inter);
      strcat(prim,"'");
      system(prim);

    }	

    //Se cierra el socket
    close(sock);

    ///////////////////////////////////

    ////////////////////////////////////////////////////////////
    //////////////Se realiza la conexion por UDP////////////////
    ///////////////////////////////////////////////////////////


  } else if (!strcmp(protocolo,"-u")) {

    //Se crea el socket de comunicacion
    sock = socket(AF_INET,SOCK_DGRAM,0);
    if (sock < 0) error("Error al crear el socket!");

    servidor.sin_family = AF_INET;

    //Se obtiene el nombre del host o la direccion
    host = gethostbyname(serv);
    if (host == 0) error("Error! Host desconocido"); 

    bcopy((char *)host->h_addr,(char *)&servidor.sin_addr,host->h_length);

    servidor.sin_port = htons(puerto);
    longt = sizeof(struct sockaddr_in);
      
    //////////////////////////////////////////////////////////
    //////Aqui se hace la peticion con sendto y recvfrom//////
    {
      ////Aca empieza marzullo////
      it = num_preg;
      
      i = 0;
      a = 0;
  
      for(i= 0; i < it ; i++){
	if (i==0) primera = time(NULL);  	
	lista[a].offset  = time(NULL);
	lista[a].type = -1;

	{	
	  //Se inician las peticiones
	  bzero(buffer,256);
	  n=sendto(sock,"Dame la hora!", 256,0,(struct sockaddr *)&servidor,longt);
	  if (n < 0) error("Sendto");
	  n = recvfrom(sock,buffer,256,0,(struct sockaddr *)&emisor, &longt);
	  if (n < 0) error("recvfrom");
	  printf("Tiempo = %f\n",atof(buffer));

	}
	a = a+1;
	lista[a].offset  = time(NULL);
	if ( i == it-1) ultima = lista[a].offset;
	lista[a].type = 1;

	//Normalizando//
	desface = (primera-lista[a-1].offset);
	tj = lista[a].offset - desface;
	lista[a-1].offset = atof(buffer) -(tj-primera)/2;
	lista[a].offset = atof(buffer)+(tj-primera)/2;
	a= a+1;
      }
      //Se llama la funcion de Marzullo
      par = Marzullo(it,lista);

      printf("El intervalo es: %d - %d\n", par->a , par->b);
      hora = (ultima-primera) + ((par->b - par->a)/2) + par->a;
      
      //Dependiendo de la opcion n, se toma la accion respectiva
      if (opcion_ene) {
	strcat(prim,"date --date='@");
      } else {	
	strcat(prim,"date --set='@");
      }
      sprintf(inter,"%i",hora);
      strcat(prim,inter);
      strcat(prim,"'");
      system(prim);
    }

    //Se cierra el socket
    close(sock);

    /////////////////////////////////////////////////////

  }

  return 0;

}
