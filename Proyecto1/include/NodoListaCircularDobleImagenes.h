#ifndef NODOLISTACIRCULARDOBLEIMAGENES_H
#define NODOLISTACIRCULARDOBLEIMAGENES_H
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <fstream>
#include <iomanip>
#include "Profundidad_Matriz.h"

using namespace std;

class NodoListaCircularDobleImagenes
{
    public:
        NodoListaCircularDobleImagenes();
        string filtro;
        NodoListaCircularDobleImagenes *siguiente;
        NodoListaCircularDobleImagenes *anterior;
        Profundidad_Matriz *copiacubo;

};

#endif // NODOLISTACIRCULARDOBLEIMAGENES_H
