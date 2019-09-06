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
NodoABB *aux;
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
//---------------------------------------------fin caroables globales ----------------------------------------------------
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
            arbol->Crear(nombreimagen,altoimage,anchoimage);
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
    std::ifstream in (path.c_str());
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
        cout<<"No existe el archivo "<< path << endl;
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
            /*std::istringstream iss(color);
            getline(iss,R,'-');
            getline(iss,G,'-');
            getline(iss,B,'-');
            salida=RGBToHex(atoi(R.c_str()),atoi(G.c_str()),atoi(B.c_str())).c_str();*/
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
    std::ifstream in (path.c_str());
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
            else if(caracter == ';'){
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
        cout<<"No existe el archivo "<< path << endl;
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
        getline(in,columna,';');
        getline(in,fila,'\n');
        getline(in,inicial,';');
        getline(in,archivoinicial,'\n');
        fprintf(fp,"%s %s\n",archivoinicial.c_str(),"config");
        while(in.good()){
        getline(in,profundidad,';');
        getline(in,archivo,'\n');
        fprintf(fp,"%s %s\n",profundidad.c_str(),"capa");
        fprintf(fp,"%s %s\n",archivo.c_str(),"archivo");
        }
        cout<<"archivo leido" << endl;
        fclose(fp);
    }else {
        cout<<"No existe el archivo "<< path << endl;
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


             aux = arbol->buscar(arbol->raiz,nombreimagen);

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

void FiltroNegativo(){
    filtro->InsertarFiltro("Negative");
    Profundidad_Matriz *matrix= new Profundidad_Matriz();
    NodoABB *popo=arbol->buscar(arbol->raiz,"mario");
    if (popo != NULL){
        NodoListaCircularDobleImagenes *pi=filtro->Buscar("Negative");
        if (pi != NULL){
            NodoDobleProfundidad *au=popo->matriz->primero;
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
   string op;
   cout<<"1. Aplicar Filtro Imagen Completa"<<endl;
   cout<<"2. Aplicar Filtro a una Capa"<<endl;
   cin>>op;
   if (op == "1"){
        NodoListaCircularDobleImagenes *pip=filtro->Buscar("Negative");
            if (pip != NULL){
            Profundidad_Matriz *aux2=pip->copiacubo;
            NodoDobleProfundidad *aux3=aux2->primero;
            NodoDobleProfundidad *por=aux2->primero;
            while(aux3 != NULL){
                if (aux3->matriz != NULL){
                    aux2->UnirCapas(aux3->matriz,por->matriz);
                }
                aux3 = aux3->siguiente;
            }

            por->matriz->Negative();
        }else cout<<"Filtro no Aplicado"<<endl;
   }else if(op == "2"){
        int opcion;
        system("cls");
        NodoListaCircularDobleImagenes *neg=filtro->Buscar("Negative");
        if (neg != NULL){
            cout<<"Ingrese el id de profundidad"<<endl;
            cin >> opcion;
            NodoDobleProfundidad * aux3 = neg->copiacubo->Buscar(opcion);///
            if(aux3 != NULL){
                aux3->matriz->Negative();
            }else cout<<"No se encontro el id a buscar"<<endl;
            Profundidad_Matriz *aux2=neg->copiacubo;
            NodoDobleProfundidad *aux4=aux2->primero;
            NodoDobleProfundidad *por=aux2->primero;
            while(aux4 != NULL){
                if (aux4->matriz != NULL){
                    aux2->UnirCapas(aux4->matriz,por->matriz);
                }
                aux4 = aux4->siguiente;
            }
        }else cout<<"No se encontro el filtro"<<endl;
   }
}
void FiltroGrayScale(){
    filtro->InsertarFiltro("Grayscale");
    Profundidad_Matriz *matrix= new Profundidad_Matriz();
    NodoABB *popo=arbol->buscar(arbol->raiz,"mario");
    if (popo != NULL){
        NodoListaCircularDobleImagenes *pi=filtro->Buscar("Grayscale");
        if (pi != NULL){
            NodoDobleProfundidad *au=popo->matriz->primero;
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
   string op;
   cout<<"1. Aplicar Filtro Imagen Completa"<<endl;
   cout<<"2. Aplicar Filtro a una Capa"<<endl;
   cin>>op;
   if (op == "1"){
        NodoListaCircularDobleImagenes *pip=filtro->Buscar("Grayscale");
            if (pip != NULL){
            Profundidad_Matriz *aux2=pip->copiacubo;
            NodoDobleProfundidad *aux3=aux2->primero;
            NodoDobleProfundidad *por=aux2->primero;
            while(aux3 != NULL){
                if (aux3->matriz != NULL){
                    aux2->UnirCapas(aux3->matriz,por->matriz);
                }
                aux3 = aux3->siguiente;
            }
            por->matriz->GrayScale();
        }else cout<<"Filtro no Aplicado"<<endl;
   }else if(op == "2"){
        int opcion;
        system("cls");
        NodoListaCircularDobleImagenes *neg=filtro->Buscar("Grayscale");
        if (neg != NULL){
            cout<<"Ingrese el id de profundidad"<<endl;
            cin >> opcion;
            NodoDobleProfundidad * aux3 = neg->copiacubo->Buscar(opcion);///
            if(aux3 != NULL){
                aux3->matriz->GrayScale();
            }else cout<<"No se encontro el id a buscar"<<endl;
            Profundidad_Matriz *aux2=neg->copiacubo;
            NodoDobleProfundidad *aux4=aux2->primero;
            NodoDobleProfundidad *por=aux2->primero;
            while(aux4 != NULL){
                if (aux4->matriz != NULL){
                    aux2->UnirCapas(aux4->matriz,por->matriz);
                }
                aux4 = aux4->siguiente;
            }
        }else cout<<"No se encontro el filtro"<<endl;
   }

}
Profundidad_Matriz *CopiaCubo(string filtro,string imagen,ListaCircularDobleFiltros *filt,NodoDobleProfundidad*pr,Profundidad_Matriz *completo){
    filt->InsertarFiltro(filtro);
    Profundidad_Matriz *matrix= new Profundidad_Matriz();
    NodoABB *popo=arbol->buscar(arbol->raiz,imagen);
    int a=0;
    if (popo != NULL){
        NodoListaCircularDobleImagenes *pi=filt->Buscar(filtro);
        if (pi != NULL){
            NodoDobleProfundidad *au=popo->matriz->primero;
            cabecera* auxcabe=au->matriz->primerocolumna;
            while (auxcabe != NULL){
                a=auxcabe->numero;
                auxcabe=auxcabe->siguiente;
            }
            while(au != NULL ){
                cabecera *fila=au->matriz->primerocolumna;
                pi->copiacubo->Insertar_eje_Z(au->profundidad);
                pr=completo->Buscar(au->profundidad);
                while(fila !=NULL){
                    Nodomatriz *mat=fila->primeromatriz;
                    while(mat != NULL){
                       if(pr != NULL){
                            cout<<a<<endl;
                            pr->matriz->InsertarTodoMatriz(a-(mat->x),mat->y,mat->color);
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
void FiltroMirrorX(){

   string op;
   cout<<"1. Aplicar Filtro Imagen Completa"<<endl;
   cout<<"2. Aplicar Filtro a una Capa"<<endl;
   cin>>op;
   if (op == "1"){
          filtro->InsertarFiltro("MirrorX");
    NodoABB *popo=arbol->buscar(arbol->raiz,"mario");
    int a=0;
    if (popo != NULL){
        NodoListaCircularDobleImagenes *pi=filtro->Buscar("MirrorX");
        if (pi != NULL){
            NodoDobleProfundidad *au=popo->matriz->primero;
            cabecera* auxcabe=au->matriz->primerocolumna;
            while (auxcabe != NULL){
                a=auxcabe->numero;
                auxcabe=auxcabe->siguiente;
            }
            while(au != NULL ){
                cabecera *fila=au->matriz->primerocolumna;
                pi->copiacubo->Insertar_eje_Z(au->profundidad);
                NodoDobleProfundidad *pr=pi->copiacubo->Buscar(au->profundidad);
                while(fila !=NULL){
                    Nodomatriz *mat=fila->primeromatriz;
                    while(mat != NULL){
                       if(pr != NULL){
                            //cout<<a<<endl;
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
   /*-----------------------------------------AQUI SE UNE TODAS EN UNA MATRIZ DE LA CIRCULAR------*/
        NodoListaCircularDobleImagenes *pip=filtro->Buscar("MirrorX");
        if (pip != NULL){
            Profundidad_Matriz *aux2=pip->copiacubo;
            NodoDobleProfundidad *aux3=aux2->primero;
            NodoDobleProfundidad *por=aux2->primero;//matriz temporal
            matriztemporal=new raiz();
            cabecera *a=aux3->matriz->primerocolumna;
            int p=0;
            while(a != NULL){
                p=a->numero;
                a=a->siguiente;
            }
            while(aux3 != NULL){
                if (aux3->matriz != NULL){
                    aux2->UnirCapas(aux3->matriz,por->matriz);
                }
                aux3 = aux3->siguiente;
            }
            por->matriz->GraficarDispersa();
        }else cout<<"Filtro no Aplicado"<<endl;
   }else if(op == "2"){
       int opcion;
          filtro->InsertarFiltro("MirrorX");
    NodoABB *popo=arbol->buscar(arbol->raiz,"mario");
    int a=0;
    if (popo != NULL){
        system("cls");
        NodoListaCircularDobleImagenes *pi=filtro->Buscar("MirrorX");
        cout<<"Ingrese el id de profundidad"<<endl;
        cin >> opcion;
        NodoDobleProfundidad * aux3 = pi->copiacubo->Buscar(opcion);///
        if (pi != NULL){
            NodoDobleProfundidad *au=popo->matriz->primero;
            cabecera* auxcabe=au->matriz->primerocolumna;
            while (auxcabe != NULL){
                a=auxcabe->numero;
                auxcabe=auxcabe->siguiente;
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
        /*-------------------------------------------AQUI SE UNEN EN UNA SOLA--------*/
           NodoListaCircularDobleImagenes *pip=filtro->Buscar("MirrorX");
        if (pip != NULL){
            Profundidad_Matriz *aux2=pip->copiacubo;
            NodoDobleProfundidad *aux3=aux2->primero;
            NodoDobleProfundidad *por=aux2->primero;//matriz temporal
            cabecera *a=aux3->matriz->primerocolumna;
            int p=0;
            while(a != NULL){
                p=a->numero;
                a=a->siguiente;
            }
            while(aux3 != NULL){
                if (aux3->matriz != NULL){
                    aux2->UnirCapas(aux3->matriz,por->matriz);
                }
                aux3 = aux3->siguiente;
            }
            por->matriz->GraficarDispersa();
   }
}
}
void FiltroMirrorY(){
    string op;
   cout<<"1. Aplicar Filtro Imagen Completa"<<endl;
   cout<<"2. Aplicar Filtro a una Capa"<<endl;
   cin>>op;
   if (op == "1"){
          filtro->InsertarFiltro("MirrorY");
    NodoABB *popo=arbol->buscar(arbol->raiz,"mario");
    int a=0;
    if (popo != NULL){
        NodoListaCircularDobleImagenes *pi=filtro->Buscar("MirrorY");
        if (pi != NULL){
            NodoDobleProfundidad *au=popo->matriz->primero;
            cabecera* auxcabe=au->matriz->ultimofila;
            Nodomatriz *pito=auxcabe->primeromatriz;
            while(pito != NULL){
            while (auxcabe != NULL){
                a=auxcabe->numero;
                auxcabe=auxcabe->siguiente;
            }
                pito=pito->abajo;
            }
            while(au != NULL ){
                cabecera *fila=au->matriz->primerocolumna;
                pi->copiacubo->Insertar_eje_Z(au->profundidad);
                NodoDobleProfundidad *pr=pi->copiacubo->Buscar(au->profundidad);
                while(fila !=NULL){
                    Nodomatriz *mat=fila->primeromatriz;
                    while(mat != NULL){
                       if(pr != NULL){
                            cout<<a<<endl;
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
   /*-----------------------------------------AQUI SE UNE TODAS EN UNA MATRIZ DE LA CIRCULAR------*/
        NodoListaCircularDobleImagenes *pip=filtro->Buscar("MirrorY");
        if (pip != NULL){
            Profundidad_Matriz *aux2=pip->copiacubo;
            NodoDobleProfundidad *aux3=aux2->primero;
            NodoDobleProfundidad *por=aux2->primero;//matriz temporal
            matriztemporal=new raiz();
            cabecera *a=aux3->matriz->primerocolumna;
            int p=0;
            while(a != NULL){
                p=a->numero;
                a=a->siguiente;
            }
            while(aux3 != NULL){
                if (aux3->matriz != NULL){
                    aux2->UnirCapas(aux3->matriz,por->matriz);
                }
                aux3 = aux3->siguiente;
            }
            por->matriz->GraficarDispersa();
        }else cout<<"Filtro no Aplicado"<<endl;
   }else if(op == "2"){
       int opcion;
          filtro->InsertarFiltro("MirrorY");
    NodoABB *popo=arbol->buscar(arbol->raiz,"mario");
    int a=0;
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
                auxcabe=auxcabe->siguiente;
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
        /*-------------------------------------------AQUI SE UNEN EN UNA SOLA--------*/
           NodoListaCircularDobleImagenes *pip=filtro->Buscar("MirrorY");
        if (pip != NULL){
            Profundidad_Matriz *aux2=pip->copiacubo;
            NodoDobleProfundidad *aux3=aux2->primero;
            NodoDobleProfundidad *por=aux2->primero;//matriz temporal
            cabecera *a=aux3->matriz->primerocolumna;
            int p=0;
            while(a != NULL){
                p=a->numero;
                a=a->siguiente;
            }
            while(aux3 != NULL){
                if (aux3->matriz != NULL){
                    aux2->UnirCapas(aux3->matriz,por->matriz);
                }
                aux3 = aux3->siguiente;
            }
            por->matriz->GraficarDispersa();
   }
}

}
void FiltroDobleMirror(){
     string op;
   cout<<"1. Aplicar Filtro Imagen Completa"<<endl;
   cout<<"2. Aplicar Filtro a una Capa"<<endl;
   cin>>op;
   if (op == "1"){
          filtro->InsertarFiltro("DobleMirror");
    NodoABB *popo=arbol->buscar(arbol->raiz,"mario");
    int a=0;
    int b=0;
    if (popo != NULL){
        NodoListaCircularDobleImagenes *pi=filtro->Buscar("DobleMirror");
        if (pi != NULL){
            NodoDobleProfundidad *au=popo->matriz->primero;
            cabecera* auxcabe=au->matriz->primerofila;
            cabecera* auxfila=au->matriz->primerocolumna;
            Nodomatriz *pito=auxcabe->primeromatriz;
            while (auxcabe != NULL){
                a=auxcabe->numero;
                auxcabe=auxcabe->siguiente;
            }
            while (auxfila != NULL){
                b=auxfila->numero;
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
                            cout<<b<<endl;
                            cout<<a<<endl;
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
   /*-----------------------------------------AQUI SE UNE TODAS EN UNA MATRIZ DE LA CIRCULAR------*/
        NodoListaCircularDobleImagenes *pip=filtro->Buscar("DobleMirror");
        if (pip != NULL){
            Profundidad_Matriz *aux2=pip->copiacubo;
            NodoDobleProfundidad *aux3=aux2->primero;
            NodoDobleProfundidad *por=aux2->primero;//matriz temporal
            matriztemporal=new raiz();
            cabecera *a=aux3->matriz->primerocolumna;
            int p=0;
            while(a != NULL){
                p=a->numero;
                a=a->siguiente;
            }
            while(aux3 != NULL){
                if (aux3->matriz != NULL){
                    aux2->UnirCapas(aux3->matriz,por->matriz);
                }
                aux3 = aux3->siguiente;
            }
            por->matriz->GraficarDispersa();
        }else cout<<"Filtro no Aplicado"<<endl;
   }else if(op == "2"){
       int opcion;
          filtro->InsertarFiltro("MirrorY");
    NodoABB *popo=arbol->buscar(arbol->raiz,"mario");
    int a=0;
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
                auxcabe=auxcabe->siguiente;
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
        /*-------------------------------------------AQUI SE UNEN EN UNA SOLA--------*/
           NodoListaCircularDobleImagenes *pip=filtro->Buscar("DobleMirror");
        if (pip != NULL){
            Profundidad_Matriz *aux2=pip->copiacubo;
            NodoDobleProfundidad *aux3=aux2->primero;
            NodoDobleProfundidad *por=aux2->primero;//matriz temporal
            cabecera *a=aux3->matriz->primerocolumna;
            int p=0;
            while(a != NULL){
                p=a->numero;
                a=a->siguiente;
            }
            while(aux3 != NULL){
                if (aux3->matriz != NULL){
                    aux2->UnirCapas(aux3->matriz,por->matriz);
                }
                aux3 = aux3->siguiente;
            }
            por->matriz->GraficarDispersa();
   }
}
}
void FiltroCollage(){
    filtro->InsertarFiltro("Collage");
    NodoABB *popo=arbol->buscar(arbol->raiz,"mario");
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
                            pr->matriz->InsertarTodoMatriz((a*j)+mat->x,((b+5)*i)+mat->y,mat->color);
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
        NodoListaCircularDobleImagenes *pip=filtro->Buscar("Collage");
        if (pip != NULL){
            Profundidad_Matriz *aux2=pip->copiacubo;
            NodoDobleProfundidad *aux3=aux2->primero;
            NodoDobleProfundidad *por=aux2->primero;//matriz temporal
            cabecera *a=aux3->matriz->primerocolumna;
            int p=0;
            while(a != NULL){
                p=a->numero;
                a=a->siguiente;
            }
            while(aux3 != NULL){
                if (aux3->matriz != NULL){
                    aux2->UnirCapas(aux3->matriz,por->matriz);
                }
                aux3 = aux3->siguiente;
            }
            por->matriz->GraficarDispersa();
   }
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

    }

}


void MenuExports(){
    int opcion;
    string nombre;
    string name;
    cout<<"1. Exportar Imagen original "<<endl;
    cout<<"2. Exportar Filtro\n\n"<<endl;
    cout<<"ingrese su opcion: "<<endl;
    cin>>opcion;
    if (opcion == 1){
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
        matriztemporal->graficarHTML();
        matriztemporal->GenerarSCSS();
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
        int opcion;
        system("cls");
        NodoListaCircularDobleImagenes *neg=filtro->Buscar("Negative");
        if (neg != NULL){
            Profundidad_Matriz *aux2=neg->copiacubo;
            NodoDobleProfundidad *aux3=aux2->primero;
            if (aux3->matriz != NULL){
                string nom;
                cout<<"Ingrese el nombre de su imagen de salida"<<endl;
                cin>>nom;
                aux3->matriz->GraficarDispersa();
                aux3->matriz->graficarHTML2(nom);
                aux3->matriz->GenerarSCSS2(nom);
            }
        }else cout<<"No se encontro el filtro"<<endl;
        }
        else if(opcion == "2"){
            int opcion;
            system("cls");
            NodoListaCircularDobleImagenes *neg=filtro->Buscar("Grayscale");
            if (neg != NULL){
                Profundidad_Matriz *aux2=neg->copiacubo;
                NodoDobleProfundidad *aux3=aux2->primero;
                if (aux3->matriz != NULL){
                    string nom;
                    cout<<"Ingrese el nombre de su imagen de salida"<<endl;
                    cin>>nom;
                    aux3->matriz->GraficarDispersa();
                    aux3->matriz->graficarHTML2(nom);
                    aux3->matriz->GenerarSCSS2(nom);
                }
            }else cout<<"No se encontro el filtro"<<endl;
        }
        else if(opcion == "3"){
            string chooise;
            cout << "[1]X-Mirror(Espejo en eje X)" << endl;
            cout << "[2]Y-Mirror(Espejo en eje Y)" << endl;
            cout << "[3]Double Mirror(Espejo en ambos ejes)" << endl;
            cin>>chooise;
            if (chooise == "1"){
                int opcion;
                system("cls");
                NodoListaCircularDobleImagenes *neg=filtro->Buscar("MirrorX");
                if (neg != NULL){
                    Profundidad_Matriz *aux2=neg->copiacubo;
                    NodoDobleProfundidad *aux3=aux2->primero;
                    if (aux3->matriz != NULL){
                        string nom;
                        cout<<"Ingrese el nombre de su imagen de salida"<<endl;
                        cin>>nom;
                        aux3->matriz->GraficarDispersa();
                        aux3->matriz->graficarHTML2(nom);
                        aux3->matriz->GenerarSCSS2(nom);
                    }
                }else cout<<"No se encontro el filtro"<<endl;

            }
            else if(chooise == "2"){
                int opcion;
                system("cls");
                NodoListaCircularDobleImagenes *neg=filtro->Buscar("MirrorY");
                if (neg != NULL){
                    Profundidad_Matriz *aux2=neg->copiacubo;
                    NodoDobleProfundidad *aux3=aux2->primero;
                    if (aux3->matriz != NULL){
                        string nom;
                        cout<<"Ingrese el nombre de su imagen de salida"<<endl;
                        cin>>nom;
                        aux3->matriz->GraficarDispersa();
                        aux3->matriz->graficarHTML2(nom);
                        aux3->matriz->GenerarSCSS2(nom);
                    }
                }else cout<<"No se encontro el filtro"<<endl;

            }
            else if (chooise == "3"){
                int opcion;
                system("cls");
                NodoListaCircularDobleImagenes *neg=filtro->Buscar("DobleMirror");
                if (neg != NULL){
                    Profundidad_Matriz *aux2=neg->copiacubo;
                    NodoDobleProfundidad *aux3=aux2->primero;
                    if (aux3->matriz != NULL){
                        string nom;
                        cout<<"Ingrese el nombre de su imagen de salida"<<endl;
                        cin>>nom;
                        aux3->matriz->GraficarDispersa();
                        aux3->matriz->graficarHTML2(nom);
                        aux3->matriz->GenerarSCSS2(nom);
                    }
                }else cout<<"No se encontro el filtro"<<endl;

            }

        }
        else if(opcion == "4"){
            int opcion;
                system("cls");
                NodoListaCircularDobleImagenes *neg=filtro->Buscar("Collage");
                if (neg != NULL){
                    Profundidad_Matriz *aux2=neg->copiacubo;
                    NodoDobleProfundidad *aux3=aux2->primero;
                    if (aux3->matriz != NULL){
                        string nom;
                        cout<<"Ingrese el nombre de su imagen de salida"<<endl;
                        cin>>nom;
                        aux3->matriz->GraficarDispersa();
                        aux3->matriz->graficarHTML2(nom);
                        aux3->matriz->GenerarSCSS2(nom);
                    }
                }else cout<<"No se encontro el filtro"<<endl;
        }
    }

}
/*--------------------------------------REPORTE DE CADA CAPA DEL CUBO--------------------------*/
void ReportePorCapaCubo(){
    int opcion;
    string nombre;
    system("cls");
    cout<<"ingrese nombre de la imagen"<<endl;
    cin>>nombre;
    NodoABB * imagen=arbol->buscar(arbol->raiz,nombre);
    if (imagen != NULL){
        cout<<"Ingrese el id de profundidad"<<endl;
        cin >> opcion;
        NodoDobleProfundidad * aux3 = imagen->matriz->Buscar(opcion);
        if(aux != NULL){
            aux3->matriz->GraficarDispersa();
        }else cout<<"No se encontro el id a buscar"<<endl;
    }

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
    int opcion;
    cout << "[1]Imported Images report(Arbol ABB)" << endl;
    cout << "[2]Image layer report(Cada capa del cubo)" << endl;
    cout << "[3]Linear Matrix Report(Reporte de linealizar cada capa)" << endl;
    cout << "[4]Transversal Report(Recorridos Arbol ABB)" << endl;
    cout << "[5]Filters Report(Lista Circular Doble)" << endl;
    cout << "\nIngresa tu opcion: ";
    cin >> opcion;
    if (opcion == 1){
        arbol->GraficarInOrden();
    }
    else if(opcion == 2){
        ReportePorCapaCubo();
    }
    else if(opcion == 4){
        system("cls");
        string opcion1;
        cout <<"1. Recorrido INORDER"<<endl;
        cout <<"2. Recorrido POSTORDER"<<endl;
        cout <<"3. Recorrido PREORDER"<<endl;
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
    }
    else if(opcion == 5){
        filtro->GraficarFiltro();
    }
    else cout<<"Opcion Incorrecta"<<endl;

}
void s(){
int opcion;
        system("cls");
        NodoABB *neg=arbol->buscar(arbol->raiz,"mario");
        if (neg != NULL){
            cout<<"Ingrese el id de profundidad"<<endl;
            cin >> opcion;
            NodoDobleProfundidad * aux3 = neg->matriz->Buscar(opcion);
            if(aux3 != NULL){
                int x;
                int y;
                aux3->matriz->LinealizarCapaColumna();
            }else cout<<"No se encontro el id a buscar"<<endl;
        }else cout<<"No se encontro el filtro"<<endl;
}

/*----------------------------------MAIN-------------------------------*/
int main()
{   system("cls");
    string direccion;
    string token;
    string punto=".";
    int opcion;
    int opcioninorden;
    //cout<<RGBToHex(230,230,230)<<endl;
   //cout<<setprecision(1)<< matriztemporal->ConvertirSacleGray(255,228,181)<<endl;
   arbol->Crear("Mario1",1,100);
   arbol->Crear("Pikachu",1,100);
   arbol->Crear("Boo",1,100);
   arbol->Crear("Geoff",1,100);
   arbol->Crear("Mario2",1,100);
   arbol->Crear("Mushroom",1,100);
    while (1)
    {

        cout << "[1]Insert Image" << endl;
        cout << "[2]Select Image" << endl;
        cout << "[3]Apply Filters" << endl;
        cout << "[4]Manual Editing" << endl;
        cout << "[5]Export Image" << endl;
        cout << "[6]Reports" << endl;
        cout << "[7]Exit" << endl;
        cout << "\nIngresa tu opcion: ";
        cin >> opcion;

        switch(opcion)
        {
        case 1:
            system("cls");
            cout<< "Ingrese la ruta del archivo Inicial"<<endl;
            cin >> direccion;
            token= direccion.substr(0, direccion.find(punto));
            nombreimagen=token;
            AnalizarArchivoinicial(direccion,"archivo.txt");
            analisisSintacticoArchivoInicial();
            break;
        case 2:
            system("cls");
            arbol->mostrarInOrden(arbol->raiz);
            cout<<"seleccione una imagen"<<endl;
            cin>>opcioninorden;
            break;
        case 3:
            system("cls");
            AplicarFiltrosMenu();

            break;
        case 4:
            system("cls");
             //unircapaprueba();
            s();
            break;
        case 5:
            system("cls");
            MenuExports();
            break;
        case 6:
            system("cls");
            Reportes();
            break;
        case 7:
            return 0;
            break;
        default:
            cout << "Por favor ingresa una opcion correcta.\n";
            break;
        }
    }
    return 0;


}
