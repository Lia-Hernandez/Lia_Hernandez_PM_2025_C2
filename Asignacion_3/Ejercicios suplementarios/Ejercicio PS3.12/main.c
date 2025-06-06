#include <stdio.h>
#include <stdbool.h>

int N;  //N debe ser entero positivo//
int NUM;
int i, j;
bool es_primo;

void main (void)
{
    int N=0;
    int NUM=0;
    int i, j=0;
  printf("\nIngrese el numero aqui: ");
  scanf("%d", &NUM);
  if(NUM<=2)
  {
      printf("No hay numeros menores que %d. \n", NUM);

  }
    printf("Numeros primos menores que %d: \n",  NUM);
    for (i=2; i<NUM; i++)

    {
        es_primo=true;

    for (j=2; j<=i/2; j++)
    {
        if (i%j==0)
        {
            es_primo =false;
        break;
        }
    } if (es_primo)
    {
        printf("%d", i) ;

    }


    }

}
