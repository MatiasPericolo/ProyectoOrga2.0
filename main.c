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
    char*  palabra=clave;
    for (int i = 0; i < strlen(palabra); i++) {
        hash = 31 * hash + palabra[i];
    }
    return hash;
}

int fComparacion(tClave c1,tClave c2){

    int toReturn=1;

    char * palabra1=c1;
    char * palabra2=c2;

    if(strcmp(palabra1,palabra2)==0)
        toReturn=0;

    //printf("Palabra1: %s/Palabra2: %s/Devuelve: %i ",palabra1,palabra2,toReturn);

    return toReturn;
}

int main(int argc,char ** args)
{
    tMapeo mapeo;

    crear_mapeo(&mapeo,10,fHash,fComparacion);

    char* claveAux=(char*) malloc(sizeof(char));
    int* valorAux=(int*) malloc(sizeof(int));

    char * archivo=args[1];

    char caracter;
    FILE *file;
    file = fopen(archivo, "r");
    int i=0;

    if(file){
        while(fscanf(file,"%c",&caracter)==1){
            if(caracter != ' ' && caracter != '\n'){
                claveAux[i]=caracter;
                i++;
            } else {
                claveAux[i]='\0';
                printf("%s\n",claveAux);
                if(m_recuperar(mapeo,claveAux) == NULL){
                    valorAux = 1;
                } else {
                    valorAux = m_recuperar(mapeo,claveAux)+1;
                }
                m_insertar(mapeo,claveAux,valorAux);
                claveAux=(char*) malloc(sizeof(char));
                valorAux=(int*) malloc(sizeof(int));
                i = 0;
            }
        }
    }
    fclose(file);


    claveAux = "Matias";
    printf("%i\n",m_recuperar(mapeo,claveAux));


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
