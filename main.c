#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "mapeo.h"

#define MAXCHAR 1000

void programa(tMapeo m);
void salir(tMapeo m);

void fEliminar (tElemento elemento){

    free(elemento);

}

void fEliminarC (tClave clave){

    free(clave);

}

void fEliminarV (tValor valor){

    free(valor);

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

char* sigPalabra(char buffer[],int size){
    char* claveAux=(char*) malloc(sizeof(char)*size);
    for(int i = 0;i<size;i++){
        claveAux[i]=buffer[i];
    }
    claveAux[size]='\0';
    return claveAux;
}

int main(int argc,char ** args)
{
    tMapeo mapeo;

    crear_mapeo(&mapeo,10,fHash,fComparacion);

    char* claveAux;
    int* valorAux=(int*) malloc(sizeof(int));

    char buffer[MAXCHAR];

    char * archivo=args[1];

    char caracter;
    FILE *file;
    file = fopen(archivo, "r");
    int i=0;

    if(file){
        while(fscanf(file,"%c",&caracter)==1){
            if(caracter != ' ' && caracter != '\n'){
                buffer[i]=caracter;
                i++;
            } else {
                claveAux = sigPalabra(buffer,i);
                if(m_recuperar(mapeo,claveAux) == NULL){
                    *valorAux = 1;
                } else {
                    *valorAux = *((int*)m_recuperar(mapeo,claveAux))+1;
                }
                m_insertar(mapeo,claveAux,valorAux);
                valorAux=(int*) malloc(sizeof(int));
                i = 0;
            }
        }
    }
    fclose(file);

    claveAux = sigPalabra(buffer,i);
    if(m_recuperar(mapeo,claveAux) == NULL){
        *valorAux = 1;
            } else {
        *valorAux = *((int*)m_recuperar(mapeo,claveAux))+1;
    }
    m_insertar(mapeo,claveAux,valorAux);
    valorAux=(int*) malloc(sizeof(int));
    i = 0;

    programa(mapeo);

    printf("Programa finalizado");
    scanf("%s");

    return 0;
}

void programa(tMapeo m){
    int i = -1;
    int cdadApariciones;
    char buscar[MAXCHAR];
    while(i!=0){
        printf("Ingrese 1 para buscar la cantidad de apariciones de una palabra, ingrese 0 para cerrar: ");
        scanf("%i",&i);
        if(i == 1){
            printf("Ingrese la palabra a buscar: ");
            scanf("%s",&buscar);
           if(m_recuperar(m,sigPalabra(buscar,strlen(buscar))) != NULL){
                cdadApariciones = *((int*)m_recuperar(m,sigPalabra(buscar,strlen(buscar))));
                printf("Cantidad de apariciones: %i\n",cdadApariciones);
            } else {
                printf("La palabra no existe\n");
            }
        } else if(i == 0){
            salir(m);
        }
    }
}

void salir(tMapeo m){
    m_destruir(&m,fEliminarC,fEliminarV);
}
