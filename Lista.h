#ifndef LISTA_H
#define LISTA_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXTAM 200
typedef struct  NODO
{
    char *identificador;
    char *produccion;
    struct NODO *sig;
}TNodo;

TNodo *CrearNodo(char *identificado, char *produccion);
void AgregarNodo(TNodo **cab, char *identificador, char *produccion);
void MostrarNodos(TNodo *cab);
void LiberarLista(TNodo **cab);
TNodo *BuscarNodo(TNodo*cab, char *produccion);
int CrearGramatica(TNodo *cab, TNodo *act);
void eliminarRecursividad(TNodo *nodo);
void sustituirId(TNodo *piv, TNodo *nodo);
char * eliminarLlaves(TNodo *cab);

#endif