#include <stdio.h>
#include <malloc.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <ctype.h>
#include <getopt.h>
#include <xmmintrin.h>
#include <emmintrin.h>
#include <pmmintrin.h>


int calcular(int *a, int tamano);

int main(int argc, char *argv[])
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
                if (optopt == 'f'||optopt == 'g')
                    fprintf (stderr, "La opcion -%c requiere argumento (numero).\n", optopt);
                else if (isprint (optopt))
                    fprintf (stderr, "-%c es una opción desconocida.\n", optopt);
                else
                    fprintf (stderr,"Caracter de opción desconocida `\\x%x'.\n",optopt);
                return 1;   

            default:
                return 0;
                
        }
    /******************FIN FUNCION GETOPT******************/

    /***************VALIDACIÓN DE ARGUMENTOS***************/
    FILE *entrada1 = fopen(fvalue,"r");
    if(entrada1==NULL)
    {
        printf("El archivo de entrada no existe.\n");
        return 0;
    }
    else
    {
      //  printf("El archivo de enetrada ha sido abierto.\n");
    }
    /************FIN DE VALIDACIÓN DE ARGUMENTOS***********/


    /**************CONTAR TAMAÑO DEL VECTOR a****************/
    int tamano = 1;
    char caracter;
    while(feof(entrada1)==0)
    {
        caracter=fgetc(entrada1);
        if(caracter=='\n')
        {
            tamano++;
        }
    }
    rewind(entrada1);
    //printf("El tamaño del vector a es: %i\n",tamano);
    /************FIN CONTAR TAMAÑO DEL VECTOR a**************/
    int N=tamano-1;
    float a[N] __attribute__((aligned(16))); /*vector a*/

    /**************GUARDAR VALORES EN ARREGLO**************/
    float vector1[N] __attribute__((aligned(16))); /*vector v1*/
    float vector2[N] __attribute__((aligned(16))); /*vector v2*/
    int i;
    //printf("VECTOR 1: ");
    for(i=0;i<N;i++)
    {
        fscanf(entrada1,"%f",&vector1[i]);
      //  printf("%f ",vector1[i]);
    }
    rewind(entrada1);
    int car = fgetc(entrada1);
    //printf("\nVECTOR 2: ");
    for(i=0;i<N;i++)
    {
        fscanf(entrada1,"%f",&vector2[i]);
      //  printf("%f ",vector2[i]);
    }
    fclose(entrada1);
    //printf("\nEl archivo de entrada ha sido cerrado\n");
    /*calloc para que el arreglo esté con 0 iniciales*/
    /************FIN GUARDAR VALORES EN ARREGLO************/
    __m128 acc;
    
    for(size_t i =0;i<N;i=i+4)
    {
        __m128 v1 = _mm_load_ps(&vector1[i]);
        __m128 v2 = _mm_load_ps(&vector2[i]);

        v1 = _mm_mul_ps(v1,v2); /*se elevan los valores de b al cuadrado*/
        _mm_store_ps(&a[i],v1); /*se guardan en un arreglo*/
    }
    int resultado = 0;
    for(i=0;i<N;i++)
    {
        resultado = resultado + a[i];
    }
    printf("%i\n",resultado );

    
   return 0;
}
