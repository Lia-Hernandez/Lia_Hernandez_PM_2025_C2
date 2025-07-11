#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estructura alumno//
typedef struct {
    char nombre[50];
    float promedio;
} Alumno;


void limpiarbuffer()//Para limpiar el bufer antes de seguir//
 {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


void anadirAlumno(const char *nombreArchivo) //Con esta funcion se anade el alumno al archivo //
{
    FILE *archivo = fopen(nombreArchivo, "ab");
    if (archivo == NULL) {
        perror("Error al abrir el archivo para añadir");
        return;
    }

    Alumno nuevoAlumno;
    printf("\n--- Añadir Nuevo Alumno ---\n");
    printf("Ingrese nombre del alumno (max 49 caracteres): ");
    // Usamos fgets para leer la línea completa, incluyendo espacios
    if (fgets(nuevoAlumno.nombre, sizeof(nuevoAlumno.nombre), stdin) != NULL)//Se uso fgets para asi poder leer tambien los espacios//
        {

        nuevoAlumno.nombre[strcspn(nuevoAlumno.nombre, "\n")] = '\0';
    } else {
        printf("Error al leer el nombre.\n");
        fclose(archivo); //Se cierra el archivo//
        return;
    }

    printf("Ingrese promedio del alumno: ");
    if (scanf("%f", &nuevoAlumno.promedio) != 1) { // Aqui nos dice si se leyo bien//
        printf("Entrada de promedio inválida. No se guardará el alumno.\n");
        limpiarbuffer();
        fclose(archivo);
        return;
    }
    limpiarbuffer();

    // Escribir la estructura completa en el archivo
    fwrite(&nuevoAlumno, sizeof(Alumno), 1, archivo);
    fclose(archivo);
    printf("Alumno '%s' guardado exitosamente.\n", nuevoAlumno.nombre);
}


int cargarAlumnos(const char *nombreArchivo, Alumno **listaAlumnos)//Con esta funcion cargamos todos los alumnos del archivo a la memoria//
 {
    FILE *archivo = fopen(nombreArchivo, "rb"); // Se abre en modo lectura binaria"
    if (archivo == NULL) {

        *listaAlumnos = NULL;
        return 0;
    }


    fseek(archivo, 0, SEEK_END); // Esto lo use para moverme al final del archivo//
    long tamanoArchivo = ftell(archivo); // Obtiene tamaño en bytes//
    int numAlumnos = tamanoArchivo / sizeof(Alumno); //
    fseek(archivo, 0, SEEK_SET); // Aqui se mueve al inicio del archivo//

    if (numAlumnos == 0) {
        fclose(archivo);
        *listaAlumnos = NULL;
        return 0;
    }


    *listaAlumnos = (Alumno *)malloc(numAlumnos * sizeof(Alumno));//Asigna memoria para los alumnos//
    if (*listaAlumnos == NULL) {
        perror("Error de asignación de memoria");
        fclose(archivo);
        return 0; // Indica error//
    }
    fread(*listaAlumnos, sizeof(Alumno), numAlumnos, archivo);//Lee los alumnos del archivo a la memoria//
    fclose(archivo);
    return numAlumnos; // Devuelve el número de alumnos cargados//
}
void swap(Alumno *a,Alumno *b)
{
    Alumno temp =*a;
    *a=*b;
    *b=temp;
}


void bubbleSortPorNombre(Alumno *arr, int n)//Aqui use el bubble sort para ordenar los nombres//
 {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {

            if (strcmp(arr[j].nombre, arr[j+1].nombre) > 0)//Aqui comparamos los nombres alfabeticamente//
                {
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
}

// Implementación de Bubble Sort para ordenar por promedio (descendente)
void bubbleSortPorPromedio(Alumno *arr, int n)//Otro bubble sort para ordenar por promedio//
 {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {

            if (arr[j].promedio < arr[j+1].promedio) //Se ordena de mayor a menor//
                {
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
}


// Se imprime la lista de alumnos//
void imprimirAlumnos(const Alumno *lista, int numAlumnos, const char *criterio) {
    if (numAlumnos == 0) {
        printf("\nNo hay alumnos para mostrar.\n");
        return;
    }

    printf("\nLista de Alumnos (%s)\n", criterio);
    printf("%-20s %-10s\n", "Nombre", "Promedio");
    printf("------------------------------\n");
    for (int i = 0; i < numAlumnos; i++) {
        printf("%-20s %-10.2f\n", lista[i].nombre, lista[i].promedio);
    }
    printf("\n");
}

int main() {
    const char *nombreArchivo = "alumnos.temp";
    Alumno *alumnosEnMemoria = NULL;
    int numAlumnos = 0;
    int opcion;
    int result_scanf;

    do {
        printf("\nMenu\n");
        printf("1. Añadir nuevo alumno\n");
        printf("2. Imprimir alumnos por nombre (orden alfabético)\n");
        printf("3. Imprimir alumnos por promedio (orden descendente)\n");
        printf("4. Salir\n");
        printf("Ingrese su opción: ");

        result_scanf = scanf("%d", &opcion); // Lee la opción y guarda el resultado//

        if (result_scanf != 1) { // Si se ingresó texto, sale este error//
            printf("Entrada inválida. Por favor, ingrese un número del 1 al 4.\n");
            limpiarbuffer();
            opcion = 0;
            continue; // Volvemos al inicio del bucle do-while
        }

        limpiarbuffer();

        switch (opcion) {
            case 1:
                anadirAlumno(nombreArchivo);
                break;
            case 2:
                // Cargar, ordenar e imprimir por nombre
                if (alumnosEnMemoria != NULL) {
                    free(alumnosEnMemoria);
                    alumnosEnMemoria = NULL;
                }
                numAlumnos = cargarAlumnos(nombreArchivo, &alumnosEnMemoria);
                if (numAlumnos > 0) {
                    bubbleSortPorNombre(alumnosEnMemoria, numAlumnos);
                    imprimirAlumnos(alumnosEnMemoria, numAlumnos, "Orden Alfabético");
                } else if (numAlumnos == 0) {
                    printf("No hay alumnos en el archivo para cargar.\n");
                }
                break;
            case 3:
                // Cargar, ordenar e imprimir por promedio
                if (alumnosEnMemoria != NULL) {
                    free(alumnosEnMemoria); // Liberar memoria de la carga anterior
                    alumnosEnMemoria = NULL;
                }
                numAlumnos = cargarAlumnos(nombreArchivo, &alumnosEnMemoria);
                if (numAlumnos > 0) {
                    bubbleSortPorPromedio(alumnosEnMemoria, numAlumnos);
                    imprimirAlumnos(alumnosEnMemoria, numAlumnos, "Orden por Promedio");
                } else if (numAlumnos == 0) {
                    printf("No hay alumnos en el archivo para cargar.\n");
                }
                break;
            case 4:
                printf("Saliendo del programa. ¡Hasta luego!\n");
                break;
            default:
                printf("Opción inválida. Intente de nuevo.\n");
        }
    } while (opcion != 4);


    if (alumnosEnMemoria != NULL) {
        free(alumnosEnMemoria);
    }

    return 0;
}
