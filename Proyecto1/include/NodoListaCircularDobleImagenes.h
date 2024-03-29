#ifndef NODOLISTACIRCULARDOBLEIMAGENES_H
#define NODOLISTACIRCULARDOBLEIMAGENES_H
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <fstream>
#include <iomanip>
#include "Profundidad_Matriz.h"
#include "NodoABB.h"
using namespace std;

class NodoListaCircularDobleImagenes
{
    public:
        NodoListaCircularDobleImagenes();
        string filtro;
        NodoListaCircularDobleImagenes *siguiente;
        NodoListaCircularDobleImagenes *anterior;
        Profundidad_Matriz *copiacubo;
        NodoABB *imagen;

};

#endif // NODOLISTACIRCULARDOBLEIMAGENES_H
