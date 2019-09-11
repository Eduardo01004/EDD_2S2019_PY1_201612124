#include "NodoABB.h"
#include <stdlib.h>

NodoABB::NodoABB(string nombre,int hightimagen,int widthimagen,int hightpixel,int widthpixel)
{
    izquierdo = NULL;
    derecho = NULL;
    this->nombre=nombre;
    this->hightimagen=hightimagen;
    this->widthimagen=widthimagen;
    this->hightpixel=hightpixel;
    this->widthpixel=widthpixel;
    this->matriz=new Profundidad_Matriz();
}

NodoABB::~NodoABB()
{}
