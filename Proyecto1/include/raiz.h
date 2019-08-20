#ifndef RAIZ_H
#define RAIZ_H
#include "cabecera.h"
#include <string.h>
using namespace std;

class raiz
{
    public:
    raiz();
    cabecera *primerocolumna;
    cabecera*ultimocolumna;
    cabecera *primerofila;
    cabecera*ultimofila;
    void InsertarMatriz(int ,int,string);
    void existeX(int);
    void existey(int);
    int cantidadColumnas();
    int cantidadFilas();
    void graficarMatriz();
    void GraficarDispersa();
    Nodomatriz* buscar(int,int);
    ~raiz();

};
#endif // RAIZ_H
