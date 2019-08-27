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
    void InsertarTodoMatriz(int x,int y,string color);
    void graficarCapa();
    void graficarHTML();
    void GenerarSCSS();
    void FiltroNegativo();
    string RGBToHex(int rNum, int gNum, int bNum);
    int ConvertirNegativo(int);
    ~raiz();

};
#endif // RAIZ_H
