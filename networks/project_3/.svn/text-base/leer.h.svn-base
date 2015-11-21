
//representa una lista de Servidores
struct Lista{
  struct Nodo * cab;	//Apuntador a la cabeza
  struct Nodo * cola;	//Apuntador a la cola
  int cant_elem;				//cantidad de elementos de la lista
};
	
//Elemento de una lista
struct Nodo{
  struct Nodo * sig;	//apuntador al siguiente
  struct Nodo * ant;	//apuntador al anterior
  char valor[256];		//valor del elemento
};

//Crea una lista vacía
struct Lista * crear();

//imprime el contenido de la lista en pantalla
void imprimir(struct Lista* l);
	
	
//agrega lo leido en la lista
void agregar(struct Lista * l, FILE * archivo);
