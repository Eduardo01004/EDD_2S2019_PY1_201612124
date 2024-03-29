#include "ListaCircularDobleFiltros.h"
#include <stdlib.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>

using namespace std;

ListaCircularDobleFiltros::ListaCircularDobleFiltros()
{
    primero=NULL;
    ultimo=NULL;
}

void ListaCircularDobleFiltros::InsertarFiltro(string filtro){
         NodoListaCircularDobleImagenes*nuevo=new NodoListaCircularDobleImagenes();
         nuevo->filtro=filtro;
         nuevo->copiacubo=new Profundidad_Matriz();
        if(primero == NULL){
            primero=nuevo;
            ultimo=nuevo;
            primero->siguiente=primero;
            primero->anterior=ultimo;
        }
        else{
            ultimo->siguiente=nuevo;
            nuevo->anterior=ultimo;
            nuevo->siguiente=primero;
            ultimo=nuevo;
            primero->anterior=ultimo;
        }

}


void ListaCircularDobleFiltros::Mostrar(){
    NodoListaCircularDobleImagenes *aux=primero;
    cout<<"---------"<<"Filtros Aplicados"<<"--------"<<endl;
    if (aux != NULL){
        do{
            cout<<aux->filtro<<endl;
            aux=aux->siguiente;
        }while (aux != primero);
    }else cout<<"No hay Filtros Aplicados"<<endl;

}

void ListaCircularDobleFiltros::GraficarFiltro(){
    FILE *archivo;
    archivo=fopen("ListaCircular.dot","w");
    fprintf(archivo,"digraph G {rankdir=LR;\n\n \n subgraph cluster3{label=\"Filtros\";\n");
    NodoListaCircularDobleImagenes *aux=primero;
    if(primero != NULL){
        do{
            long int point = reinterpret_cast<long int>(aux);
            long int point2 = reinterpret_cast<long int>(aux->siguiente);
            fprintf(archivo,"%d[shape=box,label=\" %s \"];\n",point,aux->filtro.c_str());
            fprintf(archivo,"%d -> %d ;\n",point,point2);
            fprintf(archivo,"%d->%d ;\n",point2,point);

            aux=aux->siguiente;
        }while(aux != primero);
    }
    fprintf(archivo,"}\n}\n");
    fclose(archivo);
    system("dot -Tpng ListaCircular.dot -o ListaCircular.png");
    system("ListaCircular.png");

}

NodoListaCircularDobleImagenes *ListaCircularDobleFiltros::Buscar(string filtro){
    NodoListaCircularDobleImagenes *aux=primero;
    do{
        if(aux->filtro == filtro)return aux;
        aux=aux->siguiente;
    }while(aux != primero);
    return NULL;
}
