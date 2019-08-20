#ifndef ARBOLABB_H
#define ARBOLABB_H
#include <iostream>
#include <string.h>
#include "NodoABB.h"

class ArbolABB
{
    public:
        ArbolABB();
        ~ArbolABB();
        NodoABB *raiz;
//------------------------METODOS DEL ARBOL ABB------------------------------------
        NodoABB* Insertar(NodoABB *,NodoABB *);
        void graficaBinario();
        void Crear(string,int,int);
        void GraficarABB(NodoABB *tree,FILE* stream);
        void Grafica_auxiliar(NodoABB* node, FILE* stream);
        void mostrarInOrden(NodoABB*);
        void GraficarInOrden();
        void HacerInorden(NodoABB * raiz,FILE* stream);
        void Inorden(FILE *stream, NodoABB *raiz);
        void GraficarPreOrden();

};

#endif // ARBOLABB_H
