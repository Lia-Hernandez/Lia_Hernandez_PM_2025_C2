#include <stdio.h>
/*Este programa sirve para expresar todos los numeros (enteros positivos) que satisfacen la operacion siguiente:
 7*T4 - 6*P3 + 12*R5 < 5850*/

int main()
{ int T,P,R;
long long resultado_express;/*Use long long para que quepan los digitos completos de las potencias*/

printf("En busqueda de valores de T,P,R que satisfagan 7*T4");
for(T=1; T<=5; T++)
{
    for (P= 1; P<=9; P++)
    {
        for(R= 1;R<=3;R++)
        {resultado_express= (long long)7 *T*T*T*T-
        (long long) 6* P*P*P+
        (long long) 12* R*R*R*R*R;

            if (resultado_express<5850)
            {
                printf("(T,P,R) = (%d, %d,%d | Resultado:%lld\n", T,P,R,resultado_express);
            }
        }
    }
}



    printf("");
    return 0;
}
