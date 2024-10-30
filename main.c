#include "main.h"
int main(){
    TNodo *cab = NULL;
    FILE *Archivo = ObtenerArchivo();
    char *identificador , *produccion; 
    //Lee todas Las lineas
    while(LeerLinea(Archivo, &identificador, &produccion)){
        identificador = realloc(identificador, sizeof(identificador)+1);
        produccion = realloc(produccion, sizeof(produccion)+1);
        //Agrega cada linea a un nodo 
        AgregarNodo(&cab,identificador, produccion);
    }
    printf("Para las producciones: \n");
    MostrarNodos(cab);    
    cab = AgruparProducciones(cab);
    CrearGramatica(cab,cab);
    eliminarLlaves(cab);
    printf("\nSu expresion Regular es:\t%s\n", eliminarLlaves(cab));
    LiberarLista(&cab);
}

/*
    
*/