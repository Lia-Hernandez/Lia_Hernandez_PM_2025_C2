#include <stdio.h>
#include <string.h>

/*Escuela.
El programa genera informacion estadistica de los alumnos de una escuela.*/

typedef struct     /*Declaracion de la estructura alumno utilizando un tyoedef.*/

{
int matricula;
char nombre[30];
float cal[5];
/*Observa que el campo de la estructura alumno es un arreglo unidimensional.*/
}alumno;

void Lectura(alumno A[], int T);
void F1(alumno A[],int TAM);        /*Prototipos de funciones.*/
void F2(alumno A[],int TAM);
void F3(alumno A[],int TAM);

void main(void)
{
alumno ARRE[50];      /*Se declara un arreglo unidimensional de tipo alumno.*/
int TAM;
do
{
printf("Ingrese el tamanio del arreglo: ");
scanf("%d", &TAM);
}
while(TAM>50 ||TAM<1);    /*Se verifica que el tamanio del arreglo sea correcto.*/

Lectura(ARRE,TAM);
F1(ARRE,TAM);
F2(ARRE,TAM);
F3(ARRE,TAM);
}

void Lectura(alumno A[],int T)
/*La funcion Lectura se utiliza para leer un arreglo unidimensional de tipo
estructura alumno de T elementos.*/
{
int I,J;
for (I=0;I<T;I++)
{
    printf("\nIngrese los datos del alumno %d",I+1);
    printf("\tIngrese la matricula del alumno: ");
    scanf("%d",&A[I].matricula);
    fflush(stdin);
    getchar();
    printf("Ingrese el nombre del alumno:");
    fgets(A[I].nombre,sizeof(A[I].nombre),stdin);
    A[I].nombre[strcspn(A[I].nombre, "\n")]=0;
    for (J=0;J<5; J++)
    {
        printf("\tIngrese la calificacion %d del alumno %d: ",J+1,I+1);
        scanf("%f",&A[I].cal[J]);
    }
}
}

void F1(alumno A[], int T)
/*La funcion F1 obtiene la matricula y el promedio de cada alumno.*/
{
int I,J;
float SUM,PRO;
for (I=0;I<T;I++)
{
    printf("\n\nMatricula del alumno: %d", A[I].matricula);
    SUM=0.0;
    for(J=0;J<5;J++)
        SUM=SUM+A[I].cal[J];
    PRO=SUM/5;
    printf("\tPromedio:%.2f",PRO);
}
}

void F2(alumno A[],int T)
/*La funcion F2 obtiene las matriculas de los alumnos cuya calificacion en la
tercera materia es mayor a 9.*/
{
int I;
printf("\nAlumnos con calificacion en la tercera materia >9");
for(I=0;I<T;I++)
    if (A[I].cal[2]>9)
    printf("\nMatricula del alumno: %d",A[I].matricula);
}

void F3(alumno A[], int T)
/*Esta funcion contiene el promedio general del gripo de la materia 4.*/
{
    int I;
    float PRO,SUM=0.0;
    for(I=0;I<T;I++)
        SUM=SUM+A[I].cal[3];
    PRO=SUM/T;
    printf("\n\nPromedio de la materia 4: %.2f",PRO);
}





