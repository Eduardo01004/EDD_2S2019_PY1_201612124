#include "Profundidad_Matriz.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <fstream>
#include <iomanip>

Profundidad_Matriz::Profundidad_Matriz()
{
   primero=NULL;
   ultimo=NULL;
}
void Profundidad_Matriz::Insertar_eje_Z(int profundidad){
    NodoDobleProfundidad *nuevo = new NodoDobleProfundidad();
    nuevo->profundidad=profundidad;
    nuevo->matriz = new raiz();
    if (primero == NULL){
        primero=nuevo;
        primero->siguiente=NULL;
        primero->atras=NULL;
        ultimo=primero;
    }
    else{
        ultimo->siguiente=nuevo;
        nuevo->siguiente=NULL;
        nuevo->atras=ultimo;
        ultimo=nuevo;
    }
}

void Profundidad_Matriz::mostrar(){
    NodoDobleProfundidad* aux=primero;
    if (aux !=NULL){
    while(aux != NULL){
        cout << aux->profundidad<<endl;
        aux=aux->siguiente;
    }
    }else cout << "vacio"<<endl;
}

NodoDobleProfundidad* Profundidad_Matriz::Buscar(int nivel){
    NodoDobleProfundidad *aux=primero;

    while(aux != NULL){
        if (aux->profundidad == nivel)return aux;
        aux=aux->siguiente;
    }
    return NULL;
}

void Profundidad_Matriz::UnirCapas(raiz *capa, raiz *unido){
    cabecera* aux = capa->primerocolumna;
    while(aux != NULL){
        Nodomatriz *aux2 = aux->primeromatriz;
        while(aux2 != NULL){
            unido->existeX(aux2->x);
            unido->existey(aux2->y);
            unido->InsertarMatriz(aux2->x,aux2->y,aux2->color);
            aux2 = aux2->siguiente;
        }
        aux = aux->siguiente;
    }
}


