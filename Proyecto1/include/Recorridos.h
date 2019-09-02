#ifndef RECORRIDOS_H
#define RECORRIDOS_H
#include "NodoRecorricodos.h"

class Recorridos
{
    public:
        Recorridos();
        NodoRecorricodos *primero;
        NodoRecorricodos *ultimo;
        void Recorrido(string);
        void RecorridoPosOrden(string);
        void RecorridoPreOrden(string);
        void GraficarRecorridoInorden();
         void GraficarRecorridoPostOrden();
          void GraficarRecorridoPreorden();
        void Mostrar();

};

#endif // RECORRIDOS_H
