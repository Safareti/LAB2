#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <ctime>

using namespace std;

#include "Usuarios.h"
#include "Empleado.h"
#include "Clientes.h"
#include "Colchon.h"
#include "Venta.h"
#include "DetalleVenta.h"
#include "fecha.h"

int main(){

    int opc;
    while(true){
        cout << "MENU PRINCIPAL" << endl;
        cout << "--------------------------" << endl;
        cout << "1- MENU USUARIO" << endl;
        cout << "2- MENU EMPLEADO" << endl;
        cout << "3- MENU CLIENTE" << endl;
        cout << "4- MENU COLCHONES" << endl;
        cout << "5- MENU VENTAS" << endl;
        cout << "6- MENU FACTURA" << endl;
        cout << "0- SALIR DEL PROGRAMA" << endl;
        cout << "--------------------------" << endl;
        cout << "INGRESAR OPCION: ";
        cin >> opc;
        system("cls");
        switch(opc){
            case 1: menuUsuarios();
                break;
            case 2: menuEmpleado();
                break;
            case 3: menuClientes();
                break;
            case 4: menuColchones();
                break;
            case 5: menuVentas();
                break;
            case 6: menuDetalleVenta();
                break;
            case 0: return 0;
                break;
        }
        system("pause");
        system("cls");
    }
    return 0;
}
