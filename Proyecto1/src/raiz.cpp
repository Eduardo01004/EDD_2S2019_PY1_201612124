#include "raiz.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <fstream>
#include <iomanip>

using namespace std;

raiz::raiz()
{
    primerocolumna=NULL;
    ultimocolumna=NULL;
    primerofila=NULL;
    ultimofila=NULL;

}



void raiz::InsertarMatriz(int coorx,int coory,string color){
    cabecera *auxiliarcolumna=primerocolumna;
    cabecera *auxiliarfila=primerofila;
    bool flag;
    bool flagsave=false;
    if(auxiliarcolumna!=NULL){
    while(auxiliarcolumna->numero!=coorx){
        auxiliarcolumna=auxiliarcolumna->siguiente;
    }

    while(auxiliarfila->numero!=coory){
        auxiliarfila=auxiliarfila->siguiente;
    }
    Nodomatriz *matriztemporal=new Nodomatriz();
    Nodomatriz *temporalmatriz;
    matriztemporal->x=coorx;
    matriztemporal->color = color;
    matriztemporal->y=coory;


    Nodomatriz *temporalmatrizMatriz = buscar(coorx,coory);
    if( temporalmatrizMatriz != NULL){
        temporalmatrizMatriz->color = color;
    }else{

        if(auxiliarcolumna->primeromatriz==NULL){
           matriztemporal ->siguiente=NULL;
            auxiliarcolumna->primeromatriz=matriztemporal;
            auxiliarcolumna->ultimomatriz=matriztemporal;
        }else{
            Nodomatriz *auxiliarmatriz=auxiliarcolumna->primeromatriz;
            flag=true;
            while(flag==true){
                if(auxiliarmatriz!=NULL){
                    if(auxiliarmatriz->y == coory){
                        flag=false;
                        flagsave=true;
                        break;
                    }else{
                        auxiliarmatriz=auxiliarmatriz->siguiente;
                    }
                }else{
                    flag=false;
                    flagsave=false;
                }
            }
            if(flagsave==false){
                if(coory<auxiliarcolumna->primeromatriz->y){
                    matriztemporal->anterior=NULL;
                    matriztemporal->siguiente=auxiliarcolumna->primeromatriz;
                    auxiliarcolumna->primeromatriz->anterior=matriztemporal;
                    auxiliarcolumna->primeromatriz=matriztemporal;
                }else if(coory>auxiliarcolumna->ultimomatriz->y){
                    matriztemporal->siguiente=NULL;
                    matriztemporal->anterior=auxiliarcolumna->ultimomatriz;
                    auxiliarcolumna->ultimomatriz->siguiente=matriztemporal;
                    auxiliarcolumna->ultimomatriz=matriztemporal;
                }else{
                    Nodomatriz *nodoauxiliar;
                    temporalmatriz=auxiliarcolumna->primeromatriz;
                    flag=true;
                    while(flag){
                        if(temporalmatriz->siguiente!=NULL){
                            if(coory<temporalmatriz->siguiente->y){
                              flag=false;
                            }else{
                                temporalmatriz=temporalmatriz->siguiente;
                            }
                        }else{
                            flag=false;
                        }
                    }
                    nodoauxiliar=temporalmatriz->siguiente;
                    temporalmatriz->siguiente=matriztemporal;
                    matriztemporal->siguiente=nodoauxiliar;
                }
            }
        }

        if(auxiliarfila->primeromatriz==NULL){
           matriztemporal->arriba=NULL;
           auxiliarfila->primeromatriz=matriztemporal;
           auxiliarfila->ultimomatriz=matriztemporal;
        }else{
            Nodomatriz *auxiliarmatriz=auxiliarfila->primeromatriz;
            flag=true;
            flagsave=false;
            while(flag==true){
                if(auxiliarmatriz!=NULL){
                    if(auxiliarmatriz->x==coorx){
                        flag=false;
                        flagsave=true;
                    }else{
                        auxiliarmatriz=auxiliarmatriz->arriba;
                    }
                }else{
                    flag=false;
                    flagsave=false;
                }
            }
             if(flagsave==false){
                 if(coorx<auxiliarfila->primeromatriz->x){
                     matriztemporal->abajo=NULL;
                     matriztemporal->arriba=auxiliarfila->primeromatriz;
                     auxiliarfila->primeromatriz->abajo=matriztemporal;
                     auxiliarfila->primeromatriz=matriztemporal;
                 }else if(coorx>auxiliarfila->ultimomatriz->x){
                     matriztemporal->arriba=NULL;
                     matriztemporal->abajo=auxiliarfila->ultimomatriz;
                     auxiliarfila->ultimomatriz->arriba=matriztemporal;
                     auxiliarfila->ultimomatriz=matriztemporal;
                 }else{
                    Nodomatriz *nodoauxiliar;
                     temporalmatriz=auxiliarfila->primeromatriz;
                     flag=true;
                     while(flag){
                         if(temporalmatriz->arriba!=NULL){
                             if(coorx<temporalmatriz->arriba->x){
                               flag=false;
                             }else{
                                 temporalmatriz=temporalmatriz->arriba;
                             }
                         }else{
                             flag=false;
                         }
                     }
                     nodoauxiliar=temporalmatriz->arriba;
                     temporalmatriz->arriba=matriztemporal;
                     matriztemporal->arriba=nodoauxiliar;
                 }

             }


        }
        }

    }
}

void raiz::existeX(int coorx){
    bool flag=true;
    bool flag_guardar=false;
    cabecera *temporal=primerocolumna;
    cabecera *aucoorx;
    if(primerocolumna==NULL){
       cabecera *cabeza=new cabecera();
        cabeza->numero=coorx;
        cabeza->primeromatriz=NULL;
        cabeza->siguiente=NULL;
        primerocolumna=cabeza;
        ultimocolumna=cabeza;
    }else{
        while(flag==true){
            if(temporal!=NULL){
                if(temporal->numero==coorx){
                    flag=false;
                    flag_guardar=true;
                }else{
                    temporal=temporal->siguiente;
                }
            }else{
                flag=false;
                flag_guardar=false;
            }
        }
        if(flag_guardar==false){
            cabecera*cabeza=new cabecera();
            cabeza->numero=coorx;
            cabeza->primeromatriz=NULL;

            if(coorx<primerocolumna->numero){
                cabeza->siguiente=primerocolumna;
                primerocolumna=cabeza;
            }else if(coorx>ultimocolumna->numero){
                ultimocolumna->siguiente=cabeza;
                cabeza->siguiente=NULL;
                ultimocolumna=cabeza;
            }else{
                temporal=primerocolumna;
                flag=true;
                while(flag){
                    if(temporal->siguiente!=NULL){
                        if(coorx<temporal->siguiente->numero){
                          flag=false;
                        }else{
                            temporal=temporal->siguiente;
                        }
                    }else{
                        flag=false;
                    }
                }
                aucoorx=temporal->siguiente;
                temporal->siguiente=cabeza;
                cabeza->siguiente=aucoorx;
            }


        }
    }
}
Nodomatriz* raiz::buscar(int x,int y){
    int encontradoColumna = 0;

    cabecera* aux = primerocolumna;
    //----------------------- buscar la columna ---------------------------------------
    while(aux != NULL){
        if(aux->numero == x){
            encontradoColumna = 1;
            break;
        }
        aux = aux->siguiente;
    }

    //------------------------------- recorrer la fila -----------------------------------
    if(encontradoColumna){
        Nodomatriz* aux2 = aux->primeromatriz;
        while(aux2 != NULL){
            if(aux2->y == y) return aux2;
            aux2 = aux2->siguiente;
        }
    }
    return NULL;
}

void raiz::existey(int y){

    bool estado=true;
    bool encontrado=false;
    cabecera*temp=primerofila;
    cabecera *auy;
    if(primerofila==NULL){
       cabecera *nuevo=new cabecera();
        nuevo->primeromatriz=NULL;
        nuevo->numero=y;
        nuevo->siguiente=NULL;
        primerofila=nuevo;
        ultimofila=nuevo;
    }else{
        while(estado==true){
            if(temp!=NULL){
                if(temp->numero==y){
                    estado=false;
                    encontrado=true;
                }else{
                    temp=temp->siguiente;
                }
            }else{
                estado=false;
                encontrado=false;
            }
        }

        if(encontrado==false){
       cabecera *nuevo=new cabecera();
            nuevo->primeromatriz=NULL;
            nuevo->numero=y;

            if(y<primerofila->numero){
                nuevo->siguiente=primerofila;
                primerofila=nuevo;
            }else if(y>ultimofila->numero){
                ultimofila->siguiente=nuevo;
                nuevo->siguiente=NULL;
                ultimofila=nuevo;
            }else{
                temp=primerofila;
                estado=true;
                while(estado){
                    if(temp->siguiente!=NULL){
                        if(y<temp->siguiente->numero){
                          estado=false;
                        }else{
                            temp=temp->siguiente;
                        }
                    }else{
                        estado=false;
                    }
                }
                auy=temp->siguiente;
                temp->siguiente=nuevo;
                nuevo->siguiente=auy;
            }


        }
    }
}

    //--------------------------------- OBTENER TAMANO DE LA MATRIZ----------------------------------------------------
int raiz::cantidadColumnas(){
    if(ultimocolumna != NULL) return ultimocolumna->numero;
    return -1;
}
int raiz::cantidadFilas(){
    if(ultimofila != NULL) return ultimofila->numero;
    return -1;
}

void raiz::GraficarDispersa()
{
    std::ofstream afile("Matriz.dot",std::ios::out);
    cabecera *aux2=primerocolumna;
    cabecera *aux=primerofila;
    afile << "digraph G{\n";
    afile << "node [shape = box] \n";
    afile << "raiz[label=\"*\"  group=1];\n";

    if(aux != NULL){

        while(aux != NULL){
            long int point = reinterpret_cast<long int>(aux);
            afile << point << " [label=\"" << aux->numero << "\" group = 1]; \n";
            aux = aux->siguiente;
        }
        aux=primerofila;
        while(aux != NULL){
            long int point = reinterpret_cast<long int>(aux);
            if(aux->siguiente != NULL){
                long int point2 = reinterpret_cast<long int>(aux->siguiente);
                afile << point << "->" << point2 << ";\n";
                afile << point2 << "->" << point << ";\n";//si se chinga puede eque sea esto
            }
             aux = aux->siguiente;
        }
//Funciona Bien---------------------------------------------------
        while(aux2 != NULL){
            long int point = reinterpret_cast<long int>(aux2);
            int level = aux2->numero + 2;
            afile << point << " [label=\"" << aux2->numero << "\" group = " << level << "]; \n";
            aux2 = aux2->siguiente;
        }
        ////////////////////////////////////////funciona////////////////////////////////////
        aux2=primerocolumna;
        while(aux2 != NULL){
            long int point = reinterpret_cast<long int>(aux2);
            if(aux2->siguiente != NULL){
                long int point2 = reinterpret_cast<long int>(aux2->siguiente);
                afile << point << "->" << point2 << ";\n";
                afile << point2 << "->" << point << ";\n";
            }
             aux2 = aux2->siguiente;
        }

//----------------------------------------------------------------------------------------------------
        aux=primerofila;
        aux2=primerocolumna;
        long int a = reinterpret_cast<long int>(aux);
        long int b = reinterpret_cast<long int>(aux2);
        afile << "raiz -> " << a << ";\n";
        afile << "raiz -> " << b << ";\n";
        afile << "{ rank  = same; raiz ";

        while(aux2 != NULL){
            long int a = reinterpret_cast<long int>(aux2);
            afile << a << "; ";
            aux2 = aux2->siguiente;
        }
        afile << "}\n";
//////////----------------------------------
        aux2=primerocolumna;
        while(aux2 != NULL){
            int level = aux2->numero + 2;
            Nodomatriz *temp = aux2->primeromatriz;
            if(temp!=NULL){
                while(temp!=NULL){
                    long int point = reinterpret_cast<long int>(temp);
                    afile << point << " [style=filled,fillcolor=seashell2,label= \""<<temp->color<<"\" group = " << level << " ]; \n";
                    temp = temp->siguiente;
                }
            }
            aux2 = aux2->siguiente;
        }
        //**********************************fila entre nodos matriz***********************************
         aux=primerofila;
        while(aux != NULL){
            long int fi = reinterpret_cast<long int>(aux);
            Nodomatriz *temp=aux->primeromatriz;
            if(temp != NULL){
                long int nod = reinterpret_cast<long int>(temp);
                afile << fi << "->" << nod << ";\n";
                while(temp->arriba != NULL){
                    nod= reinterpret_cast<long int>(temp);
                    long int nextNode = reinterpret_cast<long int>(temp->arriba);
                    afile << nod << "->" << nextNode << ";\n";
                    afile << nextNode << "->" << nod << ";\n";
                    temp = temp->arriba;
                }
                afile << "{ rank = same; " << fi << "; ";
                temp = aux->primeromatriz;
                while(temp!=NULL){
                    long int rankFi = reinterpret_cast<long int>(temp);
                    afile << rankFi << "; ";
                    temp = temp->arriba;
                }
                afile << "}\n";
            }
            aux = aux->siguiente;
        }

/*------------------------------------------------------------------------------------*/
        aux2=primerocolumna;
        while(aux2 != NULL){
            long int col = reinterpret_cast<long int>(aux2);
            Nodomatriz *temp=aux2->primeromatriz;
            if(temp != NULL){
                long int nod = reinterpret_cast<long int>(temp);
                afile << col << "->" << nod << ";\n";
                while(temp->siguiente != NULL){
                    nod= reinterpret_cast<long int>(temp);
                    long int nextNode = reinterpret_cast<long int>(temp->siguiente);
                    afile << nod << "->" << nextNode << ";\n";
                    afile << nextNode << "->" << nod << ";\n";
                    temp=temp->siguiente;
                }
            }
            aux2=aux2->siguiente;
        }


    }
    afile<<"}\n";
    afile.close();
    system("dot -Tpng Matriz.dot -o Matriz.png");
    system("Matriz.png");

}

void raiz::graficarMatriz(){
    std::ofstream afile("Matriz.dot",std::ios::out);
    cabecera *auxiliar=primerocolumna;
    cabecera *auxiliar2=primerofila;
    afile << "digraph G{\n";
    afile << "subgraph cluster_area{\n";
    afile << "{rank=same raiz ";

    while(auxiliar!=NULL){
        long int point = reinterpret_cast<long int>(auxiliar);
        afile << point;
        afile << " ";
        auxiliar=auxiliar->siguiente;
    }
    afile << "}\n";
    afile << "}\n";
    auxiliar=primerocolumna;
    if(auxiliar!=NULL){
        afile << "subgraph cluster_lista_columna{\n";
        afile <<  "raiz[shape=box,label=\"*\"];\n";
        long int point = reinterpret_cast<long int>(auxiliar);
        afile << "raiz->"<<point<<";\n";
        while(auxiliar!=NULL){
            long int point = reinterpret_cast<long int>(auxiliar);
            if(auxiliar->siguiente!=NULL){
                        long int point2 = reinterpret_cast<long int>(auxiliar->siguiente);
                        afile << point << "[shape=box,label=\"" <<auxiliar->numero<<"\"];\n";
                        afile << point2 << "[shape=box,label=\"" <<auxiliar->siguiente->numero<<"\"];\n";
                        afile <<point<<"->"<<point2<<";\n";
            }else if(auxiliar==primerocolumna){
                        afile<<point<<"[shape=box,label=\""<<auxiliar->numero<<"\"];\n";
            }
            auxiliar=auxiliar->siguiente;

        }
         afile<<"}\n";
        auxiliar=primerocolumna;
         afile << "subgraph cluster_lista_Nodos{\n";
        while(auxiliar!=NULL){
            Nodomatriz *temp=auxiliar->primeromatriz;
            if(temp!=NULL){
                point=reinterpret_cast<long int>(auxiliar);
                long int point2=reinterpret_cast<long int>(temp);
                afile <<point<<"->"<<point2<<";\n";
                while(temp!=NULL){
                    if(temp!=auxiliar->ultimomatriz){
                         long int point = reinterpret_cast<long int>(temp);
                         long int point2 = reinterpret_cast<long int>(temp->siguiente);
                         afile<<point<<"->"<<point2<<";\n";
                         afile <<point <<"[label=\""<<temp->color<<"\"]\n";
                         afile<<point2<<"->"<<point<<";\n";
                         }else if(temp==auxiliar->primeromatriz || temp==auxiliar->ultimomatriz){
                            long int point = reinterpret_cast<long int>(temp);
                            afile<<point<<"[label=\""<<temp->color<<"\"]\n";
                         }
                    temp=temp->siguiente;
                }
            }
            auxiliar=auxiliar->siguiente;
        }
         afile<<"}\n";
        point=reinterpret_cast<long int>(auxiliar2);
        if(auxiliar2!=NULL){
            afile<<"raiz->"<<point<<";\n";
            int contador=0;
            while(auxiliar2!=NULL){
               long int point = reinterpret_cast<long int>(auxiliar2);
               if(auxiliar2->siguiente!=NULL){
                            long int point2 = reinterpret_cast<long int>(auxiliar2->siguiente);
                            afile<<point<<"[shape=box,label=\""<<auxiliar2->numero<<"\"];\n";
                            afile<<point2<<"[shape=box,label=\""<<auxiliar2->siguiente->numero<<"\"];\n";
                            afile<<point<<"->"<<point2<<";\n";
               }else if(auxiliar2==primerofila){
                    afile<<point<<"[shape=box,label=\""<<auxiliar2->numero<<"\"];\n";
               }
               Nodomatriz *temp=auxiliar2->primeromatriz;
                 point = reinterpret_cast<long int>(auxiliar2);
                 afile<<"{rank=same "<<point<<" ";
               while(temp!=NULL){
                   long int point = reinterpret_cast<long int>(temp);
                   afile<<point;
                   afile<<" ";
                   temp=temp->arriba;
               }
                    afile<<"}\n";
               temp=auxiliar2->primeromatriz;
               if(temp!=NULL){
                   point=reinterpret_cast<long int>(auxiliar2);
                   long int point2=reinterpret_cast<long int>(temp);
                   afile<<point<<"->"<<point2<<";\n";
                   while(temp!=NULL){
                       if(temp!=auxiliar2->ultimomatriz){
                            long int point = reinterpret_cast<long int>(temp);
                            long int point2 = reinterpret_cast<long int>(temp->arriba);
                            afile<<point<<"->"<<point2<<";\n";
                            afile<<point2<<"->"<<point<<";\n";
                            }else if(temp==auxiliar2->primeromatriz || temp==auxiliar2->ultimomatriz){
                               long int point = reinterpret_cast<long int>(temp);
                            }
                       temp=temp->arriba;
                   }
               }

                auxiliar2=auxiliar2->siguiente;
                contador+=1;
            }

        }

    }
    afile<<"}\n";
    afile.close();
    system("dot -Tpng Matriz.dot -o Matriz.png");
    system(" Matriz.png");
}





raiz::~raiz(){}