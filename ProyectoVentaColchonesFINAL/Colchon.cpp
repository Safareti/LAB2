#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iomanip>

using namespace std;

#include "Colchon.h"
#include "Empleado.h"

int verificarMedida(int);
void cargarMedida(int);
int verificarModelo(int);
void cargarModelo(int);

void listarModelos(){
    Modelo obj;
    int pos=0;
    while(obj.leerDeDisco(pos++)){
        obj.Mostrar();
        cout << endl;
    }
}

void grabarModelo(){
    Modelo obj;
    obj.Cargar();
    cout << endl;
}

void listarMedidas(){
    Medida obj;
    int pos=0;
    while(obj.leerDeDisco(pos++)){
        obj.Mostrar();
        cout << endl;
    }
}

void grabarMedida(){
    Medida obj;
    obj.Cargar();
    cout << endl;
}

int verificarIdMedida(int idMed){
    Medida obj;
    int pos=0;
    if(obj.contarMedidas()==-1){
        return -1;
    }
    while(obj.leerDeDisco(pos++)){
        if(obj.getIdMedida()==idMed){
            return pos;
        }
    }
    return -1;
}

int verificarIdModelo(int idMod){
    Modelo obj;
    int pos=0;
    if(obj.contarModelos()==-1){
        return -1;
    }
    while(obj.leerDeDisco(pos++)){
        if(obj.getIdModelo()==idMod){
            return pos;
        }
    }
    return -1;
}

int verificarIDColchon(int id){
    Colchon obj;
    int pos=0;
    if(obj.contarColchones()==-1){
        return -1;
    }
    while(obj.leerDeDisco(pos++)){
        if(obj.getIdColchon()==id && obj.getEstado()==true){
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
    while (_stock < 0){
        cout << "INGRESE UN STOCK CORRECTO POR FAVOR: ";
        cin >> _stock;
    }
    cout << "ID MEDIDA: ";
    cin >> _idMedida;
    if(verificarMedida(_idMedida)==-1){
        cout << endl;
        cargarMedida(_idMedida);
    }
    cout << "PRECIO: ";
    cin >> _precio;
    while (_precio < 0) {
        cout << "INGRESE UN PRECIO CORRECTO POR FAVOR: ";
            cin >> _precio;
    }
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

void consultaColchonPrecio(){
    Colchon obj;
    int pos=0;
    int rango1, rango2;
    cout << "INGRESA PRIMER NUMERO: ";
    cin >> rango1;
    while(rango1<0){
        cout << "NUMERO NO PERMITIDO, INGRESE OTRO" << endl;
        cout << "INGRESA PRIMER NUMERO: ";
        cin >> rango1;
    }
    cout << "INGRESA SEGUNDO NUMERO: ";
    cin >> rango2;
    while(rango2<0 || rango2<=rango1){
        cout << "NUMERO NO PERMITIDO, INGRESE OTRO" << endl;
        cout << "INGRESA SEGUNDO NUMERO: ";
        cin >> rango2;
    }
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
        if(obj.getPrecio()>=rango1 && obj.getPrecio()<=rango2){
            obj.Mostrar();
            cout << endl;
        }
    }
}

void consultaColchonStock(){
    Colchon obj;
    int pos=0;
    int rango1, rango2;
    cout << "INGRESA PRIMER NUMERO: ";
    cin >> rango1;
    while(rango1<0){
        cout << "NUMERO NO PERMITIDO, INGRESE OTRO" << endl;
        cout << "INGRESA PRIMER NUMERO: ";
        cin >> rango1;
    }
    cout << "INGRESA SEGUNDO NUMERO: ";
    cin >> rango2;
    while(rango2<0 || rango2<=rango1){
        cout << "NUMERO NO PERMITIDO, INGRESE OTRO" << endl;
        cout << "INGRESA SEGUNDO NUMERO: ";
        cin >> rango2;
    }
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
        if(obj.getStock()>=rango1 && obj.getStock()<=rango2){
            obj.Mostrar();
            cout << endl;
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
    Empleado reg;
    int posCol=0, posEmp=0;
    int cant;
    int idColchon;
    int idEmpleado, pass;
    bool continuar=false, estadoCol=false;
    cout << "INGRESAR ID EMPLEADO: ";
    cin >> idEmpleado;
    cout << "INGRESAR CONTRASEÑA: ";
    cin >> pass;
    cout << endl;
    while(reg.leerDeDisco(posEmp++)){
        if(reg.getIdEmpleado()==idEmpleado && reg.getPass()==pass && reg.getTipoEmpleado()==2){
            continuar=true;
        }
    }
    if(continuar==false){
        cout << "ID EMPLEADO Y/O CONTRASEÑA INCORRECTOS" << endl;
        return;
    }
    cout << "INGRESAR ID DE COLCHON A COMPARAR: ";
    cin >> idColchon;
    while(estadoCol==false){
        posCol=0;
        while(obj.leerDeDisco(posCol)){
            if(obj.getIdColchon()==idColchon){
                estadoCol=true;
                cout << "STOCK ACTUAL: " << obj.getStock() << endl;
                cout << "STOCK A AGREGAR: ";
                cin >> cant;
                while(cant<=0){
                    cout << "INGRESAR UN NUMERO VALIDO" << endl;
                    cout << "STOCK A AGREGAR: ";
                    cin >> cant;
                }
                obj.setStock(obj.getStock()+cant);
                obj.modificarEnDisco(posCol);
                cout << "STOCK AGREGADO" << endl;
            }
            posCol++;
        }
        if(estadoCol==false){
            cout << "ID COLCHON NO ENCONTRADO, INGRESE OTRO" << endl << endl;
            cout << "INGRESAR ID DE COLCHON A COMPARAR: ";
            cin >> idColchon;
        }
    }
}

void modificarPrecioColchon(){
    Empleado reg;
    Colchon obj;
    int posEmp=0;
    int posCol=0;
    int idCol, idEmpleado, pass;
    float precioNuevo;
    bool continuar=false;
    cout << "INGRESAR ID EMPLEADO: ";
    cin >> idEmpleado;
    cout << "INGRESAR CONTRASEÑA: ";
    cin >> pass;
    cout << endl;
    while(reg.leerDeDisco(posEmp++)){
        if(reg.getIdEmpleado()==idEmpleado && reg.getPass()==pass && reg.getTipoEmpleado()==2){
            continuar=true;
        }
    }
    if(continuar==false){
        cout << "ID EMPLEADO Y/O CONTRASEÑA INCORRECTOS" << endl;
        return;
    }
    cout << "INGRESAR ID COLCHON A MODIFICAR PRECIO: ";
    cin >> idCol;
    while(obj.leerDeDisco(posCol)){
        if(obj.getIdColchon()==idCol){
            cout << "INGRESAR PRECIO NUEVO: ";
            cin >> precioNuevo;
            while(precioNuevo<=0){
                cout << "PRECIO NO PERMITIDO, INGRESE OTRO" << endl;
                cout << "INGRESAR PRECIO NUEVO: ";
                cin >> precioNuevo;
            }
            obj.setPrecio(precioNuevo);
            obj.modificarEnDisco(posCol);
            cout << "PRECIO MODIFICADO CON EXITO" << endl;
            return;
         }
        posCol++;
    }
    cout << "ID COLCHON NO ENCONTRADO" << endl;
}

void ordenarColchonMayorPrecio(){
    Colchon obj;
    int cantReg=obj.contarColchones()-1;
    float *vPrecio, aux;
    int *vIdCol, aux2;
    vPrecio=new float[cantReg];
    if(vPrecio==NULL){
        return;
    }
    vIdCol=new int[cantReg];
    if(vIdCol==NULL){
        return;
    }
    for(int i=0; i<cantReg; i++){
        obj.leerDeDisco(i);
        vPrecio[i]=obj.getPrecio();
        vIdCol[i]=obj.getIdColchon();
    }
    for(int i=0; i<cantReg; i++){
        for(int j=i+1; j<cantReg; j++){
            if(vPrecio[i]<vPrecio[j]){
                aux=vPrecio[j];
                vPrecio[j]=vPrecio[i];
                vPrecio[i]=aux;
                aux2=vIdCol[j];
                vIdCol[j]=vIdCol[i];
                vIdCol[i]=aux2;
            }
        }
    }
    cout << left;
    cout << setw(6) << "ID";
    cout << setw(10) << "STOCK";
    cout << setw(10) << "MEDIDA";
    cout << setw(10) << "PRECIO";
    cout << setw(15) << "MODELO" << endl;
    cout << "----------------------------------------------";
    cout << endl;
    for(int i=0; i<cantReg; i++){
        for(int j=0; j<cantReg; j++){
            obj.leerDeDisco(j);
            if(obj.getPrecio()==vPrecio[i] && obj.getIdColchon()==vIdCol[i]){
                obj.Mostrar();
            }
        }
        cout << endl;
    }
    delete vPrecio;
    delete vIdCol;
}

void ordenarColchonMenorPrecio(){
    Colchon obj;
    int cantReg=obj.contarColchones()-1;
    float *vPrecio, aux;
    int *vIdCol, aux2;
    vPrecio=new float[cantReg];
    if(vPrecio==NULL){
        return;
    }
    vIdCol=new int[cantReg];
    if(vIdCol==NULL){
        return;
    }
    for(int i=0; i<cantReg; i++){
        obj.leerDeDisco(i);
        vPrecio[i]=obj.getPrecio();
        vIdCol[i]=obj.getIdColchon();
    }
    for(int i=0; i<cantReg; i++){
        for(int j=i+1; j<cantReg; j++){
            if(vPrecio[i]>vPrecio[j]){
                aux=vPrecio[j];
                vPrecio[j]=vPrecio[i];
                vPrecio[i]=aux;
                aux2=vIdCol[j];
                vIdCol[j]=vIdCol[i];
                vIdCol[i]=aux2;
            }
        }
    }
    cout << left;
    cout << setw(6) << "ID";
    cout << setw(10) << "STOCK";
    cout << setw(10) << "MEDIDA";
    cout << setw(10) << "PRECIO";
    cout << setw(15) << "MODELO" << endl;
    cout << "----------------------------------------------";
    cout << endl;
    for(int i=0; i<cantReg; i++){
        for(int j=0; j<cantReg; j++){
            obj.leerDeDisco(j);
            if(obj.getPrecio()==vPrecio[i] && obj.getIdColchon()==vIdCol[i]){
                obj.Mostrar();
            }
        }
        cout << endl;
    }
    delete vPrecio;
    delete vIdCol;
}

void ordenarColchonMayorStock(){
    Colchon obj;
    int cantReg=obj.contarColchones()-1;
    int *vStock, aux, *vIdCol, aux2;
    vStock=new int[cantReg];
    if(vStock==NULL){
        return;
    }
    vIdCol=new int[cantReg];
    if(vIdCol==NULL){
        return;
    }
    for(int i=0; i<cantReg; i++){
        obj.leerDeDisco(i);
        vStock[i]=obj.getStock();
        vIdCol[i]=obj.getIdColchon();
    }
    for(int i=0; i<cantReg; i++){
        for(int j=i+1; j<cantReg; j++){
            if(vStock[i]<vStock[j]){
                aux=vStock[j];
                vStock[j]=vStock[i];
                vStock[i]=aux;
                aux2=vIdCol[j];
                vIdCol[j]=vIdCol[i];
                vIdCol[i]=aux2;
            }
        }
    }
    cout << left;
    cout << setw(6) << "ID";
    cout << setw(10) << "STOCK";
    cout << setw(10) << "MEDIDA";
    cout << setw(10) << "PRECIO";
    cout << setw(15) << "MODELO" << endl;
    cout << "----------------------------------------------";
    cout << endl;
    for(int i=0; i<cantReg; i++){
        for(int j=0; j<cantReg; j++){
            obj.leerDeDisco(j);
            if(obj.getStock()==vStock[i] && obj.getIdColchon()==vIdCol[i]){
                obj.Mostrar();
            }
        }
        cout << endl;
    }
    delete vStock;
    delete vIdCol;
}

void ordenarColchonMenorStock(){
    Colchon obj;
    int cantReg=obj.contarColchones()-1;
    int *vStock, aux, *vIdCol, aux2;
    vStock=new int[cantReg];
    if(vStock==NULL){
        return;
    }
    vIdCol=new int[cantReg];
    if(vIdCol==NULL){
        return;
    }
    for(int i=0; i<cantReg; i++){
        obj.leerDeDisco(i);
        vStock[i]=obj.getStock();
        vIdCol[i]=obj.getIdColchon();
    }
    for(int i=0; i<cantReg; i++){
        for(int j=i+1; j<cantReg; j++){
            if(vStock[i]>vStock[j]){
                aux=vStock[j];
                vStock[j]=vStock[i];
                vStock[i]=aux;
                aux2=vIdCol[j];
                vIdCol[j]=vIdCol[i];
                vIdCol[i]=aux2;
            }
        }
    }
    cout << left;
    cout << setw(6) << "ID";
    cout << setw(10) << "STOCK";
    cout << setw(10) << "MEDIDA";
    cout << setw(10) << "PRECIO";
    cout << setw(15) << "MODELO" << endl;
    cout << "----------------------------------------------";
    cout << endl;
    for(int i=0; i<cantReg; i++){
        for(int j=0; j<cantReg; j++){
            obj.leerDeDisco(j);
            if(obj.getStock()==vStock[i] && obj.getIdColchon()==vIdCol[i]){
                obj.Mostrar();
            }
        }
        cout << endl;
    }
    delete vStock;
    delete vIdCol;
}

bool backUpColchon(){
    FILE *p;
    p=fopen("colchones.bkp","wb");
    if(p==NULL){
        return false;
    }
    Colchon reg;
    int pos=0;
    while(reg.leerDeDisco(pos++)){
        if(fwrite(&reg, sizeof reg, 1, p)==0){
            fclose(p);
            return false;
        }
    }
    fclose(p);
    cout << "BACK UP REALIZADO CON EXITO" << endl;
    system("pause>nul");
    system("cls");
    return true;
}

bool limpiarArchivoColchon(){
    FILE *p;
    p=fopen("colchones.dat","wb");
    if(p==NULL){
        return false;
    }
    fclose(p);
    return true;
}

bool restaurarColchones(){
    if(limpiarArchivoColchon()==false){
        return false;
    }
    FILE *pCol;
    FILE *p;
    Colchon reg;
    pCol=fopen("colchones.dat", "wb");
    if(pCol==NULL){
        cout<<"ERROR DE ARCHIVO"<<endl;
        return false;
    }
    p=fopen("colchones.bkp", "rb");
    if(p==NULL){
        fclose(pCol);
        cout<<"ERROR DE ARCHIVO";
        return false;
    }
    int pos=0;
    while(reg.leerDeBU(pos++)){
         if(fwrite(&reg, sizeof reg, 1, pCol)==0){
            fclose(p);
            return false;
        }
    }
    fclose(pCol);
    fclose(p);
    cout << "ARCHIVO COLCHON RESTAURADO CON EXITO" << endl;
    return true;
}

bool guardarColchon(){
    FILE *p;
    p=fopen("colchones.bkp","wb");
    if(p==NULL){
        return false;
    }
    Colchon reg;
    int pos=0;
    while(reg.leerDeDisco(pos)){
        if(reg.getEstado()==true){
            if(fwrite(&reg, sizeof reg, 1, p)==0){
                fclose(p);
                return false;
            }
        }
        pos++;
    }
    fclose(p);
    return true;
}

void bajaColchon(){
    Colchon obj;
    int pos=0;
    Empleado reg;
    int posEmp=0;
    int idEmp, pass;
    bool encontro=false;
    cout << "INGRESAR ID EMPLEADO: ";
    cin >> idEmp;
    cout << "INGRESAR CONTRASEÑA: ";
    cin >> pass;
    cout << endl;
    while(reg.leerDeDisco(posEmp++)){
        if(reg.getIdEmpleado()==idEmp && reg.getPass()==pass){
            encontro=true;
        }
    }
    if(encontro==false){
        cout << "ID EMPLEADO Y/O CONTRASEÑA INCORRECTO" << endl;
        return;
    }
    system("cls");
    posEmp=0;
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
    cout << endl;
    pos=0;
    int id;
    cout << "INGRESAR ID A DAR DE BAJA: ";
    cin >> id;
    while(obj.leerDeDisco(pos)){
        if(obj.getIdColchon()==id){
            obj.setEstado(false);
            obj.modificarEnDisco(pos);
            guardarColchon();
            restaurarColchones();
            cout << "BAJA LOGICA EXITOSA" << endl;
            return;
        }
        pos++;
    }
}

void mostrarColchonPorMedida(int id){
    Colchon reg;
    int pos = 0;
    cout << endl;
    cout << left;
    cout << setw(6) << "ID";
    cout << setw(10) << "STOCK";
    cout << setw(10) << "ID MEDIDA";
    cout << setw(10) << "PRECIO";
    cout << setw(15) << "MODELO" << endl;
    cout << "----------------------------------------------";
    cout << endl;
    while(reg.leerDeDisco(pos++)){
        if(reg.getMedida() == id){
            reg.Mostrar();
            cout << endl;
        }
    }
}

void consultaColchonMedida(){
    Medida reg;
    float largo, ancho, alto;
    int pos = 0;
    cout << "INGRESE MEDIDA" << endl;
    cout << "LARGO: "; cin >> largo;
    cout << "ANCHO: "; cin >> ancho;
    cout << "ALTO: "; cin >> alto;
    while(reg.leerDeDisco(pos++)){
        if(reg.getLargo() == largo && reg.getAncho() == ancho && reg.getAlto() == alto){
            mostrarColchonPorMedida(reg.getIdMedida());
        }
    }
}

void ordenarColchonMenorModelo(){
    Colchon obj;
    Modelo reg;
    int *vMod, aux, pos=0;
    int cantReg=reg.contarModelos()-1;
    vMod=new int[cantReg];
    if(vMod==NULL){
        return;
    }
    for(int i=0; i<cantReg; i++){
        reg.leerDeDisco(i);
        vMod[i]=reg.getIdModelo();
    }
    for(int i=0; i<cantReg; i++){
        for(int j=i+1; j<cantReg; j++){
            if(vMod[i]>vMod[j]){
                aux=vMod[j];
                vMod[j]=vMod[i];
                vMod[i]=aux;
            }
        }
    }
    cout << left;
    cout << setw(6) << "ID";
    cout << setw(10) << "STOCK";
    cout << setw(10) << "ID MEDIDA";
    cout << setw(10) << "PRECIO";
    cout << setw(15) << "MODELO" << endl;
    cout << "----------------------------------------------";
    cout << endl;
    for(int i=0; i<cantReg; i++){
        pos=0;
        while(obj.leerDeDisco(pos)){
            if(obj.getModeloColchon()==vMod[i]){
                obj.Mostrar();
                cout << endl;
            }
            pos++;
        }
    }
    delete vMod;
}

void ordenarColchonMayorModelo(){
    Colchon obj;
    Modelo reg;
    int *vMod, aux, pos=0;
    int cantReg=reg.contarModelos()-1;
    vMod=new int[cantReg];
    if(vMod==NULL){
        return;
    }
    for(int i=0; i<cantReg; i++){
        reg.leerDeDisco(i);
        vMod[i]=reg.getIdModelo();
    }
    for(int i=0; i<cantReg; i++){
        for(int j=i+1; j<cantReg; j++){
            if(vMod[i]<vMod[j]){
                aux=vMod[j];
                vMod[j]=vMod[i];
                vMod[i]=aux;
            }
        }
    }
    cout << left;
    cout << setw(6) << "ID";
    cout << setw(10) << "STOCK";
    cout << setw(10) << "ID MEDIDA";
    cout << setw(10) << "PRECIO";
    cout << setw(15) << "MODELO" << endl;
    cout << "----------------------------------------------";
    cout << endl;
    for(int i=0; i<cantReg; i++){
        pos=0;
        while(obj.leerDeDisco(pos)){
            if(obj.getModeloColchon()==vMod[i]){
                obj.Mostrar();
                cout << endl;
            }
            pos++;
        }
    }
    delete vMod;
}

void ordenarColchonMenorMedida(){
    Colchon obj;
    Medida reg;
    int *vMed, aux, pos=0;
    int cantReg=reg.contarMedidas()-1;
    vMed=new int[cantReg];
    if(vMed==NULL){
        return;
    }
    for(int i=0; i<cantReg; i++){
        reg.leerDeDisco(i);
        vMed[i]=reg.getIdMedida();
    }
    for(int i=0; i<cantReg; i++){
        for(int j=i+1; j<cantReg; j++){
            if(vMed[i]>vMed[j]){
                aux=vMed[j];
                vMed[j]=vMed[i];
                vMed[i]=aux;
            }
        }
    }
    cout << left;
    cout << setw(6) << "ID";
    cout << setw(10) << "STOCK";
    cout << setw(10) << "ID MEDIDA";
    cout << setw(10) << "PRECIO";
    cout << setw(15) << "MODELO" << endl;
    cout << "----------------------------------------------";
    cout << endl;
    for(int i=0; i<cantReg; i++){
        pos=0;
        while(obj.leerDeDisco(pos)){
            if(obj.getMedida()==vMed[i]){
                obj.Mostrar();
                cout << endl;
            }
            pos++;
        }
    }
    delete vMed;
}

void ordenarColchonMayorMedida(){
    Colchon obj;
    Medida reg;
    int *vMed, aux, pos=0;
    int cantReg=reg.contarMedidas()-1;
    vMed=new int[cantReg];
    if(vMed==NULL){
        return;
    }
    for(int i=0; i<cantReg; i++){
        reg.leerDeDisco(i);
        vMed[i]=reg.getIdMedida();
    }
    for(int i=0; i<cantReg; i++){
        for(int j=i+1; j<cantReg; j++){
            if(vMed[i]<vMed[j]){
                aux=vMed[j];
                vMed[j]=vMed[i];
                vMed[i]=aux;
            }
        }
    }
    cout << left;
    cout << setw(6) << "ID";
    cout << setw(10) << "STOCK";
    cout << setw(10) << "ID MEDIDA";
    cout << setw(10) << "PRECIO";
    cout << setw(15) << "MODELO" << endl;
    cout << "----------------------------------------------";
    cout << endl;
    for(int i=0; i<cantReg; i++){
        pos=0;
        while(obj.leerDeDisco(pos)){
            if(obj.getMedida()==vMed[i]){
                obj.Mostrar();
                cout << endl;
            }
            pos++;
        }
    }
    delete vMed;
}

void consultaColchonModelo() {
    Colchon oColchon;
    int p = 0;
    int id;
    cout << "INGRESE EL ID DEL MODELO: ";
    cin >> id;
    cout << endl;
    cout << left;
    cout << setw(6) << "ID";
    cout << setw(10) << "STOCK";
    cout << setw(10) << "ID MEDIDA";
    cout << setw(10) << "PRECIO";
    cout << setw(15) << "MODELO" << endl;
    cout << "----------------------------------------------";
    cout << endl;
    while (oColchon.leerDeDisco(p++)) {
        if (id == oColchon.getModeloColchon()) {
            oColchon.Mostrar();
            cout << endl;
        };
    }
    return;
}

int submenuColchonesListados(){
    int opc;
    while(true){
        cout << "MENU LISTADOS" << endl;
        cout << "---------------------------" << endl;
        cout << "1- LISTAR COLCHONES" << endl;
        cout << "2- LISTAR COLCHON POR ID" << endl;
        cout << "3- LISTADO COLCHON POR RANGO PRECIO" << endl;
        cout << "4- LISTADO COLCHON POR RANGO STOCK" << endl;
        cout << "5- LISTADO COLCHONES POR MAYOR PRECIO" << endl;
        cout << "6- LISTADO COLCHONES POR MENOR PRECIO" << endl;
        cout << "7- LISTADO COLCHONES POR MAYOS STOCK" << endl;
        cout << "8- LISTADO COLCHONES POR MENOR STOCK" << endl;
        cout << "9- LISTADO COLCHON POR MEDIDA" << endl;
        cout << "10- LISTADO COLCHON MODELO" << endl;
        cout << "11- LISTADO COLCHONES POR MENOR MODELO" << endl;
        cout << "12- LISTADO COLCHONES POR MAYOR MODELO" << endl;
        cout << "13- LISTADO COLCHONES POR MENOR MEDIDA" << endl;
        cout << "14- LISTADO COLCHONES POR MAYOR MEDIDA" << endl;
        cout << "0- VOLVER AL MENU COLCHONES" << endl;
        cout << "---------------------------" << endl;
        cout << "INGRESAR OPCION: ";
        cin >> opc;
        system("cls");
        switch(opc){
            case 1: listarColchones();
                break;
            case 2: listarColchonPorId();
                break;
            case 3: consultaColchonPrecio();
                break;
            case 4: consultaColchonStock();
                break;
            case 5: ordenarColchonMayorPrecio();
                break;
            case 6: ordenarColchonMenorPrecio();
                break;
            case 7: ordenarColchonMayorStock();
                break;
            case 8: ordenarColchonMenorStock();
                break;
            case 9: consultaColchonMedida();
                break;
            case 10: consultaColchonModelo();
                break;
            case 11: ordenarColchonMenorModelo();
                break;
            case 12: ordenarColchonMayorModelo();
                break;
            case 13: ordenarColchonMenorMedida();
                break;
            case 14: ordenarColchonMayorMedida();
                break;
            case 0: return 0;
                break;
        }
        system("pause>null");
        system("cls");
    }
    return 0;
}

int submenuColchonModeloMedida(){
    int opc;
    while(true){
        cout << "MENU MODELO Y MEDIDA" << endl;
        cout << "---------------------------" << endl;
        cout << "1- GRABAR MODELO" << endl;
        cout << "2- LISTAR MODELOS" << endl;
        cout << "3- GRABAR MEDIDA" << endl;
        cout << "4- LISTAR MEDIDAS" << endl;
        cout << "0- VOLVER AL MENU COLCHONES" << endl;
        cout << "---------------------------" << endl;
        cout << "INGRESAR OPCION: ";
        cin >> opc;
        system("cls");
        switch(opc){
            case 1: grabarModelo();
                break;
            case 2: listarModelos();
                break;
            case 3: grabarMedida();
                break;
            case 4: listarMedidas();
                break;
            case 0: return 0;
                break;
        }
        system("pause>null");
        system("cls");
    }
    return 0;
}

int submenuColchonBackUp(){
    int opc;
    while(true){
        cout << "MENU BACK UP" << endl;
        cout << "---------------------------" << endl;
        cout << "1- REALIZAR BACK UP COLCHON" << endl;
        cout << "2- RESTAURAR ARCHIVO COLCHON" << endl;
        cout << "0- VOLVER AL MENU COLCHON" << endl;
        cout << "---------------------------" << endl;
        cout << "INGRESAR OPCION: ";
        cin >> opc;
        system("cls");
        switch(opc){
            case 1: backUpColchon();
                break;
            case 2: restaurarColchones();
                break;
            case 0: return 0;
                break;
        }
        system("pause>null");
        system("cls");
    }
    return 0;
}

int menuColchones(){
    int opc;
    while(true){
        cout << "MENU COLCHONES" << endl;
        cout << "---------------------------" << endl;
        cout << "1- INGRESAR COLCHON" << endl;
        cout << "2- MENU LISTADOS" << endl;
        cout << "3- AGREGAR STOCK" << endl;
        cout << "4- MODIFICAR PRECIO" << endl;
        cout << "5- BAJA COLCHON" << endl;
        cout << "6- MENU MODELO Y MEDIDA" << endl;
        cout << "7- CONFIGURACION" << endl;
        cout << "0- VOLVER AL MENU PRINCIPAL" << endl;
        cout << "---------------------------" << endl;
        cout << "INGRESAR OPCION: ";
        cin >> opc;
        system("cls");
        switch(opc){
            case 1: cargarColchon();
                break;
            case 2: submenuColchonesListados();
                break;
            case 3: agregarStock();
                break;
            case 4: modificarPrecioColchon();
                break;
            case 5: bajaColchon();
                break;
            case 6: submenuColchonModeloMedida();
                break;
            case 7: submenuColchonBackUp();
                break;
            case 0: return 0;
                break;
        }
        system("pause>null");
        system("cls");
    }
    return 0;
}
