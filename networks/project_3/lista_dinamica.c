#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista_dinamica.h"

//Esta funcion crea una lista de intervalos vacia
struct Linter * create(){
  struct Linter * nueva;
  nueva = malloc(sizeof(struct Linter));
  if(nueva != NULL){
    nueva -> cab = NULL;
    nueva ->cola = NULL;
    nueva -> cant_elem = 0; 
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
      l-> cola -> sig = aux;
      aux -> ant = l -> cola;
    }
    l -> cola = aux;
    aux -> sig = NULL;
    l -> cant_elem++;
  }
  else{
    printf("\aNo se pudo agregar el elemento");
    printf("El sistema operativo ha rehusado a la peticion ");
    printf("para su espacio\n");
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
