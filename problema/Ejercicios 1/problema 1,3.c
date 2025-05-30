#include <stdio.h>
/*Promedio de sueldos.
El programa, al recibir como datos seis sueldos de un empleado, calcula tanto el
ingreso total como el promedio mensual.

CLA: variable de tipo entero.
SU1, SU2, SU3, SU4, SU6, ING, PRO: variables de tipo real. */
void main (void)

{
    int CLA;
    float SU1, SU2, SU3, SU4, SU5, SU6, ING, PRO;
    printf("Ingrese la clave del empleado y los sueldos: \n");
    scanf("%d %f %f %f %f %f %f", &CLA, &SU2, &SU3, &SU4, &SU5, &SU6);
    ING = (SU1 + SU2 +SU3 +SU4 + SU5+ SU6);
    PRO =ING / 6;
    printf("*\n, %d %5.2f %5.2f", CLA, ING, PRO);
    return ;

}

//Este programa es para insertar la clave de los empleados y los sueldos//
