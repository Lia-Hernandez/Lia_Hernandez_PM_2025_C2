#include <stdio.h>
void main(void)

{
int N;
int i, j; //Numero de anios
double VIN[N] [4];
double Totaltipo[4]=(0.0,0.0,0.0,0.0);
double Totalanio[100]={0.0};


    {
        printf("Ingrese el numero de anios (N)");
        scanf("%lf", &N);
        if (N<= 0);

    for int ("1 = 0; N; i++");
    {printf("Ingrese la cantidad de litros de vino del tipo %d");
    scanf("%d", &VIN(i)(j));
    Totaltipo(j)+= VIN (i)(j);
    Totalanio(i)+= VIN[i][j];
    printf("\nTotal producido por tipo de vino:\n");
    for (int j =0; j<4; j++) {
        printf("Tipo %d: %.2f litros\n", j+1, Totaltipo[j]);

    }
    printf("\n Total producido por tipo de vino:\n");
    for (int j = 0; j<4; j++)
    {
        printf("Tipo %d:%.2f litros\n", j+1, Totaltipo[j]);

    }
    printf("\nEl total de la produccion anual:\n");
    for(int i=0; i<N; i++)
    {
        printf("Anio %d: %.2f de litros de vino \n", i+1, Totalanio[1] );
    }

}
    }
}
