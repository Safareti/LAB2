#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iomanip>

using namespace std;

#include "Colchon.h"

int verificarMedida(int);
void cargarMedida(int);
int verificarModelo(int);
void cargarModelo(int);

int verificarIDColchon(int id){
    Colchon obj;
    int pos=0;
    if(obj.contarColchones()==-1){
        return -1;
    }
    while(obj.leerDeDisco(pos++)){
        if(obj.getIdColchon()==id){
            return pos;
        }
    }
    return -1;
}

void Colchon::Cargar(){
    cout << "ID COLCHON: ";
    cin >> _idColchon;
    if(verificarIDColchon(_idColchon)!=-1){
        return;
    }
    cout << "STOCK: ";
    cin >> _stock;
    cout << "ID MEDIDA: ";
    cin >> _idMedida;
    if(verificarMedida(_idMedida)==-1){
        cout << endl;
        cargarMedida(_idMedida);
    }
    cout << "PRECIO: ";
    cin >> _precio;
    cout << "ID MODELO: ";
    cin >> _idModelo;
    if(verificarModelo(_idModelo)==-1){
        cout << endl;
        cargarModelo(_idModelo);
    }
    _estado = true;
}

void Colchon::Mostrar(){
    cout << setw(6) << _idColchon;
    cout << setw(10) << _stock;
    cout << setw(10) << _idMedida;
    cout << setw(10) << _precio;
    cout << setw(15) << _idModelo;
}

bool Colchon::grabarEnDisco(){
    FILE *p;
    p = fopen("colchones.dat", "ab");
    if (p == NULL) {
        cout << "NO SE PUDO ABRIR EL ARCHIVO" << endl;
        return false;
    }
    bool leyo = fwrite(this, sizeof(Colchon), 1, p);
    fclose(p);
    return leyo;
}

bool Colchon::leerDeDisco(int pos){
     FILE *p;
    p = fopen("colchones.dat", "rb");
    if (p== NULL) {
        cout<< "NO SE PUDO ABRIR EL ARCHIVO" << endl;
        return false;
    }
    fseek(p, pos * sizeof(Colchon), 0);
    bool leyo = fread(this, sizeof(Colchon), 1, p);
    fclose(p);
    return leyo;
}

void listarColchonPorId(){
    Colchon obj;
    int idCol;
    int pos=0;
    cout << "INGRESAR ID COLCHON: ";
    cin >> idCol;
    cout << endl;
    cout << left;
    cout << "----------------------------------------------" << endl;
    cout << setw(6) << "ID";
    cout << setw(10) << "STOCK";
    cout << setw(10) << "MEDIDA";
    cout << setw(10) << "PRECIO";
    cout << setw(15) << "MODELO" << endl;
    cout << "----------------------------------------------";
    cout << endl;
    while(obj.leerDeDisco(pos++)){
        if(obj.getIdColchon()==idCol){
            obj.Mostrar();
        }
    }
}

void cargarMedida(int med){
    Medida obj;
    float alto, ancho, largo;
    cout << "EL ID DE MEDIDA INGRESADO NO EXISTE" << endl;
    cout << "INGRESE LOS DATOS PARA REGISTRARLO" << endl;
    cout << endl;
    cout << "ID MEDIDA: " << med << endl;
    cout << "INGRESAR LARGO: ";
    cin >> largo;
    cout << "INGRESAR ANCHO: ";
    cin >> ancho;
    cout << "INGRESAR ALTO: ";
    cin >> alto;
    obj.setIdMedida(med);
    obj.setLargo(largo);
    obj.setAncho(ancho);
    obj.setAlto(alto);
    if(obj.grabarEnDisco()){
        cout << "MEDIDA REGISTRADA" << endl << endl;
    }
}

int verificarMedida(int med){
    Medida obj;
    if(obj.contarMedidas()==-1){
        return -1;
    }
    int pos=0;
    while(obj.leerDeDisco(pos)){
        if(med==obj.getIdMedida()){
            return pos;
        }
        pos++;
    }
    return -1;
}

void cargarModelo(int mod){
    Modelo obj;
    char descripcion[30];
    cout << "EL ID DE MODELO INGRESADO NO EXISTE" << endl;
    cout << "INGRESE LOS DATOS PARA REGISTRARLO" << endl;
    cout << endl;
    cout << "ID MODELO: " << mod << endl;
    cout << "INGRESAR DESCRIPCION: ";
    cin >> descripcion;
    obj.setIdModelo(mod);
    obj.setDescripcion(descripcion);
    if(obj.grabarEnDisco()){
        cout << "MODELO REGISTRADO" << endl;
    }
}

int verificarModelo(int mod){
    Modelo obj;
    if(obj.contarModelos()==-1){
        return -1;
    }
    int pos=0;
    while(obj.leerDeDisco(pos)){
        if(mod==obj.getIdModelo()){
            return pos;
        }
        pos++;
    }
    return -1;
}

void cargarColchon(){
    Colchon obj;
    obj.Cargar();
    cout << endl;
    if(verificarIDColchon(obj.getIdColchon())!=-1){
        cout << "NO SE PUDO CARGAR EL COLCHON" << endl;
        return;
    }
    if(obj.grabarEnDisco() && obj.getEstado()==true){
        cout << "COLCHON GRABADO CON EXITO" << endl;
    }else{
        cout << "NO SE PUDO CARGAR EL COLCHON" << endl;
    }
}

void listarColchones(){
    Colchon obj;
    int pos=0;
    cout << left;
    cout << setw(6) << "ID";
    cout << setw(10) << "STOCK";
    cout << setw(10) << "ID MEDIDA";
    cout << setw(10) << "PRECIO";
    cout << setw(15) << "ID MODELO" << endl;
    cout << "----------------------------------------------";
    cout << endl;
    while(obj.leerDeDisco(pos++)){
        if(obj.getEstado()==true){
            obj.Mostrar();
            cout << endl;
        }
    }
}

void agregarStock(){
    Colchon obj;
    int pos=0;
    int cant;
    int idColchon;
    cout << "INGRESAR ID DE COLCHON A COMPARAR: ";
    cin >> idColchon;
    while(obj.leerDeDisco(pos)){
        if(obj.getIdColchon()==idColchon){
            cout << "STOCK A AGREGAR: ";
            cin >> cant;
            while(cant<=0){
                cout << "INGRESAR UN NUMERO VALIDO" << endl;
                cout << "STOCK A AGREGAR: ";
                cin >> cant;
            }
            obj.setStock(obj.getStock()+cant);
            obj.modificarEnDisco(pos);
            cout << "STOCK AGREGADO" << endl;
        }
        pos++;
    }
}

int menuColchones(){
    int opc;
    while(true){
        cout << "MENU COLCHONES" << endl;
        cout << "---------------------------" << endl;
        cout << "1- INGRESAR COLCHON" << endl;
        cout << "2- LISTAR COLCHONES" << endl;
        cout << "3- LISTAR COLCHON POR ID" << endl;
        cout << "4- AGREGAR STOCK" << endl;
        cout << "0- VOLVER AL MENU PRINCIPAL" << endl;
        cout << "---------------------------" << endl;
        cout << "INGRESAR OPCION: ";
        cin >> opc;
        system("cls");
        switch(opc){
            case 1: cargarColchon();
                break;
            case 2: listarColchones();
                break;
            case 3: listarColchonPorId();
                break;
            case 4: agregarStock();
                break;
            case 0: return 0;
                break;
        }
        system("pause>null");
        system("cls");
    }
    return 0;
}
