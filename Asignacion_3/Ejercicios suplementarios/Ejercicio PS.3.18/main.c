#include <stdio.h>

int main()
{ int N;
int a,b;
int num_espacios;

    printf("Ingrese un numero entero:");
    scanf("%d",&N);
    for (a=N;a>=1; a--)
        {
    for(b=1;b<=a; b++)
    {
        printf("%d",b);
    }
    num_espacios=N-a;
    for(b=0; b< num_espacios; b++)
    {
        printf("   ");
    }
    for(b=a;b>=1;b--)
    {
        printf("%d", b);

    }
    printf("\n");
}
    return 0;
}
