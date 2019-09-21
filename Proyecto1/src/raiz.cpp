#include "raiz.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <direct.h>

string RNeg="";
string GNeg="";
string BNeg="";
string text="";
string out="";
int a=0;
int b=0;
int c=0;
string negativo="#CCCCCC";
raiz::raiz()
{
    primerocolumna=NULL;
    ultimocolumna=NULL;
    primerofila=NULL;
    ultimofila=NULL;

}
void raiz::InsertarTodoMatriz(int x,int y,string color){
    existeX(x);
    existey(y);
    InsertarMatriz(x,y,color);

}



void raiz::InsertarMatriz(int coorx,int coory,string color){
    cabecera *auxiliarcolumna=primerocolumna;
    cabecera *auxiliarfila=primerofila;
    bool flag;
    bool flagsave=false;
    if(auxiliarcolumna != NULL){
    while(auxiliarcolumna->numero != coorx){
        auxiliarcolumna=auxiliarcolumna->siguiente;
    }

    while(auxiliarfila->numero != coory){
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
    }
    else{
        if(auxiliarcolumna->primeromatriz == NULL){
            matriztemporal ->siguiente=NULL;
            auxiliarcolumna->primeromatriz=matriztemporal;
            auxiliarcolumna->ultimomatriz=matriztemporal;
        }else{
            Nodomatriz *auxiliarmatriz=auxiliarcolumna->primeromatriz;
            flag=true;
            while(flag == true){
                if(auxiliarmatriz != NULL){
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
            if(flagsave == false){
                if(coory < auxiliarcolumna->primeromatriz->y){
                    matriztemporal->anterior=NULL;
                    matriztemporal->siguiente=auxiliarcolumna->primeromatriz;
                    auxiliarcolumna->primeromatriz->anterior=matriztemporal;
                    auxiliarcolumna->primeromatriz=matriztemporal;
                }else if(coory > auxiliarcolumna->ultimomatriz->y){
                    matriztemporal->siguiente=NULL;
                    matriztemporal->anterior=auxiliarcolumna->ultimomatriz;
                    auxiliarcolumna->ultimomatriz->siguiente=matriztemporal;
                    auxiliarcolumna->ultimomatriz=matriztemporal;
                }else{
                    temporalmatriz=auxiliarcolumna->primeromatriz;
                    flag=true;
                    while(flag){
                        if(temporalmatriz->siguiente != NULL){
                            if(coory < temporalmatriz->siguiente->y){
                              flag=false;
                            }else{
                                temporalmatriz=temporalmatriz->siguiente;
                            }
                        }else{
                            flag=false;
                        }
                    }
                    Nodomatriz *nodoauxiliar=temporalmatriz->siguiente; // esto
                    temporalmatriz->siguiente=matriztemporal;
                    matriztemporal->siguiente=nodoauxiliar;
                }
            }
        }
        //aqui se inserta en la posicion en y
        if(auxiliarfila->primeromatriz == NULL){
           matriztemporal->arriba=NULL;
           auxiliarfila->primeromatriz=matriztemporal;
           auxiliarfila->ultimomatriz=matriztemporal;
        }else{
            Nodomatriz *auxiliarmatriz=auxiliarfila->primeromatriz;
            flag=true;
            flagsave=false;
            while(flag == true){
                if(auxiliarmatriz != NULL){
                    if(auxiliarmatriz->x == coorx){
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
                 if(coorx < auxiliarfila->primeromatriz->x){
                     matriztemporal->abajo=NULL;
                     matriztemporal->arriba=auxiliarfila->primeromatriz;
                     auxiliarfila->primeromatriz->abajo=matriztemporal;
                     auxiliarfila->primeromatriz=matriztemporal;
                 }else if(coorx > auxiliarfila->ultimomatriz->x){
                     matriztemporal->arriba=NULL;
                     matriztemporal->abajo=auxiliarfila->ultimomatriz;
                     auxiliarfila->ultimomatriz->arriba=matriztemporal;
                     auxiliarfila->ultimomatriz=matriztemporal;
                 }else{
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
                     Nodomatriz *nodoauxiliar=temporalmatriz->arriba;//esto
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
    if(primerocolumna == NULL){
        cabecera *cabeza=new cabecera();
        cabeza->numero=coorx;
        cabeza->primeromatriz=NULL;
        cabeza->siguiente=NULL;
        primerocolumna=cabeza;
        ultimocolumna=cabeza;
    }else{
        while(flag == true){
            if(temporal != NULL){
                if(temporal->numero == coorx){
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

            if(coorx < primerocolumna->numero){
                cabeza->siguiente=primerocolumna;
                primerocolumna=cabeza;
            }else if(coorx > ultimocolumna->numero){
                ultimocolumna->siguiente=cabeza;
                cabeza->siguiente=NULL;
                ultimocolumna=cabeza;
            }else{
                temporal=primerocolumna;
                flag=true;
                while(flag){
                    if(temporal->siguiente != NULL){
                        if(coorx < temporal->siguiente->numero){
                          flag=false;
                        }else{
                            temporal=temporal->siguiente;
                        }
                    }else{
                        flag=false;
                    }
                }
                cabecera *aucoorx=temporal->siguiente;
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
    bool flag=true;
    bool flagsave=false;
    cabecera*temporal=primerofila;
    if(primerofila == NULL){
       cabecera *columna=new cabecera();
        columna->primeromatriz=NULL;
        columna->numero=y;
        columna->siguiente=NULL;
        primerofila=columna;
        ultimofila=columna;
    }else{
        while(flag == true){
            if(temporal!=NULL){
                if(temporal->numero == y){
                    flag=false;
                    flagsave=true;
                }else{
                    temporal=temporal->siguiente;
                }
            }else{
                flag=false;
                flagsave=false;
            }
        }

        if(flagsave == false){
            cabecera *columna=new cabecera();
            columna->primeromatriz=NULL;
            columna->numero=y;

            if(y < primerofila->numero){
                columna->siguiente=primerofila;
                primerofila=columna;
            }else if(y > ultimofila->numero){
                ultimofila->siguiente=columna;
                columna->siguiente=NULL;
                ultimofila=columna;
            }else{
                temporal=primerofila;
                flag=true;
                while(flag){
                    if(temporal->siguiente!=NULL)
                        if(y < temporal->siguiente->numero) flag=false;
                        else temporal=temporal->siguiente;
                    else flag=false;
                }
                cabecera *auy=temporal->siguiente;
                temporal->siguiente=columna;
                columna->siguiente=auy;
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
    afile << "raiz[label=\"Matriz\"  group=1];\n";
    if(aux != NULL){
        while(aux != NULL){
            long int point = reinterpret_cast<long int>(aux);
            afile << point << " [label=\"F" << aux->numero << "\" group = 1]; \n";
            aux = aux->siguiente;
        }
        aux=primerofila;
        while(aux != NULL){
            long int point = reinterpret_cast<long int>(aux);
            if(aux->siguiente != NULL){
                long int point2 = reinterpret_cast<long int>(aux->siguiente);
                afile << point << "->" << point2 << "[dir=both];\n";
                //afile << point2 << "->" << point << ";\n";//si se chinga puede eque sea esto
            }
             aux = aux->siguiente;
        }
//Funciona Bien---------------------------------------------------
        while(aux2 != NULL){
            long int point = reinterpret_cast<long int>(aux2);
            int level = aux2->numero + 2;
            afile << point << " [label=\"C" << aux2->numero << "\" group = " << level << "]; \n";
            aux2 = aux2->siguiente;
        }
        ////////////////////////////////////////funciona////////////////////////////////////
        aux2=primerocolumna;
        while(aux2 != NULL){
            long int point = reinterpret_cast<long int>(aux2);
            if(aux2->siguiente != NULL){
                long int point2 = reinterpret_cast<long int>(aux2->siguiente);
                afile << point << "->" << point2 << "[dir=both];\n";
                //afile << point2 << "->" << point << ";\n";
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
                    afile << nod << "->" << nextNode << "[dir=both];\n";
                    //afile << nextNode << "->" << nod << ";\n";
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
                afile << col << "->" << nod << "[dir=both];\n";
                while(temp->siguiente != NULL){
                    nod= reinterpret_cast<long int>(temp);
                    long int nextNode = reinterpret_cast<long int>(temp->siguiente);
                    afile << nod << "->" << nextNode << "[dir=both];\n";
                   // afile << nextNode << "->" << nod << ";\n";
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
void raiz::graficarCapa(){
}

void raiz::graficarHTML(string nombre,string nombre2){
    int x = cantidadColumnas();
    int y = cantidadFilas();
    int i = 1;
    int j = 1;
    int contador=0;
    string dot="Exports/"+nombre2+"/"+nombre+".html";
    string css=nombre+".css";
    FILE* salida;
    salida = fopen(dot.c_str(),"w");
    fprintf(salida,"<!DOCTYPE html>\n");
    fprintf(salida,"<html>\n");
    fprintf(salida,"<head>\n");
    fprintf(salida,"<link rel=\"stylesheet\" href=\"%s\">\n",css.c_str());
    fprintf(salida,"</head>\n");
    fprintf(salida,"<body>\n");
    fprintf(salida,"<div class=\"canvas\">\n");
    if( x != -1 && y != -1){
        while(j <= y){
            i = 1;
            while( i <= x){
                Nodomatriz* aux = buscar(i,j);
                if(aux != NULL){
                        fprintf(salida,"<div class=\"pixel\"></div>\n");
                }
                else{
                    fprintf(salida,"<div class=\"pixel\"></div>\n");
                }
                contador++;
                i++;
            }
            j++;
        }
    }
    fprintf(salida,"</div>\n\n\n");
    fprintf(salida,"</body>\n\n\n");
    fprintf(salida,"</html>");
    fclose(salida);

}

void raiz::GenerarSCSS(string nombre, int alto, int ancho,string nombre2){
    int x = cantidadColumnas();
    int y = cantidadFilas();
    int i = 1;
    int j = 1;
    int contador=1;
    string dot="Exports/"+nombre2+"/"+nombre+".html";
    string sal="C:/Users/Eduardo/Desktop/Edd2019/Proyecto1/"+dot;
    FILE* salida;
    string css="Exports/"+nombre2+"/"+nombre+".css";
    salida = fopen(css.c_str(),"w");
    fprintf(salida,"body { \n background: #333333; \n");
    fprintf(salida," height: 100vh;\n display: flex;\n justify-content: center;\n align-items: center; \n }\n");
    fprintf(salida,".canvas{\n");
    fprintf(salida," width: %dpx;\n height: %dpx; \n }\n",ancho,alto);
    fprintf(salida,".pixel{\n");
    fprintf(salida," width: 30px;\n height: 30px;\n float: left; \n box-shadow: 0px 0px 1px #fff;\n}\n");
    if( x != -1 && y != -1){
        while(j <= y){
            i = 1;
            while( i <= x){
                Nodomatriz* aux = buscar(i,j);
                if(aux != NULL){
                    text=aux->color;
                    std::istringstream iso(text);
                    getline(iso,RNeg,'-');
                    getline(iso,GNeg,'-');
                    getline(iso,BNeg,'-');
                    out=RGBToHex(atoi(RNeg.c_str()),atoi(GNeg.c_str()),atoi(BNeg.c_str())).c_str();
                    fprintf(salida,".pixel:nth-child(%d)\n",contador);
                    fprintf(salida,"{\n background: %s; \n}\n", out.c_str());
                }
                contador++;
                i++;
            }

            j++;
        }
    }
    fclose(salida);
    system(sal.c_str());
}
void raiz::graficarHTML2(string nombre,string nombre2){
    int x = cantidadColumnas();
    int y = cantidadFilas();
    int i = 1;
    int j = 1;
    int contador=0;
    string dot="Exports/"+nombre2+"/"+nombre+".html";
    string css=nombre+".css";
    FILE* salida;
    salida = fopen(dot.c_str(),"w");
    fprintf(salida,"<!DOCTYPE html>\n");
    fprintf(salida,"<html>\n");
    fprintf(salida,"<head>\n");
    fprintf(salida,"<link rel=\"stylesheet\" href=\"%s\">\n",css.c_str());
    fprintf(salida,"</head>\n");
    fprintf(salida,"<body>\n");
    fprintf(salida,"<div class=\"canvas\">\n");
    if( x != -1 && y != -1){
        while(j <= y){
            i = 1;
            while( i <= x){
                Nodomatriz* aux = buscar(i,j);
                if(aux != NULL){
                    fprintf(salida,"<div class=\"pixel\"></div>\n");
                }
                else{
                    fprintf(salida,"<div class=\"pixel\"></div>\n");
                }
                contador++;
                i++;
            }
            j++;
        }
    }
    fprintf(salida,"</div>\n\n\n");
    fprintf(salida,"</body>\n\n\n");
    fprintf(salida,"</html>");
    fclose(salida);
}
void raiz::GenerarSCSSNeg(string nombre,int ancho,int alto,string nombre2){
    int x = cantidadColumnas();
    int y = cantidadFilas();
    int i = 1;
    int j = 1;
    string dot="Exports/"+nombre2+"/"+nombre+".html";
    string css="Exports/"+nombre2+"/"+nombre+".css";
    string name="/"+nombre+".html";
    int contador=1;
    string sal="C:/Users/Eduardo/Desktop/Edd2019/Proyecto1/"+dot;
    FILE* salida;
    salida = fopen(css.c_str(),"w");
    fprintf(salida,"body { \n background: #333333; \n");
    fprintf(salida," height: 100vh;\n display: flex;\n justify-content: center;\n align-items: center; \n }\n");

    fprintf(salida,".canvas{\n");
    fprintf(salida," width: %dpx;\n height: %dpx; \n }\n",ancho,alto);

    fprintf(salida,".pixel{\n");
    fprintf(salida," width: 30px;\n height: 30px;\n float: left; \n box-shadow: 0px 0px 1px #fff;\n}\n");
    if( x != -1 && y != -1){
        while(j <= y){
            i = 1;
            while( i <= x){
                Nodomatriz* aux = buscar(i,j);
                if(aux != NULL){
                    text=aux->color;
                    std::istringstream iso(text);
                    getline(iso,RNeg,'-');
                    getline(iso,GNeg,'-');
                    getline(iso,BNeg,'-');
                    out=RGBToHex(atoi(RNeg.c_str()),atoi(GNeg.c_str()),atoi(BNeg.c_str())).c_str();
                    fprintf(salida,".pixel:nth-child(%d)\n",contador);
                    fprintf(salida,"{\n background: %s; \n}\n", out.c_str());
                }
                contador++;
                i++;
            }

            j++;
        }
    }
    fclose(salida);
    system(sal.c_str());
}
void raiz::GenerarSCSSGray(string nombre,int ancho,int alto,string nombre2){
    int x = cantidadColumnas();
    int y = cantidadFilas();
    int i = 1;
    int j = 1;
    string css="Exports/"+nombre2+"/"+nombre+".css";
    int contador=1;
    string dot="Exports/"+nombre2+"/"+nombre+".html";
    string sal="C:/Users/Eduardo/Desktop/Edd2019/Proyecto1/"+dot;
    FILE* salida;
    salida = fopen(css.c_str(),"w");
    fprintf(salida,"body { \n background: #333333; \n");
    fprintf(salida," height: 100vh;\n display: flex;\n justify-content: center;\n align-items: center; \n }\n");

    fprintf(salida,".canvas{\n");
    fprintf(salida," width: %dpx;\n height: %dpx; \n }\n",ancho,alto);

    fprintf(salida,".pixel{\n");
    fprintf(salida," width: 30px;\n height: 30px;\n float: left; \n box-shadow: 0px 0px 1px #fff;\n}\n");
    if( x != -1 && y != -1){
        while(j <= y){
            i = 1;
            while( i <= x){
                Nodomatriz* aux = buscar(i,j);
                if(aux != NULL){
                    text=aux->color;
                    std::istringstream iso(text);
                    getline(iso,RNeg,'-');
                    getline(iso,GNeg,'-');
                    getline(iso,BNeg,'-');
                    out=RGBToHex(atoi(RNeg.c_str()),atoi(GNeg.c_str()),atoi(BNeg.c_str())).c_str();
                    fprintf(salida,".pixel:nth-child(%d)\n",contador);
                    fprintf(salida,"{\n background: %s; \n}\n", out.c_str());
                }
                contador++;
                i++;
            }

            j++;
        }
    }
    fclose(salida);
    system(sal.c_str());
}
void raiz::GenerarSCSSX(string nombre,int ancho,int alto,string nombre2){
    int x = cantidadColumnas();
    int y = cantidadFilas();
    int i = 1;
    int j = 1;
    string dot="Exports/"+nombre2+"/"+nombre+".html";
    string sal="C:/Users/Eduardo/Desktop/Edd2019/Proyecto1/"+dot;
    string css="Exports/"+nombre2+"/"+nombre+".css";
    int contador=1;
    FILE* salida;
    salida = fopen(css.c_str(),"w");
    fprintf(salida,"body { \n background: #333333; \n");
    fprintf(salida," height: 100vh;\n display: flex;\n justify-content: center;\n align-items: center; \n }\n");

    fprintf(salida,".canvas{\n");
    fprintf(salida," width: %dpx;\n height: %dpx; \n }\n",ancho,alto);

    fprintf(salida,".pixel{\n");
    fprintf(salida," width: 30px;\n height: 30px;\n float: left; \n box-shadow: 0px 0px 1px #fff;\n}\n");
    if( x != -1 && y != -1){
        while(j <= y){
            i = 1;
            while( i <= x){
                Nodomatriz* aux = buscar(i,j);
                if(aux != NULL){
                    text=aux->color;
                    std::istringstream iso(text);
                    getline(iso,RNeg,'-');
                    getline(iso,GNeg,'-');
                    getline(iso,BNeg,'-');
                    out=RGBToHex(atoi(RNeg.c_str()),atoi(GNeg.c_str()),atoi(BNeg.c_str())).c_str();
                    fprintf(salida,".pixel:nth-child(%d)\n",contador);
                    fprintf(salida,"{\n background: %s; \n}\n", out.c_str());
                }
                contador++;
                i++;
            }

            j++;
        }
    }
    fclose(salida);
    system(sal.c_str());
}
void raiz::GenerarSCSSY(string nombre,int ancho,int alto,string nombre2){
    int x = cantidadColumnas();
    int y = cantidadFilas();
    int i = 1;
    int j = 1;
    string dot="Exports/"+nombre2+"/"+nombre+".html";
    string sal="C:/Users/Eduardo/Desktop/Edd2019/Proyecto1/"+dot;
    string css="Exports/"+nombre2+"/"+nombre+".css";
    int contador=1;
    FILE* salida;
    salida = fopen(css.c_str(),"w");
    fprintf(salida,"body { \n background: #333333; \n");
    fprintf(salida," height: 100vh;\n display: flex;\n justify-content: center;\n align-items: center; \n }\n");

    fprintf(salida,".canvas{\n");
    fprintf(salida," width: %dpx;\n height: %dpx; \n }\n",ancho,alto);

    fprintf(salida,".pixel{\n");
    fprintf(salida," width: 30px;\n height: 30px;\n float: left; \n box-shadow: 0px 0px 1px #fff;\n}\n");
    if( x != -1 && y != -1){
        while(j <= y){
            i = 1;
            while( i <= x){
                Nodomatriz* aux = buscar(i,j);
                if(aux != NULL){
                    text=aux->color;
                    std::istringstream iso(text);
                    getline(iso,RNeg,'-');
                    getline(iso,GNeg,'-');
                    getline(iso,BNeg,'-');
                    out=RGBToHex(atoi(RNeg.c_str()),atoi(GNeg.c_str()),atoi(BNeg.c_str())).c_str();
                    fprintf(salida,".pixel:nth-child(%d)\n",contador);
                    fprintf(salida,"{\n background: %s; \n}\n", out.c_str());
                }
                contador++;
                i++;
            }

            j++;
        }
    }
    fclose(salida);
    system(sal.c_str());
}
void raiz::GenerarSCSSDoble(string nombre,int ancho,int alto,string nombre2){
    int x = cantidadColumnas();
    int y = cantidadFilas();
    int i = 1;
    int j = 1;
    string dot="Exports/"+nombre2+"/"+nombre+".html";
    string sal="C:/Users/Eduardo/Desktop/Edd2019/Proyecto1/"+dot;
    string css="Exports/"+nombre2+"/"+nombre+".css";
    int contador=1;
    FILE* salida;
    salida = fopen(css.c_str(),"w");
    fprintf(salida,"body { \n background: #333333; \n");
    fprintf(salida," height: 100vh;\n display: flex;\n justify-content: center;\n align-items: center; \n }\n");

    fprintf(salida,".canvas{\n");
    fprintf(salida," width: %dpx;\n height: %dpx; \n }\n",ancho,alto);

    fprintf(salida,".pixel{\n");
    fprintf(salida," width: 30px;\n height: 30px;\n float: left; \n box-shadow: 0px 0px 1px #fff;\n}\n");
    if( x != -1 && y != -1){
        while(j <= y){
            i = 1;
            while( i <= x){
                Nodomatriz* aux = buscar(i,j);
                if(aux != NULL){
                    text=aux->color;
                    std::istringstream iso(text);
                    getline(iso,RNeg,'-');
                    getline(iso,GNeg,'-');
                    getline(iso,BNeg,'-');
                    out=RGBToHex(atoi(RNeg.c_str()),atoi(GNeg.c_str()),atoi(BNeg.c_str())).c_str();
                    fprintf(salida,".pixel:nth-child(%d)\n",contador);
                    fprintf(salida,"{\n background: %s; \n}\n", out.c_str());
                }
                contador++;
                i++;
            }

            j++;
        }
    }
    fclose(salida);
    system(sal.c_str());
}

void raiz::graficarHTMLCollage(string nombre,string nombre2){
    int x = cantidadColumnas();
    int y = cantidadFilas();
    int i = 1;
    int j = 1;
    string dot="Exports/"+nombre2+"/"+nombre+".html";
    string sal="C:/Users/Eduardo/Desktop/Edd2019/Proyecto1/"+dot;
    int contador=0;
    string css=nombre+".css";
    FILE* salida;
    salida = fopen(dot.c_str(),"w");
    fprintf(salida,"<!DOCTYPE html>\n");
    fprintf(salida,"<html>\n");
    fprintf(salida,"<head>\n");
    fprintf(salida,"<link rel=\"stylesheet\" href=\"%s\">\n",css.c_str());
    fprintf(salida,"</head>\n");
    fprintf(salida,"<body>\n");
    fprintf(salida,"<div class=\"canvas2\">\n");
    fprintf(salida,"<div class=\"canvas\">\n");
    if( x != -1 && y != -1){
        while(j <= y){
            i = 1;
            while( i <= x){
                Nodomatriz* aux = buscar(i,j);
                if(aux != NULL){
                    fprintf(salida,"<div class=\"pixel\"></div>\n");
                }
                else{
                    fprintf(salida,"<div class=\"pixel\"></div>\n");
                }
                contador++;
                i++;
            }
            j++;
        }
    }
    fprintf(salida,"</div>\n\n\n");
    fprintf(salida,"</div>\n\n\n");
    fprintf(salida,"</body>\n\n\n");
    fprintf(salida,"</html>");
    fclose(salida);

}
void raiz::GenerarSCSSCollage(string nombre,int ancho,int alto,string nombre2){
    int x = cantidadColumnas();
    int y = cantidadFilas();
    int i = 1;
    int j = 1;
    string dot="Exports/"+nombre2+"/"+nombre+".html";
    string css="Exports/"+nombre2+"/"+nombre+".css";
    int contador=1;
    string sal="C:/Users/Eduardo/Desktop/Edd2019/Proyecto1/"+dot;
    FILE* salida;
    salida = fopen(css.c_str(),"w");
    fprintf(salida,"body { \n background: #333333; \n");
    fprintf(salida," height: 100vh;\n display: flex;\n justify-content: center;\n align-items: center; \n }\n");
    fprintf(salida,".canvas2{\n");
    fprintf(salida," width: 30%;\n height: 30%; \n }\n");
    fprintf(salida,".canvas{\n");
    fprintf(salida," width: %dpx;\n height: %dpx; \n }\n",ancho,alto);

    fprintf(salida,".pixel{\n");
    fprintf(salida," width: 30px;\n height: 30px;\n float: left; \n box-shadow: 0px 0px 1px #fff;\n}\n");
    if( x != -1 && y != -1){
        while(j <= y){
            i = 1;
            while( i <= x){
                Nodomatriz* aux = buscar(i,j);
                if(aux != NULL){
                    text=aux->color;
                    std::istringstream iso(text);
                    getline(iso,RNeg,'-');
                    getline(iso,GNeg,'-');
                    getline(iso,BNeg,'-');
                    out=RGBToHex(atoi(RNeg.c_str()),atoi(GNeg.c_str()),atoi(BNeg.c_str())).c_str();
                    fprintf(salida,".pixel:nth-child(%d)\n",contador);
                    fprintf(salida,"{\n background: %s; \n}\n", out.c_str());
                }
                contador++;
                i++;
            }

            j++;
        }
    }
    fclose(salida);
    system(sal.c_str());
}
void raiz::graficaDivs(FILE* salida){
    int x = cantidadColumnas();
    int y = cantidadFilas();
    int i=1;
    int j=1;
    if( x != -1 && y != -1){
        fprintf(salida,"<div class=\"canvas\">\n");
        while(j <= y){
            i = 1;
            while( i <= x){
                Nodomatriz* aux = buscar(i,j);
                if(aux != NULL){
                    fprintf(salida,"<div class=\"pixel\"></div>\n");
                }
                else{
                    fprintf(salida,"<div class=\"pixel\"></div>\n");
                }
                i++;
            }
            j++;
        }
    }
    fprintf(salida,"</div>\n\n\n");
}
void raiz::graficarHTMLMosaic(string nombre,string nombre2){
    int x = cantidadColumnas();
    int y = cantidadFilas();
    int i = 1;
    int j = 1;
    int contador=0;
    string dot="Exports/"+nombre2+"/"+nombre+".html";
    string css=nombre+".css";
    FILE* salida;
    salida = fopen(dot.c_str(),"w");
    fprintf(salida,"<!DOCTYPE html>\n");
    fprintf(salida,"<html>\n");
    fprintf(salida,"<head>\n");
    fprintf(salida,"<link rel=\"stylesheet\" href=\"%s\">\n",css.c_str());
    fprintf(salida,"</head>\n");
    fprintf(salida,"<body>\n");
    fprintf(salida,"<div class=\"canvas2\">\n");
    if( x != -1 && y != -1){
        while(j <= y){
            i = 1;
            while( i <= x){
                Nodomatriz* aux = buscar(i,j);
                if(aux != NULL){
                    graficaDivs(salida);
                }
                else graficaDivs(salida);
                i++;
            }
            j++;
        }
        fprintf(salida,"</div>\n\n\n");
    }
    fprintf(salida,"</div>\n\n\n");
    fprintf(salida,"</body>\n\n\n");
    fprintf(salida,"</html>");
    fclose(salida);
}

void raiz::GenerarSCSSMosaic(string nombre,float ancho,float alto,string nombre2){
    int x = cantidadColumnas();
    int y = cantidadFilas();
    int i = 1;
    int j = 1;
    int color1=0;
    int color2=0;
    int color3=0;
    string dot="Exports/"+nombre2+"/"+nombre+".html";
    string salida2="";
    string sal="C:/Users/Eduardo/Desktop/Edd2019/Proyecto1/"+dot;
    string css="Exports/"+nombre2+"/"+nombre+".css";
    int contador=1;
    FILE* salida;
    salida = fopen(css.c_str(),"w");
    fprintf(salida,"body { \n background: #333333; \n");
    fprintf(salida," height: 100vh;\n display: flex;\n justify-content: center;\n align-items: center; \n }\n");
    fprintf(salida,".canvas{\n");
    fprintf(salida," width: 30px;\n height: 30px; \n  float:left;\n }\n");
    fprintf(salida,".canvas2{\n");
    fprintf(salida," width: %fpx;\n height: %fpx; \n }\n",alto,ancho);
    fprintf(salida,".pixel{\n");
    fprintf(salida," width: %fpx;\n height: %fpx;\n float: left; \n box-shadow: 0px 0px 1px #fff;\n}\n",(30*30)/alto,(30*30)/ancho);
    if( x != -1 && y != -1){
        while(j <= y){
            i = 1;
            while( i <= x){
                Nodomatriz* aux = buscar(i,j);
                if(aux != NULL){
                    text=aux->color;
                    std::istringstream iso(text);
                    getline(iso,RNeg,'-');
                    getline(iso,GNeg,'-');
                    getline(iso,BNeg,'-');
                    color1=(atoi(RNeg.c_str()))/2;
                    color2=(atoi(GNeg.c_str()))/2;
                    color3=(atoi(BNeg.c_str()))/2;
                    out=RGBToHex(atoi(RNeg.c_str()),atoi(GNeg.c_str()),atoi(BNeg.c_str())).c_str();
                    salida2=RGBToHex(color1,color2,color3);
                    fprintf(salida,".pixel:nth-child(%d)\n",contador);
                    fprintf(salida,"{\n background: %s;\nopacity: .50;\n}\n", salida2.c_str());
                    fprintf(salida,".canvas:nth-child(%d)\n",contador);
                    fprintf(salida,"{\n background: %s; \n}\n", out.c_str());
                }
                contador++;
                i++;
            }

            j++;
        }
    }
    fclose(salida);
    system(sal.c_str());
}

string raiz::RGBToHex(int rNum, int gNum, int bNum){
    string result;
    char r[255];
    sprintf(r, "%.2X", rNum);
    result.append(r );
    char g[255];
    sprintf(g, "%.2X", gNum);
    result.append(g );
    char b[255];
    sprintf(b, "%.2X", bNum);
    result.append(b );
    return "#"+result;
}
int raiz::ConvertirNegativo(int number){
    return 255-number;
}
void raiz::Negative(){
    cabecera *aux=primerocolumna;
    while (aux != NULL){
        Nodomatriz *aux2=aux->primeromatriz;
        while(aux2 != NULL){
            text=aux2->color;
            std::istringstream iso(text);
            getline(iso,RNeg,'-');
            getline(iso,GNeg,'-');
            getline(iso,BNeg,'-');
            a=ConvertirNegativo(atoi(RNeg.c_str()));
            b=ConvertirNegativo(atoi(GNeg.c_str()));
            c=ConvertirNegativo(atoi(BNeg.c_str()));
            stringstream as;
            as << a;
            stringstream poe;
            poe << b;
            stringstream l;
            l << c;
            string cadena=as.str()+"-"+poe.str()+"-"+l.str();
            out=RGBToHex(a,b,c).c_str();
            aux2->color=cadena;
            aux2=aux2->siguiente;
        }
        aux=aux->siguiente;
    }

}
void raiz::GrayScale(){
    int r=0;
    int g=0;
    int b=0;
    cabecera *aux=primerocolumna;
    while (aux != NULL){
        Nodomatriz *aux2=aux->primeromatriz;
        while(aux2 != NULL){
            text=aux2->color;
            std::istringstream iso(text);
            getline(iso,RNeg,'-');
            getline(iso,GNeg,'-');
            getline(iso,BNeg,'-');
            r=ConvertirSacleGray(atoi(RNeg.c_str()),atoi(GNeg.c_str()),atoi(BNeg.c_str()));
            g=ConvertirSacleGray(atoi(RNeg.c_str()),atoi(GNeg.c_str()),atoi(BNeg.c_str()));
            b=ConvertirSacleGray(atoi(RNeg.c_str()),atoi(GNeg.c_str()),atoi(BNeg.c_str()));
            out=RGBToHex(r,g,b).c_str();
            stringstream as;
            as << r;
            stringstream poe;
            poe << g;
            stringstream l;
            l << b;
            string cadena=as.str()+"-"+poe.str()+"-"+l.str();
            //out=RGBToHex(a,b,c).c_str();
            aux2->color=cadena;
            aux2=aux2->siguiente;
        }
        aux=aux->siguiente;
    }
}
void raiz::EspejoX(raiz *p, raiz *m ,int a){
    cabecera *aux=p->primerocolumna;
    while (aux != NULL){
        Nodomatriz *mat=aux->primeromatriz;
        while(mat != NULL){
            m->InsertarTodoMatriz(a-(mat->x-1),mat->y,mat->color);
            mat=mat->siguiente;
        }
        aux=aux->siguiente;
    }
    primerocolumna=m->primerocolumna;
    primerofila=m->primerofila;
    m->primerocolumna=NULL;
    m->primerofila=NULL;
}


void raiz::EspejoY(raiz*p,raiz *m ,int a){
    int i=0;
    int j=0;
    int x=cantidadColumnas();
    int y=cantidadFilas();
    int q=a;
    cabecera *aux=p->primerofila;
    while (aux != NULL){
        Nodomatriz *mat=aux->primeromatriz;
        while(mat != NULL){
            m->InsertarTodoMatriz(mat->y,(q+3)-(mat->x-1),mat->color);
            mat=mat->arriba;
        }
        aux=aux->siguiente;
    }
}
void raiz::DobleEspejo(raiz*p,raiz *m ,int fila,int columna){
    int i=0;
    int j=0;
    int x=cantidadColumnas();
    int y=cantidadFilas();
    int q=a;
    cabecera *aux=p->primerofila;
    while (aux != NULL){
        Nodomatriz *mat=aux->primeromatriz;
        while(mat != NULL){
            m->InsertarTodoMatriz(fila-(mat->x-1),(columna+3)-(mat->y-1),mat->color);
            mat=mat->arriba;
        }
        aux=aux->siguiente;
    }
}

void raiz::Collage(raiz *rai,raiz *matriz,int fila, int columna,int cantidadf,int cantidadcol){
    cabecera *aux=rai->primerocolumna;
    for (int i=0; i<fila;i++){
        for(int j=0; j<columna;j++){
            cabecera *aux=rai->primerofila;
            while (aux != NULL){
                Nodomatriz *mat=aux->primeromatriz;
                while(mat != NULL){
                    matriz->InsertarTodoMatriz((cantidadcol*j)+mat->x,((cantidadf+3)*i)+mat->y,mat->color);
                    mat=mat->arriba;
                }
                aux=aux->siguiente;
            }
        }
    }
}

void raiz:: LinealizarCapaColumna(){
    FILE* archivo;
    archivo=fopen("LinealizarColumna.dot","w");
    fprintf(archivo, "digraph LinearColumn {rankdir = \"LR\";\n");
    cabecera *fila=primerocolumna;
    Nodomatriz *temp=fila->primeromatriz;
    int i=0;
    int contador=0;
    fprintf(archivo,"%d[shape=record, style=filled, fillcolor=seashell2,label=\" Inicio\"];\n",0);
    fprintf(archivo,"%d[shape=record, style=filled, fillcolor=seashell2,label=\" (%d,%d)%s\"];\n",1,temp->x,temp->y,temp->color.c_str());
    fprintf(archivo,"%d->%d;\n",0,1);
    while(fila != NULL){
            temp=fila->primeromatriz;
            while(temp != NULL){
                i++;
                contador=i+1;
                long int point = reinterpret_cast<long int>(temp);
                fprintf(archivo,"%d[shape=record, style=filled, fillcolor=seashell2,label=\" (%d,%d)%s\"];\n",i,temp->x,temp->y,temp->color.c_str());
                fprintf(archivo,"%d->%d;\n",i,contador);
                temp=temp->siguiente;
            }
        fila=fila->siguiente;
    }
    fila=primerocolumna;
    fprintf(archivo,"%d[shape=record, style=filled, fillcolor=seashell2,label=\" Fin\"];\n",contador);
    fprintf(archivo, "}\n");
    fclose(archivo);
    system("dot -T svg LinealizarColumna.dot -o LinealizarColumna.svg");
    system(" LinealizarColumna.svg");

}
void raiz:: LinealizarCapaFila(){
FILE* archivo;
    archivo=fopen("LinealizarFila.dot","w");
    fprintf(archivo, "digraph LinearColumn {rankdir = \"LR\";\n");
    cabecera *fila=primerofila;
    Nodomatriz *temp=fila->primeromatriz;
    int i=0;
    int contador=0;
    fprintf(archivo,"%d[shape=record, style=filled, fillcolor=seashell2,label=\" Inicio\"];\n",0);
    fprintf(archivo,"%d[shape=record, style=filled, fillcolor=seashell2,label=\" (%d,%d)%s\"];\n",1,temp->x,temp->y,temp->color.c_str());
    fprintf(archivo,"%d->%d;\n",0,1);
    while(fila != NULL){
            temp=fila->primeromatriz;
            while(temp != NULL){
                i++;
                contador=i+1;
            long int point = reinterpret_cast<long int>(temp);
            fprintf(archivo,"%d[shape=record, style=filled, fillcolor=seashell2,label=\" (%d,%d)%s\"];\n",i,temp->x,temp->y,temp->color.c_str());
            fprintf(archivo,"%d->%d;\n",i,contador);
            temp=temp->arriba;
            }
        fila=fila->siguiente;
    }
    fila=primerocolumna;
    fprintf(archivo,"%d[shape=record, style=filled, fillcolor=seashell2,label=\" Fin\"];\n",contador);
    fprintf(archivo, "}\n");
    fclose(archivo);
    system("dot -T svg LinealizarFila.dot -o LinealizarFila.svg");
    system("LinealizarFila.svg");

}
void raiz::EditarColorRGB(int x, int y){
    cabecera *aux=primerocolumna;
    string color;
    cout<<"ingrese color"<<endl;
    cin>>color;
    Nodomatriz *aux2=buscar(x,y);
    if (aux2 != NULL){
        aux2->color=color;
    }else cout<<"dato no existe"<<endl;

}
int raiz::ConvertirSacleGray(int col,int g,int b){
        int x=0;
        x=(col*0.21)+(g*0.72)+(b*0.07);
        return x;
}


raiz::~raiz(){}
