#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "mapeo.h"

void fEliminar (tElemento elemento){

    free(elemento);

}

void fEliminarC (tClave clave){

    free(clave);

}

void fEliminarV (tValor valor){

    printf("Valor: %i\n",*((int*)valor));

    free(&valor);

}

int fHash(tClave clave) {
    int hash = 0;
    char * palabra=*((char **)clave);
    for (int i = 0; i < strlen(palabra); i++) {
        hash = 31 * hash + palabra[i];
    }
    return hash;
}

int fComparacion(tClave c1,tClave c2){

    int toReturn=1;

    char * palabra1=*((char **)c1);
    char * palabra2=*((char **)c2);

    if(strcmp(palabra1,palabra2)==0)
        toReturn=0;

    //printf("Palabra1: %s/Palabra2: %s/Devuelve: %i ",palabra1,palabra2,toReturn);

    return toReturn;
}

int main(int argc,char ** args)
{
    tMapeo mapeo;

    crear_mapeo(&mapeo,10,fHash,fComparacion);

    char** claveAux=(char**) malloc(sizeof(char*));
    int* valorAux=(int*) malloc(sizeof(int));

    char * archivo=args[1];

    char caracter;
    FILE *file;
    file = fopen(archivo, "r");
    int i;
    i=0;

    if(file){
        while(fscanf(file,"%c",&caracter)==1){
            printf("%c\n",caracter);
        }
    }

    /*
    *clave="Matias";
    *valor=1;

    crear_mapeo(&mapeo,10,fHash,fComparacion);

    m_insertar(mapeo,clave,valor);

    clave=(char**) malloc(sizeof(char*));
    valor=(int*) malloc(sizeof(int));

    *clave="Sol";
    *valor=2;

    m_insertar(mapeo,clave,valor);

    clave=(char**) malloc(sizeof(char*));
    valor=(int*) malloc(sizeof(int));

    *clave="Sol";
    *valor=1;

    m_insertar(mapeo,clave,valor);

    clave=(char**) malloc(sizeof(char*));
    valor=(int*) malloc(sizeof(int));

    *clave="Sol";

    int* aux=m_recuperar(mapeo,clave);

    m_eliminar(mapeo,clave,fEliminarC,fEliminarV);

    if(aux!=NULL)
        printf("Devuelve: %i\n",*aux);
    */

    int fin;
    printf("Fin");
    scanf("Ingrese algo: %i",&fin);

    return 0;
}
