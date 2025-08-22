#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOM_vehiculos "vehiculos.dat"
#define NOM_precios "precios.dat"
typedef struct
{ char marca[50];
char matricula[20];
char modelo[50];
char combustible[20];
float km_x_galon_max;
float km_x_galon_min;
float costo_gomasfijo;
int km_para_gomas;
float costo_mantenimientofijo;
int km_para_mantenimiento;
int vidaUtil;
int km_anuales_promedio;
float depreciacion_anualfija;
float costo_seguroanual;
float costo_vehiculo;
}Vehiculo;

typedef struct{
float precio_gasolina;
float precio_gasoil;
}Preciocombustible;

void mostrar_Menu();
void Agregar_vehiculo(Vehiculo ** lista,int* n);
void editar_vehiculo(Vehiculo* lista, int n);
void eliminar_vehiculo(Vehiculo** lista,int *n);
void selec_vehiculo_calcula(Vehiculo* lista,int n,Preciocombustible precios);
void mostrar_costos(float km_recorrer,float porc_carreterra,float porc_ciudad,Vehiculo v,Preciocombustible precios);
void act_precio_combustible(Preciocombustible* precios);
void guardar_datos(Vehiculo* lista,int n,Preciocombustible precios);
void cargar_datos(Vehiculo** lista,int* n,Preciocombustible* precios);
void mostrar_vehiculos(Vehiculo* lista, int n);

int main(){
int opcion=0;
Vehiculo* lista_vehiculos=NULL;
int num_vehiculos=0;
Preciocombustible precios;
cargar_datos(&lista_vehiculos,&num_vehiculos,&precios);
do{
    mostrar_Menu();
    printf("Ingrese su opcion: ");
    scanf("%d",&opcion);
    switch(opcion){
    case 1:Agregar_vehiculo(&lista_vehiculos,&num_vehiculos);
    break;
    case 2: if(num_vehiculos>0){editar_vehiculo(lista_vehiculos,num_vehiculos);
    }else{
    printf("\nNo hay vehiculos para editar.\n");
    }
    break;
    case 3:
        if(num_vehiculos>0){eliminar_vehiculo(&lista_vehiculos,&num_vehiculos);
        }else{
        printf("\nNo hay vehiculos para eliminar.\n");
        }break;
    case 4: if(num_vehiculos>0){selec_vehiculo_calcula(lista_vehiculos,num_vehiculos,precios);
    }else{
    printf("\nNo hay vehiculos registrados.\n");
    }
    break;
    case 5:act_precio_combustible(&precios);
    break;
    case 6:if(num_vehiculos>0){mostrar_vehiculos(lista_vehiculos,num_vehiculos);
    }else{
        printf("No hay vehiculos registrados\n");}
    break;
    case 7:guardar_datos(lista_vehiculos,num_vehiculos,precios);
    printf("\nGuardando datos y saliendo del programa.\n");
    break;
    default:
        printf("\nOpcion no valida.Intente de nuevo.\n");
        break;
}
printf("\n");
}while(opcion !=7);
free(lista_vehiculos);
return 0;
}
void mostrar_Menu(){
printf("----Menu de Opciones----\n");
printf("1.Agregar un vehiculo\n");
printf("2.Editar un vehiculo\n");
printf("3.Eliminar un vehiculo\n");
printf("4.Calcular el costo de viaje\n");
printf("5.Actualizar precios del combustible\n");
printf("6.Mostrar los vehiculos registrados\n");
printf("7.Guardar y salir\n");
}
void Agregar_vehiculo(Vehiculo** lista,int* n)
{*lista =(Vehiculo*)realloc(*lista,(*n+1)* sizeof(Vehiculo));
if(*lista==NULL){
    printf("No se pudo asignar memoria.\n");
    exit(1);
}
printf("\n----AGREGAR VEHICULO----\n");
printf("Marca: ");
scanf(" %49[^\n]",(*lista)[*n].marca);
printf("Matricula:");
scanf(" %19[^\n]",(*lista)[*n].matricula);
printf("Modelo:");
scanf(" %49[^\n]",(*lista)[*n].modelo);
printf("Tipo de combustible (Gasolina/Gasoil):");
scanf(" %19[^\n]",(*lista)[*n].combustible);
printf("Km por galon(carretera): ");
scanf("%f",&(*lista)[*n].km_x_galon_max);
printf("Km por galon (ciudad): ");
scanf("%f",&(*lista)[*n].km_x_galon_min);
printf("Costo de gomas: ");
scanf("%f",&(*lista)[*n].costo_gomasfijo);
printf("Kilometraje para cambio de gomas:");
scanf("%d",&(*lista)[*n].km_para_gomas);
printf("Costo de mantenimiento:");
scanf("%f",&(*lista)[*n].costo_mantenimientofijo);
printf("Kilometraje para mantenimiento:");
scanf("%d",&(*lista)[*n].km_para_mantenimiento);
printf("Costo de seguro anual: ");
scanf("%f",&(*lista)[*n].costo_seguroanual);
printf("Costo total de vehiculo:");
scanf("%f",&(*lista)[*n].costo_vehiculo);
printf("Vida util (Anios):");
scanf("%d",&(*lista)[*n].vidaUtil);
printf("Kilometraje promedio anual:");
scanf("%d",&(*lista)[*n].km_anuales_promedio);
printf("Monto de depreciacion anual(ej:20000):");
scanf("%f",&(*lista)[*n].depreciacion_anualfija);
(*n)++;
printf("\nVehiculo agregado correctamente.\n");
}
void editar_vehiculo(Vehiculo* lista ,int n){
int selec_vehiculo,selec_campo;
printf("\n----EDITAR VEHICULO----\n");
for(int i=0;i<n;i++){
 printf("%d. %s %s (%s)\n",i + 1,lista[i].marca,lista[i].modelo,lista[i].matricula);
}
printf("Seleccione el vehiculo a editar (1 a %d):",n);
scanf("%d",&selec_vehiculo);

if(selec_vehiculo<1 ||selec_vehiculo>n){
    printf("Seleccion no valida.\n");
    return;
}
printf("\n----CAMPOS A EDITAR----\n");
printf("1.Marca\n");
printf("2.Matricula\n");
printf("3.Modelo\n");
printf("4.Tipo de combustible\n");
printf("5.Km /galon en carreterra\n");
printf("6.Km/galon en ciudad\n");
printf("7.Depreciacion anual\n");
printf("8.Costo de gomas\n");
printf("9.Kilometraje para cambio de gomas\n");
printf("10.Costo de mantenimiento\n ");
printf("11.Kilometraje para mantenimiento\n");
printf("12.Costo de seguro anual\n");
printf("13.Costo de vehiculo\n");
printf("14.Km anuales promedio\n");
printf("15.Vida util\n");

printf("Ingrese el numero del campo que desea editar: ");
scanf("%d",&selec_campo);
switch(selec_campo){
case 1: printf("Nueva marca: ");
scanf(" %49[^\n]",lista[selec_vehiculo-1].marca);
break;
case 2:printf("Nueva matricula:");
scanf(" %19[^\n]",lista[selec_vehiculo-1].matricula);
break;
case 3:printf("Nuevo modelo:");
scanf(" %49[^\n]",lista[selec_vehiculo-1].modelo);
break;
case 4:printf("Nuevo tipo de combustible(Gasolina/Gasoil):");
scanf(" %19[^\n]",lista[selec_vehiculo-1].combustible);
break;
case 5:printf("Nueva km/galon en carretera: ");
scanf(" %f",&lista[selec_vehiculo-1].km_x_galon_max);
    break;
case 6:printf("Nueva km/galon en ciudad: ");
scanf("%f",&lista[selec_vehiculo-1].km_x_galon_min);
    break;
case 7:printf("Nueva depreciacion anual: ");
scanf("%f",&lista[selec_vehiculo-1].depreciacion_anualfija);
    break;
case 8:printf("Nuevo costo de gomas: ");
scanf("%f",&lista[selec_vehiculo-1].costo_gomasfijo);
break;
case 9:printf("Nuevo kilometraje para cambio de gomas: ");
scanf("%d",&lista[selec_vehiculo-1].km_para_gomas);
break;
case 10:printf("Nuevo costo de mantenimiento: ");
scanf("%f",&lista[selec_vehiculo-1].costo_mantenimientofijo);
break;
case 11:printf("Nuevo kilometraje para mantenimiento: ");
scanf("%d",&lista[selec_vehiculo-1].km_para_mantenimiento);
break;
case 12:printf("Nuevo costo de seguro anual:");
scanf("%f",&lista[selec_vehiculo-1].costo_seguroanual);
break;
case 13:printf("Nuevo costo de vehiculo: ");
scanf("%f",&lista[selec_vehiculo-1].costo_vehiculo);
break;
case 14:printf("Nueva km anuales promedio: ");
scanf("%d",&lista[selec_vehiculo-1].km_anuales_promedio);
break;
case 15: printf("Nueva vida util (anios): ");
scanf("%d",&lista[selec_vehiculo-1].vidaUtil);
break;
default:
    printf("Opcion no valida.\n");
    return;}
    printf("\nVehiculo editado exitosamente.\n");
}
void eliminar_vehiculo(Vehiculo** lista,int* n)
{
    int seleccion;
    printf("\n----Eliminar Vehiculo----\n");
    for(int i=0;i<*n;i++){
        printf("%d. %s %s (%s)\n",i+1,(*lista)[i].marca,(*lista)[i].modelo,(*lista)[i].matricula);
        }
        printf("Seleccione el vehiculo a eliminar (1 a %d):",*n);
        scanf("%d",&seleccion);
        if(seleccion<1||seleccion >*n){
            printf("Seleccion no valida.\n");
            return;
        }
        for(int i=seleccion-1;i<*n-1;i++){
            (*lista)[i]=(*lista)[i+1];
        }
        (*n)--;
        *lista=(Vehiculo*)realloc(*lista,(*n)*sizeof(Vehiculo));
        printf("\nVehiculo eliminado.\n");
}
void selec_vehiculo_calcula(Vehiculo* lista,int n, Preciocombustible precios){
int seleccion=0;
float km_recorrer,porc_carretera,porc_ciudad;
printf("\n----SELECCION DE VEHICULO----\n");
for(int i=0;i<n;i++){
    printf("%d. %s %s (%s)\n",i+1,lista[i].marca,lista[i].modelo,lista[i].matricula);
}
printf("Seleccione un vehiculo (1 a %d):",n);
scanf("%d",&seleccion);
if(seleccion<1 ||seleccion>n){
    printf("Seleccion no valida.\n");
    return;
}
printf("Kilometros a recorrer: ");
scanf("%f",&km_recorrer);
printf("Porcentaje en carretera (0-100):");
scanf("%f",&porc_carretera);
printf("Porcentaje en ciudad (0-100):");
scanf("%f",&porc_ciudad);
if(porc_carretera + porc_ciudad !=100){
    printf("La suma de los porcentajes no es 100.\n");
    return;
}
mostrar_costos(km_recorrer,porc_carretera,porc_ciudad,lista[seleccion-1],precios);
}
void mostrar_costos(float km_recorrer,float porc_carretera,float porc_ciudad,Vehiculo v,Preciocombustible precios){
float costo_gl_combustible;
if(strcmp(v.combustible,"Gasolina")==0){
    costo_gl_combustible=precios.precio_gasolina;
    }else if(strcmp(v.combustible,"Gasoil")==0){
    costo_gl_combustible=precios.precio_gasoil;
    }else{
    printf("Tipo de combustible no reconocido. No se puede calcular el costo del viaje.\n");
    return;
    }
    float porc_carretera_dec=porc_carretera/100.0;
    float porc_ciudad_dec=porc_ciudad/100.00;
    float km_x_galon_promedio=(v.km_x_galon_min *porc_ciudad_dec)+(v.km_x_galon_max*porc_carretera_dec);
    float costo_combustible_km=(km_x_galon_promedio >0)?(costo_gl_combustible/km_x_galon_promedio):0;
    float costo_gomas_km=(v.km_para_gomas >0)?(v.costo_gomasfijo/v.km_para_gomas):0;
    float costo_mantenimiento_km=(v.km_para_mantenimiento>0)?(v.costo_mantenimientofijo/v.km_para_mantenimiento):0;
    float costo_seguro_km=(v.km_anuales_promedio>0)?(v.costo_seguroanual/(float)v.km_anuales_promedio):0;
    float costo_depreciacion_anual_km=(v.km_anuales_promedio>0)?(v.depreciacion_anualfija/(float)v.km_anuales_promedio):0;
    float costo_total_km=costo_combustible_km+costo_gomas_km+costo_mantenimiento_km+costo_seguro_km+costo_depreciacion_anual_km;
    float costo_total_recorrido=costo_total_km * km_recorrer;
    float total_combustible=costo_combustible_km *km_recorrer;
    float total_gomas=costo_gomas_km * km_recorrer;
    float total_seguro=costo_seguro_km * km_recorrer;
    float total_depreciacion=costo_depreciacion_anual_km * km_recorrer;
    float total_mantenimiento=costo_mantenimiento_km * km_recorrer;
printf("\n----Costos del viaje----\n");
printf("Vehiculo seleccionado: %s %s (%s)\n",v.marca,v.modelo,v.matricula);
printf("Kilometros a recorrer: %.2f km\n",km_recorrer);
printf("Costo por kilometro: $%.2f\n",costo_total_km);

printf("\n----DESGLOSE DE COSTO TOTAL ($%.2f)----\n",costo_total_recorrido);
printf("Combustible: $%.2f\n",total_combustible);
printf("Gomas: $%.2f\n",total_gomas);
printf("Mantenimiento: $%.2f\n",total_mantenimiento);
printf("Seguro: $%.2f\n",total_seguro);
printf("Depreciacion: $%.2f\n",total_depreciacion);
}
void act_precio_combustible(Preciocombustible*precios){
printf("\n----ACTUALIZAR LOS PRECIOS DE LOS COMBUSTIBLES----\n");
printf("Precio actual de la gasolina: $%.2f\n",precios->precio_gasolina);
printf("Nuevo precio de la gasolina:");
scanf("%f",&precios->precio_gasolina);
printf("Precio actual del gasoil: $%.2f\n",precios->precio_gasoil);
printf("Nuevo precio del gasoil: ");
scanf("%f",&precios->precio_gasoil);
printf("\nPrecios actualizados exitosamente.\n");
}
void mostrar_vehiculos(Vehiculo* lista, int n){
if(n==0){
    printf("\nNo hay vehiculos registrados.\n");
    return;
}
printf("\n----VEHICULOS REGISTRADOS----\n");
for(int i=0;i<n;i++){
    printf("\n----Vehiculo %d----\n",i+1);
    printf("Marca: %s\n",lista[i].marca);
    printf("Modelo: %s\n",lista[i].modelo);
    printf("Matricula: %s\n",lista[i].matricula);
    printf("Combustible: %s\n", lista[i].combustible);
    printf("Km/galon (carretera): %.2f\n",lista[i].km_x_galon_max);
    printf("Km/galon (ciudad): %.2f\n",lista[i].km_x_galon_min);
    printf("Costo vehiculo: $%.2f\n", lista[i].costo_vehiculo);
    }
}
void guardar_datos(Vehiculo* lista,int n,Preciocombustible precios){
FILE* archivo_vehiculos=fopen(NOM_vehiculos,"wb");
if(archivo_vehiculos !=NULL){
    fwrite(&n,sizeof(int),1,archivo_vehiculos);
    fwrite(lista,sizeof(Vehiculo),n,archivo_vehiculos);
    fclose(archivo_vehiculos);
}
FILE* archivo_precios=fopen(NOM_precios,"wb");
if(archivo_precios !=NULL){
    fwrite(&precios,sizeof(Preciocombustible),1,archivo_precios);
    fclose(archivo_precios);
    }
}
void cargar_datos(Vehiculo** lista, int* n,Preciocombustible* precios){
FILE* archivo_vehiculos=fopen(NOM_vehiculos,"rb");
if(archivo_vehiculos !=NULL){
    fread(n,sizeof(int),1,archivo_vehiculos);
    *lista=(Vehiculo*)malloc(*n * sizeof(Vehiculo));
    if(*lista==NULL){
        printf("No se pudo asignar memoria al cargar los datos.\n");
        exit(1);
    }
    fread(*lista,sizeof(Vehiculo),*n,archivo_vehiculos);
    fclose(archivo_vehiculos);
    printf("Se cargaron %d vehiculos de %s,\n",*n,NOM_vehiculos);
    }else{
    *n=0;
    printf("No se encontro un archivo de vehiculo guardado.\n");
    }
    FILE* archivo_precios=fopen(NOM_precios,"rb");
    if(archivo_precios !=NULL){
        fread(precios,sizeof(Preciocombustible),1,archivo_precios);
        fclose(archivo_precios);
        printf("Se cargaron los precios de combustible\n");
        }else{
        precios->precio_gasolina=0;
        precios->precio_gasoil=0;
        printf("No se encontro un archivo con los precios de combustible guardado. Los precios estan en 0.\n");
        }
}



