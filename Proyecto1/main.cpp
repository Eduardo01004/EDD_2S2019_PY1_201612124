#include <iostream>
#include "ArbolABB.h"
#include "raiz.h"
#include "ListaCircularDobleFiltros.h"
using namespace std;
ArbolABB *arbol=new ArbolABB();
raiz *matriz =new raiz();
ListaCircularDobleFiltros *filtro=new ListaCircularDobleFiltros();
int main()
{
    arbol->Crear( "Mario1",1,12);
    arbol->Crear("Pikachu",12,125);
    arbol->Crear( "Boo",15,6);
    arbol->Crear("Geoff",16,61);
    arbol->Crear( "Mario2",99,5);
    arbol->Crear("Mushroom",646,4949);
    //arbol->graficaBinario();
    arbol->mostrarInOrden(arbol->raiz);
    //arbol->GraficarInOrden();
    //arbol->GraficarPreOrden();

    matriz->existeX(3);
    matriz->existey(3);
    matriz->InsertarMatriz(3,3,"1");
    matriz->existeX(3);
    matriz->existey(4);
    matriz->InsertarMatriz(3,4,"2");
    matriz->existeX(4);
    matriz->existey(2);
    matriz->InsertarMatriz(4,2,"3");
    matriz->existeX(4);
    matriz->existey(3);
    matriz->InsertarMatriz(4,3,"4");
    matriz->existeX(4);
    matriz->existey(4);
    matriz->InsertarMatriz(4,4,"5");
    matriz->existeX(4);
    matriz->existey(5);
    matriz->InsertarMatriz(4,5,"6");
    matriz->existeX(5);
    matriz->existey(2);
    matriz->InsertarMatriz(5,2,"7");
    matriz->existeX(5);
    matriz->existey(3);
    matriz->InsertarMatriz(5,3,"8");
    matriz->existeX(5);
    matriz->existey(4);
    matriz->InsertarMatriz(5,4,"1");
    matriz->existeX(5);
    matriz->existey(5);
    matriz->InsertarMatriz(5,5,"1");
    matriz->existeX(5);
    matriz->existey(6);
    matriz->InsertarMatriz(5,6,"1");
    matriz->existeX(6);
    matriz->existey(3);
    matriz->InsertarMatriz(6,3,"1");
    matriz->existeX(6);
    matriz->existey(4);
    matriz->InsertarMatriz(6,4,"1");
    matriz->existeX(6);
    matriz->existey(5);
    matriz->InsertarMatriz(6,5,"1");
    matriz->existeX(6);
    matriz->existey(6);
    matriz->InsertarMatriz(6,6,"1");
    matriz->existeX(6);
    matriz->existey(7);
    matriz->InsertarMatriz(6,7,"1");
    matriz->existeX(7);
    matriz->existey(2);
    matriz->InsertarMatriz(7,2,"1");
    matriz->existeX(7);
    matriz->existey(3);
    matriz->InsertarMatriz(7,3,"1");
    matriz->existeX(7);
    matriz->existey(4);
    matriz->InsertarMatriz(7,4,"1");
    matriz->existeX(7);
    matriz->existey(5);
    matriz->InsertarMatriz(7,5,"1");
    matriz->existeX(7);
    matriz->existey(6);
    matriz->InsertarMatriz(7,6,"1");
    matriz->existeX(8);
    matriz->existey(2);
    matriz->InsertarMatriz(8,2,"1");
    matriz->existeX(8);
    matriz->existey(3);
    matriz->InsertarMatriz(8,3,"1");
    matriz->existeX(8);
    matriz->existey(4);
    matriz->InsertarMatriz(8,4,"1");
    matriz->existeX(8);
    matriz->existey(5);
    matriz->InsertarMatriz(8,5,"1");
    matriz->existeX(9);
    matriz->existey(3);
    matriz->InsertarMatriz(9,3,"1");
    matriz->existeX(9);
    matriz->existey(4);
    matriz->InsertarMatriz(9,4,"1");
    matriz->GraficarDispersa();

    filtro->InsertarFiltro("negativo");
    filtro->InsertarFiltro("mosaico");
    filtro->InsertarFiltro("espejo");
    filtro->InsertarFiltro("grayscale");
    filtro->GraficarFiltro();

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
        case 0:
            system("cls");
            break;
        case 1:
            system("cls");
            break;
        case 3:
            system("cls");
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
