#include "NodoABB.h"
#include <stdlib.h>

NodoABB::NodoABB(string nombre,int dimension,int tamano)
{
    izquierdo = NULL;
    derecho = NULL;
    this->nombre=nombre;
    this->dimension=dimension;
    this->tamano=tamano;
    this->matriz=new Profundidad_Matriz();
}

NodoABB::~NodoABB()
{}
