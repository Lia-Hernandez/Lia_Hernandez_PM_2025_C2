#include <stdio.h>
/*Este programa nos proporciona el Maximo comun divisor entre dos numeros cualesquiera*/

int main ()
{
    int NU1,NU2;
    int a,b;
    int residuo;
    printf("Ingrese el primer numero (NU1):");
    scanf("%d", &NU1);
    printf("Ingrese el segundo numero (NU2):");
    scanf("%d", &NU2);
    a= NU1;
    b=NU2;
    while (b !=0)
    {residuo =a % b;
    a=b;
    b=residuo;

    }
    printf("\nEl maximo comun divisor de %d y %d es: %d\n", NU1,NU2,a);
    return 0;
}
