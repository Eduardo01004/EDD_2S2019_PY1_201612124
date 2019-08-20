#ifndef LISTACIRCULARDOBLEFILTROS_H
#define LISTACIRCULARDOBLEFILTROS_H
#include "NodoListaCircularDobleImagenes.h"


class ListaCircularDobleFiltros
{
    public:
        ListaCircularDobleFiltros();
        NodoListaCircularDobleImagenes *primero;
        NodoListaCircularDobleImagenes *ultimo;
        void InsertarFiltro(string filtro);
        void GraficarFiltro();
};

#endif // LISTACIRCULARDOBLEFILTROS_H
