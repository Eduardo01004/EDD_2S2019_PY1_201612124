#ifndef NODORECORRICODOS_H
#define NODORECORRICODOS_H
#include "NodoABB.h"
using namespace std;


class NodoRecorricodos
{
    public:
        NodoRecorricodos();
        NodoRecorricodos *siguiente;
        NodoABB *recorrido;
        string imagen;
};

#endif // NODORECORRICODOS_H
