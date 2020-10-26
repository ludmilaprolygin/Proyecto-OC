#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "mapeo.h"
#include "math.h"

#define ARCH_ERROR_APERTURA -1
#define ERROR_INVOCACION -2

tMapeo mapeo;

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
    return abs(hash);
}

void fEliminarV(tValor valor){
    valor=NULL;
    free(valor);
}

void fEliminarC(tClave clave){
    clave=NULL;
    free(clave);
}

int cant_apariciones(char* palabra){
    tValor valor = m_recuperar(mapeo, palabra);
    int toReturn = valor;
    return toReturn;
}

void salir(){
    m_destruir(&mapeo, &fEliminarC, &fEliminarV);
}

void cargar_archivo(char f[]){
    char linea[100]="\0";
    FILE *file = fopen(f, "r");
    char *puntero;
    char *contenido_separado;
    tValor valor;
    int cant_palabras;
    char delimitadores[] = ", ¿?¡!\n\r\0";

    if(file==NULL){
        printf("Ocurrió un error al intentar abrir el archivo.");
        exit(ARCH_ERROR_APERTURA);
    }

    crear_mapeo(&mapeo, 20, &fHash, &fComparacion);

    while(puntero!=NULL){
        puntero = fgets(linea,100,file);
        contenido_separado = strtok(puntero, delimitadores);
        while(contenido_separado!=NULL){
    printf("Contenido separado: [%s] ", contenido_separado);
    cant_palabras = (int) m_recuperar(mapeo, contenido_separado);
    valor = cant_palabras++;
    m_insertar(mapeo, contenido_separado, valor);
    printf("%i \n", cant_palabras);
    contenido_separado = strtok(NULL, delimitadores);
}
    }

    fclose(file);
    printf("Cantidad de palabras: %i", mapeo->cantidad_elementos);
}

void evaluador(char ruta_archivo[]){
    int operacion;
    int terminar = 0;
    char* buffer = NULL;
    int cantidad_apariciones;

    cargar_archivo(ruta_archivo);

    while(terminar==0){
        printf("Ingrese la operacion a realizar\n");
        printf("1: cantidad de apariciones, 2: salir >> ");
        scanf("%1i", &operacion);
        fflush(stdin);

        if(operacion!=1 || operacion!=2){
            printf("Ocurrio un error al intentar ejecutar el programa.");
            exit(ERROR_INVOCACION);
        }
        if(operacion==1){
            printf("Ingrese la palabra que desea contabilizar >> ");
            scanf("%s", buffer);
            fflush(stdin);
            cantidad_apariciones = cant_apariciones(buffer);
            printf("La palabra %s aparece %i en el archivo.", buffer, cantidad_apariciones);
        }
        else{
            salir();
            terminar = 1;
        }
    }
}


int main()
{

    char buffer[250];
    printf("Ingrese la ruta del archivo que desea abrir\n");
    scanf("%s", &buffer);
    fflush(stdin);
    printf("\n");

    cargar_archivo(buffer);


    /*
    int longitud_mapeo = 10;

    tMapeo m;
  	crear_mapeo(&m, longitud_mapeo, &fHash, &fComparacion);


  	tValor valor;
  	tClave clave;
  	tElemento elemento;
  	tEntrada entrada;

  	char* s1 = "uno";
  	void* i = 100;

  	tLista lista_actual;
  	tPosicion posicion;

  	clave = s1;
  	valor = i;

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

  	s1 = "uno";
  	clave = s1;
  	i = 200;
  	valor = i;
  	m_insertar(m, clave, valor);
  	printf("%i - ", m->cantidad_elementos);
  	printf("%i\n", m->longitud_tabla);

    valor = m_recuperar(m, "quince");
    i = valor;
    printf("quince, %i\n", valor);

    valor = m_recuperar(m, "uno");
    i = valor;
    printf("uno, %i\n", valor);

    valor = m_recuperar(m, "veinte");
    if(valor!=NULL){
        i = valor;
        printf("veinte, %i\n", valor);
    }
    else
        printf("veinte, no ta\n");

    printf("Longitud tabla: %i\n", m->longitud_tabla);
    printf("Cantidad elementos: %i\n", m->cantidad_elementos);
    m_destruir(&m, &fEliminarC, &fEliminarV);
    */

    return 0;
}
