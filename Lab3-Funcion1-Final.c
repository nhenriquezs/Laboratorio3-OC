/*
UNIVERSIDAD DE SANTIAGO DE CHILE
Facultad de Ingeniería
Departamento de Ingeniería Informática
Ingeniería Civil Informática
Organización de Computadores - Laboratorio 3
Autores:
	Nicole Macarena Henriquez Sepúlveda
	Maximiliano Felipe Andrés Pérez Ródríguez
Profesores:
	Nicolás Andrés Hidalgo Castillo
	Erika Rosas Olivos
Ayudante:
	Felipe Ignacio Garay Pérez
*/

//LIBRERIAS
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <getopt.h>
#include <math.h>
#include <xmmintrin.h>
#include <emmintrin.h>
#include <pmmintrin.h>



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
	int tamano = 1;
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
	int N = tamano;
	/**************GUARDAR VALORES EN ARREGLO**************/
	float vector[N] __attribute__((aligned(16)));
 	float aux[N] __attribute__((aligned(16)));
	float aux2[N] __attribute__((aligned(16)));

	int i;
	printf("VECTOR: ");
	for(i=0;i<tamano;i++)
	{
		fscanf(entrada,"%f",&vector[i]);
		aux[i]=vector[i];
		aux2[i]=vector[i];
		printf("%f ",vector[i]);
	}
	fclose(entrada);
	printf("\nEl archivo de entrada ha sido cerrado\n");
	/*calloc para que el arreglo esté con 0 iniciales*/
	/************FIN GUARDAR VALORES EN ARREGLO************/

	/********************OPERACION 1***********************/
	float f1;
	float min,minAux=0;
	int pos;
	int j,k,l;
	for(l=0;l<tamano;l++)
	{	
		printf("\nITERACIÓN: %i\n",l);
		min=99999;
		for(i=0;i<tamano;i++)
		{
			if(aux[i]<min)
			{
				min = aux[i];
				pos = i;
			}
		}
		aux[pos]=9999;
		aux2[pos]=1;
		printf("min: %f\n",min );
		printf("minAnt: %f\n",minAux );
		printf("min-minAnt = %f\n",min-minAux);

		for(j=0;j<min-minAux;j++)
		{
			for(size_t i =0;i<N;i=i+4)
			{
				__m128 v1 = _mm_load_ps(&vector[i]);
				__m128 a1 = _mm_load_ps(&aux2[i]);
				v1 = _mm_mul_ps(v1,a1); /*se multiplican ambos vectores*/
				_mm_store_ps(&vector[i],v1); /*se guardan en un arreglo*/
			}
		}
		minAux = min;
	}
	float resultado = 0;
	for(size_t i =0;i<N;i=i+4)
	{
		__m128 v1 = _mm_load_ps(&vector[i]);
		v1 = _mm_sqrt_ps(v1); /*se multiplican ambos vectores*/
		_mm_store_ps(&vector[i],v1); /*se guardan en un arreglo*/
	}
	for(i=0;i<tamano;i++)
	{
		resultado = resultado + vector[i];
	}
	printf("\nResultado función 1: %f\n",resultado);
	/*****************FIN OPERACIONES**********************/
	return 0;	
}
