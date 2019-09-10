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
    void graficarHTML2(string);
    void GenerarScalaDeGrises();
    string RGBToHex(int rNum, int gNum, int bNum);
    int ConvertirNegativo(int);
    int ConvertirSacleGray(int,int,int);
    void Negative();
    void GrayScale();
    void EspejoX(raiz*,raiz*,int);
    void EspejoY(raiz*,raiz*,int);
    void DobleEspejo(raiz*,raiz*,int,int);
    void Collage(raiz *,raiz *,int, int,int,int);
    void LinealizarCapaColumna();
    void LinealizarCapaFila();
    void EditarColorRGB(int,int);
    void GenerarSCSSNeg(string,int,int);
    void GenerarSCSSGray(string,int,int);
    void GenerarSCSSX(string,int,int);
    void GenerarSCSSY(string,int,int);
    void GenerarSCSSDoble(string,int,int);
    void GenerarSCSSCollage(string,int,int);
    void GenerarSCSSMosaic(string,int,int);
    ~raiz();

};
#endif // RAIZ_H
