#include <stdio.h>
#include <stdbool.h>

bool es_primo (int num){
if (num<=1)
{return false;

}
for (int l=2; l<=num/2;l++)
{
    if (num% l == 0)
    {
        return false;
    }
}
return true;
}
 void main (void)
{int NU1, NU2;
int temp;
printf("Ingrese el primer numero entero positiVo (NU1): ");
scanf("%d", &NU1);
printf("Ingrese el segundo numero entero positivo (NU2): ");
scanf("%d", &NU2);

if (NU1>NU2)
{
    temp=NU1;
    NU1=NU2;
    NU2=temp ;

}if (NU1<=2)
{NU1=3;

}
printf("Pares de numeros enteros positivos entre %d y %d:\n", NU1, NU2 );
for (int i= NU1; i<=NU2-2; i++)
{if (es_primo (i))
    {
        if (es_primo (i+2)){
            printf("(%d ,%d)\n", i,i+2);
        }
    }

}




}
