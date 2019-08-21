#include "Profundidad_Matriz.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <fstream>
#include <iomanip>

Profundidad_Matriz::Profundidad_Matriz()
{
   primero=NULL;
   ultimo=NULL;
}
void Profundidad_Matriz::Insertar_eje_Z(int profundidad){
    NodoDobleProfundidad *nuevo = new NodoDobleProfundidad();
    if (primero != NULL){
        primero=nuevo;
        primero->siguiente=NULL;
        primero->atras=NULL;
        primero=ultimo;
    }
    else{
        ultimo->siguiente=nuevo;
        nuevo->siguiente=NULL;
        nuevo->atras=ultimo;
        ultimo=nuevo;
    }
}
