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

void prueba(){
    int cantidad;
    cout << "\nIngrese dato ";
    cin >> cantidad;
    matrix->Insertar_eje_Z(cantidad);

}

void unircapaprueba(){
    int opcion;
    system("cls");
    cout<<"ingrese "<<endl;
    cin>>opcion;
    NodoDobleProfundidad *aux=matrix->primero;

    matriztemporal = new raiz();
    matrix->UnirCapas(aux->matriz,matriztemporal);

    matriztemporal->graficarCapa();
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
int main()
{


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
            prueba();
            break;
        case 2:
            system("cls");
            po();
            break;
        case 3:
            system("cls");
            unircapaprueba();
            break;
        case 4:
            system("cls");

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
