/*
 *      filtroProc.c
 *		Proyecto 1 Sistemas de Operacion I CI-3825
 * 
 *      Copyright 2008 	
 * 		Juan J Garcia 05-38207
 * 		Luis Rodriguez 05-38826
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#define MAX 255
#define MIN 0

unsigned char *imgptr;
FILE *ImagenMod;
unsigned char *matrizNueva;
struct dat{
	int ancho;
	int i;
	int ll;
	int parametro;
	float factor;
	char *codigo;
	int maximo;
	int alto;
   	char *doc;
};

unsigned char *cambiarBrillo(FILE *salida,int bot,int top,int lineas_leidas,int alto,int ancho,unsigned char A[alto][ancho][3],int d);
unsigned char *aplicarNegativo(FILE *salida,int bot,int top,int lineas_leidas,int alto,int ancho,unsigned char A[alto][ancho][3]);
int desenfocar(FILE *salida,int alto,int ancho,unsigned char A[alto][ancho][3],int radio,int factor);

/*name: cambiarBrillo
 * @param
 * @return
 */
void *Brillo(void *data){
//(FILE *salida,int bot,int top,int lineas_leidas,int alto,int ancho,unsigned char A[alto][ancho][3],int d) 
	//printf("\nSE INICIA EL NEGATIVO\n");
	
	struct dat *datos;
	datos = (struct dat *) data;
	char *codigo = datos->codigo;
	int brillo = datos->parametro;
	int maximo = datos -> maximo;
	int alto = datos->alto;
	int ancho = datos->ancho;
	int tope = datos->i;
	int ll = datos->ll;
	int bot = tope - (ll-1);
	int i,j,k;
	int l = 0;
	int val = 0;
	//printf("max: %d\n",ll);
	unsigned char B[ll+2][ancho][3];
	for (i = bot ; i <= tope ; i++) {
		for(j = 0 ; j < ancho ; j++) {
			for(k = 0 ; k < 3 ; k++) {
				val = *(imgptr+(i*ancho*3 + 3*j + k));
				if (val + brillo < MIN)B[l][j][k] = MIN;
				else if (val + brillo > MAX) B[l][j][k] = MAX;
				else B[l][j][k] = val + brillo;
			}
		}
		l++;
	}
	matrizNueva = malloc(ll*ancho*3);
	matrizNueva = &B[0][0][0];
	char *arch = datos -> doc;
	ImagenMod = fopen(arch,"r+");
	long int posicion = sizeof(codigo)+sizeof(ancho)+sizeof(alto)+sizeof(maximo) + (i-(ll-1))*3*ancho - 1; 
	int error = fseek(ImagenMod,posicion,SEEK_SET);
	int desp;
	if (error == 0) {
		for (desp = 0 ; desp < ll*ancho*3 ; desp++) {
		fwrite(matrizNueva + desp,sizeof(unsigned char),1,ImagenMod);
		
			}
		} else printf("\nERROR : Hubo un error con el fseek!!!!!\n");
	fclose(ImagenMod);
	return(0);
}

/*name: aplicarNegativo
 * @param
 * @return
 */
void *Negativo(void *data){
	//printf("\nSE INICIA EL NEGATIVO\n");
	
	struct dat *datos;
	datos = (struct dat *) data;
	char *codigo = datos->codigo;
	int maximo = datos -> maximo;
	int alto = datos->alto;
	int ancho = datos->ancho;
	int tope = datos->i;
	int ll = datos->ll;
	int bot = tope - (ll-1);
	int i,j,k;
	int l = 0;
	//printf("max: %d\n",ll);
	unsigned char B[ll+2][ancho][3];
	for (i = bot ; i <= tope ; i++) {
		for(j = 0 ; j < ancho ; j++) {
			for(k = 0 ; k < 3 ; k++) {
				B[l][j][k] = MAX - *(imgptr+(i*ancho*3 + 3*j + k));
				//printf("%d\n",B[l][j][k]);
			}
		}
		l++;
		//printf("i: %d\n",i);
	}
	matrizNueva = malloc(ll*ancho*3);
	matrizNueva = &B[0][0][0];
	char *arch = datos -> doc;
	ImagenMod = fopen(arch,"r+");
	long int posicion = sizeof(codigo)+sizeof(ancho)+sizeof(alto)+sizeof(maximo) + (i-(ll-1))*3*ancho - 1; 
	int error = fseek(ImagenMod,posicion,SEEK_SET);
	int desp;
	if (error == 0) {
		for (desp = 0 ; desp < ll*ancho*3 ; desp++) {
		fwrite(matrizNueva + desp,sizeof(unsigned char),1,ImagenMod);
		
			}
		} else printf("\nERROR : Hubo un error con el fseek!!!!!\n");
	fclose(ImagenMod);
	return(0);
}

int max(int a,int b) {
		if (a>=b) return a;
		else return b;
}

int minimo(int a,int b) {
		if (a<=b) return a;
		else return b;
}

/*name: desenfocar
 * @param
 * @return
 */
void *Desenfocar(void *data) {
	
	//printf("\nSE INICIA EL NEGATIVO\n");
	
	struct dat *datos;
	datos = (struct dat *) data;
	char *codigo = datos->codigo;
	int maximo = datos -> maximo;
	int alto = datos->alto;
	int ancho = datos->ancho;
	int top = datos->i;
	int ll = datos->ll;
	int radio = datos-> parametro;
	int factor = datos-> factor;
	int bot = top - (ll-1);
	int l = 0;
	//printf("max: %d\n",ll);
	unsigned char B[ll+2][ancho][3];
	int x1,x2,y1,y2,i,j,k,p,q,count;
	int prom;
	l = 0;
	//prueba
	p = max(bot,i - radio);
	q = max(0,j - radio);
	k = 0;
	//printf("%d\n",*(imgptr+(ancho*3 + 3 + k)));
	//fin prueba
	for (i = bot ; i <= top ; i++) {
		for (j = 0 ; j < ancho ; j++) {
			x1 = max(bot,i - radio);
			x2 = minimo(top,i + radio);
			y1 = max(0,j - radio);
			y2 = minimo(ancho-1,j + radio);
			for (k = 0 ; k < 3 ; k++) {
				prom = 0;
				count = 0;
				for (p = x1 ; p <= x2 ; p++)
					for (q = y1 ; q <= y2 ; q++) {
						//printf("al-aclavar*********************\n");
						//printf("***:%d\n",(p*ancho*3 + 3*q + k));
						prom += *(imgptr+(p*ancho*3 + 3*q + k));//Problema manejando este apuntador.
						//printf("paso\n");
						count++;
					}
				prom = prom / count;
				//printf("antes: %d\n",B[l][j][k]);
				B[l][j][k] = ((1-factor)*(*(imgptr+(i*ancho*3 + 3*j + k)))) + (factor*prom);
				//printf("despues: %d\n",B[l][j][k]);
			}
		}
		l++;
	}
	//matrizNueva = malloc(ll*ancho*3);
	matrizNueva = &B[0][0][0];
	char *arch = datos -> doc;
	ImagenMod = fopen(arch,"r+");
	long int posicion = sizeof(codigo)+sizeof(ancho)+sizeof(alto)+sizeof(maximo) + (i-(ll-1))*3*ancho - 1; 
	int error = fseek(ImagenMod,posicion,SEEK_SET);
	int desp;
	if (error == 0) {
		for (desp = 0 ; desp < ll*ancho*3 ; desp++) {
		fwrite(matrizNueva + desp,sizeof(unsigned char),1,ImagenMod);
		
			}
		} else printf("\nERROR : Hubo un error con el fseek!!!!!\n");
	fclose(ImagenMod);
	return(0);	
}

/*name: MAIN del programa principal 
 * @param
 * @return
 */
int main(int argc,char *arg[]) {
	
	printf("INICIO\n");
	
	FILE *Imagen = fopen(arg[2],"r");
	
	
	unsigned char comp[1];
	int alto, ancho,maximo , count, resto, lineas_leidas, elem, i, j, k, p, desp;
	int num_hil = atoi(arg[1]);
	int filas_proc[2];
	char *lineaLeida = malloc(100 * sizeof(char));
	unsigned char byteLeido[1];
	char *codigo = malloc(2);
	int radio;
	float factor;
	struct dat pas;
	struct dat *pas_ptr = &pas; 
	
	if (strcmp(arg[4],"desenfocar") == 0) {
		radio = atoi(arg[5]);
		pas.parametro = radio;
		pas.factor = atof(arg[6]);
		if (factor < 0 || factor > 1) {
			printf("\nError!! el factor debe ser entre 0 y 1\n\n");
			exit(0);
		}
	}
	
	//Se leen las lineas del encabezado, el codigo, el alto y ancho de la imagen y el valor maximo
	count = 0;
	for (;;) {
		fscanf(Imagen,"%s ",lineaLeida);
		count++;
		if (strncmp(lineaLeida,"#",1) == 0) {
			count--;
			for (;;) {
			fread(byteLeido,sizeof(unsigned char),1,Imagen);
			if (byteLeido[0] == 10) break;
			}
			continue;
		}
		switch(count) {
			case 1 : strcat(codigo,lineaLeida);break;
			case 2 : ancho = atoi(lineaLeida);break;
			case 3 : alto = atoi(lineaLeida);break;
			case 4 : maximo = atoi(lineaLeida);break;
		}
		if (count == 4) break;
	}
	
	//Se imprimen los valores leidos del encabezado
	printf("Codigo : %s\n",codigo);
	printf("Ancho : %d\n",ancho);
	printf("Alto : %d\n",alto);
	printf("Maximo : %d\n",maximo);
	printf("size of Codigo : %d\n",sizeof(codigo));
	printf("size of Ancho : %d\n",sizeof(ancho));
	printf("size of Alto : %d\n",sizeof(alto));
	printf("size of Maximo : %d\n",sizeof(maximo));
	
	//
	ImagenMod = fopen(arg[3],"w");
	fprintf(ImagenMod,"%s\n",codigo);
	fprintf(ImagenMod,"%d\n",ancho);
	fprintf(ImagenMod,"%d\n",alto);
	fprintf(ImagenMod,"%d\n",maximo);
	unsigned char numeroByte = 0;
	for (elem = 0 ; elem < alto*ancho*3 ; elem++) {
		fwrite(&numeroByte,sizeof(unsigned char),1,ImagenMod);
		numeroByte++;
	}
	fclose(ImagenMod);
	
	//Se inicia el procedimoento de leer,modificar la imagen y guardar imagen nueva
	filas_proc[0] = (alto / num_hil);
	printf("\nMin de lineas por Proceso = %d\n",filas_proc[0]);
	filas_proc[1] = alto % num_hil;
	printf("Resto de lineas a ser distribuido = %d\n",filas_proc[1]);
	unsigned char matImagen[alto][ancho][3];
	imgptr = &matImagen[0][0][0];
	
	count = 0;
	lineas_leidas = 0;
	if (filas_proc[1] == 0) p = 0;
	else p = 1;
	resto = filas_proc[1] -1;
	
	//Datos a ser pasados a los Hilos
	pas.ancho = ancho;
	pas.doc = arg[3];
	pas.codigo = codigo;
	pas.maximo = maximo;
	pas.alto = alto;
	if (strcmp(arg[4],"brillo") == 0) pas.parametro = atoi(arg[5]);
	pthread_t threads[num_hil];
	//int ultima = 0;
	//Inicia el ciclo que va leyendo lineas y asignado a los Hilos correspondientes
	int t = -1;
	
	i=0;
	for(t=0; t<num_hil; t++){
			while (i < alto) {
				lineas_leidas++;
				//Para una linea, se van leyendo las columnas y los pixeles de la imagen
				for(j = 0 ; j < ancho ; j++) {
					for(k = 0 ; k < 3 ; k++) {
						fread(comp,sizeof(unsigned char),1,Imagen);
						matImagen[i][j][k] = comp[0];
					}
				}
				
				//Se verifica la condicion de que estan leidas las lineas necesarias para un hilo
				//y si hay un resto, se distribuyen equitativamente entre los procesos
				if ((((i-p) % filas_proc[0]) == filas_proc[0]-1) && (lineas_leidas == filas_proc[0] || lineas_leidas == filas_proc[0]+1)) {
					
					//printf("\nCreo hilo %d con i = %d\n",count+1,i);
					t++;
					//printf("t: %d\n",t);
					count++;
					if (resto > 0)  { 
						p++;
						resto--;
					}
						
						// Codigo que ejecutaran los hijos
						//printf("Lineas leidas: %d\n",lineas_leidas);
						//matrizNueva = malloc(lineas_leidas*ancho*3);
						if (strcmp(arg[4],"brillo") == 0) {
							int hil;
							pas.i = i;
							pas.ll = lineas_leidas;
							hil =  pthread_create(&threads[t], NULL, Brillo, (void *)pas_ptr);
						} 
						else if (strcmp(arg[4],"negativo") == 0){
							int hil;
							pas.i = i;
							pas.ll = lineas_leidas;
							hil =  pthread_create(&threads[t], NULL, Negativo, (void *)pas_ptr);}
						else if (strcmp(arg[4],"desenfocar") == 0) {
							int hil;
							pas.i = i;
							pas.ll = lineas_leidas;
							hil = pthread_create(&threads[t], NULL, Desenfocar, (void *)pas_ptr);
						}
						
						ImagenMod = fopen(arg[3],"r+");
						long int posicion = sizeof(codigo)+sizeof(ancho)+sizeof(alto)+sizeof(maximo) + (i-(lineas_leidas-1))*3*ancho - 1; 
						int error = fseek(ImagenMod,posicion,SEEK_SET);
						if (error == 0) {
							for (desp = 0 ; desp < lineas_leidas*ancho*3 ; desp++) {
								fwrite(matrizNueva + desp,sizeof(unsigned char),1,ImagenMod);
							}
						} else printf("\nERROR : Hubo un error con el fseek!!!!!\n");
						fclose(ImagenMod);
						//exit(33);
						
					lineas_leidas = 0;
					//break;
				}
			if ((((i-p) % filas_proc[0]) == filas_proc[0]-1) && (lineas_leidas == filas_proc[0] || lineas_leidas == filas_proc[0]+1)) break;
			i++;
			}
		}
		pthread_exit(NULL);
}
