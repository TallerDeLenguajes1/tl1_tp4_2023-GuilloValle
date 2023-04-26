#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<time.h>


struct Tarea
{
    int TareaID;
    char *Descripcion;
    int Duracion; //entre 10 - 100
}typedef Tarea;

void inicializarArreglo(Tarea **arreglo, int cantidad); //Inicializa en NULL todos los punteros
void cargarTareas(Tarea **arreglo, int cantidad);  
void controlarTareas(Tarea **arregloPendientes,Tarea **arregloRealizadas, int cantidad);
void mostrarTareas(Tarea **arreglo, int cantidad);
void buscarTareaPorID(Tarea **arregloPendientes,Tarea **arregloRealizados, int cantidad );
void buscarTareaPorPalabra(Tarea **arregloPendientes,Tarea **arregloRealizados, int cantidad  );
void liberarMemoria(Tarea **arreglo, int cantidad);


int main(){

    int cantTareas;

    printf("Cuantas tareas debe cargar?:");
    scanf("%d",&cantTareas);

   Tarea **tareasSolicitadas = (Tarea **) malloc(sizeof(Tarea *) * cantTareas);

   Tarea **tareasRealizadas = (Tarea **) malloc(sizeof(Tarea *) * cantTareas);

    inicializarArreglo(tareasSolicitadas,cantTareas); //Inicializo las tareas sol en NULL

    inicializarArreglo(tareasRealizadas,cantTareas);  //Inicializo las tareas real en NULL

    cargarTareas(tareasSolicitadas,cantTareas);  //Cargo las tareas a sol

    controlarTareas(tareasSolicitadas, tareasRealizadas, cantTareas);  // controlo cual tarea se realizo y cual no


    printf("----Tareas pendientes ----\n");
    mostrarTareas(tareasSolicitadas, cantTareas);

    printf("----Tareas realizadas ----\n");
    mostrarTareas(tareasRealizadas, cantTareas);


    buscarTareaPorID(tareasSolicitadas,tareasRealizadas,cantTareas);

    buscarTareaPorPalabra(tareasSolicitadas,tareasRealizadas,cantTareas);


    liberarMemoria(tareasSolicitadas,tareasRealizadas);




    return 0;
}


void inicializarArreglo(Tarea **arreglo, int cantidad){

        for (int i = 0; i < cantidad; i++)
        {
            arreglo[i] = NULL;
        }
        
}

void cargarTareas(Tarea **arreglo, int cantidad){

    

    for (int i = 0; i < cantidad; i++)
    {

        char *buff = (char *)malloc(100 * sizeof(char));

        arreglo[i] = (Tarea *) malloc(sizeof(Tarea));
       
        arreglo[i]->TareaID = i;

        printf("Ingrese la descripcion de la tarea:\n");
        scanf("%s",buff);

        arreglo[i]->Descripcion =(char *) malloc(sizeof(char) * (strlen(buff)+1));
        
        strcpy(arreglo[i]->Descripcion,buff);

        free(buff);

        printf("Ingrese la duracion de la tarea:\n");
        scanf("%d",&arreglo[i]->Duracion);

        

    }
    
}


void controlarTareas(Tarea **arregloPendientes,Tarea **arregloRealizadas, int cantidad){

    int seRealizo;
    for (int i = 0; i < cantidad; i++)
    {
        
        printf("Se realizo la tarea? SI:1 , NO:2\n");
        scanf("%d",&seRealizo);

        if (seRealizo == 1)
        {
            
            arregloRealizadas[i] = arregloPendientes[i];
            arregloPendientes[i] = NULL;

        }
        

    }
    
}

void mostrarTareas(Tarea **arreglo, int cantidad){

    for (int i = 0; i < cantidad; i++)
    {   
        if (arreglo[i] != NULL)
        {
            printf("------------------- Tarea Num %d -------------------\n",i+1);
            printf("ID de la tarea: %d\n",arreglo[i]->TareaID);
            printf("Descripcion: %s\n",arreglo[i]->Descripcion);
            printf("Duracion: %d\n",arreglo[i]->Duracion);

        } else
        {
            printf("La tarea Num %d esta en NULL\n", i+1);
        }
        
        
        
    }
    
}


void buscarTareaPorID(Tarea **arregloPendientes,Tarea **arregloRealizados, int cantidad){

    int ID;
    printf("Ingrese el ID a buscar:");
    scanf("%d",&ID);

    for (int i = 0; i < cantidad; i++)
    {
        
        if (arregloPendientes[i] != NULL && arregloPendientes[i]->TareaID == ID)
        {
            printf("------------------- Tarea Num %d (pendiente) -------------------\n",i+1);
            printf("ID de la tarea: %d\n",arregloPendientes[i]->TareaID);
            printf("Descripcion: %s\n",arregloPendientes[i]->Descripcion);
            printf("Duracion: %d\n",arregloPendientes[i]->Duracion);
            break;

        }

        if (arregloRealizados[i] != NULL && arregloRealizados[i]->TareaID == ID)
        {
            printf("------------------- Tarea Num %d (Realizado) -------------------\n",i+1);
            printf("ID de la tarea: %d\n",arregloRealizados[i]->TareaID);
            printf("Descripcion: %s\n",arregloRealizados[i]->Descripcion);
            printf("Duracion: %d\n",arregloRealizados[i]->Duracion);
            break;
        }
        
        
    }

    printf("No existe ese ID\n");
    
    
}

void buscarTareaPorPalabra(Tarea **arregloPendientes,Tarea **arregloRealizados, int cantidad ){
 
    char* cadenaAbuscar;
    printf("Ingrese la descripcion a buscar");
    scanf("%s",cadenaAbuscar);

    for (int i = 0; i < cantidad; i++)
    {
        
        if (arregloPendientes[i] != NULL && strstr(arregloPendientes[i]->Descripcion,cadenaAbuscar) != NULL)
        {
            printf("------------------- Tarea Num %d (pendiente) -------------------\n",i+1);
            printf("ID de la tarea: %d\n",arregloPendientes[i]->TareaID);
            printf("Descripcion: %s\n",arregloPendientes[i]->Descripcion);
            printf("Duracion: %d\n",arregloPendientes[i]->Duracion);

        }

        if (arregloRealizados[i] != NULL && strstr(arregloRealizados[i]->Descripcion,cadenaAbuscar) != NULL)
        {
            printf("------------------- Tarea Num %d (Realizado) -------------------\n",i+1);
            printf("ID de la tarea: %d\n",arregloRealizados[i]->TareaID);
            printf("Descripcion: %s\n",arregloRealizados[i]->Descripcion);
            printf("Duracion: %d\n",arregloRealizados[i]->Duracion);
        }
        
        
    }
}

void liberarMemoria(Tarea **arreglo, int cantidad){

    for (int i = 0; i < cantidad; i++)
    {   
        if (arreglo[i] != NULL)
        {
            free(arreglo[i]->Descripcion);
        }
        
        free(arreglo[i]);
    }

    free(arreglo);
    
}