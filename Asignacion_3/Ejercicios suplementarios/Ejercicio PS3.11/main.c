#include <stdio.h>
#include <stdlib.h>
int main(void)

{
int N;
int i, j; //Numero de anios




        printf("Ingrese el numero de anios (N):");
        scanf("%d", &N);

        if (N<= 0)
        {
            printf("Error: El numero de anios debe ser un numero positivo.\n");
            return 1;
        }
double VIN[N][4];
double Totaltipo[4]={0.0,0.0,0.0,0.0};
double Totalanio[N];
    for (i =0; i<N; i++)
    {Totalanio[i]=0.0;}
    for (i=0;i<N;i++)
    { printf("\nIngrese datos para el Anio %d\n",i+1);
    for(j=0;j<4;j++)
    {
    printf("Ingrese la cantidad de litros de vino del tipo %d");
    scanf("%lf", &VIN[i][j]);
    Totaltipo[j]+= VIN [i][j];
    Totalanio[i]+= VIN[i][j];
    }
    }
    printf("\nTotal producido por tipo de vino:\n");
    for ( j =0; j<4; j++) {
        printf("Tipo %d: %.2f litros\n", j+1, Totaltipo[j]);

    }

    printf("\nEl total de la produccion anual:\n");
    for( i=0; i<N; i++)
    {
        printf("Anio %d: %.2f de litros de vino\n", i+1, Totalanio[i]);
}

}


