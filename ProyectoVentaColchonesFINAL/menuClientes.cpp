#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iomanip>

using namespace std;

#include "Clientes.h"
#include "Empleado.h"

void modificarCliente(int dni, int id){
    Clientes obj;
    int posCli=0;
    char _nombreCliente[30];
	char _apellidoCliente[30];
	char _email[30];
	char _telefono[30];
    while(obj.leerDeDisco(posCli)){
        if(obj.getDniCliente()==dni){
            cout << "ID: " << id << endl;
            cout << "DNI: " << dni << endl;
            cout << "INGRESAR NOMBRE: ";
            cin >> _nombreCliente;
            cout << "INGRESAR APELLIDO: ";
            cin >> _apellidoCliente;
            cout << "INGRESAR EMAIL" << endl;
            cin >> _email;
            cout << "INGRESAR TELEFONO" << endl;
            cin >> _telefono;
            obj.setIdCliente(id);
            obj.setDniCliente(dni);
            obj.setNombreCliente(_nombreCliente);
            obj.setApellidoCliente(_apellidoCliente);
            obj.setEmail(_email);
            obj.setTelfono(_telefono);
            obj.setEstado(true);
            obj.modificarEnDisco(posCli);
            cout << "CLIENTE REGISTRADO CON EXITO" << endl;
            return;
        }
        posCli++;
    }
}

int verificarIDCliente(int id){
    Clientes obj;
    int pos=0;
    if(obj.contarClientes()==-1){
        return -1;
    }
    while(obj.leerDeDisco(pos++)){
        if(obj.getIdCliente()==id && obj.getEstado()==true){
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
        if(obj.getDniCliente()==dni && obj.getEstado()==true){
            return pos;
        }
    }
    return -1;
}

void cargarCliente(){
    Clientes obj;
    obj.Cargar();
    cout << endl;
}

void listarClientes(){
    Clientes obj;
    int pos=0;
    cout << left;
    cout << setw(4) << "ID";
    cout << setw(10) << "DNI";
    cout << setw(11) << "NOMBRE";
    cout << setw(11) << "APELLIDO";
    cout << setw(17) << "EMAIL";
    cout << setw(12) << "TELEFONO" << endl;
    cout << "-------------------------------------------------------------------------";
    cout << endl;
    while(obj.leerDeDisco(pos++)){
        if(obj.getEstado()==true){
            obj.Mostrar();
            cout << endl;
        }
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
    cout << setw(4) << "ID";
    cout << setw(10) << "DNI";
    cout << setw(11) << "NOMBRE";
    cout << setw(11) << "APELLIDO";
    cout << setw(17) << "EMAIL";
    cout << setw(12) << "TELEFONO" << endl;
    cout << "-------------------------------------------------------------------------";
    cout << endl;
    while(obj.leerDeDisco(pos++)){
        if(id==obj.getIdCliente() && obj.getEstado()==true){
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
    cout << setw(4) << "ID";
    cout << setw(10) << "DNI";
    cout << setw(11) << "NOMBRE";
    cout << setw(11) << "APELLIDO";
    cout << setw(17) << "EMAIL";
    cout << setw(12) << "TELEFONO" << endl;
    cout << "-------------------------------------------------------------------------";
    cout << endl;
    while(obj.leerDeDisco(pos++)){
        if(dni==obj.getDniCliente() && obj.getEstado()==true){
            obj.Mostrar();
            encontro=true;
        }
    }
    if(encontro==false){
        cout << "NO SE ENCONTRO CLIENTE CON ESE DNI" << endl;
    }
}

bool backUpCliente(){
    FILE *p;
    p=fopen("clientes.bkp","wb");
    if(p==NULL){
        return false;
    }
    Clientes reg;
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

bool limpiarArchivoCliente(){
    FILE *p;
    p=fopen("clientes.dat","wb");
    if(p==NULL){
        return false;
    }
    fclose(p);
    return true;
}

bool restaurarClientes(){
    if(limpiarArchivoCliente()==false){
        return false;
    }
    FILE *pCli;
    FILE *p;
    Clientes reg;
    pCli=fopen("clientes.dat", "wb");
    if(pCli==NULL){
        cout<<"ERROR DE ARCHIVO"<<endl;
        return false;
    }
    p=fopen("clientes.bkp", "rb");
    if(p==NULL){
        fclose(pCli);
        cout<<"ERROR DE ARCHIVO";
        return false;
    }
    int pos=0;
    while(reg.leerDeBU(pos++)){
         if(fwrite(&reg, sizeof reg, 1, pCli)==0){
            fclose(p);
            return false;
        }
    }
    fclose(pCli);
    fclose(p);
    cout << "ARCHIVO RESTAURADO CON EXITO" << endl;
    return true;
}

bool guardarCliente(){
    FILE *p;
    p=fopen("clientes.bkp","wb");
    if(p==NULL){
        return false;
    }
    Clientes reg;
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

void bajaCliente(){
    Clientes obj;
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
    cout << setw(4) << "ID";
    cout << setw(10) << "DNI";
    cout << setw(11) << "NOMBRE";
    cout << setw(11) << "APELLIDO";
    cout << setw(17) << "EMAIL";
    cout << setw(12) << "TELEFONO" << endl;
    cout << "-------------------------------------------------------------------------";
    cout << endl;
    while(obj.leerDeDisco(pos++)){
        if(obj.getEstado()==true){
            obj.Mostrar();
            cout << endl;
        }
    }
    int id;
    cout << endl;
    cout << "INGRESAR ID A DAR DE BAJA: ";
    cin >> id;
    pos=0;
    while(obj.leerDeDisco(pos)){
        if(obj.getIdCliente()==id){
            obj.setEstado(false);
            obj.modificarEnDisco(pos);
            guardarCliente();
            restaurarClientes();
            cout << "BAJA LOGICA EXITOSA" << endl;
            return;
        }
        pos++;
    }
}

void listarClientesMenorDni() {
    Clientes oCliente;
    int* vCli, aux;
    int cantReg = oCliente.contarClientes() - 1;
    vCli = new int[cantReg];
    if (vCli == NULL) {
        return;
    }
    for (int i = 0; i < cantReg; i++) {
        oCliente.leerDeDisco(i);
        vCli[i] = oCliente.getDniCliente();
    }
    for (int i = 0; i < cantReg; i++) {
        for (int j = i + 1; j < cantReg; j++) {
            if (vCli[j] < vCli[i]) {
                aux = vCli[j];
                vCli[j] = vCli[i];
                vCli[i] = aux;
            }
        }
    }
    cout << left;
    cout << setw(4) << "ID";
    cout << setw(10) << "DNI";
    cout << setw(11) << "NOMBRE";
    cout << setw(11) << "APELLIDO";
    cout << setw(17) << "EMAIL";
    cout << setw(12) << "TELEFONO" << endl;
    cout << "-------------------------------------------------------------------------";
    cout << endl;
    for (int i = 0; i < cantReg; i++) {
        for (int j = 0; j < cantReg; j++) {
            oCliente.leerDeDisco(j);
            if (vCli[i] == oCliente.getDniCliente() ) {
                oCliente.Mostrar();
                cout << endl;
            }
        }
    }
    delete vCli;
}

void listarClientesMayorDni() {
    Clientes oCliente;
    int* vCli, aux;
    int cantReg = oCliente.contarClientes() - 1;
    vCli = new int[cantReg];
    if (vCli == NULL) {
        return;
    }
    for (int i = 0; i < cantReg; i++) {
        oCliente.leerDeDisco(i);
        vCli[i] = oCliente.getDniCliente();
    }
    for (int i = 0; i < cantReg; i++) {
        for (int j = i + 1; j < cantReg; j++) {
            if (vCli[j] > vCli[i]) {
                aux = vCli[j];
                vCli[j] = vCli[i];
                vCli[i] = aux;
            }
        }
    }
    cout << left;
    cout << setw(4) << "ID";
    cout << setw(10) << "DNI";
    cout << setw(11) << "NOMBRE";
    cout << setw(11) << "APELLIDO";
    cout << setw(17) << "EMAIL";
    cout << setw(12) << "TELEFONO" << endl;
    cout << "-------------------------------------------------------------------------";
    cout << endl;
    for (int i = 0; i < cantReg; i++) {
        for (int j = 0; j < cantReg; j++) {
            oCliente.leerDeDisco(j);
            if (vCli[i] == oCliente.getDniCliente()) {
                oCliente.Mostrar();
                cout << endl;
            }
        }
    }
    delete vCli;
}

void modificarNombreCliente() {
    Clientes oCliente;
    int id;
    char nombre[30], apellido[30];
    std::cout << "INGRESE EL ID DEL CLIENTE A MODIFICAR" << endl;
    std::cin >> id;
    int pos = 0;
    while (oCliente.leerDeDisco(pos)) {
        if (oCliente.getIdCliente() == id) {
            std::cout << "INGRESE EL NUEVO NOMBRE: ";
            std::cin >> nombre;
            std::cout << "INGRESE EL NUEVO APELLIDO: ";
            std::cin >> apellido;
            oCliente.setNombreCliente(nombre);
            oCliente.setApellidoCliente(apellido);
            oCliente.modificarEnDisco(pos);
            cout << "CLIENTE MODIFICADO CORRECTAMENTE";
            return;
        }
        pos++;
    }
    cout << "INGRESE UN ID CORRECTO POR FAVOR." << endl;
}

void modificarDniCliente() {
    Clientes oCliente;
    int dni, id;
    std::cout << "INGRESE EL ID DEL CLIENTE A MODIFICAR" << endl;
    std::cin >> id;
    int pos = 0;
    while (oCliente.leerDeDisco(pos)) {
        if (oCliente.getIdCliente() == id) {
            std::cout << "INGRESE EL DNI ";
            std::cin >> dni;
            oCliente.setDniCliente(dni);
            oCliente.modificarEnDisco(pos);
            cout << "CLIENTE MODIFICADO CORRECTAMENTE";
            return;
        }
        pos++;
    }
    cout << "INGRESE UN ID CORRECTO POR FAVOR." << endl;
}

void modificarEmailCliente() {
    Clientes oCliente;
    int id;
    char email[30];
    std::cout << "INGRESE EL ID DEL CLIENTE A MODIFICAR" << endl;
    std::cin >> id;
    int pos = 0;
    while (oCliente.leerDeDisco(pos)) {
        if (oCliente.getIdCliente() == id) {
            std::cout << "INGRESE EL EMAIL ";
            std::cin >> email;
            oCliente.setEmail(email);
            oCliente.modificarEnDisco(pos);
            cout << "CLIENTE MODIFICADO CORRECTAMENTE";
            return;
        }
        pos++;
    }
    cout << "INGRESE UN ID CORRECTO POR FAVOR." << endl;
}

void modificarTelefonoCliente() {
    Clientes oCliente;
    int id;
    char telefono[30];
    std::cout << "INGRESE EL ID DEL CLIENTE A MODIFICAR" << endl;
    std::cin >> id;
    int pos = 0;
    while (oCliente.leerDeDisco(pos)) {
        if (oCliente.getIdCliente() == id) {
            std::cout << "INGRESE EL TELEFONO: ";
            std::cin >> telefono;
            oCliente.setTelfono(telefono);
            oCliente.modificarEnDisco(pos);
            cout << "CLIENTE MODIFICADO CORRECTAMENTE";
            return;
        }
        pos++;
    }
    cout << "INGRESE UN ID CORRECTO POR FAVOR." << endl;
}

int menuModificarCliente() {
    int opc;
    do {
        cout << "MENU MODIFICAR CLIENTES" << endl;
        cout << "-------------------------------" << endl;
        cout << "1- MODIFICAR NOMBRE Y APELLIDO" << endl;
        cout << "2- MODIFICAR DNI" << endl;
        cout << "3- MODIFICAR EMAIL" << endl;
        cout << "4- MODIFICAR TELEFONO" << endl;
        cout << "0- VOLVER AL MENU CLIENTE" << endl;
        cout << "-------------------------------" << endl;
        cout << "INGRESAR OPCION: ";
        cin >> opc;
        system("cls");
        switch (opc) {
        case 1: modificarNombreCliente();
            break;
        case 2: modificarDniCliente();
            break;
        case 3: modificarEmailCliente();
            break;
        case 4: modificarTelefonoCliente();
            break;
        case 0: return 0;
        default: cout << "COLOQUE UNA OPCION CORRECTA POR FAVOR. \n";
            break;
        }
        system("pause>null");
        system("cls");
    } while (true);
    return 0;
}

int submenuClientesListados(){
    int opc;
	do{
        cout << "MENU LISTADOS" << endl;
        cout << "---------------------------" << endl;
        cout << "1- LISTAR CLIENTES" << endl;
        cout << "2- LISTAR CLIENTE POR ID" << endl;
        cout << "3- LISTAR CLIENTE POR DNI" << endl;
        cout << "4- LISTAR CLIENTE MENOR DNI" << endl;
        cout << "5- LISTAR CLIENTE MAYOR DNI" << endl;
        cout << "0- VOLVER AL MENU CLIENTES" << endl;
        cout << "---------------------------" << endl;
        cout << "INGRESAR OPCION: ";
        cin >> opc;
        system("cls");
        switch (opc){
            case 1: listarClientes();
                break;
            case 2: buscarClientePorId();
                break;
            case 3: buscarClientePorDni();
                break;
            case 4: listarClientesMenorDni();
                break;
            case 5: listarClientesMayorDni();
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

int submenuClienteBackUp(){
    int opc;
    while(true){
        cout << "MENU BACK UP" << endl;
        cout << "---------------------------" << endl;
        cout << "1- REALIZAR BACK UP CLIENTE" << endl;
        cout << "2- RESTAURAR ARCHIVO CLIENTE" << endl;
        cout << "0- VOLVER AL MENU CLIENTE" << endl;
        cout << "---------------------------" << endl;
        cout << "INGRESAR OPCION: ";
        cin >> opc;
        system("cls");
        switch(opc){
            case 1: backUpCliente();
                break;
            case 2: restaurarClientes();
                break;
            case 0: return 0;
                break;
        }
        system("pause>null");
        system("cls");
    }
    return 0;
}

int menuClientes() {
	int opc;
	do{
        cout << "MENU CLIENTES" << endl;
        cout << "---------------------------" << endl;
        cout << "1- INGRESAR CLIENTE" << endl;
        cout << "2- MENU LISTADOS" << endl;
        cout << "3- BAJA CLIENTE" << endl;
        cout << "4- MENU MODIFICACION CLIENTE" << endl;
        cout << "5- CONFIGURACION" << endl;
        cout << "0- VOLVER AL MENU PRINCIPAL" << endl;
        cout << "---------------------------" << endl;
        cout << "INGRESAR OPCION: ";
        cin >> opc;
        system("cls");
        switch (opc){
            case 1: cargarCliente();
                break;
            case 2: submenuClientesListados();
                break;
            case 3: bajaCliente();
                break;
            case 4: menuModificarCliente();
                break;
            case 5: submenuClienteBackUp();
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
