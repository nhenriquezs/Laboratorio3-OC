#include <stdio.h>
#include <malloc.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <ctype.h>
#include <getopt.h>


float calcular(float *a, float *b, int tamano);

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
        printf("Los archivos de entrada han sido abiertos\n");
    }
    /************FIN DE VALIDACIÓN DE ARGUMENTOS***********/


    /**************CONTAR TAMAÑO DEL VECTOR a****************/
    int tamanoa = 0;
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
    printf("El tamaño del vector a es: %i\n",tamanoa);
    /************FIN CONTAR TAMAÑO DEL VECTOR a**************/
    /**************CONTAR TAMAÑO DEL VECTOR b****************/
    int tamanob = 0;
    while(feof(entrada2)==0)
    {
        caracter=fgetc(entrada2);
        if(caracter=='\n')
        {
            tamanob++;
        }
    }
    rewind(entrada2);
    printf("El tamaño del vector b es: %i\n",tamanob);
    /************FIN CONTAR TAMAÑO DEL VECTOR b**************/
    if(tamanoa!=tamanob)
    {
        printf("ERROR: los vectores no son del mismo tamaño");
        return 0;
    }


    float *a;
    a = (float*)calloc(tamanoa, sizeof(float));
    float *b;
    b = (float*)calloc(tamanob, sizeof(float));

    /*************GUARDAR VALORES EN LOS ARREGLOS***********/
    int i;
    printf("VECTOR a: ");
    for(i=0;i<tamanoa;i++)
    {
        fscanf(entrada1,"%f",&a[i]);
        printf("%f ",a[i]);
    }
    printf("\nVECTOR b: ");
    for(i=0;i<tamanob;i++)
    {
        fscanf(entrada2,"%f",&b[i]);
        printf("%f ",b[i]);
    }
    fclose(entrada1);
    fclose(entrada2);
    printf("\nlos archivo de entrada han sido cerrados\n");
    /*calloc para que los arreglos estén con 0 iniciales*/
    /************FIN GUARDAR VALORES EN LOS ARREGLOS********/

    printf("\n%f\n", calcular(a, b,tamanoa));
    
   return 0;
}

float calcular(float *a, float *b,int tamano){
    int i;
    float acc = 0;
    float acc2 = 0;

    for(i = 0; i < tamano; i++){
        acc = acc + a[i] / 2 + sqrt(b[i]);
    }
    printf("\nACC: %f\n",acc);
    printf("\n");

    for(i = 0; i < tamano; i++){
        acc2 = acc2 + pow(a[i], 2) - acc;
        printf("%f ",pow(a[i], 2) - acc);
    }

    return acc2;
    
}
