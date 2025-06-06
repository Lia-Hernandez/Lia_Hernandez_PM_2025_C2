#include <stdio.h>
/*Este programa sirve para formar un triangulo con los digitos que decidamos*/


int main()
{
    int N_filas;
    int fila_num;
    int val;
    int num_to_print;

    printf("Ingrese el numero de filas (N_filas): ");
    scanf("%d", &N_filas);

    for(fila_num=1; fila_num<=N_filas; fila_num++)
    {
        for(val=fila_num; val <=(fila_num * 2-1); val++)
        {
            num_to_print=val%10;
            printf("%d ",  num_to_print);

        }
        for (val=(fila_num * 2-2); val>= fila_num;val--)
        {
            num_to_print=val% 10;
            printf("%d ", num_to_print);
        }
        printf("\n");

    }



    return 0;
}
