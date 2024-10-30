#include "Lector.h"
// Apartir de un Path obten un archivo de texto
FILE *ObtenerArchivo(){ 
    char Nombre[MAXTAM];
    printf("Ingresa el nombre del archivo: ");
    fgets(Nombre,MAXTAM,stdin);
    Nombre[strlen(Nombre) - 1] = '\0';
    FILE *archivo = fopen(Nombre, "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo");
    }
    return archivo;
}
//Regresa la dirección de memoria de cada linea
int LeerLinea(FILE *archivo, char **identificador, char **produccion){
    char *Linea;
    int prv = 0;
    int idIndex = 0, prodIndex = 0;
    if(archivo == NULL || feof(archivo)){
        return 0;
    }
    Linea = (char *)malloc(MAXTAM);
    fgets(Linea,MAXTAM,archivo);
    if(Linea[strlen(Linea) - 1] == '\n'){
        Linea[strlen(Linea) - 1] = '\0';
    }
    *identificador = (char*)malloc(MAXTAM);
    *produccion = (char*)malloc(MAXTAM);

    strcpy(*identificador, "");
    strcpy(*produccion, "");

     for (int i = 0; i < strlen(Linea); i++) {
        if (Linea[i] == '-') {
            i++;
            prv = 1; // Cambiar a la producción
            continue;
        }

        if (prv == 0) {
            (*identificador)[idIndex++] = Linea[i];
            (*identificador)[idIndex] = '\0'; // Asegurar terminación de la cadena
        } else {
            (*produccion)[prodIndex++] = Linea[i];
            (*produccion)[prodIndex] = '\0'; // Asegurar terminación de la cadena
        }
    }
    return 1;
} 
