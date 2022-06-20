#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iomanip>

using namespace std;

#include "DetalleVenta.h"
#include "Venta.h"

void listarDetalleVentas(){
    DetalleVenta obj;
    int pos=0;
    cout << left;
    cout << setw(10) << "ID FACT";
    cout << setw(10) << "ID CL";
    cout << setw(10) << "ID VEND";
    cout << setw(14) << "FECHA VENTA";
    cout << setw(14) << "CANT. TOTAL";
    cout << setw(15) << "IMP. TOTAL" << endl;
    cout << "-------------------------------------------------------------------------" << endl;
    while(obj.leerDisco(pos++)){
        obj.Mostrar();
        cout << endl;
    }
}

int menuDetalleVenta(){
    int opc;
    while(true){
        cout << "MENU DETALLE VENTA" << endl;
        cout << "---------------------------" << endl;
        cout << "1- LISTAR DETALLE VENTA" << endl;
        cout << "0- VOLVER AL MENU PRINCIPAL" << endl;
        cout << "---------------------------" << endl;
        cout << "INGRESAR OPCION: ";
        cin >> opc;
        system("cls");
        switch(opc){
            case 1: listarDetalleVentas();
                break;
            case 0: return 0;
                break;
        }
        system("pause>null");
        system("cls");
    }
    return 0;
}
