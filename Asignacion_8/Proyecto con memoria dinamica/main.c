#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char nombre[50];
    float promedio;
}Alumno;

void Limpiar()
{
    int d;
    while((d=getchar()) !='\n' &&d!=EOF);
}

void Grabadisco(const char *nombrearchivo)
{
    FILE *archivo=fopen(nombrearchivo,"ab");
    if(archivo ==NULL)
    {
        perror("Error al abrir el archivo para escribir");
        return;
    }

    Alumno *nueAlumno =(Alumno *)malloc (sizeof(Alumno));
    if(nueAlumno==NULL)
    {
        perror("Error al asignar memoria para el nuevo alumno");
        fclose(archivo);
        return;
    }
    printf("\nGraba alumno nuevo\n");
    printf("Ingrese nombre del alumno:");
    if(fgets(nueAlumno->nombre,sizeof(nueAlumno->nombre),stdin) !=NULL)
    {
        nueAlumno->nombre[strcspn(nueAlumno->nombre,"\n")]= '\0';}
        else
        {
            printf("Error al leer el nombre.\n");
            free(nueAlumno);
            fclose(archivo);
            return;
        }
        printf("Ingrese promedio del alumno:");
        if(scanf("%f",&nueAlumno->promedio) !=1)
        {
            printf("Entrada de promedio puesta incorrectamente.No se guardara.\n");
            free(nueAlumno);
            fclose(archivo);
            Limpiar();
            return;
        }
        Limpiar();
        fwrite(nueAlumno,sizeof(Alumno),1,archivo);
        printf("Alumno '%s' guardado en disco.\n", nueAlumno->nombre);
        free(nueAlumno);
        fclose(archivo);
        }
        Alumno* leeralumnodis(const char *nombreArchivo, int *numAlumnos)
        {
            FILE *archivo=fopen(nombreArchivo,"rb");
            if(archivo ==NULL)
            {
                *numAlumnos=0;
                return NULL;
            }
            fseek(archivo,0,SEEK_END);
            long tamanoarch=ftell(archivo);
            *numAlumnos=tamanoarch/sizeof(Alumno);

            if(*numAlumnos==0)
            {
                fclose(archivo);
                return NULL;
            }
            Alumno *listaAlumnos=(Alumno *)malloc(*numAlumnos * sizeof(Alumno));
            if(listaAlumnos==NULL)
            {
                perror("Error al asignar memoria para la lista de alumnos");
                fclose(archivo);
                *numAlumnos=0;
                return NULL;
            }

        fseek(archivo,0,SEEK_SET);
        fread(listaAlumnos,sizeof(Alumno),*numAlumnos,archivo);
        printf("\n%d alumnos leidos desde el disco.\n",*numAlumnos);
        fclose(archivo);
        return listaAlumnos;
        }
        int main()
        {
            const char *nombreArchivo="alumnos.temp";
            Alumno *alumnosENMEMORIA=NULL;
                int numAlumnos=0;
                int opcion;
                int result_scanf;
                do{
                    printf("\nMenu\n");
                    printf("1.Grabar nuevo alumno en disco\n");
                    printf("2.Leer todos los alumnos del disco y mostrar\n");
                    printf("3.Salir\n");
                    printf("Ingrese su opcion:");

                    result_scanf=scanf("%d",&opcion);
                    if (result_scanf !=1)
                    {
                        printf("Entrada invalida.Ingrese un numero del 1 al 3\n");
                        Limpiar();
                        opcion=0;
                        continue;
                        }
                        Limpiar();
                        switch(opcion)
                        {
                            case 1:Grabadisco(nombreArchivo);
                            break;
                            case 2:if(alumnosENMEMORIA !=NULL)
                            {
                                free(alumnosENMEMORIA);
                                alumnosENMEMORIA=NULL;
                            }
                            alumnosENMEMORIA=leeralumnodis(nombreArchivo,&numAlumnos);
                            if(numAlumnos >0 &&alumnosENMEMORIA !=NULL)
                            {
                                printf("\nLista de gente en memoria\n");
                                printf("%-20s %-10s\n","Nombre","Promedio");
                                printf("\n");

                                Alumno *ptrActual=alumnosENMEMORIA;
                                for(int i=0; i<numAlumnos; i++)
                                {
                                    printf("%-20s %-10.2f\n", ptrActual->nombre,ptrActual->promedio);
                                    ptrActual++;
                                    }
                                    printf("\n");
                                    }
                                    else if(numAlumnos==0)
                                    {
                                        printf("No hay alumnos guardados o el archivo esta vacio\n");
                                    }
                                    break;
                            case 3:printf("\nBye, se acabo\n");
                            break;
                            default:
                                printf("Opcion no valida.Intente de nuevo mas tarde.\n");
                        }
                }while(opcion !=3);
                if(alumnosENMEMORIA !=NULL)
               {
                free(alumnosENMEMORIA);
                alumnosENMEMORIA=NULL;
        }
        return 0;
        }
