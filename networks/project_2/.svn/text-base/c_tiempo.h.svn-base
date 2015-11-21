
/*Lista de Intervalos*/


//representa una lista de Servidores
struct Linter{
	struct Intervalo * cab;	//Apuntador a la cabeza
	struct Intervalo * co;	//Apuntador a la cola
	int e;				//cantidad de elementos de la lista
	};
	
//Elemento de una lista
struct Intervalo{
	struct Intervalo * sig;	//apuntador al siguiente
	struct Intervalo * ant;	//apuntador al anterior
	double offset;		    //valor del
	int type;				// elemento
	};

//Crea una lista vacía
struct Linter * create();

void add(double n,int t,struct Linter * l);
//imprime el contenido de la lista en pantalla
void print(struct Linter* l);
void addF(struct Linter * l, FILE * archivo);			

void tomarParametros(int,char **,char **,int *,int *,char **,int *);

void matarZombies();
