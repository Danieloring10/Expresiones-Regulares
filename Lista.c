#include "Lista.h"

//Crea un nodo en la memoria
TNodo *CrearNodo(char *identificador, char *produccion){
    TNodo *aux;
    aux = (TNodo *)malloc(sizeof(TNodo));
    //identificador - Production
    aux->identificador = identificador;
    aux->produccion = produccion;
    aux->sig = NULL;
    return aux;
}
    //Crea y agrega un nodo a la lista pasada
void AgregarNodo(TNodo **cab, char *identificador, char *produccion){
    //Buscar nodo antes
    TNodo *aux = CrearNodo(identificador, produccion), *corre = *cab;
    if(*cab == NULL){
        *cab = aux;
        return;
    }
    //Recorre hasta encontrar el final
    while(corre->sig != NULL){
        corre = corre->sig;
    }
    corre->sig = aux; //Agregalo al final
}

//Imprime nodos en la consola
void MostrarNodos(TNodo *cab){
    TNodo *corre = cab;
    while(corre != NULL){
        printf("%s -> %s\n", corre->identificador, corre->produccion);  
        corre = corre->sig;
    }
}

//Libera todos los nodos de una lista
void LiberarLista(TNodo **cab){
    *cab = NULL;
    if((*cab)->sig != NULL){
        LiberarLista((*cab)->sig);
    }
    free(*cab);
}       

//Segun la produccion, busca el primer nodo en la lista
TNodo *BuscarNodo(TNodo*cab, char *produccion){
    TNodo *corre = cab;
    if(cab == NULL){
        return NULL;
    }
    while (corre->sig != NULL){
        if(corre->produccion == produccion)return corre;
        corre = corre->sig;
    }
    return NULL;
}

//Agrupa todos los nodos con la misma cabecera
TNodo *AgruparProducciones(TNodo *cabL){
    TNodo *act = cabL, *aux, *lsNode = cabL;
    char *identAct = cabL->identificador;
    while (act != NULL){
        if(act == cabL){ // El primer nodo saltalo
            act = act->sig;
        }
        //Si el identificador agrupandose es el mismo que el del nodo actual
        if(!strcmp(identAct, act->identificador)){
            // Agrega los datos al nodo base
            strcat(lsNode->produccion, " | ");
            strcat(lsNode->produccion, act->produccion);
            aux = act; 
            act = act->sig; // avanza el corre
            free(aux);   //Libera el nodo
        }
        else{ // si no lo es
            lsNode->sig = act; 
            lsNode = act;   // cambia el nodo pivote 
            identAct = act->identificador;
            act = act->sig;
        }
        //Finaliza correctamente el ultimo nodo
        lsNode->sig = NULL;
    }
    return cabL;
}

//Crea la gramatica segun las operaciones ya agrupadas (Recursiva)
int CrearGramatica(TNodo *cab,TNodo *act){
    TNodo *corre = act;
    char *construct, *aux;
    int ProdTam = 0;
    construct =  (char *)malloc(MAXTAM);

    //caso Base para la recursión
    if(act == NULL) return 1;

    //Elimina la recursion en la produccion del nodo actual
    eliminarRecursividad(act);

    //Por cada Nodo enfrente, busca si dentro de sus producciones esta el identificador actual (Sustitución descendiente)
    while(corre != NULL){
        sustituirId(act, corre);
        corre = corre->sig;
    }

    // Espera a que el siguiente Nodo termine
    //Si ya es el ultimo inicia
    if(CrearGramatica(cab,act->sig)){ 
        corre = cab;
        eliminarRecursividad(act); // Vuelve a eliminar la recursividad 

        // Sustituye, ahora desde el inicio hasta el nodo actual (Sustitución ascendente)
        while(corre != act){
           sustituirId(act, corre); 
            corre = corre->sig;
        }
    }
    return 1;
}


void eliminarRecursividad(TNodo *nodo){
    char *construct;
    int ProdTam = 0;
    construct =  (char *)malloc(MAXTAM);
    for(int i = 0; i < strlen(nodo->produccion); i++){ // Por cada char en el string
        if(nodo->produccion[i] == ' ')continue; //Si es espacio ignoralo
        if(nodo->produccion[i] ==  *nodo->identificador){   //Si es igual a su identificador 
        //sustituyelo por {x} mostrando que es recursivo (muchas veces)
            construct[ProdTam] = construct[ProdTam-1];
            construct[ProdTam-1] = '{';
            construct[ProdTam+1] = '}';
            ProdTam+=2;
        }
        else{ // Si no agregalo al constructor
           construct[ProdTam] = nodo->produccion[i];
           ProdTam++;
        }
    }

    //Sustituye las producciones y libera la anterior
    construct[ProdTam] = '\0';
    construct = realloc(construct, ProdTam+1);
    char *aux = nodo->produccion;
    nodo->produccion = construct;
    free(aux);
}
void sustituirId(TNodo *piv, TNodo *nodo){
    TNodo *aux;
    int prodCreTam = 0;
    char *construct2;
     construct2 = (char*)malloc(MAXTAM);
        for(int i = 0; i < strlen(nodo->produccion); i++){ // Por cada char en el string
            if(nodo->produccion[i] == *piv->identificador){ // Si el char es igual al identificador del piv
                //sustituye el caracter del identificador por su valor correspondiente
                construct2[prodCreTam++] = '('; 
                strcpy(construct2 + prodCreTam, piv->produccion); 
                prodCreTam += strlen(piv->produccion); 
                construct2[prodCreTam++] = ')';
            }
            else{ // Si no es agrega el char al constructor
                construct2[prodCreTam] = nodo->produccion[i];
                prodCreTam++;
            }
        }

        //Sustituye las producciones y libera la anterior
        construct2[prodCreTam] = '\0';
        construct2 = realloc(construct2, prodCreTam);
        aux = nodo->produccion;
        nodo->produccion = construct2;
        free(aux);
}

char *eliminarLlaves(TNodo *nodo){
    char *construct;
    int consTam = 0;
    construct = (char*)malloc(MAXTAM);
    for(int i = 0; i < strlen(nodo->produccion); i++){  //Por cada char en el string
        //Si encuentra {} (Signos de la recursividad), elimina "{" deja el valor de enmedio y sustituye "}" por "*"
        if(nodo->produccion[i] == '{') continue;
        if(nodo->produccion[i] == '}'){
            construct[consTam] = '*';
            consTam++;
            continue;
        }
        //Si no es ninguna sigue agregando al constructor
        construct[consTam] = nodo->produccion[i];
        consTam++;
    }
    construct[consTam] = '\0';
    construct = realloc(construct, consTam);
    return construct;
}