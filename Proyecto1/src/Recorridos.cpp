#include "Recorridos.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <fstream>
#include <iomanip>
#include <sstream>

Recorridos::Recorridos()
{
    primero=NULL;
    ultimo=NULL;
}
void Recorridos::Mostrar(){
    NodoRecorricodos *aux=primero;
    while (aux != NULL){
        cout<<aux->imagen<<endl;
        aux=aux->siguiente;
    }
}


void Recorridos::Recorrido( string dato){
    NodoRecorricodos *nuevo= new NodoRecorricodos();
    nuevo->imagen=dato;
    if (primero == NULL){
        primero=nuevo;
        primero->siguiente=NULL;
        ultimo=nuevo;
    }
    else{
        ultimo->siguiente=nuevo;
        nuevo->siguiente=NULL;
        ultimo=nuevo;
    }
}
void Recorridos::RecorridoPosOrden( string dato){
    NodoRecorricodos *nuevo= new NodoRecorricodos();
    nuevo->imagen=dato;
    if (primero == NULL){
        primero=nuevo;
        primero->siguiente=NULL;
        ultimo=nuevo;
    }
    else{
        ultimo->siguiente=nuevo;
        nuevo->siguiente=NULL;
        ultimo=nuevo;
    }
}
void Recorridos::RecorridoPreOrden( string dato){
    NodoRecorricodos *nuevo= new NodoRecorricodos();
    nuevo->imagen=dato;
    if (primero == NULL){
        primero=nuevo;
        primero->siguiente=NULL;
        ultimo=nuevo;
    }
    else{
        ultimo->siguiente=nuevo;
        nuevo->siguiente=NULL;
        ultimo=nuevo;
    }
}

void Recorridos::GraficarRecorridoInorden(){
        FILE *archivo;
        archivo=fopen("RecorridoInorden.dot","w");
        fprintf(archivo, "digraph inorden {\nrankdir = LR;\n");
        NodoRecorricodos *aux=primero;
        if (aux !=NULL){
            while(aux != NULL){
            long int  point = reinterpret_cast<long int>(aux);
            fprintf(archivo,"%d[shape=record, style=filled, fillcolor=seashell2,label=\"Imagen: %s\"];\n",point,aux->imagen.c_str());
            if( aux->siguiente != NULL){
            long int point2 = reinterpret_cast<long int>(aux->siguiente);
            fprintf(archivo,"%d->%d;\n",point,point2);
            }
            aux=aux->siguiente;
            }
        }

        fprintf(archivo, "}\n");
        fclose(archivo);
        system("dot -Tpng RecorridoInorden.dot -o RecorridoInorden.png");
        system(" RecorridoInorden.png");


    }
    void Recorridos::GraficarRecorridoPreorden(){
        FILE *archivo;
        archivo=fopen("RecorridoPreorden.dot","w");
        fprintf(archivo, "digraph Pre {\nrankdir = LR;\n");
        NodoRecorricodos *aux=primero;
        if (aux !=NULL){
            while(aux != NULL){
            long int  point = reinterpret_cast<long int>(aux);
            fprintf(archivo,"%d[shape=record, style=filled, fillcolor=seashell2,label=\"Imagen: %s\"];\n",point,aux->imagen.c_str());
            if( aux->siguiente != NULL){
            long int point2 = reinterpret_cast<long int>(aux->siguiente);
            fprintf(archivo,"%d->%d;\n",point,point2);
            }
            aux=aux->siguiente;
            }
        }

        fprintf(archivo, "}\n");
        fclose(archivo);
        system("dot -Tpng RecorridoPreorden.dot -o RecorridoPreorden.png");
        system(" RecorridoPreorden.png");


    }
    void Recorridos::GraficarRecorridoPostOrden(){
        FILE *archivo;
        archivo=fopen("RecorridoPostorden.dot","w");
        fprintf(archivo, "digraph Post {\nrankdir = LR;\n");
        NodoRecorricodos *aux=primero;
        if (aux !=NULL){
            while(aux != NULL){
            long int  point = reinterpret_cast<long int>(aux);
            fprintf(archivo,"%d[shape=record, style=filled, fillcolor=seashell2,label=\"Imagen: %s\"];\n",point,aux->imagen.c_str());
            if( aux->siguiente != NULL){
            long int point2 = reinterpret_cast<long int>(aux->siguiente);
            fprintf(archivo,"%d->%d;\n",point,point2);
            }
            aux=aux->siguiente;
            }
        }

        fprintf(archivo, "}\n");
        fclose(archivo);
        system("dot -Tpng RecorridoPostorden.dot -o RecorridoPostorden.png");
        system(" RecorridoPostorden.png");


    }


