#include <iostream>
#include "ArbolABB.h"
#include "raiz.h"
#include "ListaCircularDobleFiltros.h"
#include "Profundidad_Matriz.h"
#include <sstream>
using namespace std;
ArbolABB *arbol=new ArbolABB();
raiz *matriztemporal =new raiz();
ListaCircularDobleFiltros *filtro=new ListaCircularDobleFiltros();
Profundidad_Matriz *matrix=new Profundidad_Matriz();
NodoABB *aux;
NodoDobleProfundidad *aux2;
//---------------------------variables globales del archivo inicial-------------------------
string id="";
int faseinicial=0;
int capa=0;
string leerarchivo="";
string archivoconfig="";
string nombreimagen="";
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
                if (aux2 ){
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
    int coorx=1;//fila
    int coory=0;//columna
    std::ifstream in (path.c_str());
    if(in.is_open()){
        FILE *fp;
        fp = fopen(archivo.c_str(),"w");
        string palabra = "";
        while(in.get(caracter)){
            if(caracter == 'x'){
            }else if( caracter == 9 || caracter == 8 || caracter == 11 || caracter == 13 || caracter ==32){

                //---------------------------- Espacios en blanco --------------------------
            }else if(caracter == 10){
                coorx++;
                coory=0;
            }
            else if(caracter == ';'){
                if(palabra != "") {
                fprintf(fp,"%s %s\n",palabra.c_str(),"color");
                fprintf(fp,"%d %s\n",coory,"COORX");
                fprintf(fp,"%d %s\n",coorx,"COORY");
                }
                coory++;
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
void AplicarFiltrosMenu(){
     string opcion;
    cout << "[1]Negative(Negativo)" << endl;
    cout << "[2]GrayScale(Escala de Grises)" << endl;
    cout << "[3]Mirror(Espejo)" << endl;
    cout << "[4]Collage(Collage)" << endl;
    cout << "[5]Mosaic(Mosaico)" << endl;
    cout << "\nIngresa tu opcion: ";

    cin >> opcion;
    if (opcion == "Negativo"){

    }
}
void FiltroNegativo(){

}

void unircapaprueba(){
    string opcion;
    system("cls");
    cout<<"ingrese nombre imagen"<<endl;
    cin>>opcion;
    NodoABB* aux = arbol->buscar(arbol->raiz,opcion);
    if (aux != NULL){
        matriztemporal = new raiz();
        Profundidad_Matriz *aux2=aux->matriz;
        NodoDobleProfundidad *aux3=aux2->primero;
        while(aux3 != NULL){
            if(aux3-> matriz != NULL) aux2->UnirCapas(aux3->matriz,matriztemporal);
            aux3 = aux3->siguiente;
        }
        matriztemporal->graficarCapa();
        matriztemporal->graficarHTML();
        matriztemporal->GenerarSCSS();
    }else cout<<"No se encontro la imagen a buscar"<<endl;

}

void po(){
    int dato;
    int x;
    int y;
    string color;
    cout << "\nIngrese dato ";
    cin >> dato;
     NodoDobleProfundidad *aux=matrix->Buscar(dato);
    if (aux){
        cout << "\nIngrese x ";
        cin >> x;
        cout << "\nIngrese y ";
        cin >> y;
        cout << "\nIngrese color ";
        cin >> color;
        aux->matriz->InsertarTodoMatriz(x,y,color);
        aux->matriz->GraficarDispersa();
    }else cout<<"No se encontro "<<endl;
}

void joo(){
    int opcion;
    int opcion2;
    string nombre;
    int dato;
    int x;
    int y;
    string color;
    cout << "\nIngrese nombre ";
    cin >> nombre;
    NodoABB* aux = arbol->buscar(arbol->raiz,nombre);
    if (aux != NULL){
        cout << "\nIngrese 1 para agreagar a la doble ";
        cin >> opcion;
        if (opcion == 1){
        int cantidad;
        cout << "\nIngrese dato ";
        cin >> cantidad;
        aux->matriz->Insertar_eje_Z(cantidad);
        cout<<"dato ingresado"<<endl;
        }
        else{
        cout << "\nIngrese dato ";
        cin >> dato;
        NodoDobleProfundidad *aux2=aux->matriz->Buscar(dato);

        if (aux2 != NULL){
        cout << "\nIngrese 1 para agreagar a la matriz ";
        cin >> opcion2;
        if (opcion2 == 1){
        cout << "\nIngrese x ";
        cin >> x;
        cout << "\nIngrese y ";
        cin >> y;
        cout << "\nIngrese color ";
        cin >> color;
        aux2->matriz->InsertarTodoMatriz(x,y,color);
        aux2->matriz->GraficarDispersa();
        }else cout<<"salir"<<endl;
        }else cout<<"dato no encontrado"<<endl;
        }
    }else cout<<"dato no encontrado"<<endl;
}

void porCapa(){
    int opcion;
    system("cls");
    cout<<"Ingrese el id de profundidad"<<endl;
    cin >> opcion;
    NodoDobleProfundidad * aux3 = aux->matriz->Buscar(opcion);
    if(aux != NULL){
        aux3->matriz->GraficarDispersa();
    }else cout<<"No se encontro el id a buscar"<<endl;
}




/*--------------------------------------REPORTES--------------------------*/
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

}


/*----------------------------------MAIN-------------------------------*/
int main()
{
    string direccion;
    string token;
    string punto=".";
    int opcion;
    int opcioninorden;
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
             unircapaprueba();
            break;
        case 5:
            system("cls");
            porCapa();
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
