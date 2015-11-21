#include <stdlib.h>
#include <stdio.h>

#include "c_tiempo.h"

struct Par{
  int a;
  int b;
};


void bub( int tam, struct Intervalos* lista) { 
  int i= 0;
  double auxa, auxb;
  int x = 1;
  while(x != 0){
    x = 0;
    for(i = 0; i< tam-1; i++){
      if (lista[i].offset > lista[i+1].offset){
	auxa = lista[i].offset;
	auxb = lista[i].type;
	lista[i].offset = lista[i+1].offset;
	lista[i].type = lista[i+1].type;
	lista[i+1].offset = auxa;
	lista[i+1].type = auxb;	
	x++;
      }
      if (lista[i].offset == lista[i+1].offset && lista[i].type < lista [i+1].type){
	auxa = lista[i].offset;
	auxb = lista[i].type;
	lista[i].offset = lista[i+1].offset;
	lista[i].type = lista[i+1].type;
	lista[i+1].offset = auxa;
	lista[i+1].type = auxb;
	x++;
      }
    }
    }
		

}


struct Par* Marzullo(int it,struct Intervalos* lista) {
	
  bub(it*2,lista);
  int i;
  double iz = lista[i].offset;
  double de = lista[i+1].offset;
  double mej =0;
  double cont =0;
  for( i = 0; i < (it*2)-1; i++){
    cont = cont - lista[i].type;	
    if (cont > mej) {
      mej = cont;
      iz = lista[i].offset;
      de = lista[i+1].offset;		
    }	
    }
  struct Par * inter;
  inter = malloc(sizeof(struct Par));
  inter->a = iz;
    inter->b = de;
  
 
  return inter;
	
}
 
