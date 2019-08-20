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
		char nq[20];
		char np[20];
		strcpy(nq,q->nombre.c_str());
		strcpy(np,p->nombre.c_str());
		if(strcmp(nq,np)<=0)
		p->izquierdo=Insertar(p->izquierdo,q);
		else
		p->derecho=Insertar(p->derecho,q);
	}
	return p;
}

void ArbolABB::Crear(string nombre,int dimension, int tamano){
    NodoABB* nuevo = new NodoABB(nombre,dimension,tamano);
	raiz=Insertar(raiz,nuevo);
}

void ArbolABB::Grafica_auxiliar(NodoABB* node, FILE* stream)
{
    if(node != NULL)
    {
        long int point = reinterpret_cast<long int>(node);
        fprintf(stream,"%d[label=\"Nombre: %s Dimension: %d Tamano: %d\"];\n",point,node->nombre.c_str(),node->dimension,node->tamano);
    }
	if (node->izquierdo)
	{
        long int point = reinterpret_cast<long int>(node);
        long int point2 = reinterpret_cast<long int>(node->izquierdo);
		fprintf(stream, "%d -> %d;\n", point,point2);
		Grafica_auxiliar(node->izquierdo, stream);
	}
	if (node->derecho)
	{
        long int point = reinterpret_cast<long int>(node);
        long int point2 = reinterpret_cast<long int>(node->derecho);
		fprintf(stream, "%d -> %d;\n", point,point2);
		Grafica_auxiliar(node->derecho, stream);
	}
}

void ArbolABB::GraficarABB(NodoABB *tree,FILE* stream)
{
	fprintf(stream, "digraph BINARIO {\n");
	fprintf(stream, "node [fontname=\"Arial\", color=gray30, style=	rounded];\n");
	if (!tree)
	fprintf(stream, "\n");
	else if (!tree->derecho && !tree->izquierdo)
	{
        long int point = reinterpret_cast<long int>(tree);
        fprintf(stream, "%d;\n", point);
	}
	else
	Grafica_auxiliar(tree, stream);
	fprintf(stream, "}\n");
}
void ArbolABB::graficaBinario(){
	FILE *archivo;
	archivo=fopen("ABB.dot","w");
	GraficarABB(raiz,archivo);
	fclose(archivo);
	system("dot -Tjpg ABB.dot -o ABB.jpg");
    //system(" ABB.jpg");
}


void ArbolABB::mostrarInOrden(NodoABB * raiz)
{
    if(raiz != NULL){
        mostrarInOrden(raiz->izquierdo);
        cout<<"Capa: "<<raiz->nombre.c_str()<<endl;
        mostrarInOrden(raiz->derecho);

    }
}
void ArbolABB::GraficarInOrden()
{
    FILE *archivo;
    archivo=fopen("Inorden.dot","w");
    fprintf(archivo, "digraph inorden {\n");
    HacerInorden(raiz,archivo);
    //Inorden(archivo,raiz);
    fprintf(archivo, "}\n");
    fclose(archivo);
    system("dot -Tjpg Inorden.dot -o Inorden.jpg");
    system(" Inorden.jpg");
}

void ArbolABB::HacerInorden(NodoABB * raiz,FILE* stream){

    if(raiz != NULL){
        HacerInorden(raiz->izquierdo,stream);
        fprintf(stream,"%s[shape=record, style=filled, fillcolor=seashell2,label=\"Nombre: %s\"];\n",raiz->nombre.c_str(),raiz->nombre.c_str());
        if (raiz->derecho != NULL){

            fprintf(stream, "%s -> %s;\n ",raiz->nombre.c_str(),raiz->derecho->nombre.c_str());
        }
        if (raiz->izquierdo != NULL){
            fprintf(stream, "%s -> %s;\n ",raiz->nombre.c_str(),raiz->izquierdo->nombre.c_str());
        }
        HacerInorden(raiz->derecho,stream);
    }

}

void ArbolABB:: Inorden(FILE* fs, NodoABB *raiz)
{
    if (raiz != NULL){

        if(raiz -> izquierdo != NULL)fprintf(fs, "%s -> %s; \n", raiz->nombre.c_str(), raiz->izquierdo->nombre.c_str());
        if(raiz -> derecho != NULL) fprintf(fs, "%s -> %s; \n", raiz->nombre.c_str(), raiz->derecho->nombre.c_str());
        Inorden(fs, raiz->izquierdo);
        Inorden(fs, raiz->derecho);
    }
}
void ArbolABB::GraficarPreOrden()
{
    FILE *archivo;
    archivo=fopen("Preorden.dot","w");
    fprintf(archivo, "digraph preorden {\n");
    Inorden(archivo,raiz);
    fprintf(archivo, "}\n");
    fclose(archivo);
    system("dot -Tjpg Preorden.dot -o Preorden.jpg");
    system(" Preorden.jpg");
}



ArbolABB::~ArbolABB()
{}
