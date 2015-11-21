//Operaciones básicas con archivos

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leer.h"

//Crea una lista vacía
struct Lista * crear(){
  struct Lista * nueva;
  nueva = malloc(sizeof(struct Lista));
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

//imprime el contenido de la lista en pantalla
void imprimir(struct Lista* l){
  struct Nodo *e;
  e = l->cab;
  while( e != NULL ){
    printf(" fila = %s \n", e-> valor);
    if( e->sig != NULL )
      e = e->sig;
    else
      break;
  }
}	
	
	
//agrega lo leido en la lista
void agregar(struct Lista * l, FILE * archivo){
  while(!feof(archivo)){
    struct Nodo * aux;
    aux = malloc(sizeof(struct Nodo));
    if(aux != NULL){
      fscanf(archivo,"%s",aux->valor);
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
      (l -> cant_elem)++;
    }
    else{
      printf("\aNo se pudo agregar el elemento");
      printf("El sistema operativo ha rehusado a la peticion ");
      printf("para su espacio\n");
		
    }
  }
}	
