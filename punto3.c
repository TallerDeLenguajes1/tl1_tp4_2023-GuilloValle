#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<time.h>

/*------------------------*/
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

void cargarLista(Nodo** tareas);
Nodo* crearListaVacia();
Nodo* crearNodo(Tarea T);
Nodo* insertarNodoPrincipio(Nodo* Tareas,Tarea Tar);
void insertarNodoPrincipioDoblePuntero(Nodo** Tareas, Nodo* tar);  /* creaTarea  creanodo insertarnodo buscarnodo quitarNodo  eliminar */
void listarTareas(Nodo** TareasPendientes,Nodo** TareasRealizadas);
void MostrarTareas(Nodo* Tareas);
void Eliminar(Nodo* tareas);
void MostrarUnaTarea(Nodo* Tareas);
//void Mover(Nodo** t1,Nodo** t2);
Nodo* buscarTareaPorID(Nodo* tareasPendientes,Nodo* tareasRealizadas);
Nodo* buscarTareaPorPalabra(Nodo* tareasPendientes,Nodo* tareasRealizadas);
Nodo* quitarNodo(Nodo** tareas,int id);
void mostrarDatos(Nodo* tarea);


int main(){

    //lista tareasPendientes, tareasRealizadas;

    Nodo* tareasPendientes, *tareasRealizadas, *tareasEnProceso;
    int id, opcion;

    tareasPendientes = crearListaVacia();
    tareasRealizadas = crearListaVacia();
    tareasEnProceso = crearListaVacia();

    cargarLista(&tareasPendientes);

    printf("Tareas pendientes:\n");
    MostrarTareas(tareasPendientes);
    printf("------------------------------------------------\n");

    listarTareas(&tareasPendientes,&tareasRealizadas);

    printf("Tareas pendientes:\n");
    MostrarTareas(tareasPendientes);

    printf("\n");

    printf("\nTareas realizadas:\n");
    MostrarTareas(tareasRealizadas);
    printf("\n");

    Nodo * tareaBuscada = buscarTareaPorID(tareasPendientes,tareasRealizadas);

    printf("\n---------------------\n");
    
    buscarTareaPorPalabra(tareasPendientes,tareasRealizadas);

    printf("Seleccione el Id que quiere eliminar o mover:");
    scanf("%d", &id);
    printf("\n");
    printf("Si desea eliminar el nodo presione 1, si desea moverlo presione 2 y si no desea hacer nada presione 0:");
    scanf("%d", &opcion);
    printf("\n");

    if (opcion == 1)
    {
        
    }
    
    
    

    return 0;
}


Nodo* crearListaVacia(){
    return NULL;
}



void cargarLista(Nodo** tareas){

    int nuevaT,dur,i = 1;
    Tarea Tar;
    

    printf("Desea ingresar una nueva tarea? 1:SI 0:NO:");
    scanf("%d",&nuevaT);
    printf("\n");

    while (nuevaT == 1)
    {
        char *buff = (char *)malloc(100 * sizeof(char));
    
        printf("ingrese la duracion de la tarea:");
        scanf("%d",&Tar.Duracion);
        printf("\n");
        printf("Ingrese la descripcion de la tarea?:");
        scanf("%s",buff);
        printf("\n");
        Tar.TareaID = i;
        i++;

        Tar.Descripcion =(char *) malloc(sizeof(char) * (strlen(buff)+1));

        strcpy(Tar.Descripcion,buff);

        Nodo* nuevoNodo = crearNodo(Tar);

        free(buff);

       insertarNodoPrincipioDoblePuntero(tareas,nuevoNodo);
        
        printf("Desea ingresar una nueva tarea? 1:SI 0:NO: ");
        scanf("%d",&nuevaT);
        printf("\n");
    }
    
}

void listarTareas(Nodo** TareasPendientes,Nodo** TareasRealizadas){

    int SeRealizo;
    Nodo* aux;
    Nodo* listaAux = NULL;

    while ((*TareasPendientes) != NULL)
    {
        MostrarUnaTarea(*TareasPendientes);
        printf("Se realizo esta tarea? 1:SI 0:NO: ");
        scanf("%d",&SeRealizo);
        printf("\n");
        int id = (*TareasPendientes)->T.TareaID;

        if (SeRealizo == 1)
        {
            
            aux = quitarNodo(TareasPendientes,id);
            insertarNodoPrincipioDoblePuntero(TareasRealizadas,aux);
            /*aux = (*TareasPendientes);         //Asigno en aux el puntero de la tarea que se realizo
            (*TareasPendientes) = (*TareasPendientes)->siguiente;  //Muevo el puntero de tareas Pendientes para que en la siguiente linea no se mezclen
            aux->siguiente = (*TareasRealizadas); //apunto la tarea realizada a los nodos de tareas realizadas
            (*TareasRealizadas) = aux;  //apunto la cabecera a la tarea pendiente que recien entro (Se guarda primero)*/
    
        }else
        {
            aux = quitarNodo(TareasPendientes,id);
            insertarNodoPrincipioDoblePuntero(&listaAux,aux);
           /* aux = (*TareasPendientes);   //Asigno en aux el puntero de la tarea que no se realizo
            (*TareasPendientes) = (*TareasPendientes)->siguiente; //Muevo el puntero de tareas Pendientes para que en la siguiente linea no se mezclen o sea no me lo mueva desde aux a tareas pendientes
            aux->siguiente = listaAux; //voy guardando en una lista auxiliar las tareas pendientes
            listaAux = aux;*/
        }
        
        
        
    }
    
   (*TareasPendientes) = listaAux;   //asigno tareas pendientes a la cabecerea de la lista auxiliar en donde estan todas las tareas pendientess

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



void insertarNodoPrincipioDoblePuntero(Nodo** Tareas,Nodo* tar){

    tar = *Tareas;
    **Tareas = &tar;
}



void MostrarTareas(Nodo* Tareas){
    
    Nodo* aux = Tareas;       // ES NECESARIO PONER UNA VARAIABLE AUXILIAR? SI TRABAJO CON TAREA NO ME QUEDA LA CABECERA APUNTANDO A NULL?
    while (aux != NULL)
    {
        printf("-------------Tarea:-----------------\n\n");
        printf("ID de la tarea: %d\n",aux->T.TareaID);
        printf("La duracion de la tarea es %d:\n",aux->T.Duracion);
        printf("La descripcion de la tarea es: %s\n",aux->T.Descripcion);


        aux = aux->siguiente;
        
    }
    
}


void MostrarUnaTarea(Nodo* Tareas){

        printf("ID de la tarea: %d\n",Tareas->T.TareaID);
        printf("La duracion de la tarea es %d:\n",Tareas->T.Duracion);
        printf("La descripcion de la tarea es: %s\n",Tareas->T.Descripcion);
}


Nodo* buscarTareaPorID(Nodo* tareasPendientes,Nodo* tareasRealizadas){

    int id,bandera = 0;
    printf("Ingrese el id a buscar:");
    scanf("%d", &id);

    while (tareasPendientes != NULL)
    {
        if (tareasPendientes->T.TareaID == id)
        {
            MostrarUnaTarea(tareasPendientes);
            return(tareasPendientes);
            bandera = 1;
        }

        tareasPendientes = tareasPendientes->siguiente;
    }

    while (tareasRealizadas != NULL)
    {
        if (tareasRealizadas->T.TareaID == id)
        {
            MostrarUnaTarea(tareasRealizadas);
            return(tareasPendientes);
            bandera = 1;
        }

        tareasRealizadas = tareasRealizadas->siguiente;
    }
    
    if (bandera == 0)
    {
        printf("No existe ese id\n");
    }
    
}


Nodo* buscarTareaPorPalabra(Nodo* tareasPendientes,Nodo* tareasRealizadas){

    int bandera = 0;
    char* palabra;
    printf("Ingrese la palabra a buscar:");
    fflush(stdin);
    gets(palabra);
    printf("\n");

    while (tareasPendientes != NULL)
    {
        if (strstr(tareasPendientes->T.Descripcion,palabra) != NULL)
        {
  
            MostrarUnaTarea(tareasPendientes);
            return(tareasPendientes);
            bandera = 1;
        }
        
        tareasPendientes = tareasPendientes->siguiente;
    }

    while (tareasRealizadas != NULL)
    {
        if (strstr(tareasRealizadas->T.Descripcion,palabra) != NULL)
        {
  
            MostrarUnaTarea(tareasRealizadas);
            return(tareasPendientes);
            bandera = 1;
        }
        
        tareasRealizadas = tareasRealizadas->siguiente;
    }

    if (bandera == 0)
    {
        printf("No existe esa palabra\n");
    }
    
    
    
}


void Eliminar(Nodo* tarea){

    if (tarea != NULL)
    {
        free(tarea);
        printf("La tarea se elimino con exito\n");
    }else  
    {
        printf("La tarea no se elimino\n");
    }
    
}

Nodo* quitarNodo(Nodo** tarea,int id){  //desengache de la lista le paso un nodo

    Nodo* aux = *tarea;
    Nodo* auxAnterior = NULL;

    while (aux != NULL && aux->T.TareaID != id)
    {
        auxAnterior = aux;
        aux = aux->siguiente;
    }
    
    if (aux != NULL)
    {
        
        if (aux == *tarea) // Caso que sea el primer nodo
        {
            *tarea = aux->siguiente;
        }else
        {
            auxAnterior->siguiente = aux->siguiente; //saltea el nodo y se engancha con el siguinte, aca se produce el desenlace
        }
        
        aux->siguiente = NULL;
    }

    return aux;
    
    
    
}

void mostrarDatos(Nodo* tarea){

    int cant = 0;
    int duracionTotal = 0;
    while (tarea != NULL)
    {   
        cant++;
        duracionTotal = duracionTotal + tarea->T.Duracion;
        tarea = tarea->siguiente;
    }

    printf("la cantidad de tareas que tiene es %d\n",cant);
    printf("la duracion de las tareas es %d\n",duracionTotal);
    
}
