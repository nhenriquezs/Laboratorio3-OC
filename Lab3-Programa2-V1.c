#include <stdio.h>
#include <malloc.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <ctype.h>
#include <getopt.h>


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

    int *a;
    a = (int*)calloc(tamano, sizeof(int));

    /*************GUARDAR VALORES EN EL ARREGLO***********/
    int i;
    printf("VECTOR a: ");
    for(i=0;i<tamano;i++)
    {
        fscanf(entrada1,"%i",&a[i]);
        printf("%i ",a[i]);
    }
    fclose(entrada1);
    printf("\nEl archivo de entrada se ha cerrado.\n");
    /*calloc para que los arreglos estén con 0 iniciales*/
    /************FIN GUARDAR VALORES EN EL ARREGLO********/

    printf("\n%i\n", calcular(a,tamano));
    
   return 0;
}


int calcular(int *a,int tamano){
    int acc = 0;
    int i,j;
    int tmp=1;
    for(i = 0; i < tamano - 1; i++)
    {
        for(j=0;j<a[i+1];j++)
        {
            tmp = tmp*a[i];
        }
       printf("%i\n",tmp );
       acc = acc + tmp;
    }
    return acc;
}
