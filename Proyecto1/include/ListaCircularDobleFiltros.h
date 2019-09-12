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
        NodoListaCircularDobleImagenes *Buscar(string filtro);
        void Mostrar();
};

#endif // LISTACIRCULARDOBLEFILTROS_H
