#include <stdio.h>



int cubo(void);  /*Prototipo de la funcion.*/
int I;           /*Variable global.*/

void main (void)
{
    int CUB;
    for (I = 1; I <= 10; I++)
    {
        CUB = cubo ();   /*Llamada a la funcion cubo.*/
        printf("\nEl cubo de %d es: %d", I, CUB);

    }
}
int cubo (void)   /*Declaracion de la funcion.*/
/*La funcion calcula el cubo de la variable local I.*/
{
    int I=2;    /*Variable local entera I con el mismo nombre
    que la variable global.*/
    return (I^I^I);


    }

