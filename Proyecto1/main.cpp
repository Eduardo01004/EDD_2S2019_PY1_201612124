#include <iostream>
#include "ArbolABB.h"
#include "raiz.h"
#include "ListaCircularDobleFiltros.h"
#include "Profundidad_Matriz.h"
using namespace std;
ArbolABB *arbol=new ArbolABB();
raiz *matriztemporal =new raiz();
ListaCircularDobleFiltros *filtro=new ListaCircularDobleFiltros();
Profundidad_Matriz *matrix=new Profundidad_Matriz();

//---------------------------variables globales del archivo inicial-------------------------
string id="";
int faseinicial=0;
int capa=0;
string leerarchivo="";
string archivoconfig="";
//------------------------variables globales del archivo configuracion------------------------------------
int altoimage=0;
int anchoimage=0;
int altopixel=0;
int anchopixel=0;

//-----------variables globales de los archivos de las capas ------------------------------------------------
int fila=0;
int columna=0;
string color="";
//---------------------------------------------fin caroables globales ----------------------------------------------------

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
                fprintf(fp,"%s %s\n",palabra.c_str(),"X");
                palabra = "";
            }else if( caracter == 9 || caracter == 8 || caracter == 11 || caracter == 13 || caracter ==32){

                //---------------------------- Espacios en blanco --------------------------
            }else if(caracter == 10){
                coorx++;
                coory=0;
            }
            else if(caracter == ';'){
                if(palabra != "") fprintf(fp,"%s %s\n",palabra.c_str(),"color");
                coory++;
                fprintf(fp,"%d %s\n",coory,"COORX");
                fprintf(fp,"%d %s\n",coorx,"COORY");
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
        fprintf(fp,"%s %s\n",columna.c_str(),"Config");
        fprintf(fp,"%s %s\n",fila.c_str(),"Value");
        while(in.good()){
            getline(in,palabra,',');
            getline(in,alto,'\n');
            fprintf(fp,"%s %s\n",palabra.c_str(),"datos");
            fprintf(fp,"%s %s\n",alto.c_str(),"ancho");
        }
        cout<<"archivo leido" << endl;
        fclose(fp);
    }else {
        cout<<"No existe el archivo "<< path << endl;
     }

}
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
        fprintf(fp,"%s %s\n",columna.c_str(),"layer");
        fprintf(fp,"%s %s\n",fila.c_str(),"file");
        fprintf(fp,"%s %s\n",inicial.c_str(),"inicial");
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
            cout<<"esta es el encabezado layer no sse hace nada"<<endl;
            faseinicial=1;
        }else {
            faseinicial=111;
            cout<<"Se esperaba un id se encontro: "<<lexema<< " "<<token<<endl;
        }
        break;
    case 1:
        if (token == "file"){
            cout<<"esta es el encabezado file no sse hace nada"<<endl;
            faseinicial=2;
        }else {
            faseinicial=111;
            cout<<"Se esperaba un id se encontro: "<<lexema<< " "<<token<<endl;
        }
        break;
    case 2:
        if (token == "inicial"){
            cout<<"esta es la capa  0 no se hace nada"<<endl;
            faseinicial=3;
        }else {
            faseinicial=111;
            cout<<"Se esperaba un id se encontro: "<<lexema<< " "<<token<<endl;
        }
        break;
    case 3:
        if (token == "config"){
            archivoconfig=lexema;
            cout<<"este es el archivo de configuracion aqui se deberia insertar  el nombre la dimension y el tamano al arbol abb"<<endl;
            cout<<archivoconfig<<endl;
            AnalizarConfig(archivoconfig,"configuracion.txt");
            faseinicial=4;
        }else {
            faseinicial=111;
            cout<<"Se esperaba un id se encontro: "<<lexema<< " "<<token<<endl;
        }
        break;
    case 4:
        if (token == "capa"){
            capa=atoi(lexema.c_str());
            cout<<"esta son las capas del cubo disperso"<<endl;
            cout<<capa<<endl;
            faseinicial=5;
        }else {
            faseinicial=111;
            cout<<"Se esperaba un id se encontro: "<<lexema<< " "<<token<<endl;
        }
        break;
    case 5:
        if (token == "archivo"){
            leerarchivo=lexema;
            cout<<"este es el archivo de las capas que se van insertanto en el cubo disperso"<<endl;
            AnalizarArchivoCapas(leerarchivo,"capas.txt");
            cout<<leerarchivo<<endl;
            faseinicial=6;
        }else {
            faseinicial=111;
            cout<<"Se esperaba un id se encontro: "<<lexema<< " "<<token<<endl;
        }
        break;
    case 6:
        if (token == "capa"){
            faseinicial=4;
            automataArchivoinicial(lexema,token);
        }
        else if(token == "archivo"){
            faseinicial=5;
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
int main()
{
    arbol->Crear("pito",100,8989);
    arbol->Crear("jojo",51,46);
    arbol->Crear("poto",79,32);
    arbol->Crear("nana",795,98);

    string direccion;
    int opcion;
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
            AnalizarArchivoinicial(direccion,"archivo.txt");
            system("cls");
            analisisSintacticoArchivoInicial();

            break;
        case 2:
            system("cls");
             joo();

            break;
        case 3:
            system("cls");
             unircapaprueba();
            break;
        case 4:
            system("cls");
            cout<< "Ingrese la ruta del archivo Inicial"<<endl;
            cin >> direccion;
            AnalizarArchivoCapas(direccion,"capas.txt");
            break;
        case 5:
            system("cls");
            break;
        case 6:
            system("cls");
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
