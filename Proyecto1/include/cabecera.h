#ifndef CABECERA_H
#define CABECERA_H
#include "Nodomatriz.h"


class cabecera
{
    public:
    cabecera();
    ~cabecera();
    int numero;
    cabecera *siguiente;
    cabecera *anterior;
    Nodomatriz *primeromatriz;
    Nodomatriz *ultimomatriz;

};

#endif // CABECERA_H
