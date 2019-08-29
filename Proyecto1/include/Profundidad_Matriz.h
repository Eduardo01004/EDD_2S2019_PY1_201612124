#ifndef PROFUNDIDAD_MATRIZ_H
#define PROFUNDIDAD_MATRIZ_H
#include "NodoDobleProfundidad.h"
#include "raiz.h"


class Profundidad_Matriz
{
    public:
        Profundidad_Matriz();
        NodoDobleProfundidad *primero;
        NodoDobleProfundidad *ultimo;
        void Insertar_eje_Z(int profundidad);
        NodoDobleProfundidad* Buscar(int nivel);
        void EspejoX(raiz*,raiz*);
        void mostrar();
        int cantidadColumnas(raiz*);
        void UnirCapas(raiz *capa, raiz *unido);
};

#endif // PROFUNDIDAD_MATRIZ_H
