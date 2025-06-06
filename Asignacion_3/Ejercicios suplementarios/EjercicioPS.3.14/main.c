#include <stdio.h>
#include <math.h>
/*Este programa nos proporciona el valor del seno de un valor que se le de*/

void main(void)
{
    int x_entero;
    long double x_double;
    long double sen_x=0.0;
    long double numero_actual;
    int num_numeros= 0;
    int i=1;
    const long double  Precision =0.001;

    printf("Ingrese el valor de x (entero):");
    scanf("%d", &x_entero);
    x_double= (long double) x_entero;
    numero_actual=x_double;
    i=1;

    while(fabs(numero_actual) >=Precision) {sen_x+= numero_actual;
    num_numeros++;
    i +=2;
    numero_actual= numero_actual* (-1)*x_double *x_double /(i *(i-1)) ;
    }
     printf("\nEl valor de sen(%d) es: %.6Lf\n", x_entero, sen_x);

        printf("Numero de terminos deseados: %d\n", num_numeros);
        }





