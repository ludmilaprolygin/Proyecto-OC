#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "mapeo.h"
#include "math.h"

#define ARCH_ERROR_APERTURA -1
#define ERROR_INVOCACION -2

void fEliminar(tElemento elemento){
    elemento=NULL;
    free(elemento);
}

int fComparacion(void* s1, void* s2){
    char *string1 = s1;
    char *string2 = s2;
    int toReturn = strcmp(string1, string2);
    return toReturn;
}

int fHash(void* s){
    char* str = s;
    int hash = 0;
    for (int i = 0; i < strlen(str); i++) {
        hash = 31 * hash + str[i];
    }
    return hash;
}

void fEliminarV(tValor valor){
    valor=NULL;
    free(valor);
}

void fEliminarC(tClave clave){
    clave=NULL;
    free(clave);
}

void cargar_mapeo(tMapeo m, char* contenido){
    tValor valor;
    int cant_palabras;
    char *contenido_separado = strtok(contenido, " ");
    while(contenido_separado!=NULL){
        valor = m_recuperar(m, contenido_separado);
        if(valor == NULL)
            cant_palabras = 0;
        else
            cant_palabras = (int) valor;
        valor = cant_palabras++;
        m_insertar(m, contenido_separado, valor);
        contenido_separado = strtok(NULL, " ");
    }
}

void iniciar_programa(char* rutaArchivo, tMapeo m){
    char *linea = "\0";
    char *puntero = malloc(sizeof(char));
    char *archivo = malloc(sizeof(char));
    FILE *file = fopen(rutaArchivo, "r");
    if(file==NULL){
        printf("Ocurrió un error al intentar abrir el archivo");
        exit(ARCH_ERROR_APERTURA);
    }
    while(puntero!=NULL){
        puntero = fgets(linea, 100, file);
        archivo = strcat(archivo, puntero);
    }
    fclose(file);

    crear_mapeo(&m, 25, &fHash, &fComparacion);

    cargar_mapeo(m, archivo);
}

int cantApariciones(char* palabra, tMapeo m){
    tValor valor = m_recuperar(m, palabra);
    int toReturn = valor;
    return toReturn;
}

void salir(tMapeo m){
    m_destruir(&m, &fEliminarC, &fEliminarV);
}

int main()
{
    return 0;
}
