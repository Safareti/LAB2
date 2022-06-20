#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iomanip>

using namespace std;

#include "Clientes.h"

int verificarIDCliente(int id){
    Clientes obj;
    int pos=0;
    if(obj.contarClientes()==-1){
        return -1;
    }
    while(obj.leerDeDisco(pos++)){
        if(obj.getIdCliente()==id){
            return pos;
        }
    }
    return -1;
}

int verificarDNICliente(int dni){
    Clientes obj;
    int pos=0;
    if(obj.contarClientes()==-1){
        return -1;
    }
    while(obj.leerDeDisco(pos++)){
        if(obj.getDniCliente()==dni){
            return pos;
        }
    }
    return -1;
}

void cargarCliente(){
    Clientes obj;
    obj.Cargar();
    cout << endl;
    if(verificarIDCliente(obj.getIdCliente())!=-1 || verificarDNICliente(obj.getDniCliente())!=-1){
        cout << "NO SE PUDO CARGAR EL CLIENTE" << endl;
        return;
    }
    if(obj.grabarEnDisco()){
        cout << "CLIENTE GRABADO CON EXITO" << endl;
    }else{
        cout << "NO SE PUDO CARGAR EL CLIENTE" << endl;
    }
}

void listarClientes(){
    Clientes obj;
    int pos=0;
    cout << left;
    cout << setw(6) << "ID";
    cout << setw(10) << "DNI";
    cout << setw(12) << "SALDO";
    cout << setw(25) << "EMAIL";
    cout << setw(15) << "TELEFONO" << endl;
    cout << "-----------------------------------------------------------------";
    cout << endl;
    while(obj.leerDeDisco(pos++)){
        obj.Mostrar();
        cout << endl;
    }
}

void buscarClientePorId(){
    Clientes obj;
    int pos=0;
    int id;
    bool encontro=false;
    cout << "INGRESAR ID A COMPARAR: ";
    cin >> id;
    system("cls");
    cout << left;
    cout << setw(6) << "ID";
    cout << setw(10) << "DNI";
    cout << setw(12) << "SALDO";
    cout << setw(25) << "EMAIL";
    cout << setw(15) << "TELEFONO" << endl;
    cout << "-----------------------------------------------------------------";
    cout << endl;
    while(obj.leerDeDisco(pos++)){
        if(id==obj.getIdCliente()){
            obj.Mostrar();
            encontro=true;
        }
    }
    if(encontro==false){
        cout << "NO SE ENCONTRO CLIENTE CON ESE ID" << endl;
    }
}

void buscarClientePorDni(){
    Clientes obj;
    int pos=0;
    int dni;
    bool encontro=false;
    cout << "INGRESAR DNI A COMPARAR: ";
    cin >> dni;
    system("cls");
    cout << left;
    cout << setw(6) << "ID";
    cout << setw(10) << "DNI";
    cout << setw(12) << "SALDO";
    cout << setw(25) << "EMAIL";
    cout << setw(15) << "TELEFONO" << endl;
    cout << "-----------------------------------------------------------------";
    cout << endl;
    while(obj.leerDeDisco(pos++)){
        if(dni==obj.getDniCliente()){
            obj.Mostrar();
            encontro=true;
        }
    }
    if(encontro==false){
        cout << "NO SE ENCONTRO CLIENTE CON ESE DNI" << endl;
    }
}

int menuClientes() {
	int opc;
	do{
        cout << "MENU CLIENTES" << endl;
        cout << "---------------------------" << endl;
        cout << "1- INGRESAR CLIENTE" << endl;
        cout << "2- LISTAR CLIENTES" << endl;
        cout << "3- LISTAR CLIENTE POR ID" << endl;
        cout << "4- LISTAR CLIENTE POR DNI" << endl;
        cout << "0- VOLVER AL MENU PRINCIPAL" << endl;
        cout << "---------------------------" << endl;
        cout << "INGRESAR OPCION: ";
        cin >> opc;
        system("cls");
        switch (opc){
            case 1: cargarCliente();
                break;
            case 2: listarClientes();
                break;
            case 3: buscarClientePorId();
                break;
            case 4: buscarClientePorDni();
                break;
            case 0:
                return 0;
                break;
            default: cout << "COLOQUE UNA OPCION CORRECTA POR FAVOR. \n";
                break;
        }
        system("pause>null");
        system("cls");
    }while (true);
	return 0;
}
