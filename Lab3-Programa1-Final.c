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


//float calcular(float *a, float *b, float *v);

int main(int argc, char *argv[])
{
    int fflag=0;
    int gflag=0;
    char* fvalue =NULL;
    char* gvalue =NULL;

    /******************INICIO FUNCION GETOPT******************/
    int c;
    while ((c = getopt (argc, argv, "f:g:")) != -1)
        switch (c)
        {
            case 'f':
                fflag = 1;
                fvalue=optarg;
                break;

            case 'g':
                gflag = 1;
                gvalue=optarg;
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
    FILE *entrada2 = fopen(gvalue,"r");
    if(entrada1==NULL||entrada2==NULL)
    {
        printf("Algun archivo de entrada no existe\n");
        return 0;
    }
    else
    {
        //printf("Los archivos de entrada han sido abiertos\n");
    }
    /************FIN DE VALIDACIÓN DE ARGUMENTOS***********/


    /**************CONTAR TAMAÑO DEL VECTOR a****************/
    int tamanoa = 1;
    char caracter;
    while(feof(entrada1)==0)
    {
        caracter=fgetc(entrada1);
        if(caracter=='\n')
        {
            tamanoa++;
        }
    }
    rewind(entrada1);
    //printf("El tamaño del vector a es: %i\n",tamanoa);
    /************FIN CONTAR TAMAÑO DEL VECTOR a**************/
    /**************CONTAR TAMAÑO DEL VECTOR b****************/
    int tamanob = 1;
    while(feof(entrada2)==0)
    {
        caracter=fgetc(entrada2);
        if(caracter=='\n')
        {
            tamanob++;
        }
    }
    rewind(entrada2);
    //printf("El tamaño del vector b es: %i\n",tamanob);
    /************FIN CONTAR TAMAÑO DEL VECTOR b**************/
    if(tamanoa!=tamanob)
    {
        printf("ERROR: los vectores no son del mismo tamaño");
        return 0;
    }

    int N = tamanoa;

    float a[N] __attribute__((aligned(16))); /*vector a*/
    float b[N] __attribute__((aligned(16))); /*vector b*/
    float res[N] __attribute__((aligned(16))); /*vector resultado*/

    /*************GUARDAR VALORES EN LOS ARREGLOS***********/
    int i;
    //printf("VECTOR a: ");
    for(i=0;i<N;i++)
    {
        fscanf(entrada1,"%f",&a[i]);
        //printf("%f ",a[i]);
    }
    //printf("\nVECTOR b: ");
    for(i=0;i<N;i++)
    {
        fscanf(entrada2,"%f",&b[i]);
        //printf("%f ",b[i]);
    }
    fclose(entrada1);
    fclose(entrada2);
    //printf("\nlos archivo de entrada han sido cerrados\n");
    /************FIN GUARDAR VALORES EN LOS ARREGLOS********/

    __m128 acc;
    __m128 acc2;
    /*********************PRIMERA OPERACION*****************/
    for(size_t i =0;i<N;i=i+4)
    {
        __m128 a1 = _mm_load_ps(&a[i]);
        __m128 b1 = _mm_load_ps(&b[i]);
        b1 = _mm_sqrt_ps(b1); /*se elevan los valores de b al cuadrado*/
        a1 = a1/2; /*se dividen los valores del vector a en 2*/
        acc = _mm_add_ps(a1,b1); /*se suman ambos vectores*/
        _mm_store_ps(&res[i],acc); /*se guardan en un arreglo*/
    }
    /*****************FIN PRIMERA OPERACION*****************/
    float suma1 = 0;
    /*for(i=0;i<N;i++)
    {
        printf("%f ",res[i]); /*Imprimir valor del vector resultante
    }
    printf("\n");*/
    /*********************SEGUNDA OPERACION*****************/
    for(i=0;i<N;i++)
    {
        suma1 = suma1 +res[i]; /*Para la segunda parte necesitamos la suma de todos los elementos del vector*/
    }
    /*printf("acc : %f\n",suma1);*/
    for(i=0;i<N;i++)
    {
        res[i]=suma1; /*creamos un arreglo que contenga la suma para poder operar después*/
    }
    for(size_t i =0;i<N;i=i+4)
    {
        __m128 a2 = _mm_load_ps(&a[i]);
        __m128 r1 = _mm_load_ps(&res[i]);
        a2 = _mm_mul_ps(a2,a2); /*elevamos al cuadrado el vector a*/
        a2 = _mm_sub_ps(a2,r1); /*le restamos el resultado anterior*/
        _mm_store_ps(&res[i],a2); /*lo guardamos en el arreglo de resultado*/
    }
    /*****************FIN SEGUNDA OPERACION*****************/
    /*printf("\nSEGUNDA PARTE\n");
    for(i=0;i<N;i++)
    {
        printf("%f ",res[i]); /*se imprime todos los elementos de resultado
    }*/
    float suma2=0;
    for (i = 0; i < N; ++i)
    {
        suma2=suma2+res[i];
    }
    printf("%f\n",suma2);
    return 0;
}
