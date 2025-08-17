#include <stdio.h>
#include <math.h>
/*Este programa nos proporciona el valor del seno de un valor que se le de*/

int main()
{
    int x_entero;
    long double x_double;
    long double sen_x=0.0L;
    long double numero_actual;
    int num_numeros= 0;
    int k=0;
    const long double  Precision =0.0000001L;

    printf("Ingrese el valor de x (entero):");
    scanf("%d", &x_entero);
    x_double= (long double) x_entero * 3.14159265358979323846L/180.0L;
    numero_actual=x_double;
    sen_x+=numero_actual;
    num_numeros++;



    while(fabsl(numero_actual) >=Precision)
        {int num = 2 * k+1;
    numero_actual=numero_actual * (-1.0L)* x_double * x_double/ ((long double) (num+1)*(num +2));
    if(fabsl(numero_actual)>=Precision)
    {
        sen_x+= numero_actual;
        num_numeros++;
    }

    k++;

    }
     printf("\nEl valor de sen(%d) es: %.10Lf\n", x_entero, sen_x);

        printf("Numero de terminos deseados: %d\n", num_numeros);
        return 0;
        }





