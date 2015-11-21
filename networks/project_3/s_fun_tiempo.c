/*
  Proyecto 3 Redes de Computadores I
  Cliente - Servidor con RPC

  Grupo 11
  Jessica Perez 05-38724
  Juan Garcia 05-38207
*/

#include "tiempo.h"

//Funcion que entrega la hora al cliente
double *
peticion_hora_1_svc(void *argp, struct svc_req *rqstp)
{
	static double  result;

	//Se efectua la llamada al tiempo
	result = time(NULL);

	return &result;
}

//Funcion que entrega la calidad del servidor al cleinte
int *
peticion_calidad_1_svc(void *argp, struct svc_req *rqstp)
{
	static int  result;

	FILE *fd;

	//Se lee la calidad del archivo
	fd = fopen("calidad","r");
	fscanf(fd,"%d",&result);
	fclose(fd);

	return &result;
}
