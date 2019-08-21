#ifndef NODODOBLEPROFUNDIDAD_H
#define NODODOBLEPROFUNDIDAD_H
#include "raiz.h"


class NodoDobleProfundidad
{
    public:
        NodoDobleProfundidad();
        int profundidad;
        raiz *matriz;
        NodoDobleProfundidad *siguiente;
        NodoDobleProfundidad *atras;

};

#endif // NODODOBLEPROFUNDIDAD_H
