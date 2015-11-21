/*
  Proyecto 3 Redes de Computadores I
  Cliente - Servidor con RPC

  Grupo 11
  Jessica Perez 05-38724
  Juan Garcia 05-38207
*/

//Librerias necesarias
#include <pthread.h>
#include <semaphore.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

//Librerias propias incluidad
#include "lista_dinamica.h"
#include "tiempo.h"
#include "leer.h"
#include "sock_utils.h"
#include "marzullo.h"


//Semaforo para la region critica
sem_t sem;

//Estructura que guarda la informacion del Hilo
typedef struct {
  int num_preg, hilo, *no_resp;
  struct Linter *lista, *prom;
  CLIENT *clnt;
} infoHilo;

//Funcion que ejecuta cada hilo
void *programa_tiempo_1(void *data) {
  infoHilo *th;
  th = (infoHilo *)data;
  infoHilo t = *th;
  double  *tiempo, inicio, fin, principio, final;
  char *peticion_hora_1_arg;
  int  *result_2, i;
  char *peticion_calidad_1_arg;
  int *calidad,desface;
  double primera;
  double ultima;
  int a = 0;

  for (i = 0; i < t.num_preg ; i++) {

    if (i==0) primera = time(NULL);

    //Se entra en una region critica, en la que el hilo de ejecucion agrega un elemento a la lista de intervalos
    if (sem_wait(&(sem)) < 0) error("Fallo el sem_wait\n");
    inicio = time(NULL);
    principio = time(NULL);
    add(time(NULL),-1,t.lista);
    if (sem_post(&(sem)) < 0) error("Fallo el sem_post\n");

    //Se realiza la peticion del tiempo
    tiempo = peticion_hora_1((void*)&peticion_hora_1_arg, t.clnt);
    if (tiempo == (double *) NULL) {
      clnt_perror (t.clnt, "call failed");
    }
    if (tiempo == 0) (*t.no_resp)++;
 
    //Se realiza la peticion de la calidad
    calidad = peticion_calidad_1((void*)&peticion_calidad_1_arg, t.clnt);
    if (calidad == (int *) NULL) {
      clnt_perror (t.clnt, "call failed");
    }

    //Se agrega el tiempo final a la lista
    if (sem_wait(&(sem)) < 0) error("Fallo el sem_wait");
    final = time(NULL);
    add(time(NULL),1,t.lista);
    fin = time(NULL);
    add(fin - inicio,0,t.prom);

    if ( i == t.num_preg-1) ultima = t.lista->cola->offset;
  
    //Comienza a aplicarse la Normalizacion
    desface = (primera-t.lista->cola->ant->offset);
    int tj = t.lista->cola->offset - desface;
    t.lista->cola->ant->offset = *tiempo +(tj-primera)/2;
    t.lista->cola->offset = *tiempo - (tj-primera)/2;
  
    double abre = t.lista->cola->ant->offset;
    double cierra = t.lista->cola->offset;
    //agregar extras por calidad
    for(a=0;a<(*calidad)-1;a++){
      add(abre,-1,t.lista);  
      add(cierra,1,t.lista);
    }

    if (sem_post(&(sem)) < 0) error("Fallo el sem_post");

  }

#ifndef	DEBUG
  clnt_destroy (t.clnt);
#endif	 /* DEBUG */

  //Termina la ejecucion del hilo
  //pthread_exit(0);

}

//Calcula el promedio de los tamanos de los intervalos de las paticiones
double promedioInter(struct Linter* l) {
  double prom = 0;
  struct Intervalo *e;
  e = l->cab;
  while( e != NULL ){
    prom = prom + (e -> offset / l -> cant_elem);
    if( e->sig != NULL ) e = e->sig; else break;
  }
  return prom;
}


//Funcion que recibe los parametros para el programa
void tomarParametros(int argc,char *argv[],char **file,int *num_preg,int *opcion_ene) {
  int c;
  char subStr[2];
  //Se revisa que los parametros esten completos
  if (argc != 5 && argc != 6) error("Parametros incompletos o incorrectos");

  opterr = 0;
  *opcion_ene = 0;
     
  //El siguiente codigo administra los parametros y los almacena en variables
  while ((c = getopt (argc, argv, "f:v:n")) != -1)
    switch (c) {
    case 'f':
      substring(0,1,optarg,subStr,sizeof(subStr));
      if (!strcmp(subStr,"-")) error("Ingrese el Nombre del archivo luego de -f");
      *file = optarg;
      break;
    case 'v':
      substring(0,1,optarg,subStr,sizeof(subStr));
      if (!strcmp(subStr,"-")) error("Ingrese el numero de preguntas luego de -v");
      *num_preg = atoi(optarg);
      break;
    case 'n':
      *opcion_ene = 1;
      break;
    case '?':
      error("Opcion invalida");
      break;
    default:
      abort();
      break;
    }
}

int main (int argc, char *argv[]) {
 
  //Declaracion de Variables
  struct Lista *lista_servidores = crear();
  struct Linter *lista_intervalos = create();
  struct Linter *lista_promedios = create();
  struct Nodo *servidor = (struct Nodo *)malloc(sizeof(struct Nodo));
  struct Par * par = malloc(sizeof(struct Par));
  FILE * archivo;
  char *host, *file;
  char *prim = malloc(256);
  char *inter = malloc(256);
  int no_resp, hora, num_preg, opcion_ene, contador, num_serv;
  double primera;
  infoHilo *structHilo = (infoHilo *)malloc(sizeof(infoHilo));
  no_resp = 0;

  //Se procede a tomar los parametros del programa
  tomarParametros(argc,argv,&file,&num_preg,&opcion_ene);
 
  //Se abre el archivo para leer 
  archivo = fopen (file ,"r"); 
  if (archivo == NULL) error("El archivo no existe o no se puede leer");
  /*agregamos a la lista_servidores los servidores especificados en el archivo*/
  agregar(lista_servidores,archivo);				
  fclose(archivo);

  //Se inicializan las variables del los hilos y se establece el numero de servidores
  num_serv = lista_servidores->cant_elem - 1;
  pthread_t threadUDP[num_serv];
  int fdThread[num_serv];
  *servidor = *lista_servidores->cab;

  printf("\nHaciendo peticiones...\n");

  //Comieza el ciclo que itera sobre los servidores
  for (contador = 0; contador < num_serv; contador++) {

     primera=time(NULL);

    //Inicializamos el semaforo utilizado en la region critica de los hilos.
    if (sem_init(&sem,0,1) < 0) error("Al inicializar el semaforo - UDP");

    //Se inicializan las variables de la estructura del Hilo
    structHilo->no_resp = &no_resp;
    structHilo->num_preg = num_preg;
    structHilo->lista = lista_intervalos;
    structHilo->prom = lista_promedios;
    printf("Host: %s\n",servidor->valor);
#ifndef	DEBUG
    structHilo->clnt = clnt_create (servidor->valor, PROGRAMA_TIEMPO, VERSION_TIEMPO, "udp");
    if (structHilo->clnt == NULL) {
      clnt_pcreateerror (servidor->valor);
      exit (1);
    }
#endif	/* DEBUG */

    //Se hace la llamada al hilo de ejecucion
    fdThread[contador] = pthread_create(&threadUDP[contador],NULL,programa_tiempo_1,(void *)structHilo);

    //Se toma el siguiente servidor en la lista
    servidor = servidor->sig;

  }

  //Se cierran los hilos de ejecucion
  for(contador = 0; contador < num_serv; contador++) {
    pthread_join(threadUDP[contador],NULL);
  }

  //Se llama la funcion de Marzullo
  par = Marzullo(lista_intervalos);

  //Termina la ejecucucion del programa y se muestran los datos obtenidos en pantalla
  printf("Listo...\n");
  printf("\nEl intervalo es: %d - %d\n", par->a , par->b);
  printf("El promedio de duracion de los intervalos es: %f\n",promedioInter(lista_promedios));
  printf("Las peticiones no respondidas fueron = %d\n",no_resp);
  hora = (time(NULL)-primera) + ((par->b - par->a)/2) + par->a;

  //printf("El promedio de intervalos es = %f\n",promedioInter(lista));

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

  //Se destruye el semaforo
  sem_destroy(&sem);

  exit (0);
}
