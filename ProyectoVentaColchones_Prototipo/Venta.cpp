#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <iomanip>

using namespace std;

#include "Venta.h"
#include "Empleado.h"
#include "Clientes.h"
#include "DetalleVenta.h"

int chequearEmpleado(int);
int chequearCliente(int);
int chequearColchon(int);
int chequearCantidadColchon(int, int);
float calcularImporte(int, int);
int devolverStock(int);
int verificarStock(int);
void detalleVenta(int, int);

void Venta::Cargar(){
    cout << "ID FACTURA: " << contarVenta() << endl;
    setIdFactura(contarVenta());
    cout << "FECHA FACTURA" << endl;
    _fecha.Cargar();
    cout << "ID EMPLEADO: ";
    cin >> _IdEmpleado;
    while(chequearEmpleado(_IdEmpleado)==-1){
        cout << "EMPLEADO NO EXISTENTE, LA VENTA NO SE REGISTRARA, INGRESE OTRO" << endl;
        cout << "ID EMPLEADO: ";
        cin >> _IdEmpleado;
    }
    cout << "ID CLIENTE: ";
    cin >> _idCliente;
    if(chequearCliente(_idCliente)==-2){
    }
    cout << "ID COLCHON: ";
    cin >> _idColchon;
    while(chequearColchon(_idColchon)==-1){
        cout << "ID COLCHON NO EXISTENTE, INGRESE OTRO" << endl;
        cout << "ID COLCHON: ";
        cin >> _idColchon;
    }
    if(verificarStock(_idColchon)==-2){
        cout << "COLCHON SIN STOCK" << endl;
        return;
    }
    devolverStock(_idColchon);
    cout << "CANTIDAD: ";
    cin >> _cantidad;
    while(chequearCantidadColchon(_idColchon,_cantidad)!=-1){
        cout << "CANTIDAD: ";
        cin >> _cantidad;
    }
    this->setImporte(calcularImporte(_idColchon,_cantidad));
    cout << "FORMA DE PAGO (EFECIVO O TARJETA): ";
    cin >> _formaPago;
}

void Venta::seguirCargando(){
    cout << "ID COLCHON: ";
    cin >> _idColchon;
    while(chequearColchon(_idColchon)==-1){
        cout << "ID COLCHON NO EXISTENTE, INGRESE OTRO" << endl;
        cout << "ID COLCHON: ";
        cin >> _idColchon;
    }
    if(verificarStock(_idColchon)==-2){
        return;
    }
    devolverStock(_idColchon);
    cout << "CANTIDAD: ";
    cin >> _cantidad;
    while(chequearCantidadColchon(_idColchon,_cantidad)!=-1){
        cout << "CANTIDAD: ";
        cin >> _cantidad;
    }
    this->setImporte(calcularImporte(_idColchon,_cantidad));
}

void Venta::Mostrar(){
    cout << "ID FACTURA: " << _idFactura << endl;
    cout << "ID EMPLEADO: " << _IdEmpleado << endl;
    cout << "ID CLIENTE: " << _idCliente << endl;
    cout << "ID COLCHON: " << _idColchon << endl;
    cout << "CANTIDAD: " << _cantidad << endl;
    cout << "IMPORTE: " << _importe << endl;
    cout << "FECHA FACTURA: ";
    _fecha.Mostrar();
    cout << endl;
    cout << "FORMA DE PAGO: " << _formaPago << endl;
}

bool Venta::grabarEnDisco(){
    FILE *p;
    p = fopen("ventas.dat", "ab");
    if (p == NULL) {
        cout << "NO SE PUDO ABRIR EL ARCHIVO" << endl;
        return false;
    }
    bool leyo = fwrite(this, sizeof(Venta), 1, p);
    fclose(p);
    return leyo;
}

bool Venta::leerDeDisco(int pos){
    FILE *p;
    p = fopen("ventas.dat", "rb");
    if (p== NULL) {
        cout<< "NO SE PUDO ABRIR EL ARCHIVO" << endl;
        return false;
    }
    fseek(p, pos * sizeof(Venta), 0);
    bool leyo = fread(this, sizeof(Venta), 1, p);
    fclose(p);
    return leyo;
}

int verificarStock(int idColchon){
    Colchon obj;
    int pos=0;
    while(obj.leerDeDisco(pos++)){
        if(idColchon==obj.getIdColchon()){
            if(obj.getStock()==0){
                return -2;
            }else{
                return pos;
            }
        }
    }
    return -1;
}

int devolverStock(int idColchon){
    Colchon obj;
    int pos=0;
    while(obj.leerDeDisco(pos++)){
        if(idColchon==obj.getIdColchon()){
            cout << "STOCK DISPONIBLE: " << obj.getStock() << endl;
            return pos;
        }
    }
    return -1;
}

float calcularImporte(int id, int cant){
    Colchon obj;
    int pos=0;
    float importe;
    while(obj.leerDeDisco(pos++)){
        if(obj.getIdColchon()==id){
            importe=cant*obj.getPrecio();
        }
    }
    return importe;
}

int chequearColchon(int id){
    Colchon obj;
    int pos=0;
    while(obj.leerDeDisco(pos++)){
        if(obj.getIdColchon()==id){
            return pos;
        }
    }
    return -1;
}

int chequearCantidadColchon(int id, int cant){
    Colchon obj;
    int pos=0;
    while(obj.leerDeDisco(pos)){
        if(obj.getIdColchon()==id){
            if(cant>obj.getStock()){
                cout << "CANTIDAD NO PERMITIDA" << endl;
                return pos;
            }else{
                obj.setStock(obj.getStock()-cant);
                obj.modificarEnDisco(pos);
                return -1;
            }
        }
        pos++;
    }
    return -1;
}

int chequearEmpleado(int id){
    Empleado obj;
    int pos=0;
    while(obj.leerDeDisco(pos++)){
        if(obj.getIdEmpleado()==id){
            return pos;
        }
    }
    return -1;
}
int chequearCliente(int id){
    Clientes obj;
    Usuario aux;
    int pos=0;
    bool chequeo=false;
    while(obj.leerDeDisco(pos++)){
        if(obj.getIdCliente()==id){
            return pos;
            chequeo=true;
        }
    }
    int _dniCliente;
	float _saldoCuenta;
	char _email[30];
	char _telefono[30];
	char nombre[30];
	char apellido[30];
	char registro;
    if(chequeo==false){
        cout << "ID DE CLIENTE NO REGISTRADO, DESEAS REGISTRARLO?" << endl;
        cout << "INGRESE S/N: ";
        cin >> registro;
        cout << endl;
        if(registro=='S' || registro=='s'){
            cout << "INGRESE DNI: ";
            cin >> _dniCliente;
            cout << "INGRESE NOMBRE: ";
            cin >> nombre;
            cout << "INGRESE APELLIDO: ";
            cin >> apellido;
            cout << "INGRESE SALDO: ";
            cin >> _saldoCuenta;
            cout << "INGRESE EMAIL: ";
            cin >> _email;
            cout << "INGRESE TELEFONO: ";
            cin >> _telefono;
            obj.setIdCliente(id);
            obj.setDniCliente(_dniCliente);
            obj.setSaldoCuenta(_saldoCuenta);
            obj.setEmail(_email);
            obj.setTelfono(_telefono);
            obj.grabarEnDisco();
            aux.setDniUsuario(_dniCliente);
            aux.setNombreUsuario(nombre);
            aux.setApellidoUsuario(apellido);
            aux.setEstadoUsuario(true);
            aux.grabarEnDisco();
            cout << "CLIENTE REGISTRADO CON EXITO" << endl;
            cout << "USUARIO REGISTRADO CON EXITO" << endl;
            cout << endl;
        }else{
            cout << "CLIENTE NO REGISTRADO" << endl;
            return -2;
        }
    }
    return -1;
}

void cargarVenta(){
    Venta obj;
    DetalleVenta reg;
    int cantTotal=0;
    float importeTotal=0;
    bool seguir=true;
    char continuar;
    obj.Cargar();
    if(chequearEmpleado(obj.getIdEmpleado())==-1 && chequearCliente(obj.getIdCliente())==-2){
        cout << "NO SE PUDO CARGAR LA VENTA" << endl;
    }
    if(verificarStock(obj.getIdColchon())!=-2){
        obj.grabarEnDisco();
        cantTotal+=obj.getCantidad();
        importeTotal+=obj.getImporte();
    }
    cout << endl;
    cout << "DESEA SEGUIR COMPRANDO?" << endl;
    cout << "INGRESE S/N: ";
    cin >> continuar;
    continuar= tolower(continuar);
    if(continuar=='n'){
        seguir=false;
    }
    while(seguir==true){
        obj.setIdFactura(obj.getIdFactura());
        obj.setIdCliente(obj.getIdCliente());
        obj.setIdEmpleado(obj.getIdEmpleado());
        obj.setFecha(obj.getFecha());
        obj.setFormaPago(obj.getFormaPago());
        obj.seguirCargando();
        if(verificarStock(obj.getIdColchon())!=-2){
            obj.grabarEnDisco();
            cantTotal+=obj.getCantidad();
            importeTotal+=obj.getImporte();
        }
        cout << endl;
        cout << "DESEA SEGUIR COMPRANDO?" << endl;
        cout << "INGRESE S/N: ";
        cin >> continuar;
        continuar= tolower(continuar);
        if(continuar=='n'){
            seguir=false;
        }
    }
    reg.setIDfactura(obj.getIdFactura());
    reg.setIDcliente(obj.getIdCliente());
    reg.setIDempleado(obj.getIdEmpleado());
    reg.setfecha(obj.getFecha());
    reg.setCantidad(cantTotal);
    reg.setImporte(importeTotal);
    if(importeTotal!=0){
        reg.grabarDisco();
    }
    cout << "COMPRA REALIZADA CON EXITO, APRETE ENTER PARA VER EL DETALLE" << endl;
    system("pause>null");
    system("cls");
    detalleVenta(obj.getIdFactura(),obj.getIdCliente());
}

void listarVentas(){
    Venta obj;
    int pos=0;
    while(obj.leerDeDisco(pos++)){
        obj.Mostrar();
        cout << endl;
    }
}

void detalleVenta(int idFactura, int idCliente){
    Venta obj;
    int idEmpleado;
    ///el id se puede buscar por el dni
    char formaPago;
    float importeTotal=0, importeColchon, precioColchon;
    Fecha fechaVenta;
    int *v;
    Colchon reg;
    bool encontro=false;
    int cantReg=reg.contarColchones();
    v=new int[cantReg];
    if(v==NULL){
        return;
    }
    for(int i=0; i<cantReg; i++){
        v[i]=0;
    }
    int pos=0;
    while(obj.leerDeDisco(pos++)){
        if(obj.getIdFactura()==idFactura && obj.getIdCliente()==idCliente){
            idEmpleado=obj.getIdEmpleado();
            formaPago=obj.getFormaPago();
            fechaVenta=obj.getFecha();
            importeTotal+=obj.getImporte();
            v[obj.getIdColchon()-1]+=obj.getCantidad();
            encontro=true;
        }
    }
    pos=0;
    if(encontro==true){
        cout << "DETALLE VENTA" << endl;
        cout << "------------------" << endl;
        cout << "ID FACTURA: " << idFactura << endl;
        cout << "ID CLIENTE: " << idCliente << endl;
        cout << "ID EMPLEADO: " << idEmpleado << endl;
        cout << "FORMA PAGO: " << formaPago << endl;
        cout << "----------------------------------" << endl;
        cout << left;
        cout << setw(8) << "ID COL";
        cout << setw(8) << "PRECIO";
        cout << setw(10) << "CANTIDAD";
        cout << setw(9) << "IMPORTE" << endl;
        cout << "----------------------------------" << endl;
        for(int i=0; i<cantReg; i++){
            pos=0;
            while(reg.leerDeDisco(pos++)){
                if(reg.getIdColchon()==i+1){
                    importeColchon=reg.getPrecio()*v[i];
                    precioColchon=reg.getPrecio();
                }
            }
            if(v[i]>0){
                cout << left;
                cout << setw(8) << i+1;
                cout << setw(8) << precioColchon;
                cout << setw(10) << v[i];
                cout << setw(9) << importeColchon;
                cout << endl;
            }
        }
        cout << "----------------------------------" << endl;
        cout << "IMP. TOTAL: " << importeTotal << endl;
        cout << "------------------" << endl;
        cout << "FECHA: ";
        fechaVenta.Mostrar();
    }
}

void buscarDetalleVenta(){
    Venta obj;
    char formaPago;
    int idFactura, idCliente, idVendedor;
    float importeTotal=0, importeColchon, precioColchon;
    Fecha fechaVenta;
    int *v;
    Colchon reg;
    bool encontro=false;
    int cantReg=reg.contarColchones();
    v=new int[cantReg];
    if(v==NULL){
        return;
    }
    for(int i=0; i<cantReg; i++){
        v[i]=0;
    }
    int pos=0;
    cout << "INGRESAR ID FACTURA: ";
    cin >> idFactura;
    cout << "INGRESAR ID CLIENTE: ";
    cin >> idCliente;
    cout << endl;
    while(obj.leerDeDisco(pos++)){
        if(obj.getIdFactura()==idFactura && obj.getIdCliente()==idCliente){
            idVendedor=obj.getIdEmpleado();
            formaPago=obj.getFormaPago();
            fechaVenta=obj.getFecha();
            importeTotal+=obj.getImporte();
            v[obj.getIdColchon()-1]+=obj.getCantidad();
            encontro=true;
        }
    }
    pos=0;
    if(encontro==true){
        cout << "DETALLE VENTA" << endl;
        cout << "------------------" << endl;
        cout << "ID FACTURA: " << idFactura << endl;
        cout << "ID CLIENTE: " << idCliente << endl;
        cout << "ID VENDEDOR: " << idVendedor << endl;
        cout << "FORMA PAGO: " << formaPago << endl;
        cout << "----------------------------------" << endl;
        cout << left;
        cout << setw(8) << "ID COL";
        cout << setw(8) << "PRECIO";
        cout << setw(10) << "CANTIDAD";
        cout << setw(9) << "IMPORTE" << endl;
        cout << "----------------------------------" << endl;
        for(int i=0; i<cantReg; i++){
            pos=0;
            while(reg.leerDeDisco(pos++)){
                if(reg.getIdColchon()==i+1){
                    importeColchon=reg.getPrecio()*v[i];
                    precioColchon=reg.getPrecio();
                }
            }
            if(v[i]>0){
                cout << left;
                cout << setw(8) << i+1;
                cout << setw(8) << precioColchon;
                cout << setw(10) << v[i];
                cout << setw(9) << importeColchon;
                cout << endl;
            }
        }
        cout << "----------------------------------" << endl;
        cout << "IMP. TOTAL: " << importeTotal << endl;
        cout << "------------------" << endl;
        cout << "FECHA: ";
        fechaVenta.Mostrar();
    }else{
        cout << "NO SE ENCONTRO NINGUN ID DE FACTURA Y/O ID DE CLIENTE" << endl;
    }
}

int menuVentas(){
    int opc;
    while(true){
        cout << "MENU VENTAS" << endl;
        cout << "---------------------------" << endl;
        cout << "1- INGRESAR VENTA" << endl;
        cout << "2- LISTAR VENTAS" << endl;
        cout << "3- DETALLE VENTA" << endl;
        cout << "0- VOLVER AL MENU PRINCIPAL" << endl;
        cout << "---------------------------" << endl;
        cout << "INGRESAR OPCION: ";
        cin >> opc;
        system("cls");
        switch(opc){
            case 1: cargarVenta();
                break;
            case 2: listarVentas();
                break;
            case 3: buscarDetalleVenta();
                break;
            case 0: return 0;
                break;
        }
        system("pause>null");
        system("cls");
    }
    return 0;
}
