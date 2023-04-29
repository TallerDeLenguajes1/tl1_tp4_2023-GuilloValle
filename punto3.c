#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
Tarea crearTarea(int id);
Nodo* crearNodo(Tarea T);
Nodo* insertarNodoPrincipio(Nodo* Tareas,Tarea Tar);
void insertarNodoPrincipioDoblePuntero(Nodo** Tareas, Nodo* tar);  /* creaTarea  creanodo insertarnodo buscarnodo quitarNodo  eliminar */
void listarTareas(Nodo** TareasPendientes,Nodo** TareasRealizadas,Nodo** TareasEnProceso);         //FALTA HACER INSERTAR NODO AL FINAL, Y QUE MAS?
void MostrarTareas(Nodo* Tareas);
void EliminarNodo(Nodo* tareas);
void MostrarUnaTarea(Nodo* Tareas);
Nodo* buscarTareaPorID(Nodo* tareas, int id);
Nodo* buscarTareaPorPalabra(Nodo* tareas,char* palabra);
Nodo* quitarNodo(Nodo** tareas,int id);
void mostrarDatos(Nodo* tarea);
void liberarLista(Nodo** tarea);


int main(){

    //lista tareasPendientes, tareasRealizadas;
    srand(time(NULL));

    Nodo* tareasPendientes, *tareasRealizadas, *tareasEnProceso;
    int id, opcion;

    tareasPendientes = crearListaVacia();
    tareasRealizadas = crearListaVacia();
    tareasEnProceso = crearListaVacia();

    cargarLista(&tareasPendientes);

    printf("Tareas pendientes:\n");
    MostrarTareas(tareasPendientes);
    printf("------------------------------------------------\n");

    listarTareas(&tareasPendientes,&tareasRealizadas,&tareasEnProceso);

    printf("Tareas pendientes:\n");
    MostrarTareas(tareasPendientes);

    printf("\n");

    printf("Tareas en proceso:\n");
    MostrarTareas(tareasEnProceso);

    printf("\n");

    printf("\nTareas realizadas:\n");
    MostrarTareas(tareasRealizadas);
    printf("\n");
    printf("\n");
    
    
    int enQueListaEsta=0;
    int mov;

    printf("Desea mover o eliminar algun nodo 1:SI 0:NO ?");
    scanf("%d",&mov);

    while (mov != 0)
    {   

        printf("Seleccione el Id que quiere eliminar o mover:");
        scanf("%d", &id);
        printf("\n");
        printf("Si desea eliminar el nodo presione 1, si desea moverlo presione 2 y si no desea hacer nada presione 0:");
        scanf("%d", &opcion);
        printf("\n");


        if (buscarTareaPorID(tareasPendientes,id))  //ME FIJO EN QUE LISTA ESTA EL ID
            {
                enQueListaEsta = 1;
            }else{ 
                if (buscarTareaPorID(tareasEnProceso,id))
                {
                enQueListaEsta = 2;
                }else{
                    if (buscarTareaPorID(tareasRealizadas,id))
                    {
                        enQueListaEsta = 3;
                    }else
                        {
                            printf("No existe ese id\n");
                        }
                        
                    }
            }

    Nodo* auxil;     
    
    if (opcion == 1) //ELIMINO
    {   
        switch (enQueListaEsta)
        {
        case 1:
            auxil = quitarNodo(&tareasPendientes,id);
            EliminarNodo(auxil);
            break;
        case 2:
            auxil = quitarNodo(&tareasEnProceso,id);
            EliminarNodo(auxil);
            break;
        case 3:
            auxil = quitarNodo(&tareasRealizadas,id);
            EliminarNodo(auxil);
            break;    
        default:
            break;
        }
    }

    if (opcion == 2) //MUEVO
    {   
        int sel;
        switch (enQueListaEsta)
        {
        case 1: //tareas pendientes
            printf("selecione a la lista que quiere mover el nodo:\n");
            printf("-tareas realizadas (1):\n");
            printf("-tareas en proceso (2):\n");
            scanf("%d",&sel);
            auxil = quitarNodo(&tareasPendientes,id);

            switch (sel)
            {
            case 1:
                insertarNodoPrincipioDoblePuntero(&tareasRealizadas,auxil);
                break;
            case 2:
                insertarNodoPrincipioDoblePuntero(&tareasEnProceso,auxil);
                break;
            default:
                break;
            }
            break;

        case 2: //tareas en proceso         
            printf("selecione a la lista que quiere mover el nodo:\n");
            printf("-tareas realizadas (1):\n");
            printf("-tareas pendientes (2):\n");
            scanf("%d",&sel);
            auxil = quitarNodo(&tareasEnProceso,id);

            switch (sel)
            {
            case 1:
                insertarNodoPrincipioDoblePuntero(&tareasRealizadas,auxil);
                break;
            case 2:
                insertarNodoPrincipioDoblePuntero(&tareasPendientes,auxil);
                break;
            default:
                break;
            }

            break;

        case 3: //tareas realizadas           
            printf("selecione a la lista que quiere mover el nodo:\n");
            printf("-tareas pendientes (1):\n");
            printf("-tareas en proceso (2):\n");
            scanf("%d",&sel);
            auxil = quitarNodo(&tareasRealizadas,id);

            switch (sel)
            {
            case 1:
                insertarNodoPrincipioDoblePuntero(&tareasPendientes,auxil);
                break;
            case 2:
                insertarNodoPrincipioDoblePuntero(&tareasEnProceso,auxil);
                break;
            default:
                break;
            }
            break; 

        default:
            break;
        }
    }

    printf("Tareas pendientes:\n");
    MostrarTareas(tareasPendientes);

    printf("\n");

    printf("Tareas en proceso:\n");
    MostrarTareas(tareasEnProceso);

    printf("\n");

    printf("\nTareas realizadas:\n");
    MostrarTareas(tareasRealizadas);
    printf("\n");

    printf("Desea realizar otra operacion? 1:SI 0:NO");
    scanf("%d", &mov);

    }
          
    liberarLista(&tareasPendientes);
    liberarLista(&tareasEnProceso);
    liberarLista(&tareasRealizadas);

    printf("Tareas pendientes:\n");
    MostrarTareas(tareasPendientes);

    printf("\n");

    printf("Tareas en proceso:\n");
    MostrarTareas(tareasEnProceso);

    printf("\n");

    printf("\nTareas realizadas:\n");
    MostrarTareas(tareasRealizadas);
    printf("\n");
    
    return 0;
}

/*-----------------------------------------------------------------------------------------------------------*/

Nodo* crearListaVacia(){
    return NULL;
}

Tarea crearTarea(int id){

    int nuevaT,dur;
    Tarea Tar;

    char *buff = (char *)malloc(100 * sizeof(char));
    
    Tar.Duracion = 10 + rand()%91;
    printf("\n");
    printf("Ingrese la descripcion de la tarea?:");
    scanf("%s",buff);
    printf("\n");
    Tar.TareaID = id;

    Tar.Descripcion =(char *) malloc(sizeof(char) * (strlen(buff)+1));

    strcpy(Tar.Descripcion,buff);
    free(buff);

    return Tar;

}


void cargarLista(Nodo** tareas){

    int nuevaT,dur,i = 1;
    Tarea Tar;
    

    printf("Desea ingresar una nueva tarea? 1:SI 0:NO:");
    scanf("%d",&nuevaT);
    printf("\n");

    while (nuevaT == 1)
    {
        Tar = crearTarea(i);

        Nodo* nuevoNodo = crearNodo(Tar);

       insertarNodoPrincipioDoblePuntero(tareas,nuevoNodo);
        
        printf("Desea ingresar una nueva tarea? 1:SI 0:NO: ");
        scanf("%d",&nuevaT);
        printf("\n");
        i++;
    }
    
}

void listarTareas(Nodo** TareasPendientes,Nodo** TareasRealizadas,Nodo** TareasEnProceso){

    int SeRealizo;
    Nodo* aux;
    Nodo* recorrer = *TareasPendientes;
    Nodo* listaAux = NULL;

    while ((*TareasPendientes) != NULL)
    {   
        printf("\n");
        printf("------------------------------------------------\n");
        MostrarUnaTarea((*TareasPendientes));
        printf("Se realizo esta tarea o esta en proceso? 1:realizada 2:En proceso 0:pendiente :\n");    
        scanf("%d",&SeRealizo);
        printf("\n");
        int id = (*TareasPendientes)->T.TareaID;

        if (SeRealizo == 1)
        {
            
            aux = quitarNodo(TareasPendientes,id);
            insertarNodoPrincipioDoblePuntero(TareasRealizadas,aux);
    
        }else if (SeRealizo == 2)
        {
            aux = quitarNodo(TareasPendientes,id);
            insertarNodoPrincipioDoblePuntero(TareasEnProceso,aux);
        }else
        {
            aux = quitarNodo(TareasPendientes,id);
            insertarNodoPrincipioDoblePuntero(&listaAux,aux);
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

    tar->siguiente = *Tareas;
    *Tareas = tar;
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


Nodo* buscarTareaPorID(Nodo* tareas,int id){

    int bandera = 0;

    while (tareas != NULL)
    {
        if (tareas->T.TareaID == id)
        {
            Nodo* aux = tareas;
            return(aux);
            bandera = 1;
        }

        tareas = tareas->siguiente;
    }


}


Nodo* buscarTareaPorPalabra(Nodo* tareas,char* palabra){

    int bandera = 0;
    
    while (tareas != NULL)
    {
        if (strstr(tareas->T.Descripcion,palabra) != NULL)
        {
            return(tareas);
            bandera = 1;
        }
        
        tareas = tareas->siguiente;
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

void EliminarNodo(Nodo* tarea){

    if (tarea != NULL)
    {
        free(tarea->T.Descripcion);
        free(tarea);
        printf("Se elimino con exito la tarea\n");
    }else
    {
        printf("NO se elimino la tarea\n");
    }
    
    
    
}

void liberarLista(Nodo** tarea){

        Nodo* aux;
        while ((*tarea) != NULL)
        {
            aux = *tarea;
            (*tarea) = (*tarea)->siguiente;
            free(aux->T.Descripcion);
            free(aux);
        }
        
}
