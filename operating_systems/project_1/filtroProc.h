unsigned char *cambiarBrillo(FILE *salida,int bot,int top,int lineas_leidas,int alto,int ancho,unsigned char A[alto][ancho][3],int d);
unsigned char *aplicarNegativo(FILE *salida,int bot,int top,int lineas_leidas,int alto,int ancho,unsigned char A[alto][ancho][3]);
unsigned char *desenfocar(FILE *salida,int bot,int top,int lineas_leidas,int alto,int ancho,unsigned char A[alto][ancho][3],int radio,float factor);
int maximo(int a,int b);
int minimo(int a,int b);
