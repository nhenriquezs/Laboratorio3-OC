
//LIBRERIAS
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <getopt.h>
#include <math.h>


/*************************MAIN*************************/
int main (int argc, char **argv)
{
	int fflag=0;
	char* fvalue =NULL;

	/******************INICIO FUNCION GETOPT******************/
	int c;
	while ((c = getopt (argc, argv, "f:")) != -1)
		switch (c)
		{
			case 'f':
				fflag = 1;
				fvalue=optarg;
				break;
			case '?':
				if (optopt == 'f')
					fprintf (stderr, "La opcion -%c requiere argumento (numero).\n", optopt);
				else if (isprint (optopt))
					fprintf (stderr, "-%c es una opción desconocida.\n", optopt);
				else
					fprintf (stderr,"Caracter de opción desconocida `\\x%x'.\n",optopt);
				return 1;	

			default:
				abort ();
				
		}
	/******************FIN FUNCION GETOPT******************/

	/***************VALIDACIÓN DE ARGUMENTOS***************/
	FILE *entrada = fopen(fvalue,"r");
	if(entrada==NULL)
	{
		printf("El archivo de entrada no existe\n");
		return 0;
	}
	else
	{
		printf("El archivo de entrada ha sido abierto\n");
	}
	/************FIN DE VALIDACIÓN DE ARGUMENTOS***********/


	/**************CONTAR TAMAÑO DEL VECTOR****************/
	int tamano = 0;
	char caracter;
	while(feof(entrada)==0)
	{
		caracter=fgetc(entrada);
		if(caracter=='\n')
		{
			tamano++;
		}
	}
	rewind(entrada);
	printf("El tamaño del vector es: %i\n",tamano);
	/************FIN CONTAR TAMAÑO DEL VECTOR**************/


	float vector[tamano];
	int i;
	printf("VECTOR: ");
	for(i=0;i<tamano;i++)
	{
		fscanf(entrada,"%f",&vector[i]);
		printf("%f ",vector[i]);
	}
	fclose(entrada);
	printf("\nEl archivo de entrada ha sido cerrado\n");

	float f1 = 0;
	for(i=0;i<tamano;i++)
	{
		f1 = f1+sqrt(pow(vector[i],vector[i]));
	}
	printf("\nResultado función 1: %f\n",f1);

	float f2 = 0;
	for(i=0;i<tamano-1;i++)
	{
		f2 = f2 + vector[i]*vector[i+1];
	}
	printf("Resultado función 2: %f\n",f2);;

	
	return 0;	
}
