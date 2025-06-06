#include <stdio.h>
#include <stdlib.h>
/*Este programa es utilizado para formar un patron visto de forma ascendente donde el dato que ingresamos es la cuspide y N de todos los demas*/
int main()
{
    int N;
    int a,b;

    printf("Ingrese un numero entero (N): ");
    scanf("%d", &N);
    for (a= 1; a<=N; a++)
    {
    for(b=1;b<= a; b++)
    {
        printf("\n");
    } for(a = N - 1; a>= 1;a--)
    {for (b=1; b<= a; b++)
    {
        printf("%d", b);
    }
    printf("\n");

    }
    return 0;
    }


}
