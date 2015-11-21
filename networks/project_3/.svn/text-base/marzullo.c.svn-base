#include <stdlib.h>
#include <stdio.h>

#include "lista_dinamica.h"

struct Par{
  int a;
  int b;
};

void bub(struct Linter* lista) { 
  int tam = lista->cant_elem;
  int i= 0;
  double auxa, auxb;
  int x = 1;
  while(x != 0){
    x = 0;
  struct Intervalo * aux;
  aux = lista->cab;
    for(i = 0; i< tam-1; i++){

      if (aux->offset > aux->sig->offset){
	auxa = aux->offset;
	auxb = aux->type;
	aux->offset = aux->sig->offset;
	aux->type = aux->sig->type;
	aux->sig->offset = auxa;
	aux->sig->type = auxb;	
	x++;
      }
      if (aux->offset == aux->sig->offset && aux->type < aux->sig->type){
	auxa = aux->offset;
	auxb = aux->type;
	aux->offset = aux->sig->offset;
	aux->type = aux->sig->type;
	aux->sig->offset = auxa;
	aux->sig->type = auxb;
	x++;
      }
    }
    }
		

}


struct Par* Marzullo(struct Linter* lista) {
	
  bub(lista);
  struct Intervalo * aux;
  aux = lista->cab;
  int i = 0;
  double iz = aux->offset;
  double de = aux->sig->offset;
  double mej =0;
  double cont =0;
  for( i = 0; i < lista->cant_elem-1; i++){
    cont = cont - aux->type;	
    if (cont > mej) {
      mej = cont;
      iz = aux->offset;
      de = aux->sig->offset;		
    }
    if ((aux->sig)->sig != NULL)
      aux = (aux->sig)->sig;
  }
  struct Par * inter;
  inter = malloc(sizeof(struct Par));
  inter->a = iz;
    inter->b = de;
  
 
  return inter;
	
}
 


