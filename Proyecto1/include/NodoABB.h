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
using namespace std;
class NodoABB
{
    public:
        NodoABB();
        ~NodoABB();
        string nombre;
        int dimension;
        int tamano;
        NodoABB(string,int,int);
        //aqui va el nodo del cubo disperso si lo tuviera ;v
        NodoABB *izquierdo;
        NodoABB *derecho;


};

#endif // NODOABB_H
