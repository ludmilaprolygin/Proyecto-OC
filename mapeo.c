#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "mapeo.h"

//No nos funciona bien el rehash cuando supera el factor de carga

int MAX(int num1, int num2) {
   int toReturn;
   if (num1 > num2)
      toReturn = num1;
   else
      toReturn = num2;
   return toReturn;
}

void (*fEliminarClave)(void *);
void (*fEliminarValor)(void *);
void (*fEliminarLista)(tLista *);

void fEliminarEntrada(tElemento e){
     tEntrada entrada = (tEntrada) e;
     fEliminarClave(entrada->clave);
     fEliminarValor(entrada->valor);
     entrada = NULL;
     free(entrada);
}

int es_primo(int numero) {
    int es_primo = 1;
	int divisor = 2;
	while(divisor<numero/2 && es_primo)
		if(numero%divisor != 0)
			divisor++;
		else
			es_primo = 0;
	return es_primo;
}

int proximo_primo(int numero) {
    int nro_primo = 0;
    numero++;
	while(!nro_primo)
		if(es_primo(numero))
			nro_primo=1;
		else
			numero++;
	return numero;
}

void re_size(int longitud, tMapeo *m){
    int nuevo_size = proximo_primo(2*(*m)->longitud_tabla);
    int bucket;
    tEntrada entrada;
    tClave clave;
    tPosicion posicion_actual_lista, posicion_fin_lista;
    tLista lista_actual;
    tLista* lista = malloc(nuevo_size*sizeof(struct celda));

    for(int i=0; i<nuevo_size; i++){
        crear_lista(&(lista[i]));
    }

    for(int i=0; i<(*m)->longitud_tabla; i++){
        lista_actual = *((*m)->tabla_hash+bucket);
        posicion_actual_lista = l_primera(lista_actual);
        posicion_fin_lista = l_fin(lista_actual);
        while(posicion_actual_lista!=posicion_fin_lista){
            entrada = l_recuperar(lista_actual, posicion_actual_lista);
            clave = entrada->clave;
            bucket = (*m)->hash_code(clave) % (*m)->longitud_tabla;
            l_insertar(lista[bucket], l_primera(lista[bucket]), entrada);
            posicion_actual_lista = l_siguiente(lista_actual, posicion_actual_lista);
        }
    }

	(*m)->tabla_hash = 	lista;
    (*m)->longitud_tabla = nuevo_size;
}

/**
 Inicializa un mapeo vacío, con capacidad inicial igual al MAX(10, CI).
 Una referencia al mapeo creado es referenciada en *M.
 A todo efecto, el valor hash para las claves será computado mediante la función fHash.
 A todo efecto, la comparación de claves se realizará mediante la función fComparacion.
 Finaliza indicando MAP_ERROR_MEMORIA si no es posible reservar memoria correspondientemente.
**/
extern void crear_mapeo(tMapeo * m, int ci, int (*fHash)(void *), int (*fComparacion)(void *, void *)){
    int capacidad = MAX(ci, 10);
    tLista* lista;

    *m = (tMapeo)malloc(sizeof(struct mapeo));
    if(*m==NULL)
        exit(MAP_ERROR_MEMORIA);

    lista = malloc(capacidad * sizeof(struct celda));
    if(lista == NULL)
        exit(MAP_ERROR_MEMORIA);

    (*m)->longitud_tabla = capacidad;
    (*m)->cantidad_elementos = 0;
    (*m)->hash_code = fHash;
    (*m)->comparador = fComparacion;
    (*m)->tabla_hash = lista;

    for(int i=0; i<capacidad; i++){
        crear_lista(&((*m)->tabla_hash[i]));
    }
}

/**
 Inserta una entrada con clave C y valor V, en M.
 Si una entrada con clave C y valor Vi ya existe en M, modifica Vi por V.
 Retorna NULL si la clave C no existía en M, o Vi en caso contrario.
 Finaliza indicando MAP_ERROR_MEMORIA si no es posible reservar memoria correspondientemente.
**/
extern tValor m_insertar(tMapeo m, tClave c, tValor v){
    tLista mi_lista;
    tEntrada entrada;
    tValor to_return = NULL;
    tPosicion pos_actual, pos_fin;
    int encontre = 0;
    int bucket = m->hash_code(c) % m->longitud_tabla; //Tengo que computar el hash code para la clave C.

    mi_lista = *(m->tabla_hash+bucket); //Obtengo la lista donde debería ubicarse la clave C.
    pos_actual = l_primera(mi_lista);//Tengo que recorrer la lista para observar si existe una entrada con clave C.
    pos_fin = l_fin(mi_lista);

    while(!encontre && pos_actual!=pos_fin){ //Recorre la lista en búsqueda de una entrada cuya clave sea C.
        entrada = (tEntrada) l_recuperar(mi_lista, pos_actual);
        if (m->comparador(c, entrada->clave) == 0){ //Las claves son iguales
            encontre = 1;
            to_return = entrada->valor;
            entrada->valor = v;
        }
        else{
            pos_actual = l_siguiente(mi_lista, pos_actual);
        }
    }
    if(!encontre){
        if((m->cantidad_elementos)/(m->longitud_tabla) >= 0.75)
            re_size(m->cantidad_elementos, &m);
        entrada = (tEntrada) malloc(sizeof(struct entrada));
        if(entrada==NULL)
            exit(MAP_ERROR_MEMORIA);
        entrada->clave = c;
        entrada->valor = v;
        l_insertar(mi_lista, l_primera(mi_lista), entrada);
        m->cantidad_elementos = m->cantidad_elementos+1;
    }
    return to_return;
}

/**
 Elimina la entrada con clave C en M, si esta existe.
 La clave y el valor de la entrada son eliminados mediante las funciones fEliminarC y fEliminarV.
**/
extern void m_eliminar(tMapeo m, tClave c, void (*fEliminarC)(void *), void (*fEliminarV)(void *)){
    int bucket = m->hash_code(c) % m->longitud_tabla; //Tengo que computar el hash code para la clave C.
    tLista mi_lista = m->tabla_hash[bucket]; //Obtengo la lista donde debería ubicarse la clave C.
    tEntrada entrada;
    tPosicion pos_actual, pos_fin;
    int elimine = 0;
    fEliminarClave = fEliminarC;
    fEliminarValor = fEliminarV;

    pos_actual = l_primera(mi_lista);//Tengo que recorrer la lista para observar si existe una entrada con clave C.
    pos_fin = l_fin(mi_lista);
    while(!elimine && pos_actual!=pos_fin){ //Recorre la lista en búsqueda de una entrada cuya clave sea C.
        entrada = (tEntrada) l_recuperar(mi_lista, pos_actual);
        if (m->comparador(c, entrada->clave) == 0){ //Las claves son iguales entonces tengo que borrar.
            elimine = 1;
            l_eliminar(mi_lista, pos_actual, &fEliminarEntrada);
            m->cantidad_elementos = m->cantidad_elementos-1;
        }
        else{
            pos_actual = l_siguiente(mi_lista, pos_actual);
        }
    }
}

/**
 Destruye el mapeo M, elimininando cada una de sus entradas.
 Las claves y valores almacenados en las entradas son eliminados mediante las funciones fEliminarC y fEliminarV.
**/
extern void m_destruir(tMapeo * m, void (*fEliminarC)(void *), void (*fEliminarV)(void *)){
    tMapeo mapeo = (*m);
    int capacidad = mapeo->longitud_tabla;
    int bucket;
    tLista lista_actual;
    fEliminarClave = fEliminarC;
    fEliminarValor = fEliminarV;

    /*
    for(int i=0; i<capacidad; i++){
        lista_actual = *((*m)->tabla_hash+i);
        l_destruir(&lista_actual, &fEliminarEntrada);
        free(lista_actual);
    }
    */
    //Y si solo destruimos tabla_hash? No entiendo como parametrizar la funcion para que destruya la lista una a una.

    //l_destruir(*(*m)->tabla_hash, &fEliminarLista);

    free(m);
    (*m)=NULL;
}

/**
 Recupera el valor correspondiente a la entrada con clave C en M, si esta existe.
 Retorna el valor correspondiente, o NULL en caso contrario.
**/
extern tValor m_recuperar(tMapeo m, tClave c){
    int bucket = m->hash_code(c) % m->longitud_tabla;
    int encontre = 0;
    tLista mi_lista = m->tabla_hash[bucket];
    tValor to_return = NULL;
    tPosicion pos_actual, pos_fin;
    tEntrada entrada;

    pos_actual = l_primera(mi_lista);
    pos_fin = l_fin(mi_lista);
    while(!encontre && pos_actual!=pos_fin){ //Recorro la lista correspondiente al bucket.
        entrada = (tEntrada) l_recuperar(mi_lista, pos_actual);
        if (m->comparador(c, entrada->clave) == 0){ //Las claves son iguales
            encontre = 1;
            to_return = entrada->valor;
        }
        else
            pos_actual = l_siguiente(mi_lista, pos_actual);
    }

    return to_return;
}
