//representa una lista de Servidores
struct Linter {
	struct Intervalo *cab;	//Apuntador a la cabeza
	struct Intervalo *cola;	//Apuntador a la cola
	int cant_elem;				//cantidad de elementos de la lista
	};
	
//Elemento de una lista
struct Intervalo {
	struct Intervalo *sig;	//apuntador al siguiente
	struct Intervalo *ant;	//apuntador al anterior
	double offset;		    //valor del
	int type;				// elemento
	};


struct Linter *create();

void add(double,int,struct Linter *);

void print(struct Linter*);
