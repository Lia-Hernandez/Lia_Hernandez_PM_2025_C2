#include <stdio.h>
/*Prueba de variables globales, locales y estaticas.
El progrma utiliza funciones en las que se usan diferentes tipos de
variables. */


int f1(void);
int f2(void);
int f3(void);    /*Prototipo de funciones*/
int f4(void);

int K=3;             /*Variable global.*/
void main(void)

{
    int I;
    /*La funcion f1 utilizada la variable global. */
    {
        K+= K;
        return (K);
    }
    int f2 (void)
    /* La funcion f3 utiliza la variable local.*/
    {
        int K=1;
        K++;
        return (K);
    }
         int f3(void)
        /*La funcion f3 utiliza la variable estatica.*/
        {
           static int K =8;
           K+=2;
           return (K);

        }
        int f4(void)
        /*La funcion f4 utiliza dos variables con el mismo nombre: local
        y global.*/
        {
            int K=5;
            K=K + ::K;              /*Uso de la variable local (K) y global (::K) */
            return (K);




}
