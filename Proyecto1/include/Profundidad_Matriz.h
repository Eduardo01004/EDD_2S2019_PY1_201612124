#ifndef PROFUNDIDAD_MATRIZ_H
#define PROFUNDIDAD_MATRIZ_H
#include "NodoDobleProfundidad.h"


class Profundidad_Matriz
{
    public:
        Profundidad_Matriz();
        NodoDobleProfundidad *primero;
        NodoDobleProfundidad *ultimo;
        void Insertar_eje_Z(int);
};

#endif // PROFUNDIDAD_MATRIZ_H
