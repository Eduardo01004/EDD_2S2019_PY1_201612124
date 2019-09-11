#include "ArbolABB.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <fstream>
#include <iomanip>

ArbolABB::ArbolABB()
{
    raiz=NULL;
}

NodoABB* ArbolABB::Insertar(NodoABB *p,NodoABB *q){
	if(p==NULL) p=q;
	else{
		if(q->nombre.compare(p->nombre) < 0)
            p->izquierdo=Insertar(p->izquierdo,q);
		else
            p->derecho=Insertar(p->derecho,q);
	}
	return p;
}

NodoABB* ArbolABB::buscar(NodoABB *raiz,string nombre){

    if(raiz != NULL){
        if(raiz->nombre == nombre) return raiz;
        if(raiz->derecho && nombre.compare(raiz->nombre) > 0) return buscar(raiz->derecho,nombre);
        if(raiz->izquierdo && nombre.compare(raiz->nombre) < 0) return buscar(raiz->izquierdo,nombre);
    }
    return NULL;
}

void ArbolABB::Crear(string nombre,int a, int b,int c, int d){
    NodoABB* nuevo = new NodoABB(nombre,a,b,c,d);
	raiz=Insertar(raiz,nuevo);
}

void ArbolABB::mostrarInOrden(NodoABB * raiz)
{   int contador=1;
    if(raiz != NULL){
        mostrarInOrden(raiz->izquierdo);
        cout<<raiz->nombre.c_str()<<endl;
        mostrarInOrden(raiz->derecho);

    }
}
void ArbolABB::GraficarInOrden()
{
    FILE *archivo;
    archivo=fopen("ArbolABB.dot","w");
    fprintf(archivo, "digraph ArbolABB {\n rankdir=TB;\n");
    fprintf(archivo," graph [splines=compound, nodesep=0.5];\n");
    fprintf(archivo,"node [shape = record, style=filled, fillcolor=seashell2,width=0.7,height=0.2];\n");
    HacerInorden(raiz,archivo);
    fprintf(archivo, "}\n");
    fclose(archivo);
    system("dot -Tjpg ArbolABB.dot -o ArbolABB.jpg");
    system(" ArbolABB.jpg");
}

void ArbolABB::HacerInorden(NodoABB * raiz,FILE* stream){

    if(raiz != NULL){
        HacerInorden(raiz->izquierdo,stream);
        fprintf(stream,"%s[label=\"<C0>|Nombre:%s Dimension:%dX%dpx  Tamano:%dX%dpx |<C1>\"];\n",raiz->nombre.c_str(),raiz->nombre.c_str(),raiz->widthimagen,raiz->hightimagen,raiz->widthpixel,raiz->hightpixel);
        if (raiz->derecho != NULL){

            fprintf(stream, "%s -> %s;\n ",raiz->nombre.c_str(),raiz->derecho->nombre.c_str());
        }
        if (raiz->izquierdo != NULL){
            fprintf(stream, "%s -> %s;\n ",raiz->nombre.c_str(),raiz->izquierdo->nombre.c_str());
        }
        HacerInorden(raiz->derecho,stream);
    }

}





ArbolABB::~ArbolABB()
{}
