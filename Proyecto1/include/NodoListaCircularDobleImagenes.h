#ifndef NODOLISTACIRCULARDOBLEIMAGENES_H
#define NODOLISTACIRCULARDOBLEIMAGENES_H
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <fstream>
#include <iomanip>
using namespace std;

class NodoListaCircularDobleImagenes
{
    public:
        NodoListaCircularDobleImagenes();
        string filtro;
        NodoListaCircularDobleImagenes *siguiente;
        NodoListaCircularDobleImagenes *anterior;

};

#endif // NODOLISTACIRCULARDOBLEIMAGENES_H
