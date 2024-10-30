#ifndef LECTOR_H
#define LECTOR_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXTAM 200
FILE * ObtenerArchivo();
int LeerLinea(FILE *archivo, char **identificador, char **produccion);

#endif