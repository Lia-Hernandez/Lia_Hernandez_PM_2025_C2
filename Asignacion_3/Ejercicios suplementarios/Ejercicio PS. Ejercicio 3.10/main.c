#include <stdio.h>
 /*L1, L2, L3, L4, L5, L6: Variables de tipo float.
 TOT1, T0T2, TOT3, TOT4, TOT5, TOT6: variables de tipo entero.*/

 void main(void)
{

    float T1,T2,T3, T4, T5,T6;
    float TOT1=0.0;
    float TOT2=0.0;
    float TOT3=0.0;
    float TOT4=0.0;
    float TOT5=0.0;
    float TOT6=0.0;
    float TTOT=0.0;
    int  CLA,CAB;
    printf("Ingrese precio de la Tienda 1:");
    scanf("%f",&T1 );
    printf("Ingrese precio de la Tienda 2:");
    scanf("%f", &T2);
    printf("Ingrese precio de la Tienda 3:");
    scanf("%f", &T3);
    printf("Ingrese precio de la Tienda 4:");
    scanf ("%f",&T4);
    printf("Ingrese precio de la Tienda 5:");
    scanf("%f", &T5);
    printf("Ingrese precio de la Tienda 6:");
    scanf ("%f", &T6);

    while (1)
    {

    printf("Numero de la tienda(CLA):");
    scanf("%d", &CLA);
    if (CLA== 0){
        break;
    }

   if (CLA<1|| CLA>6){printf ("Error: numero no valido. Intente con un numero del 1 al 6");
   continue; }
    printf("Cantidad de boletos (CAB): ");
    scanf("%d", &CAB);
    if (CLA==1 ){
        TOT1 += (CAB*T1);
        TTOT+=(CAB* T1);
        }else if(CLA==2){
            TOT2 +=(CAB*T2);
        TTOT+=(CAB*T2);
        }else if (CLA==3){
        TOT3 +=(CAB*T3);
        TTOT += (CAB*T3);
       } else if (CLA== 4){
            TOT4+=(CAB*T4);
        TTOT +=(CAB*T4);
        }else if (CLA==5){
            TOT5+=(CAB*T5);
        TTOT +=(CAB*T5);
        }else if (CLA==6){
            TOT6+=(CAB * T6);
        TTOT +=(CAB * T6);
        }

    {




    printf("Total de ventas Tienda 1: $%.2f\n", TOT1);//
    printf("Total de ventas Tienda 2: $%.2f\n", TOT2);//
    printf("Total de ventas Tienda 3: $%.2f\n", TOT3);//
    printf("Total de ventas Tienda 4: $%.2f\n", TOT4);//
    printf("Total de ventas Tienda 5: $%.2f\n", TOT5);//
    printf("Total de ventas Tienda 6: $%.2f\n", TOT6);//
    printf("\nTotal de ventas de todas las tiendas: $%.2f\n", TTOT);//
}
    }
}
