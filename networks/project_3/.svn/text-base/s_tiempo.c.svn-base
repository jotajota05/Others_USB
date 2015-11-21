/*
  Proyecto 3 Redes de Computadores I
  Cliente - Servidor con RPC

  Grupo 11
  Jessica Perez 05-38724
  Juan Garcia 05-38207
*/

#include "tiempo.h"
#include <stdio.h>
#include <stdlib.h>
#include <rpc/pmap_clnt.h>
#include <string.h>
#include <memory.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "sock_utils.h"

#ifndef SIG_PF
#define SIG_PF void(*)(int)
#endif

static void
programa_tiempo_1(struct svc_req *rqstp, register SVCXPRT *transp)
{
	union {
		int fill;
	} argument;
	char *result;
	xdrproc_t _xdr_argument, _xdr_result;
	char *(*local)(char *, struct svc_req *);

	switch (rqstp->rq_proc) {
	case NULLPROC:
		(void) svc_sendreply (transp, (xdrproc_t) xdr_void, (char *)NULL);
		return;

	case peticion_hora:
		_xdr_argument = (xdrproc_t) xdr_void;
		_xdr_result = (xdrproc_t) xdr_double;
		local = (char *(*)(char *, struct svc_req *)) peticion_hora_1_svc;
		break;

	case peticion_calidad:
		_xdr_argument = (xdrproc_t) xdr_void;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) peticion_calidad_1_svc;
		break;

	default:
		svcerr_noproc (transp);
		return;
	}
	memset ((char *)&argument, 0, sizeof (argument));
	if (!svc_getargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		svcerr_decode (transp);
		return;
	}
	result = (*local)((char *)&argument, rqstp);
	if (result != NULL && !svc_sendreply(transp, (xdrproc_t) _xdr_result, result)) {
		svcerr_systemerr (transp);
	}
	if (!svc_freeargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		fprintf (stderr, "%s", "unable to free arguments");
		exit (1);
	}
	return;
}

//Funcion que recibe los parametros para el programa
void tomarParametros(int argc,char *argv[],int *calidad) {
  int c;
  char subStr[2];
  //Se revisa que los parametros esten completos
  if (argc != 3) error("Parametros incompletos o incorrectos");

  opterr = 0;
     
  //El siguiente codigo administra los parametros y los almacena en variables
  while ((c = getopt (argc, argv, "c:")) != -1)
    switch (c) {
    case 'c':
      substring(0,1,optarg,subStr,sizeof(subStr));
      if (!strcmp(subStr,"-")) error("Ingrese la calidad luego de -c");
      *calidad = atoi(optarg);
      break;
    case '?':
      error("Opcion invalida");
      break;
    default:
      abort();
      break;
    }
}

int main (int argc, char **argv) {
	register SVCXPRT *transp;
	int calidad;
	FILE *fd;

	//Se toman los parametros de la linea de comandos
	tomarParametros(argc,argv,&calidad);

	//Se escribe la calidad en un archivo para pasarsela a las funciones remotas
	fd = fopen("calidad","w");
	fprintf(fd,"%d",calidad);
	fclose(fd);

	//Inicia la espera por peticiones
	printf("Calidad del servidor = %d\n",calidad);
	printf("Recibiendo Peticiones...\n");

	pmap_unset (PROGRAMA_TIEMPO, VERSION_TIEMPO);

	transp = svcudp_create(RPC_ANYSOCK);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create udp service.");
		exit(1);
	}
	if (!svc_register(transp, PROGRAMA_TIEMPO, VERSION_TIEMPO, programa_tiempo_1, IPPROTO_UDP)) {
		fprintf (stderr, "%s", "unable to register (PROGRAMA_TIEMPO, VERSION_TIEMPO, udp).");
		exit(1);
	}

	transp = svctcp_create(RPC_ANYSOCK, 0, 0);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create tcp service.");
		exit(1);
	}
	if (!svc_register(transp, PROGRAMA_TIEMPO, VERSION_TIEMPO, programa_tiempo_1, IPPROTO_TCP)) {
		fprintf (stderr, "%s", "unable to register (PROGRAMA_TIEMPO, VERSION_TIEMPO, tcp).");
		exit(1);
	}

	svc_run ();
	fprintf (stderr, "%s", "svc_run returned");
	exit (1);
	/* NOTREACHED */
}
