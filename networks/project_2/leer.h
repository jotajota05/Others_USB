
//representa una lista de Servidores
struct Lista{
  struct Nodo * cab;	//Apuntador a la cabeza
  struct Nodo * co;	//Apuntador a la cola
  int e;				//cantidad de elementos de la lista
};
	
//Elemento de una lista
struct Nodo{
  struct Nodo * sig;	//apuntador al siguiente
  struct Nodo * ant;	//apuntador al anterior
  char n[150];		//valor del elemento
};

//Crea una lista vacía
struct Lista * crear();

//imprime el contenido de la lista en pantalla
void imprimir(struct Lista* l);
	
	
//agrega lo leido en la lista
void agregar(struct Lista * l, FILE * archivo);
