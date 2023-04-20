#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<time.h>


struct Tarea
{
    int TareaID;
    char* Descripcion;
    int Duracion; //entre 10 - 100
}typedef Tarea;


struct Nodo{
    Tarea T;
    struct Nodo* siguiente;
}typedef Nodo;

//typedef Nodo* lista;

void inicializarLista(Nodo** tareas);
Nodo* crearListaVacia();
Nodo* crearNodo(Tarea T);
Nodo* insertarNodoPrincipio(Nodo* Tareas,Tarea Tar);
void insertarNodoPrincipioDoblePuntero(Nodo** Tareas,Tarea T);
void MostrarTareas(Nodo* Tareas);


int main(){

    //lista tareasPendientes, tareasRealizadas;

    Nodo* tareasPendientes, tareasRealizadas;

    tareasPendientes = crearListaVacia();

   inicializarLista(&tareasPendientes);


    MostrarTareas(tareasPendientes);

    return 0;
}


Nodo* crearListaVacia(){
    return NULL;
}



void inicializarLista(Nodo** tareas){

    int nuevaT,dur,i = 1;
    Tarea Tar;
    

    printf("Desea ingresar una nueva tarea? 1:SI 0:NO:\n");
    scanf("%d",&nuevaT);

    while (nuevaT == 1)
    {
        char *buff = (char *)malloc(100 * sizeof(char));

        printf("ingrese la duracion de la tarea:\n");
        scanf("%d",&Tar.Duracion);
        printf("Ingrese la descripcion de la tarea?:\n");
        scanf("%s",buff);
        Tar.TareaID = i;
        i++;

        Tar.Descripcion =(char *) malloc(sizeof(char) * (strlen(buff)+1));

        strcpy(Tar.Descripcion,buff);

        free(buff);

       insertarNodoPrincipioDoblePuntero(tareas, Tar);

        printf("Desea ingresar una nueva tarea? 1:SI 0:NO:\n");
        scanf("%d",&nuevaT);
    }
    
}



Nodo* crearNodo(Tarea Tar){

    Nodo* nuevoNodo = (Nodo *)malloc(sizeof(Nodo));
    nuevoNodo->T= Tar;
    nuevoNodo->siguiente = NULL;
    return nuevoNodo;   

}

Nodo* insertarNodoPrincipio(Nodo* Tareas,Tarea T){

    Nodo* nuevo = crearNodo(T);
    nuevo->siguiente = Tareas;
    Tareas = nuevo;
    return nuevo;
}



void insertarNodoPrincipioDoblePuntero(Nodo** Tareas,Tarea T){

    Nodo* nuevo = crearNodo(T);
    nuevo->siguiente = *Tareas;
    *Tareas = nuevo;
}



void MostrarTareas(Nodo* Tareas){
    int i = 1;
    Nodo* aux = Tareas;       // ES NECESARIO PONER UNA VARAIABLE AUXILIAR? SI TRABAJO CON TAREA NO ME QUEDA LA CABECERA APUNTANDO A NULL?
    while (aux != NULL)
    {
        printf("-------------Tarea Numero %d:-----------------\n\n",i);
        printf("ID de la tarea: %d\n",aux->T.TareaID);
        printf("La duracion de la tarea es %d:\n",aux->T.Duracion);
        printf("La descripcion de la tarea es: %s\n",aux->T.Descripcion);


        aux = aux->siguiente;
        i++;
    }
    
}

