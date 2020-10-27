#include <stdio.h>
#include <stdlib.h>

#include "lista.h"

/**
 Inicializa una lista vacía.
 Una referencia a la lista creada es referenciada en *L.
**/
void crear_lista(tLista * l){


        tLista lista=(tLista) malloc(sizeof(struct celda));
        if(lista==NULL)
            exit(LST_ERROR_MEMORIA);
        lista->elemento=NULL;
        lista->siguiente=NULL;


        *l=lista;
}

/**
 Inserta el elemento E, en la posición P, en L.
 Con L = A,B,C,D y la posición P direccionando C, luego:
 L' = A,B,E,C,D
**/
void l_insertar(tLista l, tPosicion p, tElemento e){

        tPosicion nodoNuevo;
        tPosicion nodoDerecho;

        nodoNuevo=(tPosicion) malloc(sizeof(struct celda));

        if(nodoNuevo==NULL){
            exit(LST_ERROR_MEMORIA);
        }
        nodoNuevo->elemento=e;

        nodoDerecho=p->siguiente;
        p->siguiente=nodoNuevo;
        nodoNuevo->siguiente=nodoDerecho;
}

/**
 Elimina la celda P de L. El elemento almacenado en la posición P es eliminado mediante la función fEliminar parametrizada.
 Si P es fin(L), finaliza indicando LST_POSICION_INVALIDA.
**/
void l_eliminar(tLista l, tPosicion p, void (*fEliminar)(tElemento)){

    tPosicion nodoEliminar;
    tPosicion nodoDerecho;

    if(p->siguiente==NULL){

        exit(LST_POSICION_INVALIDA);

    }else{

        nodoEliminar=p->siguiente;
        nodoDerecho=nodoEliminar->siguiente;
        p->siguiente=nodoDerecho;
        fEliminar(nodoEliminar->elemento);

        nodoEliminar->elemento=NULL;
        nodoEliminar->siguiente=NULL;
        free(nodoEliminar);

    }

}

/**
 Destruye la lista L, elimininando cada una de sus celdas. Los elementos almacenados en las celdas son eliminados mediante la función fEliminar parametrizada.
**/
void l_destruir(tLista * l, void (*fEliminar)(tElemento)){

    tPosicion nodoEliminar;
    tPosicion nodoViajante;
    nodoViajante=(*l);

    while(nodoViajante->siguiente!=NULL){

        nodoEliminar=nodoViajante->siguiente;
        nodoViajante=nodoViajante->siguiente;

        nodoEliminar->siguiente=NULL;
        fEliminar(nodoEliminar->elemento);
        nodoEliminar->elemento=NULL;
        free(nodoEliminar);

    }
    free(*l);
    (*l)=NULL;

}

 /**
 Recupera y retorna el elemento en la posición P.
 Si P es fin(L), finaliza indicando LST_POSICION_INVALIDA.
**/
tElemento l_recuperar(tLista l, tPosicion p){

    if(NULL==p || p->siguiente==NULL){

        exit(LST_POSICION_INVALIDA);

    }else{

        return p->siguiente->elemento;

    }

}

/**
 Recupera y retorna la primera posición de L.
 Si L es vacía, primera(L) = ultima(L) = fin(L).
**/
tPosicion l_primera(tLista l){

    return l;
}



/**
 Recupera y retorna la posición siguiente a P en L.
 Si P es fin(L), finaliza indicando LST_NO_EXISTE_SIGUIENTE.
**/
tPosicion l_siguiente(tLista l, tPosicion p){

    if(p->siguiente==NULL){

        exit(LST_NO_EXISTE_SIGUIENTE);

    }else{

        return p->siguiente;


    }

}

/**
 Recupera y retorna la posición anterior a P en L.
 Si P es primera(L), finaliza indicando LST_NO_EXISTE_ANTERIOR.
**/
tPosicion l_anterior(tLista l, tPosicion p){

    tPosicion nodoAnterior=NULL;
    int encontre=0;
    tPosicion nodoViajante;
    nodoViajante=l;

    if(l==p){

        exit(LST_NO_EXISTE_ANTERIOR);

    }else{

        while(nodoViajante!=NULL && encontre==0){
            if(nodoViajante->siguiente==p){
                nodoAnterior=nodoViajante;
                encontre=1;
            }
            nodoViajante=nodoViajante->siguiente;
        }
        if(encontre==1)
            return nodoAnterior;
        else
            exit(LST_POSICION_INVALIDA);
    }

}

 /**
 Recupera y retorna la última posición de L.
 Si L es vacía, primera(L) = ultima(L) = fin(L).
**/
tPosicion l_ultima(tLista l){

    tPosicion nodoViajante;
    nodoViajante=l;

    if(l->siguiente==NULL){

        return nodoViajante;

    }else{

        while((nodoViajante->siguiente)->siguiente!=NULL){
            nodoViajante=nodoViajante->siguiente;
        }

        return nodoViajante;
    }

}

 /**
 Recupera y retorna la posición fin de L.
 Si L es vacía, primera(L) = ultima(L) = fin(L).
**/
tPosicion l_fin(tLista l){

        tPosicion nodoViajante;
        nodoViajante=l;

        while(nodoViajante->siguiente!=NULL){
            nodoViajante=nodoViajante->siguiente;
        }

        return nodoViajante;
    }



/**
 Retorna la longitud actual de la lista.
**/
int l_longitud(tLista l){

    int contador=0;

    tPosicion nodoViajante;
    nodoViajante=l;


    while(nodoViajante->siguiente!=NULL){
        contador=contador+1;
        nodoViajante=nodoViajante->siguiente;
    }

    return contador;

}
