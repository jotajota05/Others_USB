#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "sock_utils.h"

int main (int argc, char *argv[]) {
  
  struct sockaddr_in direccion, servidor, emisor;
  int sock, longt, longt_emisor, i, n, param, conexion;
  socklen_t longDireccion = sizeof(struct sockaddr_in);
  char *primer_char = "";
  char *protocolo;
  char buf[1024];
  int puerto; 
  double tiempo;

  if (argc != 4) error("Parametros incompletos o incorrectos");

  for (i = 1; i < argc ; i++) {
    if (!strcmp(argv[i],"-p")) {
      if ((i == argc-1) || !strcmp(argv[i+1],"-t") || !strcmp(argv[i+1],"-u")) error("Ingrese el Numero de Puerto luego de -p!");
      else puerto = atoi(argv[i+1]);
    }
    else if (!strcmp(argv[i],"-t") || !strcmp(argv[i],"-u")) protocolo = argv[i];
   
  }
  
  ////////////////////////////////////////////////////////////
  //////////////Se realiza la conexion por TCP////////////////
  ///////////////////////////////////////////////////////////

  if (!strcmp(protocolo,"-t")) {
 
    //Se realiza la conexion por TCP
    if ((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0) error("Error al crear Socket con TCP");
    
    //Se establecen los campos de la direccion del socket
    direccion.sin_family = AF_INET;
    direccion.sin_port = htons(puerto);
    memset(&direccion.sin_addr, 0, sizeof(direccion.sin_addr));

    //Se asocia el socket a la direccion
    if (bind(sock, (struct sockaddr *)&direccion, longDireccion)) error("Error al asociar la direccion al socket");

    //El servidor empieza a escuchar por llamadas desde un emisor
    while (listen(sock, 5) >= 0) {

      //Comienzan a recibirse las solicitudes del emisor, y de proceden a aceptar
      conexion = accept(sock, (struct sockaddr *) &direccion, &longDireccion);

	//////////////////////////////////////
	//////Aqui se maneja la peticion//////
	{

	  bzero(buf,256);
	  while (recv(conexion,buf,1024,0)) {
	    printf("Peticion Recibida - TCP: %s\n",buf);
	    tiempo = time(NULL);
	    sprintf(buf,"%f",tiempo);
	    send(conexion,buf,256,0);
	    printf("Peticion Otorgada!\n");
	    bzero(buf,256);
	  }

	}    
	///////////////////////////////////
               
    
      ////////////////////////////////////////////////////////////
      //////////////Se realiza la conexion por UDP////////////////
      ///////////////////////////////////////////////////////////
    
    }
  } else if (!strcmp(protocolo,"-u")) {
    
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) error("Error al crear el socket!");
    longt = sizeof(servidor);
    bzero(&servidor,longt);

    //Inicializamos las variables de la estructura del servidor
    servidor.sin_family = AF_INET;
    servidor.sin_addr.s_addr = INADDR_ANY;
    servidor.sin_port = htons(puerto);

    //Establecemos el puerto para permitir la conexion de peticiones
    if (bind(sock,(struct sockaddr *)&servidor,longt) < 0) error("Error al hacer binding");

    longt_emisor = sizeof(struct sockaddr_in);

    //Se inicia el ciclo para escuchar peticiones
    while (1) {
 
      ///////////////////////////////////////////////////
      //////Aqui se responde la peticion con sendto//////
      {

	n = recvfrom(sock,buf,1024,0,(struct sockaddr *)&emisor,&longt_emisor);
	if (n < 0) error("recvfrom");
	printf("Peticion Recibida - UDP: %s\n",buf);
	tiempo = time(NULL);
	sprintf(buf,"%f",tiempo);
	n = sendto(sock,buf,256,
		   0,(struct sockaddr *)&emisor,longt_emisor);
	if (n  < 0) error("sendto");
	printf("Peticion Otorgada!\n");

      }
      /////////////////////////////////////////////////

    }
    
  }

  //Se cierra la conexion del Socket
  close(sock);

  return 0;

}
