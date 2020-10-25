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
            cant_palabras = valor;
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
    int longitud_mapeo = 10;

    tMapeo m;
  	crear_mapeo(&m, longitud_mapeo, &fHash, &fComparacion);


  	tValor valor;
  	tClave clave;

  	char* s1 = "uno";
  	void* i1 = 0;

  	clave = s1;
  	valor = i1;

  	printf("%i - ", m->cantidad_elementos);
  	printf("%i\n", m->longitud_tabla);

  	m_insertar(m, clave, valor);
  	printf("%i - ", m->cantidad_elementos);
  	printf("%i\n", m->longitud_tabla);

  	s1 = "dos";
  	clave = s1;
  	m_insertar(m, clave, valor);
  	printf("%i - ", m->cantidad_elementos);
  	printf("%i\n", m->longitud_tabla);

  	s1 = "tres";
  	clave = s1;
  	m_insertar(m, clave, valor);
  	printf("%i - ", m->cantidad_elementos);
  	printf("%i\n", m->longitud_tabla);

  	s1 = "cuatro";
  	clave = s1;
  	m_insertar(m, clave, valor);
  	printf("%i - ", m->cantidad_elementos);
  	printf("%i\n", m->longitud_tabla);

  	s1 = "cinco";
  	clave = s1;
  	m_insertar(m, clave, valor);
  	printf("%i - ", m->cantidad_elementos);
  	printf("%i\n", m->longitud_tabla);

  	s1 = "seis";
  	clave = s1;
  	m_insertar(m, clave, valor);
  	printf("%i - ", m->cantidad_elementos);
  	printf("%i\n", m->longitud_tabla);

  	s1 = "siete";
  	clave = s1;
  	m_insertar(m, clave, valor);
  	printf("%i - ", m->cantidad_elementos);
  	printf("%i\n", m->longitud_tabla);

  	s1 = "ocho";
  	clave = s1;
  	m_insertar(m, clave, valor);
  	printf("%i - ", m->cantidad_elementos);
  	printf("%i\n", m->longitud_tabla);

  	s1 = "nueve";
  	clave = s1;
  	m_insertar(m, clave, valor);
  	printf("%i - ", m->cantidad_elementos);
  	printf("%i\n", m->longitud_tabla);

  	s1 = "diez";
  	clave = s1;
  	m_insertar(m, clave, valor);
  	printf("%i - ", m->cantidad_elementos);
  	printf("%i\n", m->longitud_tabla);

  	s1 = "once";
  	clave = s1;
  	m_insertar(m, clave, valor);
  	printf("%i - ", m->cantidad_elementos);
  	printf("%i\n", m->longitud_tabla);

  	s1 = "doce";
  	clave = s1;
  	m_insertar(m, clave, valor);
  	printf("%i - ", m->cantidad_elementos);
  	printf("%i\n", m->longitud_tabla);

  	s1 = "trece";
  	clave = s1;
  	m_insertar(m, clave, valor);
  	printf("%i - ", m->cantidad_elementos);
  	printf("%i\n", m->longitud_tabla);

  	s1 = "catorce";
  	clave = s1;
  	m_insertar(m, clave, valor);
  	printf("%i - ", m->cantidad_elementos);
  	printf("%i\n", m->longitud_tabla);

  	s1 = "quince";
  	clave = s1;
  	m_insertar(m, clave, valor);
  	printf("%i - ", m->cantidad_elementos);
  	printf("%i\n", m->longitud_tabla);

  	m_destruir(&m, fEliminarC, fEliminarV);

    return 0;
}
