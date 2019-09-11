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
        NodoABB* buscar(NodoABB *raiz,string nombre);
        void graficaBinario();
        void Crear(string,int,int,int,int);
        void mostrarInOrden(NodoABB*);
        void GraficarInOrden();
        void HacerInorden(NodoABB * raiz,FILE* stream);
        void Inorden(FILE *stream, NodoABB *raiz);



};

#endif // ARBOLABB_H
