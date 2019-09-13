#include <iostream>
#include "ArbolABB.h"
#include "raiz.h"
#include "ListaCircularDobleFiltros.h"
#include "Profundidad_Matriz.h"
#include "Recorridos.h"
#include <sstream>
#include <direct.h>
using namespace std;
ArbolABB *arbol=new ArbolABB();
raiz *matriztemporal =new raiz();
ListaCircularDobleFiltros *filtro=new ListaCircularDobleFiltros();
//Profundidad_Matriz *matrix=new Profundidad_Matriz();
Recorridos *recorrido=new Recorridos();
Recorridos *recorridoPre=new Recorridos();
Recorridos *recorridoPost=new Recorridos();
//NodoABB *aux;
NodoDobleProfundidad *aux2;
NodoListaCircularDobleImagenes* copnodo;
//---------------------------variables globales del archivo inicial-------------------------
string id="";
int faseinicial=0;
int capa=0;
string leerarchivo="";
string archivoconfig="";
string nombreimagen="";
int copiacapa;
//------------------------variables globales del archivo configuracion------------------------------------
int altoimage=0;
int anchoimage=0;
int altopixel=0;
int anchopixel=0;
int Faseconfig=0;
//-----------variables globales de los archivos de las capas ------------------------------------------------
int coorx=0;
int coory=0;
string color="";
int FaseCapas=0;
string R="";
string G="";
string B="";
string salida="";
istringstream iss;

/*-----------------------*/
int numa;
int numb;
int numc;
string texto="";
string sali="";
//-----------------variables para la salida de la imagen------------------//
int widthX=0;
int hightX=0;
int widthY=0;
int hightY=0;
int widthdoble=0;
int hightdoble=0;
int widthneg=0;
int hightneg=0;
int widthgray=0;
int hightgray=0;
int widthcollage=0;
int hightcollage=0;
float widthmosaic=0;
float hightmosaic=0;
int widthoriginal=0;
int hightoriginal=0;
string rutaarchivo="";
//---------------------------------------------fin caroables globales ----------------------------------------------------

/////////----------------------------METODOS PARA CONVERTIR COLORES -------------------------------------------//////
string RGBToHex(int rNum, int gNum, int bNum){
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
int ConvertirSacleGray(int col,int g,int b){
        int x=0;
        x=(col*0.21)+(g*0.72)+(b*0.07);
        return x;
}
int ConvertirNegativo(int number){
    return 255-number;
}
/*---------------------------ANALIZA EL ARCHIVO CONFIGURACION DE LA CAPA 0-------------------*/
void automataConfig(string lexema, string token){
    switch(Faseconfig){
     case 0:
         if(token == "datos"){
            Faseconfig=1;
         }else{
            FaseCapas=1000;
            cout<<"Se esperaba un color se encontro: "<<lexema<< " "<<token<<endl;
        }
        break;
     case 1:
         if(token == "ancho"){
            anchoimage= atoi(lexema.c_str());
            Faseconfig=2;
         }else{
            FaseCapas=1000;
            cout<<"Se esperaba un color se encontro: "<<lexema<< " "<<token<<endl;
        }
        break;
     case 2:
         if(token == "datos"){
            Faseconfig=3;
         }else{
            FaseCapas=1000;
            cout<<"Se esperaba un color se encontro: "<<lexema<< " "<<token<<endl;
        }
        break;
     case 3:
        if(token == "ancho"){
            altoimage= atoi(lexema.c_str());
            Faseconfig=4;
         }else{
            FaseCapas=1000;
            cout<<"Se esperaba un color se encontro: "<<lexema<< " "<<token<<endl;
        }
        break;
     case 4:
        if(token == "datos"){
            Faseconfig=5;
         }else{
            FaseCapas=1000;
            cout<<"Se esperaba un color se encontro: "<<lexema<< " "<<token<<endl;
        }
        break;
     case 5:
        if(token == "ancho"){
            anchopixel= atoi(lexema.c_str());
            Faseconfig=6;
         }else{
            FaseCapas=1000;
            cout<<"Se esperaba un color se encontro: "<<lexema<< " "<<token<<endl;
        }
        break;
     case 6:
        if(token == "datos"){
            Faseconfig=7;
         }else{
            FaseCapas=1000;
            cout<<"Se esperaba un color se encontro: "<<lexema<< " "<<token<<endl;
        }
        break;
     case 7:
        if(token == "ancho"){
            altopixel= atoi(lexema.c_str());
            arbol->Crear(nombreimagen,altoimage*30,anchoimage*30,altopixel,anchopixel);
            Faseconfig=8;
         }else{
            FaseCapas=1000;
            cout<<"Se esperaba un color se encontro: "<<lexema<< " "<<token<<endl;
        }
        break;
     case 8:
         if(token == "datos"){
            Faseconfig=0;
            automataConfig(lexema,token);
         }else{
            FaseCapas=1000;
            cout<<"Se esperaba un color se encontro: "<<lexema<< " "<<token<<endl;
        }
        break;


    }


}
void AnalizarConfig(string path,string archivo){
    string ruta="";
    ruta=rutaarchivo+path;
    std::ifstream in (ruta.c_str());
    if(in.is_open()){
        FILE *fp;
        fp = fopen(archivo.c_str(),"w");
        string palabra;
        string columna;
        string fila;
        string alto;
        string ancho;
        string width;
        string heigth;
        getline(in,columna,',');
        getline(in,fila,'\n');
        while(in.good()){
            getline(in,palabra,',');
            getline(in,alto,'\n');
            fprintf(fp,"%s %s\n",palabra.c_str(),"datos");
            fprintf(fp,"%s %s\n",alto.c_str(),"ancho");
        }
        fclose(fp);
    }else {
        cout<<"No existe el archivo "<< path << " del archivo configuracion"<< endl;
     }

}
void analisisSintacticoConfig(){
    std::ifstream in ("configuracion.txt");
    if(in.is_open()){
        string lexema,token;
        while(in>>lexema>>token){
            if(token == "datos") faseinicial = 0;
            automataConfig(lexema, token);
        }
    }
}

/*------------------------ANALIZA LOS ARCHIVOS DE LAS CAPAS QUE FORMAN LA IMAGEN------------*/
void AutomataArchivoCapas(string lexema, string token){
    switch(FaseCapas){
     case 0:
        if (token == "color"){
            color=lexema;
            FaseCapas=1;
        }else{
            FaseCapas=1000;
            cout<<"Se esperaba un color se encontro: "<<lexema<< " "<<token<<endl;
        }
        break;
    case 1:
        if (token == "COORX"){
            coorx = atoi(lexema.c_str());
            FaseCapas=2;
        }else{
            FaseCapas=1000;
            cout<<"Se esperaba una coordenada x se encontro: "<<lexema<< " "<<token<<endl;
        }
        break;
    case 2:
        if (token == "COORY"){
            coory = atoi(lexema.c_str());
            NodoABB *aux=arbol->buscar(arbol->raiz,nombreimagen);
            aux2=aux->matriz->Buscar(capa);
            if (aux2){
                aux2->matriz->InsertarTodoMatriz(coorx,coory,color);
            }else cout<<"no encontrado"<<endl;



            FaseCapas=3;
        }else{
            FaseCapas=1000;
            cout<<"Se esperaba una coordenada y se encontro: "<<lexema<< " "<<token<<endl;
        }
        break;


    case 3:
        if (token == "color"){
            FaseCapas=0;
            AutomataArchivoCapas(lexema,token);
        }
        else{
            FaseCapas=1000;
            cout<<"Se esperaba un id se encontro: "<<lexema<< " "<<token<<endl;
        }
        break;
    }
}

void analisisSintacticoArchivoCapas(){
    std::ifstream in ("capas.txt");
    if(in.is_open()){
        string lexema,token;
        while(in>>lexema>>token){
            if(token == "color") faseinicial = 0;
            AutomataArchivoCapas(lexema, token);
        }
    }
}

void AnalizarArchivoCapas(string path, string archivo){
    char caracter;
    int coorx=0;//fila
    int coory=1;//columna
    string ruta="";
    ruta=rutaarchivo+path;
    std::ifstream in (ruta.c_str());
    if(in.is_open()){
        FILE *fp;
        fp = fopen(archivo.c_str(),"w");
        string palabra = "";
        while(in.get(caracter)){
            if(caracter == 'x'){
            }else if( caracter == 9 || caracter == 8 || caracter == 11 || caracter == 13 || caracter ==32){
            }else if(caracter == 10){//salto de linea
                coory++;
                coorx=1;
            }
            else if(caracter == ','){
                if(palabra != "") {//forma el color
                fprintf(fp,"%s %s\n",palabra.c_str(),"color");
                fprintf(fp,"%d %s\n",coorx,"COORX");
                fprintf(fp,"%d %s\n",coory,"COORY");
                }
                coorx++;
                palabra = "";
            }else{
                palabra += caracter;
            }
        }
        fclose(fp);
    }
    else{
        cout<<"No existe el archivo "<< path << "De capas" << endl;
    }
}

/*----------------------ANALIZA EL ARCHIVO INICIAL -----------------*/
void AnalizarArchivoinicial(string path,string archivo){
    std::ifstream in (path.c_str());
    if(in.is_open()){

        FILE *fp;
        fp = fopen(archivo.c_str(),"w");
        string palabra = "";
        string columna;
        string fila;
        string profundidad;
        string archivo;
        string inicial;
        string archivoinicial;
        getline(in,columna,',');
        getline(in,fila,'\n');
        getline(in,inicial,',');
        getline(in,archivoinicial,'\n');
        fprintf(fp,"%s %s\n",archivoinicial.c_str(),"config");
        while(in.good()){
        getline(in,profundidad,',');
        getline(in,archivo,'\n');
        fprintf(fp,"%s %s\n",profundidad.c_str(),"capa");
        fprintf(fp,"%s %s\n",archivo.c_str(),"archivo");
        }
        cout<<"archivo leido" << endl;
        fclose(fp);
    }else {
        cout<<"No existe el archivo "<< path << " del archivo inicial"<< endl;
     }
}

void automataArchivoinicial(string lexema , string token){
    switch(faseinicial){
    case 0:
        if (token == "layer"){
            faseinicial=1;
        }else {
            faseinicial=111;
            cout<<"Se esperaba un id se encontro: "<<lexema<< " "<<token<<endl;
        }
        break;
    case 1:
        if (token == "file"){
            faseinicial=2;
        }else {
            faseinicial=111;
            cout<<"Se esperaba un id se encontro: "<<lexema<< " "<<token<<endl;
        }
        break;
    case 2:
        if (token == "inicial"){
            faseinicial=3;
        }else {
            faseinicial=111;
            cout<<"Se esperaba un id se encontro: "<<lexema<< " "<<token<<endl;
        }
        break;
    case 3:
        if (token == "config"){
            archivoconfig=lexema;
            AnalizarConfig(archivoconfig,"configuracion.txt");
            analisisSintacticoConfig();
            faseinicial=4;
        }else {
            faseinicial=111;
            cout<<"Se esperaba un id se encontro: "<<lexema<< " "<<token<<endl;
        }
        break;
    case 4:
        if (token == "capa"){
            capa=atoi(lexema.c_str());
           NodoABB  *aux = arbol->buscar(arbol->raiz,nombreimagen);
            if (aux != NULL){
                aux->matriz->Insertar_eje_Z(capa);
            }
            else cout<<"no existe"<<endl;
            faseinicial=5;
        }else {
            faseinicial=111;
            cout<<"Se esperaba un id se encontro: "<<lexema<< " "<<token<<endl;
        }
        break;
    case 5:
        if (token == "archivo"){
            leerarchivo=lexema;
            AnalizarArchivoCapas(leerarchivo,"capas.txt");
            analisisSintacticoArchivoCapas();
            faseinicial=6;
        }else {
            faseinicial=111;
            cout<<"Se esperaba un id se encontro: "<<lexema<< " "<<token<<endl;
        }
        break;
    case 6:
        if (token == "config"){
            faseinicial=3;
            automataArchivoinicial(lexema,token);
        }
        else if(token == "capa"){
            faseinicial=4;
            automataArchivoinicial(lexema,token);
        }
        else {
            faseinicial = 1000000;
            cout<<"Se esperaba un numero coordenada X, se encontro: "<<lexema<<" "<<token<<endl;
        }
        break;
    }

}
void analisisSintacticoArchivoInicial(){
    std::ifstream in ("archivo.txt");
    if(in.is_open()){
        string lexema,token;
        while(in>>lexema>>token){
            if(token == "config") faseinicial = 3;
            automataArchivoinicial(lexema, token);
        }
    }
}
/*---------------------------------APLICACION DE FILTROS------------------*/

///////////---------------------------------Filtro Negativo----------------------------
void FiltroNegativo(){
    string op;
    cout<<"1. Aplicar Filtro Imagen Completa"<<endl;
    cout<<"2. Aplicar Filtro a una Capa"<<endl;
    cin>>op;
    string texto="";
    int a;
    int b;
    int c;
    string cadena="";
    string r="";
    string g="";
    string bn="";
    if (op == "1"){
        filtro->InsertarFiltro("Negative");
        NodoABB *popo=arbol->buscar(arbol->raiz,nombreimagen);
        if (popo != NULL){
            int n=0;
            int m=0;
            NodoListaCircularDobleImagenes *pi=filtro->Buscar("Negative");
            if (pi != NULL){
                NodoDobleProfundidad *au=popo->matriz->primero;
                cabecera* auxcabe=au->matriz->primerocolumna;
                while (auxcabe != NULL){
                    n=auxcabe->numero;
                    widthneg=n;
                    auxcabe=auxcabe->siguiente;
                }
                cabecera* auxcab=au->matriz->primerofila;
                while (auxcab != NULL){
                    m=auxcab->numero;
                    hightneg=m;
                    auxcab=auxcab->siguiente;
                }
                while(au != NULL ){
                    cabecera *fila=au->matriz->primerocolumna;
                    pi->copiacubo->Insertar_eje_Z(au->profundidad);
                    NodoDobleProfundidad *pr=pi->copiacubo->Buscar(au->profundidad);
                    while(fila !=NULL){
                        Nodomatriz *mat=fila->primeromatriz;
                        while(mat != NULL){
                           if(pr != NULL){
                                texto=mat->color;
                                std::istringstream iso(texto);
                                getline(iso,r,'-');
                                getline(iso,g,'-');
                                getline(iso,bn,'-');
                                a=ConvertirNegativo(atoi(r.c_str()));
                                b=ConvertirNegativo(atoi(g.c_str()));
                                c=ConvertirNegativo(atoi(bn.c_str()));
                                stringstream as;
                                as << a;
                                stringstream poe;
                                poe << b;
                                stringstream l;
                                l << c;
                                cadena=as.str()+"-"+poe.str()+"-"+l.str();
                                pr->matriz->InsertarTodoMatriz(mat->x,mat->y,cadena);
                            }
                            mat=mat->siguiente;
                        }
                    fila=fila->siguiente;
                    }
                au=au->siguiente;
            }
            } else cout<<"Filtro No encontrado"<<endl;
       }else cout<<"Imagen No encontrado"<<endl;
   }
   else if(op == "2"){
        int opcion;
        filtro->InsertarFiltro("Negative");
        NodoABB *popo=arbol->buscar(arbol->raiz,nombreimagen);
        int n=0;
        int m=0;
        if (popo != NULL){
            NodoListaCircularDobleImagenes *pi=filtro->Buscar("Negative");
            cout<<"Ingrese el id de profundidad"<<endl;
            cin >> opcion;
            NodoDobleProfundidad * aux3 = pi->copiacubo->Buscar(opcion);
            if (pi != NULL){
                NodoDobleProfundidad *au=popo->matriz->primero;
                cabecera* auxcabe=au->matriz->primerocolumna;
                while (auxcabe != NULL){
                    n=auxcabe->numero;
                    widthneg=n;
                    auxcabe=auxcabe->siguiente;
                }
                cabecera* auxcab=au->matriz->primerofila;
                while (auxcab != NULL){
                    m=auxcab->numero;
                    hightneg=m;
                    auxcab=auxcab->siguiente;
                }
                while(au != NULL ){
                    cabecera *fila=au->matriz->primerocolumna;
                    pi->copiacubo->Insertar_eje_Z(au->profundidad);
                    NodoDobleProfundidad *pr=pi->copiacubo->Buscar(au->profundidad);
                    while(fila !=NULL){
                        Nodomatriz *mat=fila->primeromatriz;
                        while(mat != NULL){
                           if(pr != NULL){
                                if(au->profundidad == opcion ){
                                    texto=mat->color;
                                    std::istringstream iso(texto);
                                    getline(iso,r,'-');
                                    getline(iso,g,'-');
                                    getline(iso,bn,'-');
                                    a=ConvertirNegativo(atoi(r.c_str()));
                                    b=ConvertirNegativo(atoi(g.c_str()));
                                    c=ConvertirNegativo(atoi(bn.c_str()));
                                    stringstream as;
                                    as << a;
                                    stringstream poe;
                                    poe << b;
                                    stringstream l;
                                    l << c;
                                    cadena=as.str()+"-"+poe.str()+"-"+l.str();
                                    pr->matriz->InsertarTodoMatriz(mat->x,mat->y,cadena);

                                }
                                else pr->matriz->InsertarTodoMatriz(mat->x,mat->y,mat->color);

                            }
                            mat=mat->siguiente;
                        }
                    fila=fila->siguiente;
                    }
                au=au->siguiente;
            }
            } else cout<<"Filtro No encontrado"<<endl;
       }else cout<<"Imagen No encontrado"<<endl;
   }
}
//-----------------------filtro escala de grises--------------------------
void FiltroGrayScale(){
    string op;
    cout<<"1. Aplicar Filtro Imagen Completa"<<endl;
    cout<<"2. Aplicar Filtro a una Capa"<<endl;
    cin>>op;
    string texto="";
    int a;
    int b;
    int c;
    string cadena="";
    string r="";
    string g="";
    string bn="";
    if (op == "1"){
        filtro->InsertarFiltro("Grayscale");
        NodoABB *popo=arbol->buscar(arbol->raiz,nombreimagen);
        if (popo != NULL){
            int n=0;
            int m=0;
            NodoListaCircularDobleImagenes *pi=filtro->Buscar("Grayscale");
            if (pi != NULL){
                NodoDobleProfundidad *au=popo->matriz->primero;
                cabecera* auxcabe=au->matriz->primerocolumna;
                while (auxcabe != NULL){
                    n=auxcabe->numero;
                    widthgray=n;
                    auxcabe=auxcabe->siguiente;
                }
                cabecera* auxcab=au->matriz->primerofila;
                while (auxcab != NULL){
                    m=auxcab->numero;
                    hightgray=m;
                    auxcab=auxcab->siguiente;
                }
                while(au != NULL ){
                    cabecera *fila=au->matriz->primerocolumna;
                    pi->copiacubo->Insertar_eje_Z(au->profundidad);
                    NodoDobleProfundidad *pr=pi->copiacubo->Buscar(au->profundidad);
                    while(fila !=NULL){
                        Nodomatriz *mat=fila->primeromatriz;
                        while(mat != NULL){
                           if(pr != NULL){
                                texto=mat->color;
                                std::istringstream iso(texto);
                                getline(iso,r,'-');
                                getline(iso,g,'-');
                                getline(iso,bn,'-');
                                a=ConvertirSacleGray(atoi(r.c_str()),atoi(g.c_str()),atoi(bn.c_str()));
                                b=ConvertirSacleGray(atoi(r.c_str()),atoi(g.c_str()),atoi(bn.c_str()));
                                c=ConvertirSacleGray(atoi(r.c_str()),atoi(g.c_str()),atoi(bn.c_str()));
                                stringstream as;
                                as << a;
                                stringstream poe;
                                poe << b;
                                stringstream l;
                                l << c;
                                cadena=as.str()+"-"+poe.str()+"-"+l.str();
                                pr->matriz->InsertarTodoMatriz(mat->x,mat->y,cadena);
                            }
                            mat=mat->siguiente;
                        }
                    fila=fila->siguiente;
                    }
                au=au->siguiente;
            }
            } else cout<<"Filtro No encontrado"<<endl;
       }else cout<<"Imagen No encontrado"<<endl;
   }
   else if(op == "2"){
        int opcion;
        filtro->InsertarFiltro("Grayscale");
        NodoABB *popo=arbol->buscar(arbol->raiz,nombreimagen);
        int n=0;
        int m=0;
        if (popo != NULL){

            NodoListaCircularDobleImagenes *pi=filtro->Buscar("Grayscale");
            cout<<"Ingrese el id de profundidad"<<endl;
            cin >> opcion;
            NodoDobleProfundidad * aux3 = pi->copiacubo->Buscar(opcion);

            if (pi != NULL){

                NodoDobleProfundidad *au=popo->matriz->primero;
                cabecera* auxcabe=au->matriz->primerocolumna;
                while (auxcabe != NULL){
                    n=auxcabe->numero;
                    widthgray=a;
                    auxcabe=auxcabe->siguiente;
                }
                cabecera* auxcab=au->matriz->primerofila;
                while (auxcab != NULL){
                    m=auxcab->numero;
                    hightgray=b;
                    auxcab=auxcab->siguiente;
                }

                while(au != NULL ){
                    cabecera *fila=au->matriz->primerocolumna;
                    pi->copiacubo->Insertar_eje_Z(au->profundidad);
                    NodoDobleProfundidad *pr=pi->copiacubo->Buscar(au->profundidad);
                    while(fila !=NULL){
                        Nodomatriz *mat=fila->primeromatriz;
                        while(mat != NULL){
                           if(pr != NULL){
                                if(au->profundidad == opcion ){
                                    texto=mat->color;
                                    std::istringstream iso(texto);
                                    getline(iso,r,'-');
                                    getline(iso,g,'-');
                                    getline(iso,bn,'-');
                                    a=ConvertirSacleGray(atoi(r.c_str()),atoi(g.c_str()),atoi(bn.c_str()));
                                    b=ConvertirSacleGray(atoi(r.c_str()),atoi(g.c_str()),atoi(bn.c_str()));
                                    c=ConvertirSacleGray(atoi(r.c_str()),atoi(g.c_str()),atoi(bn.c_str()));
                                    stringstream as;
                                    as << a;
                                    stringstream poe;
                                    poe << b;
                                    stringstream l;
                                    l << c;
                                    cadena=as.str()+"-"+poe.str()+"-"+l.str();
                                    pr->matriz->InsertarTodoMatriz(mat->x,mat->y,cadena);

                                }
                                else pr->matriz->InsertarTodoMatriz(mat->x,mat->y,mat->color);

                            }
                            mat=mat->siguiente;
                        }
                    fila=fila->siguiente;
                    }
                au=au->siguiente;
            }
            } else cout<<"Filtro No encontrado"<<endl;
       }else cout<<"Imagen No encontrado"<<endl;
   }
}

//---------------------------Filtro espejo X-----------------------------
void FiltroMirrorX(){
   string op;
   cout<<"1. Aplicar Filtro Imagen Completa"<<endl;
   cout<<"2. Aplicar Filtro a una Capa"<<endl;
   cin>>op;
   if (op == "1"){
        filtro->InsertarFiltro("MirrorX");
        NodoABB *popo=arbol->buscar(arbol->raiz,nombreimagen);
        int a=0;
        int b=0;
        if (popo != NULL){
            NodoListaCircularDobleImagenes *pi=filtro->Buscar("MirrorX");
            if (pi != NULL){
                NodoDobleProfundidad *au=popo->matriz->primero;
                cabecera* auxcabe=au->matriz->primerocolumna;
                while (auxcabe != NULL){
                    a=auxcabe->numero;
                    widthX=a;
                    auxcabe=auxcabe->siguiente;
                }
                cabecera* auxcab=au->matriz->primerofila;
                while (auxcab != NULL){
                    b=auxcab->numero;
                    hightX=b;
                    auxcab=auxcab->siguiente;
                }
                while(au != NULL ){
                    cabecera *fila=au->matriz->primerocolumna;
                    pi->copiacubo->Insertar_eje_Z(au->profundidad);
                    NodoDobleProfundidad *pr=pi->copiacubo->Buscar(au->profundidad);
                    while(fila !=NULL){
                        Nodomatriz *mat=fila->primeromatriz;
                        while(mat != NULL){
                           if(pr != NULL){
                                pr->matriz->InsertarTodoMatriz(a-(mat->x-1),mat->y,mat->color);
                            }
                            mat=mat->siguiente;
                        }
                    fila=fila->siguiente;
                    }
                au=au->siguiente;
            }
            } else cout<<"Filtro No encontrado"<<endl;
       }else cout<<"Imagen No encontrado"<<endl;
   }
   else if(op == "2"){
        int opcion;
        filtro->InsertarFiltro("MirrorX");
        NodoABB *popo=arbol->buscar(arbol->raiz,"mario");
        int a=0;
        int b=0;
        if (popo != NULL){
            system("cls");
            NodoListaCircularDobleImagenes *pi=filtro->Buscar("MirrorX");
            cout<<"Ingrese el id de profundidad"<<endl;
            cin >> opcion;
            NodoDobleProfundidad * aux3 = pi->copiacubo->Buscar(opcion);
            if (pi != NULL){
                NodoDobleProfundidad *au=popo->matriz->primero;
                cabecera* auxcabe=au->matriz->primerocolumna;
                while (auxcabe != NULL){
                    a=auxcabe->numero;
                    widthX=a;
                    auxcabe=auxcabe->siguiente;
                }
                cabecera* auxcab=au->matriz->primerofila;
                while (auxcab != NULL){
                    b=auxcab->numero;
                    hightX=b;
                    auxcab=auxcab->siguiente;
                }
                while(au != NULL ){
                    cabecera *fila=au->matriz->primerocolumna;
                    pi->copiacubo->Insertar_eje_Z(au->profundidad);
                    NodoDobleProfundidad *pr=pi->copiacubo->Buscar(au->profundidad);
                    while(fila !=NULL){
                        Nodomatriz *mat=fila->primeromatriz;
                        while(mat != NULL){
                           if(pr != NULL){
                                if(au->profundidad == opcion ) pr->matriz->InsertarTodoMatriz(a-(mat->x-1),mat->y,mat->color);
                                else pr->matriz->InsertarTodoMatriz(mat->x,mat->y,mat->color);
                            }
                            mat=mat->siguiente;
                        }
                    fila=fila->siguiente;
                    }
                au=au->siguiente;
            }
            } else cout<<"Filtro No encontrado"<<endl;
       }else cout<<"Imagen No encontrado"<<endl;

}
}

//-------------------------------filtro espejo Y------------------------
void FiltroMirrorY(){
    string op;
   cout<<"1. Aplicar Filtro Imagen Completa"<<endl;
   cout<<"2. Aplicar Filtro a una Capa"<<endl;
   cin>>op;
   if (op == "1"){
        filtro->InsertarFiltro("MirrorY");
    NodoABB *popo=arbol->buscar(arbol->raiz,nombreimagen);
    int a=0;
    int b=0;
    if (popo != NULL){
        NodoListaCircularDobleImagenes *pi=filtro->Buscar("MirrorY");
        if (pi != NULL){
            NodoDobleProfundidad *au=popo->matriz->primero;
            cabecera* auxcabe=au->matriz->ultimofila;
            Nodomatriz *pito=auxcabe->primeromatriz;
            while(pito != NULL){
            while (auxcabe != NULL){
                a=auxcabe->numero;
                hightY=a;
                auxcabe=auxcabe->siguiente;
            }
                pito=pito->abajo;
            }
            cabecera* auxcab=au->matriz->primerocolumna;
                while (auxcab != NULL){
                    b=auxcab->numero;
                    widthY=b;
                    auxcab=auxcab->siguiente;
                }
            while(au != NULL ){
                cabecera *fila=au->matriz->primerocolumna;
                pi->copiacubo->Insertar_eje_Z(au->profundidad);
                NodoDobleProfundidad *pr=pi->copiacubo->Buscar(au->profundidad);
                while(fila !=NULL){
                    Nodomatriz *mat=fila->primeromatriz;
                    while(mat != NULL){
                       if(pr != NULL){
                            pr->matriz->InsertarTodoMatriz((mat->x),((a+5)-(mat->y-1)),mat->color);
                        }
                        mat=mat->siguiente;
                    }
                fila=fila->siguiente;
                }
            au=au->siguiente;
        }
        } else cout<<"Filtro No encontrado"<<endl;
   }else cout<<"Imagen No encontrado"<<endl;
   }else if(op == "2"){
       int opcion;
          filtro->InsertarFiltro("MirrorY");
    NodoABB *popo=arbol->buscar(arbol->raiz,nombreimagen);
    int a=0;
    int b=0;
    if (popo != NULL){
        system("cls");
        NodoListaCircularDobleImagenes *pi=filtro->Buscar("MirrorY");
        cout<<"Ingrese el id de profundidad"<<endl;
        cin >> opcion;
        NodoDobleProfundidad * aux3 = pi->copiacubo->Buscar(opcion);///
        if (pi != NULL){
            NodoDobleProfundidad *au=popo->matriz->primero;
            cabecera* auxcabe=au->matriz->primerocolumna;
            while (auxcabe != NULL){
                a=auxcabe->numero;
                hightY=a;
                auxcabe=auxcabe->siguiente;
            }
            cabecera* auxcab=au->matriz->primerocolumna;
                while (auxcab != NULL){
                    b=auxcab->numero;
                    widthY=b;
                    auxcab=auxcab->siguiente;
                }
            while(au != NULL ){
                cabecera *fila=au->matriz->primerocolumna;
                pi->copiacubo->Insertar_eje_Z(au->profundidad);
                NodoDobleProfundidad *pr=pi->copiacubo->Buscar(au->profundidad);
                while(fila !=NULL){
                    Nodomatriz *mat=fila->primeromatriz;
                    while(mat != NULL){
                       if(pr != NULL){
                            if(au->profundidad == opcion ) pr->matriz->InsertarTodoMatriz(a-(mat->x-1),mat->y,mat->color);
                            else pr->matriz->InsertarTodoMatriz(mat->x,mat->y,mat->color);
                        }
                        mat=mat->siguiente;
                    }
                fila=fila->siguiente;
                }
            au=au->siguiente;
        }
        } else cout<<"Filtro No encontrado"<<endl;
   }else cout<<"Imagen No encontrado"<<endl;

}

}

//---------------------------------filtro doble espejo----------------------------
void FiltroDobleMirror(){
     string op;
   cout<<"1. Aplicar Filtro Imagen Completa"<<endl;
   cout<<"2. Aplicar Filtro a una Capa"<<endl;
   cin>>op;
   if (op == "1"){
          filtro->InsertarFiltro("DobleMirror");
    NodoABB *popo=arbol->buscar(arbol->raiz,nombreimagen);
    int a=0;
    int b=0;
    if (popo != NULL){
        NodoListaCircularDobleImagenes *pi=filtro->Buscar("DobleMirror");
        if (pi != NULL){
            NodoDobleProfundidad *au=popo->matriz->primero;
            cabecera* auxfila=au->matriz->primerocolumna;
            cabecera* auxcabe=au->matriz->primerofila;
            Nodomatriz *pito=auxcabe->primeromatriz;
            while (auxcabe != NULL){
                a=auxcabe->numero;
                hightdoble=a;
                auxcabe=auxcabe->siguiente;
            }
            while (auxfila != NULL){//para x
                b=auxfila->numero;
                widthdoble=b;
                auxfila=auxfila->siguiente;
            }
            while(au != NULL ){
                cabecera *fila=au->matriz->primerocolumna;
                pi->copiacubo->Insertar_eje_Z(au->profundidad);
                NodoDobleProfundidad *pr=pi->copiacubo->Buscar(au->profundidad);
                while(fila !=NULL){
                    Nodomatriz *mat=fila->primeromatriz;
                    while(mat != NULL){
                       if(pr != NULL){
                            pr->matriz->InsertarTodoMatriz(b-(mat->x-1),((a+5)-(mat->y-1)),mat->color);
                        }
                        mat=mat->siguiente;
                    }
                fila=fila->siguiente;
                }
            au=au->siguiente;
        }
        } else cout<<"Filtro No encontrado"<<endl;
   }else cout<<"Imagen No encontrado"<<endl;
   cout<<widthdoble<<endl;

   }else if(op == "2"){
       int opcion;
          filtro->InsertarFiltro("MirrorY");
    NodoABB *popo=arbol->buscar(arbol->raiz,nombreimagen);
    int a=0;
    int b=0;
    if (popo != NULL){
        system("cls");
        NodoListaCircularDobleImagenes *pi=filtro->Buscar("DobleMirror");
        cout<<"Ingrese el id de profundidad"<<endl;
        cin >> opcion;
        NodoDobleProfundidad * aux3 = pi->copiacubo->Buscar(opcion);///
        if (pi != NULL){
            NodoDobleProfundidad *au=popo->matriz->primero;
            cabecera* auxcabe=au->matriz->primerocolumna;
            while (auxcabe != NULL){
                a=auxcabe->numero;
                widthdoble=a;
                auxcabe=auxcabe->siguiente;
            }
            cabecera* auxcab=au->matriz->primerofila;
                while (auxcab != NULL){
                    b=auxcab->numero;
                    hightdoble=b;
                    auxcab=auxcab->siguiente;
                }
            while(au != NULL ){
                cabecera *fila=au->matriz->primerocolumna;
                pi->copiacubo->Insertar_eje_Z(au->profundidad);
                NodoDobleProfundidad *pr=pi->copiacubo->Buscar(au->profundidad);
                while(fila !=NULL){
                    Nodomatriz *mat=fila->primeromatriz;
                    while(mat != NULL){
                       if(pr != NULL){
                            if(au->profundidad == opcion ) pr->matriz->InsertarTodoMatriz(b-(mat->x-1),((a+5)-(mat->y-1)),mat->color);
                            else pr->matriz->InsertarTodoMatriz(mat->x,mat->y,mat->color);
                        }
                        mat=mat->siguiente;
                    }
                fila=fila->siguiente;
                }
            au=au->siguiente;
        }
        } else cout<<"Filtro No encontrado"<<endl;
   }else cout<<"Imagen No encontrado"<<endl;
}
}

//--------------------filtro collage-------------
void FiltroCollage(){
    filtro->InsertarFiltro("Collage");
    NodoABB *popo=arbol->buscar(arbol->raiz,nombreimagen);
    int a=0;
    int b=0;
    if (popo != NULL){
        NodoListaCircularDobleImagenes *pi=filtro->Buscar("Collage");
        if (pi != NULL){
            int y;
            int x;
            cout<<"ingrese x"<<endl;
            cin>>x;
            cout<<"ingrese y"<<endl;
            cin>>y;
            NodoDobleProfundidad *au=popo->matriz->primero;
            cabecera* auxcabe=au->matriz->primerofila;
            cabecera* auxfila=au->matriz->primerocolumna;
            Nodomatriz *pito=auxcabe->primeromatriz;
            while (auxcabe != NULL){
                a=auxcabe->numero;
                hightcollage=a;
                auxcabe=auxcabe->siguiente;
            }
            while (auxfila != NULL){
                b=auxfila->numero;
                auxfila=auxfila->siguiente;
            }

            while(au != NULL ){
                for(int i=0;i<y;i++){
                    for(int j=0;j<x;j++){
                cabecera *fila=au->matriz->primerocolumna;
                pi->copiacubo->Insertar_eje_Z(au->profundidad);
                NodoDobleProfundidad *pr=pi->copiacubo->Buscar(au->profundidad);
                while(fila !=NULL){

                    Nodomatriz *mat=fila->primeromatriz;
                    while(mat != NULL){
                       if(pr != NULL){
                            pr->matriz->InsertarTodoMatriz((b*j)+mat->x,((a+5)*i)+mat->y,mat->color);

                            widthcollage=(b*x);


                        }
                        mat=mat->siguiente;
                    }
                fila=fila->siguiente;
                }
                }
                }
            au=au->siguiente;
        }

        } else cout<<"Filtro No encontrado"<<endl;
   }else cout<<"Imagen No encontrado"<<endl;
}

void FiltroMosaico(){
    filtro->InsertarFiltro("Mosaic");
    NodoABB *popo=arbol->buscar(arbol->raiz,nombreimagen);
    int a=0;
    int b=0;
    if (popo != NULL){
        NodoListaCircularDobleImagenes *pi=filtro->Buscar("Mosaic");
        if (pi != NULL){
            NodoDobleProfundidad *au=popo->matriz->primero;
            cabecera* auxcabe=au->matriz->ultimofila;
            Nodomatriz *pito=auxcabe->primeromatriz;
            while(pito != NULL){
            while (auxcabe != NULL){
                a=auxcabe->numero;
                hightmosaic=a;
                auxcabe=auxcabe->siguiente;
            }
                pito=pito->abajo;
            }
            cabecera* auxcab=au->matriz->primerocolumna;
                while (auxcab != NULL){
                    b=auxcab->numero;
                    widthmosaic=b;
                    auxcab=auxcab->siguiente;
                }
            while(au != NULL ){
                cabecera *fila=au->matriz->primerocolumna;
                pi->copiacubo->Insertar_eje_Z(au->profundidad);
                NodoDobleProfundidad *pr=pi->copiacubo->Buscar(au->profundidad);
                while(fila !=NULL){
                    Nodomatriz *mat=fila->primeromatriz;
                    while(mat != NULL){
                       if(pr != NULL){
                            pr->matriz->InsertarTodoMatriz(mat->x,mat->y,mat->color);
                        }
                        mat=mat->siguiente;
                    }
                fila=fila->siguiente;
                }
            au=au->siguiente;
        }
        } else cout<<"Filtro No encontrado"<<endl;

   }else cout<<"Imagen No encontrado"<<endl;
}

void AplicarFiltrosMenu(){
     int opcion;
    cout << "[1]Negative(Negativo)" << endl;
    cout << "[2]GrayScale(Escala de Grises)" << endl;
    cout << "[3]Mirror(Espejo)" << endl;
    cout << "[4]Collage(Collage)" << endl;
    cout << "[5]Mosaic(Mosaico)" << endl;
    cout << "\nIngresa tu opcion: ";
    cin >> opcion;
    if (opcion == 1){
        FiltroNegativo();
    }else if(opcion == 2){
        FiltroGrayScale();
    }
    else if(opcion == 3){
        string opcion;
        cout << "[1]X-Mirror(Espejo en eje X)" << endl;
        cout << "[2]Y-Mirror(Espejo en eje Y)" << endl;
        cout << "[3]Double Mirror(Espejo en ambos ejes)" << endl;
        cin>>opcion;
        if (opcion == "1"){
            FiltroMirrorX();
        }
        else if(opcion == "2"){
            FiltroMirrorY();
        }
        else if(opcion == "3"){
            FiltroDobleMirror();
        }
    }
    else if (opcion == 4){
        FiltroCollage();
    }
    else if (opcion == 5){
        FiltroMosaico();

    }

}


void MenuExports(){
    system("cls");
    int opcion;
    string nombre;
    string name;
    cout<<"1. Exportar Imagen original "<<endl;
    cout<<"2. Exportar Filtro\n\n"<<endl;
    cout<<"ingrese su opcion: "<<endl;
    cin>>opcion;
    if (opcion == 1){
        int a=0;
        int b=0;
        cout<<"-----------------"<<"IMAGES"<<"------------------------"<<endl;
        arbol->mostrarInOrden(arbol->raiz);
        cout<<"ingrese nombre de la imagen"<<endl;
        cin>>nombre;
        NodoABB *image=arbol->buscar(arbol->raiz,nombreimagen);
        if (image != NULL){
            matriztemporal = new raiz();
            Profundidad_Matriz *aux2=image->matriz;
            NodoDobleProfundidad *aux3=aux2->primero;
            cabecera *fila=aux3->matriz->primerofila;
            while(fila != NULL){
                a=fila->numero;
                fila=fila->siguiente;
            }
            cabecera *colum=aux3->matriz->primerocolumna;
            while(colum != NULL){
                b=colum->numero;
                colum=colum->siguiente;
            }
            while(aux3 != NULL){
                if (aux3->matriz != NULL){
                    aux2->UnirCapas(aux3->matriz,matriztemporal);
                }
                aux3 = aux3->siguiente;
            }
        string nom;
        cout<<"Ingrese el nombre de su imagen de salida"<<endl;
        cin>>nom;
        matriztemporal->graficarHTML(nom,nombreimagen);
        matriztemporal->GenerarSCSS(nom,a*30,b*30,nombreimagen);
        //matriztemporal->graficarCapa();
        }else cout<<"No se encontro la imagen a buscar"<<endl;

    }
    else{
        string opcion="";
        cout << "[1]Negative(Negativo)" << endl;
        cout << "[2]GrayScale(Escala de Grises)" << endl;
        cout << "[3]Mirror(Espejo)" << endl;
        cout << "[4]Collage(Collage)" << endl;
        cout << "[5]Mosaic(Mosaico)" << endl;
        cout << "\nIngresa tu opcion: ";
        cin >> opcion;
        if (opcion == "1"){
            NodoListaCircularDobleImagenes *pip=filtro->Buscar("Negative");
                if (pip != NULL){
                    Profundidad_Matriz *aux2=pip->copiacubo;
                    NodoDobleProfundidad *aux3=aux2->primero;
                    matriztemporal=new raiz();
                    while(aux3 != NULL){
                        if (aux3->matriz != NULL){
                            aux2->UnirCapas(aux3->matriz,matriztemporal);
                        }
                        aux3 = aux3->siguiente;
                    }
                string nom;
                cout<<"Ingrese el nombre de su imagen de salida"<<endl;
                cin>>nom;
                //matriztemporal->GraficarDispersa();
                matriztemporal->graficarHTML2(nom,nombreimagen);
                matriztemporal->GenerarSCSSNeg(nom,widthneg*30,hightneg*30,nombreimagen);
                }else cout<<"Filtro no Aplicado"<<endl;
        }
        else if(opcion == "2"){
            NodoListaCircularDobleImagenes *pip=filtro->Buscar("Grayscale");
                if (pip != NULL){
                    Profundidad_Matriz *aux2=pip->copiacubo;
                    NodoDobleProfundidad *aux3=aux2->primero;
                    matriztemporal=new raiz();
                    while(aux3 != NULL){
                        if (aux3->matriz != NULL){
                            aux2->UnirCapas(aux3->matriz,matriztemporal);
                        }
                        aux3 = aux3->siguiente;
                    }
                string nom;
                cout<<"Ingrese el nombre de su imagen de salida"<<endl;
                cin>>nom;
                matriztemporal->GraficarDispersa();
                matriztemporal->graficarHTML2(nom,nombreimagen);
                matriztemporal->GenerarSCSSGray(nom,widthgray*30,hightgray*30,nombreimagen);
                }else cout<<"Filtro no Aplicado"<<endl;
        }
        else if(opcion == "3"){
            string chooise;
            cout << "[1]X-Mirror(Espejo en eje X)" << endl;
            cout << "[2]Y-Mirror(Espejo en eje Y)" << endl;
            cout << "[3]Double Mirror(Espejo en ambos ejes)" << endl;
            cin>>chooise;
            if (chooise == "1"){
                NodoListaCircularDobleImagenes *pip=filtro->Buscar("MirrorX");
                if (pip != NULL){
                    Profundidad_Matriz *aux2=pip->copiacubo;
                    NodoDobleProfundidad *aux3=aux2->primero;
                    NodoDobleProfundidad *por=aux2->primero;//matriz temporal
                    matriztemporal=new raiz();
                    while(aux3 != NULL){
                        if (aux3->matriz != NULL){
                            aux2->UnirCapas(aux3->matriz,matriztemporal);
                        }
                        aux3 = aux3->siguiente;
                    }
                string nom;
                cout<<"Ingrese el nombre de su imagen de salida"<<endl;
                cin>>nom;
                matriztemporal->GraficarDispersa();
                matriztemporal->graficarHTML2(nom,nombreimagen);
                matriztemporal->GenerarSCSSX(nom,widthX*30,hightX*30,nombreimagen);
                }else cout<<"Filtro no Aplicado"<<endl;
            }
            else if(chooise == "2"){
                NodoListaCircularDobleImagenes *pip=filtro->Buscar("MirrorY");
                if (pip != NULL){
                    Profundidad_Matriz *aux2=pip->copiacubo;
                    NodoDobleProfundidad *aux3=aux2->primero;
                    NodoDobleProfundidad *por=aux2->primero;//matriz temporal
                    matriztemporal=new raiz();
                    while(aux3 != NULL){
                        if (aux3->matriz != NULL){
                            aux2->UnirCapas(aux3->matriz,matriztemporal);
                        }
                    aux3 = aux3->siguiente;
                    }
                    string nom;
                    cout<<"Ingrese el nombre de su imagen de salida"<<endl;
                    cin>>nom;
                    matriztemporal->GraficarDispersa();
                    matriztemporal->graficarHTML2(nom,nombreimagen);
                    matriztemporal->GenerarSCSSY(nom,widthY*30,hightY*30,nombreimagen);
                }else cout<<"Filtro no Aplicado"<<endl;
            }
            else if (chooise == "3"){
                NodoListaCircularDobleImagenes *pip=filtro->Buscar("DobleMirror");
                if (pip != NULL){
                    Profundidad_Matriz *aux2=pip->copiacubo;
                    NodoDobleProfundidad *aux3=aux2->primero;
                    NodoDobleProfundidad *por=aux2->primero;//matriz temporal
                    matriztemporal=new raiz();
                    while(aux3 != NULL){
                        if (aux3->matriz != NULL){
                            aux2->UnirCapas(aux3->matriz,matriztemporal);
                        }
                    aux3 = aux3->siguiente;
                    }
                    string nom;
                    cout<<"Ingrese el nombre de su imagen de salida"<<endl;
                    cin>>nom;
                    matriztemporal->GraficarDispersa();
                    matriztemporal->graficarHTML2(nom,nombreimagen);
                    matriztemporal->GenerarSCSSDoble(nom,(widthdoble-1)*30,hightdoble*30,nombreimagen);
                }else cout<<"Filtro no Aplicado"<<endl;
            }
        }
        else if(opcion == "4"){
            NodoListaCircularDobleImagenes *pip=filtro->Buscar("Collage");
                if (pip != NULL){
                    Profundidad_Matriz *aux2=pip->copiacubo;
                    NodoDobleProfundidad *aux3=aux2->primero;
                    NodoDobleProfundidad *por=aux2->primero;
                    matriztemporal=new raiz();
                    while(aux3 != NULL){
                        if (aux3->matriz != NULL){
                            aux2->UnirCapas(aux3->matriz,matriztemporal);
                        }
                    aux3 = aux3->siguiente;
                    }
                    string nom;
                    cout<<"Ingrese el nombre de su imagen de salida"<<endl;
                    cin>>nom;
                    matriztemporal->GraficarDispersa();
                    matriztemporal->graficarHTML2(nom,nombreimagen);
                    matriztemporal->GenerarSCSSCollage(nom,(widthcollage)*30,hightcollage*30,nombreimagen);
                }else cout<<"Filtro no Aplicado"<<endl;
        }else if (opcion == "5"){
            NodoListaCircularDobleImagenes *pip=filtro->Buscar("Mosaic");
                if (pip != NULL){
                    Profundidad_Matriz *aux2=pip->copiacubo;
                    NodoDobleProfundidad *aux3=aux2->primero;
                    NodoDobleProfundidad *por=aux2->primero;
                    matriztemporal=new raiz();
                    while(aux3 != NULL){
                        if (aux3->matriz != NULL){
                            aux2->UnirCapas(aux3->matriz,matriztemporal);
                        }
                    aux3 = aux3->siguiente;
                    }
                    string nom;
                    cout<<"Ingrese el nombre de su imagen de salida"<<endl;
                    cin>>nom;
                    matriztemporal->graficarHTMLMosaic(nom,nombreimagen);
                    matriztemporal->GenerarSCSSMosaic(nom,hightmosaic*30,widthmosaic*30,nombreimagen);
                }else cout<<"Filtro no Aplicado"<<endl;


        }
    }

}
/*--------------------------------------REPORTE DE CADA CAPA DEL CUBO--------------------------*/
void ReportePorCapaCubo(){
    string data;
    cout<<"1.Imagen Original"<<endl;
    cout<<"2.Imagen Filtro"<<endl;
    cin>>data;
    if (data == "1"){
        string dato;
        cout<<"1.Imagen Por capa"<<endl;
        cout<<"2.Imagen Completa"<<endl;
        cin>>dato;
        if (dato == "1"){
            int opcion;
            string nombre;
            system("cls");
            cout<<"-----------------"<<"IMAGES"<<"------------------------"<<endl;
            arbol->mostrarInOrden(arbol->raiz);
            cout<<"ingrese nombre de la imagen"<<endl;
            cin>>nombre;
            NodoABB * imagen=arbol->buscar(arbol->raiz,nombre);
            if (imagen != NULL){
                cout<<"Ingrese el id de profundidad"<<endl;
                cin >> opcion;
                NodoDobleProfundidad * aux3 = imagen->matriz->Buscar(opcion);
                if(imagen != NULL){
                    aux3->matriz->GraficarDispersa();
                }else cout<<"No se encontro el id a buscar"<<endl;
            }
        }
        else if(dato == "2"){
            string nombre;
            cout<<"-----------------"<<"IMAGES"<<"------------------------"<<endl;
            arbol->mostrarInOrden(arbol->raiz);
            cout<<"ingrese nombre de la imagen"<<endl;
            cin>>nombre;
            NodoABB *image=arbol->buscar(arbol->raiz,nombre);
            if (image != NULL){
                matriztemporal = new raiz();
                Profundidad_Matriz *aux2=image->matriz;
                NodoDobleProfundidad *aux3=aux2->primero;
                while(aux3 != NULL){
                    if (aux3->matriz != NULL){
                        aux2->UnirCapas(aux3->matriz,matriztemporal);
                }
                    aux3 = aux3->siguiente;
                }
                matriztemporal->GraficarDispersa();
            }else cout<<"No se encontro la imagen a buscar"<<endl;

        }else cout<<"Opcion incorrecta"<<endl;
    }
    else if(data == "2"){
        string dato;
        cout<<"1.Imagen Por capa"<<endl;
        cout<<"2.Imagen Completa"<<endl;
        cin>>dato;
        if (dato == "1"){
            int opcion;
            string nombre;
            system("cls");
            cout<<"ingrese nombre del filtro"<<endl;
            cin>>nombre;
            NodoListaCircularDobleImagenes * filt=filtro->Buscar(nombre);
            if (filt != NULL){
                cout<<"Ingrese el id de profundidad"<<endl;
                cin >> opcion;
                NodoDobleProfundidad * aux3 = filt->copiacubo->Buscar(opcion);
                if(aux3 != NULL){
                    aux3->matriz->GraficarDispersa();
                }else cout<<"No se encontro el id a buscar"<<endl;
            }else cout<<"Filtro No Aplicado"<<endl;
        }
        else if(dato == "2"){
            string nombre;
            system("cls");
            cout<<"ingrese nombre del filtro"<<endl;
            cin>>nombre;
            NodoListaCircularDobleImagenes *pip=filtro->Buscar(nombre);
            if (pip != NULL){
                Profundidad_Matriz *aux2=pip->copiacubo;
                NodoDobleProfundidad *aux3=aux2->primero;
                NodoDobleProfundidad *por=aux2->primero;
                matriztemporal=new raiz();
                while(aux3 != NULL){
                    if (aux3->matriz != NULL){
                        aux2->UnirCapas(aux3->matriz,matriztemporal);
                    }
                    aux3 = aux3->siguiente;
                }
                matriztemporal->GraficarDispersa();
                }else cout<<"Filtro no Aplicado"<<endl;

        }else cout<<"Opcion incorrecta"<<endl;

    }else cout<<"Opcion incorrecta"<<endl;
}

void ReporteLinealizarMatriz(){
    string data;
    cout<<"1.Imagen Original"<<endl;
    cout<<"2.Imagen Filtro"<<endl;
    cin>>data;
    if (data == "1"){
        string dato;
        cout<<"1.Linealizar por Columnas"<<endl;
        cout<<"2.Linealizar Por Fila"<<endl;
        cin>>dato;
        if (dato == "1"){
            int opcion;
            string nombre;
            system("cls");
            cout<<"-----------------"<<"IMAGES"<<"------------------------"<<endl;
            arbol->mostrarInOrden(arbol->raiz);
            cout<<"ingrese nombre de la imagen"<<endl;
            cin>>nombre;
            NodoABB * imagen=arbol->buscar(arbol->raiz,nombre);
            if (imagen != NULL){
                cout<<"Ingrese el id de profundidad"<<endl;
                cin >> opcion;
                NodoDobleProfundidad * aux3 = imagen->matriz->Buscar(opcion);
                if(aux3 != NULL){
                    aux3->matriz->LinealizarCapaColumna();
                }else cout<<"No se encontro el id a buscar"<<endl;
            }
        }
        else if(dato == "2"){
            int opcion;
            string nombre;
            system("cls");
            cout<<"-----------------"<<"IMAGES"<<"------------------------"<<endl;
            arbol->mostrarInOrden(arbol->raiz);
            cout<<"ingrese nombre de la imagen"<<endl;
            cin>>nombre;
            NodoABB * imagen=arbol->buscar(arbol->raiz,nombre);
            if (imagen != NULL){
                cout<<"Ingrese el id de profundidad"<<endl;
                cin >> opcion;
                NodoDobleProfundidad * aux3 = imagen->matriz->Buscar(opcion);
                if(aux3 != NULL){
                    aux3->matriz->LinealizarCapaFila();
                }else cout<<"No se encontro el id a buscar"<<endl;
            }

        }else cout<<"Opcion incorrecta"<<endl;
    }
    else if(data == "2"){
        string dato;
        cout<<"1.Linealizar por Columnas"<<endl;
        cout<<"2.Linealizar Por Fila"<<endl;
        cin>>dato;
        if (dato == "1"){
            int opcion;
            string nombre;
            system("cls");
            cout<<"ingrese nombre del filtro"<<endl;
            cin>>nombre;
            NodoListaCircularDobleImagenes * filt=filtro->Buscar(nombre);
            if (filt != NULL){
                cout<<"Ingrese el id de profundidad"<<endl;
                cin >> opcion;
                NodoDobleProfundidad * aux3 = filt->copiacubo->Buscar(opcion);
                if(aux3 != NULL){
                    aux3->matriz->LinealizarCapaColumna();
                }else cout<<"No se encontro el id a buscar"<<endl;
            }else cout<<"Filtro No Aplicado"<<endl;
        }
        else if(dato == "2"){
            int opcion;
            string nombre;
            system("cls");
            cout<<"ingrese nombre del filtro"<<endl;
            cin>>nombre;
            NodoListaCircularDobleImagenes * filt=filtro->Buscar(nombre);
            if (filt != NULL){
                cout<<"Ingrese el id de profundidad"<<endl;
                cin >> opcion;
                NodoDobleProfundidad * aux3 = filt->copiacubo->Buscar(opcion);
                if(aux3 != NULL){
                    aux3->matriz->LinealizarCapaFila();
                }else cout<<"No se encontro el id a buscar"<<endl;
            }else cout<<"Filtro No Aplicado"<<endl;

        }else cout<<"Opcion incorrecta"<<endl;

    }else cout<<"Opcion incorrecta"<<endl;

}

/*-----------------------------------------REPORTES DE LOS RECORRIDOS ---------------------*/
void ReporteTransversalRecorrido(NodoABB *raiz){
    if(raiz != NULL){
        ReporteTransversalRecorrido(raiz->izquierdo);
        recorrido->Recorrido(raiz->nombre.c_str());
        ReporteTransversalRecorrido(raiz->derecho);
    }
}

void ReportePostOrder(NodoABB *raiz){
    if(raiz != NULL){
        ReportePostOrder(raiz->izquierdo);
        ReportePostOrder(raiz->derecho);
        recorridoPost->RecorridoPosOrden(raiz->nombre.c_str());
    }
}
void ReportePreOrder(NodoABB *raiz){
    if(raiz != NULL){
        recorridoPre->RecorridoPreOrden(raiz->nombre.c_str());
        ReportePreOrder(raiz->izquierdo);
        ReportePreOrder(raiz->derecho);
    }
}
void Reportes(){
    string opcion;
    cout << "[1]Imported Images report(Arbol ABB)" << endl;
    cout << "[2]Image layer report(Cada capa del cubo)" << endl;
    cout << "[3]Linear Matrix Report(Reporte de linealizar cada capa)" << endl;
    cout << "[4]Transversal Report(Recorridos Arbol ABB)" << endl;
    cout << "[5]Filters Report(Lista Circular Doble)" << endl;
    cout << "\nIngresa tu opcion: ";
    cin >> opcion;
    if (opcion == "1"){
        arbol->GraficarInOrden();
    }
    else if(opcion == "2"){
        ReportePorCapaCubo();
    }
    else if(opcion == "3"){
        ReporteLinealizarMatriz();

    }
    else if(opcion == "4"){
        system("cls");
        string opcion1="";
        cout <<"1. Recorrido INORDER"<<endl;
        cout <<"2. Recorrido POSTORDER"<<endl;
        cout <<"3. Recorrido PREORDER"<<endl;
        cout<<"Seleccione una opcion"<<endl;
        cin>>opcion1;
        if (opcion1 == "1"){
            ReporteTransversalRecorrido(arbol->raiz);
            recorrido->GraficarRecorridoInorden();
        }
        else if(opcion1 == "2"){
            ReportePostOrder(arbol->raiz);
            recorridoPost->GraficarRecorridoPostOrden();
        }
        else if(opcion1 == "3"){
            ReportePreOrder(arbol->raiz);
            recorridoPre->GraficarRecorridoPreorden();
        }
        else cout<<"Opcion Incorrecta"<<endl;
    }
    else if(opcion == "5"){
        filtro->GraficarFiltro();
    }
    else cout<<"Opcion Incorrecta"<<endl;

}
void Edicion_Manual(){
    string prin;
    cout<<"1.Imagen Original"<<endl;
    cout<<"2.Filtro de la imagen"<<endl;
    cout<<"Ingrese una opcion"<<endl;
    cin>>prin;
    if (prin == "1"){
        int opcion;
        system("cls");
        NodoABB *neg=arbol->buscar(arbol->raiz,nombreimagen);
        if (neg != NULL){
            cout<<"Ingrese el id de profundidad"<<endl;
            cin >> opcion;
            NodoDobleProfundidad * aux3 = neg->matriz->Buscar(opcion);
            if(aux3 != NULL){
                int x;
                int y;
                string color;
                cout<<"ingrese x"<<endl;
                cin>>x;
                cout<<"ingrese y"<<endl;
                cin>>y;
                aux3->matriz->EditarColorRGB(x,y);
            }else cout<<"No se encontro el id a buscar"<<endl;
        }else cout<<"No se encontro La imagen"<<endl;
    }
    else if (prin == "2"){
        int opcion;
        system("cls");
        string name;
        filtro->Mostrar();
        cout<<"ingrese Filtro a modificar"<<endl;
        cin>>name;
        NodoListaCircularDobleImagenes *filt=filtro->Buscar(name);
        if (filt != NULL){
            cout<<"Ingrese el id de profundidad"<<endl;
            cin >> opcion;
            NodoDobleProfundidad * aux3 = filt->copiacubo->Buscar(opcion);
            if(aux3 != NULL){
                int x;
                int y;
                cout<<"ingrese x"<<endl;
                cin>>x;
                cout<<"ingrese y"<<endl;
                cin>>y;
                aux3->matriz->EditarColorRGB(x,y);
                aux3->matriz->GraficarDispersa();
            }else cout<<"No se encontro el id a buscar"<<endl;
        }else cout<<"No se encontro El filtro"<<endl;
    }else cout<<"opcion invalida"<<endl;
}
void verificar(string opcioninorden){
    NodoABB *imagen=arbol->buscar(arbol->raiz,opcioninorden);
    if(imagen != NULL){
        nombreimagen=opcioninorden;
        string rutasalida = "Exports/" + opcioninorden;
        mkdir(rutasalida.c_str());
    }else cout<<"Imagen no Existe"<<endl;
}

/*----------------------------------MAIN-------------------------------*/
int main()
{   system("cls");
    string direccion;
    string token;
    string punto=".";
    string opcion="";
    string ruta="";
    string ruta1;
    string ruta2;
    string ruta3;

    string opcioninorden="";
    while (1){
        cout << "[1]Insert Image" << endl;
        cout << "[2]Select Image" << endl;
        cout << "[3]Apply Filters" << endl;
        cout << "[4]Manual Editing" << endl;
        cout << "[5]Export Image" << endl;
        cout << "[6]Reports" << endl;
        cout << "[7]Exit" << endl;
        cout << "\nIngresa tu opcion: ";
        cin >> opcion;
        if (opcion == "1"){
            system("cls");
            cout<< "Ingrese la ruta del archivo Inicial"<<endl;
            cin >> direccion;
            std::istringstream iso(direccion);
            getline(iso,ruta,'/');
            getline(iso,ruta2,'/');
            getline(iso,ruta3,'.');
            rutaarchivo=ruta+"/"+ruta2+"/";
            nombreimagen=ruta3;
            AnalizarArchivoinicial(direccion,"archivo.txt");
            analisisSintacticoArchivoInicial();
        }
        else if (opcion == "2"){
            system("cls");
            cout<<"-----------------"<<"IMAGES"<<"------------------------"<<endl;
            arbol->mostrarInOrden(arbol->raiz);
            cout<<"seleccione una imagen"<<endl;
            cin>>opcioninorden;
            filtro->primero=NULL;
            filtro->ultimo=NULL;
            verificar(opcioninorden);
        }
        else if(opcion == "3"){
            system("cls");
            AplicarFiltrosMenu();
        }
        else if( opcion == "4"){
            system("cls");
            Edicion_Manual();
        }
        else if (opcion == "5"){
            system("cls");
            MenuExports();
        }
        else if (opcion == "6"){
            system("cls");
            Reportes();
        }
        else if (opcion == "7"){
            return 0;
            break;
        }
        else {
            cout << "Por favor ingresa una opcion correcta.\n";
        }

}
return 0;
}
