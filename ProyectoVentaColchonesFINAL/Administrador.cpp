#include <iostream>
#include <iomanip>

using namespace std;

#include "Administrador.h"
#include "Usuarios.h"

int verificarDNIAdmin(int);
int verificarIDAdmin(int);
void verificarAdminUsuario(int);

void Administrador::Cargar(){
    cout << "ID ADMIN: ";
    cin >> _idAdmin;
    if(verificarIDAdmin(_idAdmin)!=-1){
        cout << "ID EXISTENTE" << endl;
        return;
    }
    cout << "DNI ADMIN: ";
    cin >> _dniAdmin;
    if(verificarDNIAdmin(_dniAdmin)!=-1){
        cout << "DNI EXISTENTE" << endl;
        return;
    }
    verificarAdminUsuario(_dniAdmin);
    cout << "PASS. ADMIN: ";
    cin >> _passAdmin;
    cout << "INGRESAR SUELDO: ";
    cin >> _sueldo;
    cout << "INGRESAR FECHA NACIMIENTO: ";
    _fechaNac.Cargar();
    cout << "INGRESAR FECHA INGRESO: ";
    _fechaIngreso.Cargar();
}

void Administrador::Mostrar(){
    cout << setw(4) << _idAdmin;
    cout << setw(10) << _dniAdmin;
    cout << setw(10) << _passAdmin;
    cout << setw(10) << _sueldo;
    cout << setw(7) << Edad();
    cout << setw(2) << this->getFechaNacimiento().getDia() << "/";
    cout << setw(2) << this->getFechaNacimiento().getMes() << "/";
    cout << setw(8) << this->getFechaNacimiento().getAnio();
    cout << setw(2) << this->getFechaIngreso().getDia() << "/";
    cout << setw(2) << this->getFechaIngreso().getMes() << "/";
    cout << setw(4) << this->getFechaIngreso().getAnio();
}

bool Administrador::grabarEnDisco(){
    FILE *p;
    p = fopen("admin.dat", "ab");
    if (p == NULL) {
        cout << "NO SE PUDO ABRIR EL ARCHIVO" << endl;
        return false;
    }
    bool leyo = fwrite(this, sizeof(Administrador), 1, p);
    fclose(p);
    return leyo;
}

bool Administrador::leerDeDisco(int pos){
    FILE *p;
    p = fopen("admin.dat", "rb");
    if (p== NULL) {
        cout<< "NO SE PUDO ABRIR EL ARCHIVO" << endl;
        return false;
    }
    fseek(p, pos * sizeof(Administrador), 0);
    bool leyo = fread(this, sizeof(Administrador), 1, p);
    fclose(p);
    return leyo;
}

void verificarAdminUsuario(int dni){
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
        cout << endl;
        if(reg.grabarEnDisco()){
            cout << "USUARIO GRABADO CON EXITO" << endl;
        }else{
            cout << "NO SE PUDO GRABAR EL USUARIO" << endl;
        }
    }
    cout << endl;
}

int verificarIDAdmin(int id){
    Administrador obj;
    int pos=0;
    if(obj.contarAdministradores()==-1){
        return -1;
    }
    while(obj.leerDeDisco(pos++)){
        if(obj.getIdAdmin()==id){
            return pos;
        }
    }
    return -1;
}

int verificarDNIAdmin(int dni){
    Administrador obj;
    int pos=0;
    if(obj.contarAdministradores()==-1){
        return -1;
    }
    while(obj.leerDeDisco(pos++)){
        if(obj.getDniAdmin()==dni){
            return pos;
        }
    }
    return -1;
}

void cargarAdministrador(){
    Administrador obj;
    obj.Cargar();
    cout << endl;
    if(verificarIDAdmin(obj.getIdAdmin())!=-1 || verificarDNIAdmin(obj.getDniAdmin())!=-1){
        cout << "NO SE PUDO GRABAR EL VENDEDOR" << endl;
        return;
    }
    if(obj.grabarEnDisco()){
        cout << "USUARIO GRABADO CON EXITO" << endl;
    }else{
        cout << "NO SE PUDO CARGAR EL USUARIO" << endl;
    }
}

void listarAdministradores(){
    Administrador obj;
    int pos=0;
    cout << left;
    cout << setw(4) << "ID";
    cout << setw(10) << "DNI";
    cout << setw(10) << "PASS";
    cout << setw(10) << "SUELDO";
    cout << setw(7) << "EDAD";
    cout << setw(14) << "FECHA NAC";
    cout << setw(12) << "FECHA INGRESO" << endl;
    cout << "---------------------------------------------------------------------";
    cout << endl;
    while(obj.leerDeDisco(pos++)){
        obj.Mostrar();
        cout << endl;
    }
}

void buscarAdminPorId(){
    Administrador obj;
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
        if(id==obj.getIdAdmin()){
            obj.Mostrar();
            encontro=true;
        }
    }
    if(encontro==false){
        cout << "NO SE ENCONTRO ADMIN CON ESE ID" << endl;
    }
}

void buscarAdminPorDni(){
    Administrador obj;
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
        if(dni==obj.getDniAdmin()){
            obj.Mostrar();
            encontro=true;
        }
    }
    if(encontro==false){
        cout << "NO SE ENCONTRO ADMIN CON ESE DNI" << endl;
    }
}

int menuAdministradores(){
    int opc;
    while(true){
        cout << "MENU ADMINISTRADOR" << endl;
        cout << "---------------------------" << endl;
        cout << "1- INGRESAR ADMINISTRADOR" << endl;
        cout << "2- LISTAR ADMINISTRADORES" << endl;
        cout << "3- LISTAR ADMIN POR ID" << endl;
        cout << "4- LISTAR ADMIN POR DNI" << endl;
        cout << "0- VOLVER AL MENU PRINCIPAL" << endl;
        cout << "---------------------------" << endl;
        cout << "INGRESAR OPCION: ";
        cin >> opc;
        system("cls");
        switch(opc){
            case 1: cargarAdministrador();
                break;
            case 2: listarAdministradores();
                break;
            case 3: buscarAdminPorId();
                break;
            case 4: buscarAdminPorDni();
                break;
            case 0: return 0;
                break;
        }
        system("pause>null");
        system("cls");
    }
    return 0;
}

#include "Administrador.h"
