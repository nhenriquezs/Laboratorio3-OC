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
        printf("El archivo de enetrada ha sido abierto.\n");
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
    printf("El tamaño del vector a es: %i\n",tamano);
    /************FIN CONTAR TAMAÑO DEL VECTOR a**************/

    int N = tamano-1;
    float a[N] __attribute__((aligned(16)));
    float a2[N] __attribute__((aligned(16)));

    /*************GUARDAR VALORES EN EL ARREGLO***********/
    int i;
    printf("VECTOR a: ");
    for(i=0;i<N;i++)
    {
        fscanf(entrada1,"%f",&a[i]);
        printf("%f ",a[i]);
    }
    rewind(entrada1);
    int basura = fgetc(entrada1);
     printf("\nVECTOR b: ");
    for(i=0;i<N;i++)
    {
        fscanf(entrada1,"%f",&a2[i]);
        printf("%f ",a2[i]);
    }
    fclose(entrada1);
    printf("\nEl archivo de entrada se ha cerrado.\n");
    /*calloc para que los arreglos estén con 0 iniciales*/
    /************FIN GUARDAR VALORES EN EL ARREGLO********/
    float acc = 0;
    for(size_t i =0;i<N;i=i+4)
    {
        __m128 tmp = _mm_load_ps(&a[i]);
        __m128 v2 = _mm_load_ps(&a2[i]);
        tmp = _mm_xor_ps(tmp,v2); 
        _mm_store_ps(&a[i],tmp); /*se guardan en un arreglo*/
    }

    for(i = 0; i < tamano - 1; i++)
    {
        printf("%f ",a[i]);
       acc = acc + a[i];
    }
    printf("\n%f\n", acc);
    
   return 0;
}
