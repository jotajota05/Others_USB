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
#define MAX 255
#define MIN 0

unsigned char *cambiarBrillo(FILE *salida,int bot,int top,int lineas_leidas,int alto,int ancho,unsigned char A[alto][ancho][3],int d);
unsigned char *aplicarNegativo(FILE *salida,int bot,int top,int lineas_leidas,int alto,int ancho,unsigned char A[alto][ancho][3]);
unsigned char *desenfocar(FILE *salida,int bot,int top,int lineas_leidas,int alto,int ancho,unsigned char A[alto][ancho][3],int radio,float factor);
int maximo(int a,int b);
int minimo(int a,int b);

/*name: cambiarBrillo
 * @param
 * @return
 */
unsigned char *cambiarBrillo(FILE *salida,int bot,int top,int lineas_leidas,int alto,int ancho,unsigned char A[alto][ancho][3],int d) {
	int i,j,k;
	unsigned char B[lineas_leidas+2][ancho][3];
	int l = 0;
	for (i = bot ; i <= top ; i++) {
		for(j = 0 ; j < ancho ; j++) {
			for(k = 0 ; k < 3 ; k++) {
				if (A[i][j][k] + d < MIN) B[l][j][k] = MIN;
				else if (A[i][j][k] + d > MAX) B[l][j][k] = MAX;
				else B[l][j][k] = A[i][j][k] + d;
			}
		}
		l++;
	}
	return &B[0][0][0];
}

/*name: aplicarNegativo
 * @param
 * @return
 */
unsigned char *aplicarNegativo(FILE *salida,int bot,int top,int lineas_leidas,int alto,int ancho,unsigned char A[alto][ancho][3]) {
	int i,j,k;
	int l = 0;
	unsigned char B[lineas_leidas+2][ancho][3];
	for (i = bot ; i <= top ; i++) {
		for(j = 0 ; j < ancho ; j++) {
			for(k = 0 ; k < 3 ; k++) {
				B[l][j][k] = MAX - A[i][j][k];
			}
		}
		l++;
	}
	return &B[0][0][0];
}

/*name: desenfocar
 * @param
 * @return
 */
unsigned char *desenfocar(FILE *salida,int bot,int top,int lineas_leidas,int alto,int ancho,unsigned char A[alto][ancho][3],int radio,float factor) {
	unsigned char B[lineas_leidas+2][ancho][3];
	int x1,x2,y1,y2,i,j,k,p,q,l,prom,count;
	l = 0;
	for (i = bot ; i <= top ; i++) {
		for (j = 0 ; j < ancho ; j++) {
			x1 = maximo(bot,i - radio);
			x2 = minimo(top,i + radio);
			y1 = maximo(0,j - radio);
			y2 = minimo(ancho-1,j + radio);
			for (k = 0 ; k < 3 ; k++) {
				prom = 0;
				count = 0;
				for (p = x1 ; p <= x2 ; p++)
					for (q = y1 ; q <= y2 ; q++) {
						prom += A[p][q][k];
						count++;
					}
				prom = prom / count;
				B[l][j][k] = ((1-factor)*A[i][j][k]) + (factor*prom);
			}
		}
		l++;
	}
	return &B[0][0][0];	
}

int maximo(int a,int b) {
		if (a>=b) return a;
		else return b;
}

int minimo(int a,int b) {
		if (a<=b) return a;
		else return b;
}

/*name: MAIN del programa principal 
 * @param
 * @return
 */
int main(int argc,char *arg[]) {
	
	if (atoi(arg[1]) <= 0 ) {
		printf("\nEl numero de procesos debe ser mayor o igual que 1\n");
		exit(-1);
	}
	
	FILE *Imagen = fopen(arg[2],"r");
	FILE *ImagenMod;
	pid_t pidhijo;
	
	unsigned char comp[1];
	int status, alto, ancho,maximo , count, resto, lineas_leidas, elem, i, j, k, p, desp;
	int num_proc = atoi(arg[1]);
	int filas_proc[2];
	char *lineaLeida = malloc(100 * sizeof(char));
	unsigned char byteLeido[1];
	char *codigo = malloc(2);
	char *anchoStr = malloc(100);
	char *altoStr = malloc(100);
	char *maximoStr = malloc(100);
	int radio;
	float factor;
	
	if (strcmp(arg[4],"desenfocar") == 0) {
		radio = atoi(arg[5]);
		factor = atof(arg[6]);
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
			case 2 : strcat(anchoStr,lineaLeida);ancho = atoi(lineaLeida);break;
			case 3 : strcat(altoStr,lineaLeida);alto = atoi(lineaLeida);break;
			case 4 : strcat(maximoStr,lineaLeida);maximo = atoi(lineaLeida);break;
		}
		if (count == 4) break;
	}
	
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
	filas_proc[0] = (alto / num_proc);
	filas_proc[1] = alto % num_proc;
	resto = filas_proc[1] -1;
	if (num_proc > alto) {
		filas_proc[0] = 1;
		filas_proc[1] = 0;
		resto = 0;
	}
	unsigned char matImagen[alto][ancho][3];
	unsigned char *matrizNueva;
	count = 0;
	lineas_leidas = 0;
	if (filas_proc[1] == 0) p = 0;
	else p = 1;
	

	//Inicia el ciclo que va leyendo lineas y asignado a los procesos correspondientes
	for (i = 0 ; i < alto ; i++) {  
		lineas_leidas++;

		//Para una linea, se van leyendo las columnas y los pixeles de la imagen
		for(j = 0 ; j < ancho ; j++) {
			for(k = 0 ; k < 3 ; k++) {
				fread(comp,sizeof(unsigned char),1,Imagen);
				matImagen[i][j][k] = comp[0];
			}
		}
     
     	//Se verifica la condicion de que estan leidas las lineas necesarias para un proceso
     	//y si hay un resto, se distribuyen equitativamente entre los procesos
		if ( (((i-p) % filas_proc[0]) == filas_proc[0]-1) && (lineas_leidas == filas_proc[0] || lineas_leidas == filas_proc[0]+1)) { 
			count++;
			if (resto > 0)  { 
				p++;
				resto--;
			}
			
			//Creo un nuevo proceso hijo
			pidhijo = fork();

			if (pidhijo == 0) {
	
     			// Codigo que ejecutaran los hijos
       			matrizNueva = malloc(lineas_leidas*ancho*3);
       			if (strcmp(arg[4],"brillo") == 0) {
       				int brillo = atoi(arg[5]);
       				matrizNueva = cambiarBrillo(ImagenMod,i-(lineas_leidas-1),i,lineas_leidas,alto,ancho,matImagen,brillo);
       			} else if (strcmp(arg[4],"negativo") == 0) {
       				matrizNueva = aplicarNegativo(ImagenMod,i-(lineas_leidas-1),i,lineas_leidas,alto,ancho,matImagen);
       			} else if (strcmp(arg[4],"desenfocar") == 0) {
					matrizNueva = desenfocar(ImagenMod,i-(lineas_leidas-1),i,lineas_leidas,alto,ancho,matImagen,radio,factor);
				}

				ImagenMod = fopen(arg[3],"r+");
				long int posicion = strlen(codigo)+strlen(anchoStr)+strlen(altoStr)+strlen(maximoStr) + 4 + (i-(lineas_leidas-1))*3*ancho; 
				int error = fseek(ImagenMod,posicion,SEEK_SET);
				if (error == 0) {
					for (desp = 0 ; desp < lineas_leidas*ancho*3 ; desp++) {
						fwrite(matrizNueva + desp,sizeof(unsigned char),1,ImagenMod);
					}
				} else printf("\nERROR : Hubo un error con el fseek!!!!!\n");
				fclose(ImagenMod);
       			exit(33);
       			
			} else if (pidhijo  < 0) {
       			perror("Error al crear proceso hijo");
       			exit(-1);
     		} 
     		lineas_leidas = 0;
     	}
	}

	// El padre espera por todos los hijos que creo.
  	for (i = 0; i < num_proc; ++i) 
    	wait(&status);     
    	
   	printf("\nModificacion de imagen exitosa!!\n");
   	
	exit(0);
}
