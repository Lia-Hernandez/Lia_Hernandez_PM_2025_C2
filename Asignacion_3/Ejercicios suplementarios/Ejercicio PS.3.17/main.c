#include <stdio.h>
/*Este programa lo usamos para formar un patron con nuestros datos*/


int main()
{int N;
int i,j;
    printf("Ingrese un numero entero(N): ");
    scanf("%d", &N);
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=i;j++)
        {
            printf("%d", j);
    }printf("\n");
    }

    return 0;
}
