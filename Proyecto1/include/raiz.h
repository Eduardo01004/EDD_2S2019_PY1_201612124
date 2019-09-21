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
    void graficarHTML(string,string );
    void GenerarSCSS(string,int,int,string);
    void graficarHTML2(string,string);
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
    void GenerarSCSSNeg(string,int,int,string);
    void GenerarSCSSGray(string,int,int,string);
    void GenerarSCSSX(string,int,int,string);
    void GenerarSCSSY(string,int,int,string);
    void GenerarSCSSDoble(string,int,int,string);
    void graficarHTMLCollage(string,string);
    void GenerarSCSSCollage(string,int,int,string);
    void GenerarSCSSMosaic(string,float,float,string);
    void graficarHTMLMosaic(string,string );
    void graficaDivs(FILE*);

    ~raiz();

};
#endif // RAIZ_H
