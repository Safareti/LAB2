#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iomanip>

using namespace std;

#include "Empleado.h"

void verificarEmpleadoUsuario(int dni){
    Usuario reg;
    int pos=0;
    int contUsuario=0;
    char nombre[30];
    char apellido[30];
    if(reg.contarUsuarios()!=-1){
        while(reg.leerDeDisco(pos++)){
            if(reg.getDniUsuario()==dni){
                contUsuario++;
            }
        }
    }
    if(contUsuario==0){
        cout << endl;
        cout << "EL SIGUIENTE DNI NO ESTA REGISTRADO EN EL ARCHIVO DE USUARIOS" << endl;
        cout << "DNI: " << dni;
        cout << endl;
        cout << "INGRESAR NOMBRE: ";
        cin >> nombre;
        cout << "INGRESAR APELLIDO: ";
        cin >> apellido;
        reg.setDniUsuario(dni);
        reg.setNombreUsuario(nombre);
        reg.setApellidoUsuario(apellido);
        reg.setEstadoUsuario(true);
        if(reg.grabarEnDisco()){
            cout << "USUARIO GRABADO CON EXITO" << endl;
        }else{
            cout << "NO SE PUDO GRABAR EL USUARIO" << endl;
        }
    }
    cout << endl;
}

int verificarID(int id){
    Empleado obj;
    int pos=0;
    if(obj.contarEmpleados()==-1){
        return -1;
    }
    while(obj.leerDeDisco(pos++)){
        if(obj.getIdEmpleado()==id){
            return pos;
        }
    }
    return -1;
}

int verificarDNIEmpleado(int dni){
    Empleado obj;
    int pos=0;
    if(obj.contarEmpleados()==-1){
        return -1;
    }
    while(obj.leerDeDisco(pos++)){
        if(obj.getDniEmpleado()==dni){
            return pos;
        }
    }
    return -1;
}


void cargarEmpleado(){
    Empleado obj;
    obj.Cargar();
    cout << endl;
    if(verificarID(obj.getIdEmpleado())!=-1 || verificarDNIEmpleado(obj.getDniEmpleado())!=-1){
        cout << "NO SE PUDO GRABAR EL EMPLEADO" << endl;
        return;
    }
    if(obj.grabarEnDisco()){
        cout << "EMPLEADO GRABADO CON EXITO" << endl;
    }else{
        cout << "NO SE PUDO GRABAR EL EMPLEADO" << endl;
    }
}

void listarEmpleados(){
    Empleado obj;
    int pos=0;
    cout << left;
    cout << setw(6) << "ID";
    cout << setw(10) << "DNI";
    cout << setw(10) << "SUELDO";
    cout << setw(11) << "TIPO EMP.";
    cout << setw(7) << "PASS";
    cout << setw(7) << "EDAD";
    cout << setw(14) << "FECHA NAC";
    cout << setw(12) << "FECHA INGRESO" << endl;
    cout << "-------------------------------------------------------------------------------";
    cout << endl;
    while(obj.leerDeDisco(pos++)){
        obj.Mostrar();
        cout << endl;
    }
}

void buscarEmpleadoPorId(){
    Empleado obj;
    int pos=0;
    int id;
    bool encontro=false;
    cout << "INGRESAR ID A COMPARAR: ";
    cin >> id;
    system("cls");
    cout << left;
    cout << setw(6) << "ID";
    cout << setw(12) << "DNI";
    cout << setw(10) << "SUELDO";
    cout << setw(7) << "EDAD";
    cout << setw(14) << "FECHA NAC";
    cout << setw(12) << "FECHA INGRESO" << endl;
    cout << "--------------------------------------------------------------";
    cout << endl;
    while(obj.leerDeDisco(pos++)){
        if(id==obj.getIdEmpleado()){
            obj.Mostrar();
            encontro=true;
        }
    }
    if(encontro==false){
        cout << "NO SE ENCONTRO EMPLEADO CON ESE ID" << endl;
    }
}

void buscarEmpleadoPorDni(){
    Empleado obj;
    int pos=0;
    int dni;
    bool encontro=false;
    cout << "INGRESAR DNI A COMPARAR: ";
    cin >> dni;
    system("cls");
    cout << left;
    cout << setw(6) << "ID";
    cout << setw(12) << "DNI";
    cout << setw(10) << "SUELDO";
    cout << setw(7) << "EDAD";
    cout << setw(14) << "FECHA NAC";
    cout << setw(12) << "FECHA INGRESO" << endl;
    cout << "--------------------------------------------------------------";
    cout << endl;
    while(obj.leerDeDisco(pos++)){
        if(dni==obj.getDniEmpleado()){
            obj.Mostrar();
            encontro=true;
        }
    }
    if(encontro==false){
        cout << "NO SE ENCONTRO EMPLEADO CON ESE DNI" << endl;
    }
}

int menuEmpleado(){
    int opc;
    while(true){
        cout << "MENU VENDEDORES" << endl;
        cout << "---------------------------" << endl;
        cout << "1- INGRESAR EMPLEADO" << endl;
        cout << "2- LISTAR EMPLEADOS" << endl;
        cout << "3- LISTAR EMPLEADO POR ID" << endl;
        cout << "4- LISTAR EMPLEADO POR DNI" << endl;
        cout << "0- VOLVER AL MENU PRINCIPAL" << endl;
        cout << "---------------------------" << endl;
        cout << "INGRESAR OPCION: ";
        cin >> opc;
        system("cls");
        switch(opc){
            case 1: cargarEmpleado();
                break;
            case 2: listarEmpleados();
                break;
            case 3: buscarEmpleadoPorId();
                break;
            case 4: buscarEmpleadoPorDni();
                break;
            case 0: return 0;
                break;
        }
        system("pause>null");
        system("cls");
    }
    return 0;
}
