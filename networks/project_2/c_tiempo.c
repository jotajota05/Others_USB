/*
  Proyecto 2 Redes de Computadores I
  Servidores Concurrentes  TCP (Procesos) y UDP (Hilos de Ejecucion)

  Grupo 11
  Jessica Perez 05-38724
  Juan Garcia 05-38207
*/

//Librerias necesarias para el funcionamiento del Servidor
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
#include <signal.h>
#include <sys/wait.h> 
#include <pthread.h>
#include <semaphore.h>

//Librerias implementadas para el funcionamiento del Servidor
#include "sock_utils.h"
#include "marzullo.h"
#include "leer.h"

//Semaforo para la region critica en la comunicacion UDP
sem_t sem;

//Estructura que contiene las variables necesarias por el hilo de ejecucion
typedef struct {
  int num_preg, sock, contador, *no_resp;
  struct Linter *lista;
  char *buffer;
  struct sockaddr_in servidor, emisor;
  sem_t sem;
} infoUDP;

//Esta funcion crea una lista de intervalos vacia
struct Linter * create(){
  struct Linter * nueva;
  nueva = malloc(sizeof(struct Linter));
  if(nueva != NULL){
    nueva -> cab = NULL;
    nueva ->co = NULL;
    nueva -> e = 0; 
  }
  else{
    printf("\aNo se pudo crear la lista\n");
    printf("El sistema operativo ha rehusado a la peticion para su espacio\n");
  }
  return nueva;
}

//Esta funcion recibe una lista, un double que representa el offset y un entero
//que representa el tipo, para luego agregar el intervalo a la lista.
void add(double n,int t,struct Linter * l){
  struct Intervalo * aux;
  aux = malloc(sizeof(struct Intervalo));
  if(aux != NULL){
    aux -> offset = n;
    aux -> type =t;
    if (l -> cab == NULL){
      l -> cab = aux;
      l -> cab -> ant = NULL;
    }
    else{
      l-> co -> sig = aux;
      aux -> ant = l -> co;
    }
    l -> co = aux;
    aux -> sig = NULL;
    l -> e++;
  }
  else{
    printf("\aNo se pudo agregar el elemento");
    printf("El sistema operativo ha rehusado a la peticion ");
    printf("para su espacio\n");
  }
}

//Funcion q elimina la cola de la lista	de Intervalos
void del(struct Linter * l){
  if(l->e > 2){	
  	struct Intervalo * aux = l->co;
  	l->co = aux->ant;
  	l->co->sig = NULL;
  	free(aux);
  }
  else{
  	struct Intervalo * aux = l->cab;
  	l->cab = NULL;
  	l->co = NULL;
  	free(aux);
  }  	
  	
}	
	
//Imprime el contenido de la lista de intervalos en pantalla
void print(struct Linter* l){
  struct Intervalo *e;
  e = l->cab;
  while( e != NULL ){
    printf(" %f %d\n", e-> offset, e->type);
    if( e->sig != NULL )
      e = e->sig;
    else
      break;
  }
}

//Calcula el promedio de los tamanos de los intervalos de las paticiones
double promedioInter(struct Linter* l) {
  double prom = 0;
  double inicio, fin;
  struct Intervalo *e;
  e = l->cab;
  while( e != NULL ){
    inicio = e -> offset;
    if( e->sig != NULL ) e = e->sig; else break;
    fin = e -> offset;
    prom = prom + ((inicio - fin) / l -> e);
    if( e->sig != NULL ) e = e->sig; else break;
  }
  return prom;
}

//Funcion que agrga los elementos en una lista de un proceso hijo, a una lista de un proceso
//Padre a travez de Archivos.
void addF(struct Linter * l, FILE * archivo){
  char * a;
  while(!feof(archivo)){
    struct Intervalo * aux;
    aux = malloc(sizeof(struct Intervalo));
    if(aux != NULL){
      fscanf(archivo,"%lf",&aux->offset);
      fscanf(archivo,"%d",&aux->type);
      if (l -> cab == NULL){
	l -> cab = aux;
	l -> cab -> ant = NULL;
      }
      else{
	l-> co -> sig = aux;
	aux -> ant = l -> co;
      }
      l -> co = aux;
      aux -> sig = NULL;
      l -> e++;
    }
    else{
      printf("\aNo se pudo agregar el elemento");
      printf("El sistema operativo ha rehusado a la peticion ");
      printf("para su espacio\n");
		
    }
  }
}				

//Funcion que ejecuta las acciones del hilo en la comunicacion UDP
void *clienteUDP(void *data) {

  infoUDP *th;
  th = (infoUDP *)data;
  infoUDP t = *th;
  int it = t.num_preg;
  int longt = sizeof(struct sockaddr_in);
  int i = 0;
  int a = 0;
  int d = 0;
  int calidad,primera,ultima,desface;
  char *calidadStr = malloc(sizeof(char)*256);
  char *buf = malloc(sizeof(char)*256);
  
  //Inicia el ciclo de peticiones
  for(i = 0; i < it ; i++) {

    //Se declaran las estructuras para el timeout
    struct timeval tv;
    fd_set rfds;

    //Se incializan las variables para el timeout, estableciendo el tiempo del timeout
    FD_ZERO( &rfds );
    FD_SET( t.sock, &rfds);
    tv.tv_sec  = 2;
    tv.tv_usec = 0;

    if (i==0) primera = time(NULL);
    
    //Se entra en una region critica, en la que el hilo de ejecucion agrega un elemento a la lista de intervalos
    if (sem_wait(&(sem)) < 0) error("Fallo el sem_wait\n");
    add(time(NULL),-1,t.lista);
    if (sem_post(&(sem)) < 0) error("Fallo el sem_post\n");

    //Se inician las peticiones
    bzero(t.buffer,256);
    //Se manda el paquete
    d = sendto(t.sock,"Dame la hora!", 256,0,(struct sockaddr *)&(t.servidor),longt);	    
    if(d == -1) {   //Error si el datagrama no pudo ser enviad
      printf("No se pudo enviar el datagrama por el Socket - UDP\n");
    }
    //Se ejecuta el select sobre el descriptor de conexiones para verificar el timeout
    d = select( FD_SETSIZE, &rfds, (fd_set *)NULL, (fd_set *)NULL, &tv );
    if(d == -1) {
      printf("El Select tuvo un error\n");
    }
    if(d == 0) {   //Expiro el tiempo para la recepcion del paquete
      printf("Timeout expirado... Respuesta no recibida - UDP\n");
      (*t.no_resp)++;
    } else {
      //Se recibe la respuesta del servidor
      d = recvfrom(t.sock,t.buffer,256,0,(struct sockaddr *)&(t.emisor), &longt);
      if(d == -1) {
	printf("Error al tratar de recibir un datagrama - UDP\n");
      }

      calidad = atoi(substring(0,1,t.buffer,calidadStr,sizeof(calidadStr)))+1;

    }

    if (sem_wait(&(sem)) < 0) error("Fallo el sem_wait");
    add(time(NULL),1,t.lista);
    if ( i == it-1) ultima = t.lista->co->offset;

    //Comienza a aplicarse la Normalizacion
    desface = (primera-t.lista->co->ant->offset);
    int tj = t.lista->co->offset - desface;
    t.lista->co->ant->offset = atof(&t.buffer[1]) +(tj-primera)/2;
    t.lista->co->offset = atof(&t.buffer[1]) - (tj-primera)/2;
      			
    double abre = t.lista->co->ant->offset;
    double cierra = t.lista->co->offset;
    //agregar extras por calidad
    for(a=0;a<calidad-1;a++){
      add(abre,-1,t.lista);  
      add(cierra,1,t.lista);
    }

    if (sem_post(&(sem)) < 0) error("Fallo el sem_post");

  }

  //Termina la ejecucion del hilo
  pthread_exit(0);

}

//Funcion que recibe los parametros para el programa
void tomarParametros(int argc,char *argv[],char **file,int *puerto,int *num_preg,char **protocolo,int *opcion_ene) {
  int c;
  char subStr[2];
  //Se revisa que los parametros esten completos
  if (argc != 8 && argc != 9) error("Parametros incompletos o incorrectos");

  opterr = 0;
  *opcion_ene = 0;
     
  //El siguiente codigo administra los parametros y los almacena en variables
  while ((c = getopt (argc, argv, "f:p:v:tun")) != -1)
    switch (c) {
    case 'f':
      substring(0,1,optarg,subStr,sizeof(subStr));
      if (!strcmp(subStr,"-")) error("Ingrese el Nombre del archivo luego de -f");
      *file = optarg;
      break;
    case 'p':
      substring(0,1,optarg,subStr,sizeof(subStr));
      if (!strcmp(subStr,"-")) error("Ingrese el numero de puerto luego de -p");
      *puerto = atoi(optarg);
      break;
    case 'v':
      substring(0,1,optarg,subStr,sizeof(subStr));
      if (!strcmp(subStr,"-")) error("Ingrese el numero de preguntas luego de -v");
      *num_preg = atoi(optarg);
      break;
    case 't':
      *protocolo = "-t";
      break;
    case 'u':
      *protocolo = "-u";
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

//Funcion para matar procesos zombies en la ejecucion del programa
void matarZombies() { 
  while (waitpid(-1, NULL, WNOHANG) > 0); 
} 

//Funcion principal del programa
int main (int argc, char *argv[]) {

  struct sockaddr_in direccion, servidor, emisor;
  struct in_addr direccion_host;
  struct hostent *host;
  struct Par * par = malloc(sizeof(struct Par));
  struct timeval tv;
  fd_set rfds;
  char buffer[1024], calidadStr[256], *protocolo, *serv, subStr[2], *file, tiempoStr[255];
  char *prim = malloc(256);
  char *inter = malloc(256);
  int  a, c, d, i, it, tj, desface, primera, ultima, hora, sock, longt, conexion, puerto, num_preg, opcion_ene, calidad, no_resp;
  double tiempo;
  FILE *f;
  
  //Se procede a tomar los parametros del programa
  tomarParametros(argc,argv,&file,&puerto,&num_preg,&protocolo,&opcion_ene);

  //Se inicializa la lista que guardara los servidores del archivo
  struct Lista *li = crear();
  FILE * archivo;

  //Se abre el archivo para leer 
  archivo = fopen (file ,"r"); 
  if (archivo == NULL) error("El archivo no existe o no se puede leer");
  /*agregamos a la lista li los servidores especificados en el archivo*/
  agregar(li,archivo);				
  fclose(archivo);
  
  int fd[li->e-1][2];
  pid_t childpid;

  /*Se declara la lista en donde se guardaran las intervalos para Marzullo*/
  struct Linter* lista;		
  /*Se apunta al primer elemento de la lista de servidores para luego movernos por ella*/		
  struct Nodo * mov = li->cab;		
  int contador = 0;
  infoUDP *structUDP = (infoUDP *)malloc(sizeof(infoUDP));
  
  pthread_t threadUDP[li->e];
  int fdThread[li->e];
   
  if (!strcmp(protocolo,"-t")) {
  	
    /*Iteraciones para la creacion de los procesos hijos que se encargaran de enviar
     * las peticiones a cada uno de los servidores especificados en el archivo de entrada*/
    for(contador = 0; contador < li->e-1; contador++){

      ////////////////////////////////////////////////////////////
      //////////////Se realiza la conexion por TCP////////////////
      ///////////////////////////////////////////////////////////
      
      //Se intenta convertir el argumento en una direccion, para luego buscar el host, si no, se busca por nombre
      if (inet_aton(mov->n, &direccion_host))
      	host = gethostbyaddr((char *)&direccion_host, sizeof(direccion_host), AF_INET);
      else
	host = gethostbyname(mov->n);

      if (!host) error("Error al buscar el Host - TCP");
    	
      /*mov apunta al elemento siguiente en la lista de servidores*/		
      mov = mov->sig;					  
      primera=time(NULL);
      /*Se abren las tuberias de comunicacion de los procesos padre-hijo*/
      pipe(fd[contador]);	
      /*Se crea un proceso hijo*/			
      if((childpid = fork()) == -1)
        {
	  perror("fork");
	  exit(1);
        }


      if(childpid == 0){
	/* Proceso hijo cierra el lado de lectura*/
	close(fd[contador][0]);			
    		
	f = fdopen(fd[contador][1], "w");
	/*Se crea el socket de comunicacion*/
	if(( sock = socket(PF_INET, SOCK_STREAM, 0)) < 0) error("Al crear el Socket - TCP");
    
	direccion.sin_family = AF_INET;
	direccion.sin_port = htons(puerto);
    
	/*Se Toma la primera direccion IP asociada a este hostname*/
	memcpy(&direccion.sin_addr, host->h_addr_list[0], sizeof(direccion.sin_addr));

	/*Se conecta al servidor mediante el socket creado*/
	conexion = connect(sock, (struct sockaddr *)&direccion, sizeof(direccion));
	if (conexion < 0)  exit(0);

	////////////////////////////////////
	//////Aqui se hace la peticion//////
    
	it = num_preg;
	i = 0;
	a = 0;
	lista = create();
	/*En cada peticion se van guardando los valores, antes y despues de la peticion*/
	for(i= 0; i < it ; i++) {
	  if (i==0) primera = time(NULL); 
	  add(time(NULL), -1,lista);	/*guardando antes de la peticion*/

	  /*Se realizan las peticiones*/
	  bzero(buffer,256);
	  bzero(calidadStr,256);
	  send(sock,"Dame la hora!", 256,0);
	  recv(sock,buffer,256,0);
	  //printf("Tiempo = %f\n",tiempo = atof(buffer));
	  recv(sock,calidadStr,256,0);
	  //printf("Calidad = %d\n",calidad = atoi(calidadStr));

	  add(time(NULL),1,lista);/*guardando despues de la peticion*/
	  if ( i == it-1) ultima = lista->co->offset;


	  /*Normalizacion, Se modifica la lista con los cambios
	   *realizados durante la normalizacion*/
	  desface = (primera-lista->co->ant->offset);
	  tj = lista->co->offset - desface;
	  lista->co->ant->offset = atof(buffer) +(tj-primera)/2;
	  lista->co->offset = atof(buffer) -(tj-primera)/2;
      			
	  /*agregando intervalos extras de acuerdo a la calidad del servidor*/
	  double abre = lista->co->ant->offset;
	  double cierra = lista->co->offset;
	  for(a=0;a<calidad-1;a++){
	    add(abre,-1,lista);  
	    add(cierra,1,lista);
	  }
				
      			
	}
	/* Escribe la lista de intervalos en el pipe correspondiente */
	struct Intervalo * aux = lista->cab;
	for(i=0;i<lista->e;i++){
	  fprintf(f, "%lf %d\n",aux->offset,aux->type);
	  aux = aux->sig;
	}  
	fclose(f);              
	exit(0);
      }
      else{
	/* Padre cierra el lado de lectura del pipe */
	close(fd[contador][1]);
              							
      }
    }
    signal(SIGCHLD, matarZombies);
    lista=create();
    int kk;
    /*Leyendo lo escrito por cada hijo y creando la lista
     * con todos los intervalos correspondientes a las
     * respuestas de los srervidores*/
    for(kk=0;kk<li->e-1;kk++){
      f = fdopen(fd[kk][0], "r"); 
      	addF(lista,f);
		del(lista);
      fclose(f);
    }
  
    /*Aqui llamamos la funcion de Marzullo*/
    if(lista->e>1){
    	par = Marzullo(lista);  
    	printf("El intervalo es: %d - %d\n", par->a , par->b);
    	printf("El promedio de intervalos es = %f\n",promedioInter(lista));
    	hora = (time(NULL)-primera) + ((par->b - par->a)/2) + par->a;  
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
	else{
		error("No se pudo conectar con ningun socket - TCP");
	}


    ////////////////////////////////////////////////////////////
    //////////////Se realiza la conexion por UDP////////////////
    ///////////////////////////////////////////////////////////

  } else if (!strcmp(protocolo,"-u")) {
    
    no_resp = 0;
    lista = create();

    //Inicia el ciclo para realozar las conexiones a cada servidor
    for(contador = 0; contador < li->e-1; contador++) {

      //Se crea el socket de comunicacion
      sock = socket(AF_INET,SOCK_DGRAM,0);
      if (sock < 0) { printf("Al crear el socket - UDP"); continue; }

      //Se incializa los campos de el servidor, dominio.
      servidor.sin_family = AF_INET;

      //Se obtiene el nombre del host o la direccion
      if (inet_aton(mov->n, &direccion_host))
	host = gethostbyaddr((char *)&direccion_host, sizeof(direccion_host), AF_INET);
      else host = gethostbyname(mov->n);
    
      if (host == 0) {
	printf("No se encontro el host '%s' - UDP\n",mov->n);
	mov = mov->sig;
	continue;
      }
	
      //Nos desplazamos por la lista de servidores,. para en la proxima iteracion tomar el siguiente servidor
      mov = mov->sig;

      primera=time(NULL);

      bcopy((char *)host->h_addr,(char *)&servidor.sin_addr,host->h_length);

      //Se incializa los campos de el servidor, puerto.
      servidor.sin_port = htons(puerto);
      longt = sizeof(struct sockaddr_in);

      //Inicializamos el semaforo utilizado en la region critica de los hilos.
      if (sem_init(&sem,0,1) < 0) error("Al inicializar el semaforo - UDP");
    
      //Se inicializan las variables de la estructura usada por los hilos de ejecucion
      structUDP->sock = sock;   //El socket de comunicacion
      structUDP->num_preg = num_preg;   //EL numero de preguntas a realizar
      structUDP->contador = contador;   //El contador de servidor
      structUDP->buffer = buffer;   //El buffer de comunicacion
      structUDP->emisor.sin_family = emisor.sin_family;   //El dominio del emisor
      structUDP->emisor.sin_addr.s_addr = emisor.sin_addr.s_addr;
      structUDP->emisor.sin_port = emisor.sin_port;   //El puerto de comunicacion
      *structUDP->emisor.sin_zero = *emisor.sin_zero;
      structUDP->servidor.sin_family = servidor.sin_family;   //El dominio del servidor
      structUDP->servidor.sin_addr.s_addr = servidor.sin_addr.s_addr;
      structUDP->servidor.sin_port = servidor.sin_port;   //El puerto de comunicacion
      *structUDP->servidor.sin_zero = *servidor.sin_zero;
      structUDP->lista = create();   //Se crea la lista del hilo
      structUDP->lista = lista;
      structUDP->sem = sem;   //El semaforo para la region critica
      structUDP->no_resp = &no_resp;   //Numero de respuestas No recibidas

      //Se crea el hilo de ejecucion para la comunicacion UDP
      fdThread[contador] = pthread_create(&threadUDP[contador],NULL,clienteUDP,(void *)structUDP);

    }

    //Se cierran los hilos de ejecucion
    for(contador = 0; contador < li->e-1; contador++) {
      pthread_join(threadUDP[contador],NULL);
    }

    //Se llama la funcion de Marzullo
    par = Marzullo(lista);

    printf("El intervalo es: %d - %d\n", par->a , par->b);
    hora = (time(NULL)-primera) + ((par->b - par->a)/2) + par->a;

    printf("El promedio de intervalos es = %f\n",promedioInter(lista));
    printf("El numero de preguntas no respondidas fue = %d\n",no_resp);

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
  }


  //Se cierra el socket
  close(sock);    
  return 0;
  
}  
