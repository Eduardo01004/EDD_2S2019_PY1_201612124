#ifndef NODOABB_H
#define NODOABB_H
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <fstream>
#include <iomanip>
#include "Profundidad_Matriz.h"
using namespace std;
class NodoABB
{
    public:
        NodoABB();
        ~NodoABB();
        string nombre;
        int dimension;
        int tamano;
        Profundidad_Matriz *matriz;
        NodoABB(string,int,int);
        NodoABB *izquierdo;
        NodoABB *derecho;


};

#endif // NODOABB_H
