#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iomanip>

using namespace std;

#include "Usuarios.h"

int verificarDNI(int dni){
    Usuario obj;
    int pos=0;
    if(obj.contarUsuarios()==-1){
        return -1;
    }
    while(obj.leerDeDisco(pos++)){
        if(obj.getDniUsuario()==dni){
            return pos;
        }
    }
    return -1;
}

void cargarUsuario(){
    Usuario obj;
    obj.Cargar();
    cout << endl;
    if(obj.grabarEnDisco() && obj.getEstadoUsuario()==true){
        cout << "USUARIO GRABADO CON EXITO" << endl;
    }else{
        cout << "NO SE PUDO CARGAR EL USUARIO" << endl;
    }
}

void listarUsuarios(){
    Usuario obj;
    int pos=0;
    cout << left;
    cout << setw(12) << "DNI";
    cout << setw(12) << "NOMBRE";
    cout << setw(10) << "APELLIDO" << endl;
    cout << "--------------------------------";
    cout << endl;
    while(obj.leerDeDisco(pos++)){
        obj.Mostrar();
    }
}

int menuUsuarios(){
    int opc;
    while(true){
        cout << "MENU USUARIO" << endl;
        cout << "---------------------------" << endl;
        cout << "1- LISTAR USUARIOS" << endl;
        cout << "0- VOLVER AL MENU PRINCIPAL" << endl;
        cout << "---------------------------" << endl;
        cout << "INGRESAR OPCION: ";
        cin >> opc;
        system("cls");
        switch(opc){
            case 1: listarUsuarios();
                break;
            case 0: return 0;
                break;
        }
        system("pause>null");
        system("cls");
    }
    return 0;
}

#include "Usuarios.h"
