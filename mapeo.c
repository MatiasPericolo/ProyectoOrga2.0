#include <stdio.h>
#include <stdlib.h>

#include "mapeo.h"

/**
 Variables Globales
**/
static int max(int numero1,int numero2);
void (* funcion_eliminar_clave)(void *);
void (* funcion_eliminar_valor)(void *);
void funcion_eliminar_entrada(tElemento e);
void funcion_NO_eliminar_entrada(tElemento e);
void m_reHash(tMapeo mapeo);

/**
 Inicializa un mapeo vacío, con capacidad inicial igual al MAX(10, CI).
 Una referencia al mapeo creado es referenciada en *M.
 A todo efecto, el valor hash para las claves será computado mediante la función fHash.
 A todo efecto, la comparación de claves se realizará mediante la función fComparacion.
 Finaliza indicando MAP_ERROR_MEMORIA si no es posible reservar memoria correspondientemente.
**/
void crear_mapeo(tMapeo * m, int ci, int (*fHash)(void *), int (*fComparacion)(void *, void *)){

    tMapeo mapeoAux =(tMapeo) malloc(sizeof(struct mapeo));
    int capacidad=max(10,ci);
    int i;

    if(mapeoAux==NULL)
        exit(MAP_ERROR_MEMORIA);

    mapeoAux->cantidad_elementos = 0;
    mapeoAux->comparador = fComparacion;
    mapeoAux->hash_code = fHash;
    mapeoAux->longitud_tabla=capacidad;

    mapeoAux->tabla_hash=(tLista *) malloc(capacidad*sizeof(tLista));
    for(i=0;i<capacidad;i++){
        crear_lista(&(mapeoAux->tabla_hash[i]));
    }

    *m=mapeoAux;
}

/**
 Inserta una entrada con clave C y valor V, en M.
 Si una entrada con clave C y valor Vi ya existe en M, modifica Vi por V.
 Retorna NULL si la clave C no existía en M, o Vi en caso contrario.
 Finaliza indicando MAP_ERROR_MEMORIA si no es posible reservar memoria correspondientemente.
**/
tValor m_insertar(tMapeo m, tClave c, tValor v){

    printf("Elementos: %i\n",m->cantidad_elementos);

    if((m->cantidad_elementos/m->longitud_tabla)>(0.75)){
        m_reHash(m);
    }

    int encontre=0;
    tPosicion posViajante;
    int i;
    int fin;
    tValor toReturn=NULL;
    tEntrada entradaAux;
    int h = m->hash_code(c);
    h=h%(m->longitud_tabla);
    tLista listaPrincipal = m->tabla_hash[h];
    posViajante=(l_primera(listaPrincipal));
    fin=l_longitud(listaPrincipal);

    for(i=0;i<fin && encontre==0;i++){
        entradaAux=(tEntrada)l_recuperar(listaPrincipal,posViajante);

        if(m->comparador(entradaAux->clave,c)==0){
            encontre=1;
            toReturn=entradaAux->valor;
            entradaAux->valor=v;
        }else{
            posViajante=l_siguiente(listaPrincipal,posViajante);
        }

    }

    if(encontre==0){
        m->cantidad_elementos++;
        tEntrada entradaInsertar=(tEntrada) malloc(sizeof(struct entrada));
        entradaInsertar->clave=c;
        entradaInsertar->valor=v;
        l_insertar(listaPrincipal,posViajante,entradaInsertar);
    }

    return toReturn;
}

/**
 Elimina la entrada con clave C en M, si esta existe.
 La clave y el valor de la entrada son eliminados mediante las funciones fEliminarC y fEliminarV.
**/
void m_eliminar(tMapeo m, tClave c, void (*fEliminarC)(void *), void (*fEliminarV)(void *)){

    int encontre=0;
    tPosicion posViajante;
    int i;
    int fin;
    int h = m->hash_code(c);
    h=h%(m->longitud_tabla);
    tLista listaPrincipal = m->tabla_hash[h];
    posViajante=(l_primera(listaPrincipal));
    fin=l_longitud(listaPrincipal);
    tEntrada entradaAux;



    for(i=0;i<fin && encontre==0;i++){
        entradaAux=(tEntrada)l_recuperar(listaPrincipal,posViajante);

        if(m->comparador(entradaAux->clave,c)==0){
            funcion_eliminar_valor = fEliminarV;
            funcion_eliminar_clave = fEliminarC;

            l_eliminar(listaPrincipal,posViajante,&funcion_eliminar_entrada);
        }else{
            posViajante=l_siguiente(listaPrincipal,posViajante);
        }

    }

}

/**
 Destruye el mapeo M, elimininando cada una de sus entradas.
 Las claves y valores almacenados en las entradas son eliminados mediante las funciones fEliminarC y fEliminarV.
**/
void m_destruir(tMapeo * m, void (*fEliminarC)(void *), void (*fEliminarV)(void *)){

    unsigned int i;
    funcion_eliminar_valor = fEliminarV;
    funcion_eliminar_clave = fEliminarC;
    for(i=0;i<((*m)->longitud_tabla);i++){
        l_destruir(&((*m)->tabla_hash[i]),&funcion_eliminar_entrada);
    }

    free((*m)->tabla_hash);
    (*m)->tabla_hash = NULL;
    free(m);
    (*m) = NULL;

}

/**
 Recupera el valor correspondiente a la entrada con clave C en M, si esta existe.
 Retorna el valor correspondiente, o NULL en caso contrario.
**/
tValor m_recuperar(tMapeo m, tClave c){
    int encontre=0;
    tPosicion posViajante;
    int i;
    int fin;
    tValor toReturn=NULL;
    int h = m->hash_code(c);
    h=h%(m->longitud_tabla);
    tLista listaPrincipal = m->tabla_hash[h];
    posViajante=(l_primera(listaPrincipal));
    fin=l_longitud(listaPrincipal);
    tEntrada entradaAux;

    for(i=0;i<fin && encontre==0;i++){
        entradaAux=(tEntrada)l_recuperar(listaPrincipal,posViajante);

        if(m->comparador(entradaAux->clave,c)==0){
            encontre=1;
            toReturn=entradaAux->valor;
        }else{
            posViajante=l_siguiente(listaPrincipal,posViajante);
        }

    }

    return toReturn;
}

void m_reHash(tMapeo mapeo){

    tPosicion posViajante;
    int j;
    int fin;
    tEntrada entradaAux;
    tLista * tabla_anterior=mapeo->tabla_hash;
    mapeo->longitud_tabla *= 2;
    mapeo->tabla_hash = malloc(sizeof(tLista)*mapeo->longitud_tabla);
    int i;
    tLista listaAux;
    int h;

    for(i=0;i<(mapeo->longitud_tabla);i++){
        crear_lista(&(mapeo->tabla_hash[i]));
    }

    for(i=0;i<((mapeo->longitud_tabla)/2);i++){

        listaAux=tabla_anterior[i];
        //printf("Numero: %i",i);
        scanf("%s");
        fin=l_longitud(listaAux);
        posViajante=l_primera(listaAux);
        printf("Longitud lista: %i\n",fin);

        for(j=0;j<fin;j++){

            entradaAux=(tEntrada)l_recuperar(listaAux,posViajante);
            l_eliminar(listaAux,posViajante,&funcion_NO_eliminar_entrada);

            printf("Entrada: %s\n",((char*)entradaAux->clave));

            //Ingreso de nueva entrada
            h=mapeo->hash_code(entradaAux->clave);
            h=h%(mapeo->longitud_tabla);
            l_insertar(mapeo->tabla_hash[h],l_primera(mapeo->tabla_hash[h]),entradaAux);

            if(posViajante!=l_ultima(listaAux)){
                posViajante=l_siguiente(listaAux,posViajante);
            }

        }

    }


}

void funcion_NO_eliminar_entrada(tElemento e){

}

/**
 Recibe una entrada y elimina sus datos
**/
void funcion_eliminar_entrada(tElemento e){
    tEntrada entrada=(tEntrada) e;
    funcion_eliminar_valor(entrada->valor);
    funcion_eliminar_clave(entrada->clave);

    free(e);
}

/**
 Recibe dos enteros por parametro y retorna el mayor de ellos
**/
static int max(int numero1,int numero2){

    int mayor;

    mayor = (numero1>numero2) ? numero1 : numero2;

    return mayor;

}
