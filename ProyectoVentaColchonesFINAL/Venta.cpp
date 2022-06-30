#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <algorithm>

using namespace std;

#include "Venta.h"
#include "Empleado.h"
#include "Clientes.h"
#include "DetalleVenta.h"

int fechaHoy(Fecha);
int chequearEmpleado(int);
int chequearCliente(int);
int chequearColchon(int);
int chequearCantidadColchon(int, int);
float calcularImporte(int, int);
int devolverStock(int);
int verificarStock(int);
void detalleVenta(int, int);
float devolverPrecio(int);

string tolowerString(string data) {
    transform(data.begin(), data.end(), data.begin(), ::tolower);
    return data;
}

void Venta::Cargar(){
    cout << "ID FACTURA: " << contarVenta() << endl;
    setIdFactura(contarVenta());
    cout << "FECHA FACTURA" << endl;
    _fecha.Cargar();
    cout << "ID EMPLEADO: ";
    cin >> _IdEmpleado;
    if(_IdEmpleado==0){
        return;
    }
    while(chequearEmpleado(_IdEmpleado)==-1){
        cout << "EMPLEADO NO EXISTENTE, LA VENTA NO SE REGISTRARA, INGRESE OTRO O INGRESE CERO PARA SALIR" << endl;
        cout << "ID EMPLEADO: ";
        cin >> _IdEmpleado;
        if(_IdEmpleado==0){
            return;
        }
    }
    cout << "ID CLIENTE: ";
    cin >> _idCliente;
    if(chequearCliente(_idCliente)==-2){
        return;
    }
    cout << "ID COLCHON: ";
    cin >> _idColchon;
    while(chequearColchon(_idColchon)==-1){
        cout << "ID COLCHON NO EXISTENTE, INGRESE OTRO" << endl;
        cout << "ID COLCHON: ";
        cin >> _idColchon;
    }
    setPrecio(devolverPrecio(_idColchon));
    string continuar;
    while(verificarStock(_idColchon)==-2){
        cout << "COLCHON SIN STOCK, DESEA COMPRAR OTRO? ";
        cin >> continuar;
        tolowerString(continuar);
        while(continuar!="s" || continuar!="n"){
            cout << "OPCION NO PERMITIDA (INGRESE S/N): ";
            cin >> continuar;
        }
        if(continuar=="n"){
            return;
        }
        if(continuar=="s"){
            cout << "ID COLCHON: ";
            cin >> _idColchon;
            _cantidad=0;
        }
    }
    devolverStock(_idColchon);
    cout << "CANTIDAD: ";
    cin >> _cantidad;
    while(chequearCantidadColchon(_idColchon,_cantidad)!=-1){
        cout << "CANTIDAD: ";
        cin >> _cantidad;
    }
    this->setImporte(calcularImporte(_idColchon,_cantidad));
    cout << "FORMA DE PAGO (INGRESE E PARA EFECTIVO O T PARA TARJETA): ";
    cin >> _formaPago;
}

int Venta::seguirCargando(){
    cout << "ID COLCHON: ";
    cin >> _idColchon;
    while(chequearColchon(_idColchon)==-1){
        cout << "ID COLCHON NO EXISTENTE, INGRESE OTRO" << endl;
        cout << "ID COLCHON: ";
        cin >> _idColchon;
    }
    setPrecio(devolverPrecio(_idColchon));
    string continuar;
    while(verificarStock(_idColchon)==-2){
        cout << "COLCHON SIN STOCK, DESEA COMPRAR OTRO? (INGRESE S/N)";
        cin >> continuar;
        tolowerString(continuar);
        while(continuar!="s" || continuar!="n"){
            cout << "OPCION NO PERMITIDA (INGRESE S/N): ";
            cin >> continuar;
        }
        if(continuar=="n"){
            return -1;
        }
        if(continuar=="s"){
            cout << "ID COLCHON: ";
            cin >> _idColchon;
        }
    }
    devolverStock(_idColchon);
    cout << "CANTIDAD: ";
    cin >> _cantidad;
    while(chequearCantidadColchon(_idColchon,_cantidad)!=-1){
        cout << "CANTIDAD: ";
        cin >> _cantidad;
    }
    this->setImporte(calcularImporte(_idColchon,_cantidad));
    return 0;
}

void Venta::Mostrar(){
    cout << setw(6) << _idFactura << "|| ";
    cout << setw(7) << _IdEmpleado << "|| ";
    cout << setw(6) << _idCliente << "|| ";
    cout << setw(7) << _idColchon << "|| ";
    cout << setw(5) << _cantidad << "|| ";
    cout << setw(8) << _importe << "|| ";
    cout << setw(2) << _fecha.getDia() << "/";
    cout << setw(2) << _fecha.getMes() << "/";
    cout << setw(6) << _fecha.getAnio() << "|| ";
    cout << setw(4) << _formaPago;
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

float devolverPrecio(int idCol){
    Colchon obj;
    int pos=0;
    while(obj.leerDeDisco(pos++)){
        if(obj.getIdColchon()==idCol){
            return obj.getPrecio();
        }
    }
    return -1;
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
            if(cant>obj.getStock() || cant<0){
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
    int pos=0;
    bool chequeo=false;
    while(obj.leerDeDisco(pos++)){
        if(obj.getIdCliente()==id){
            return pos;
            chequeo=true;
        }
    }
    int _dniCliente;
	char _email[30];
	char _telefono[30];
	char nombre[30], apellido[30];
	char registro;
    if(chequeo==false){
        cout << "ID DE CLIENTE NO REGISTRADO, DESEAS REGISTRARLO?" << endl;
        cout << "INGRESE S/N: ";
        cin >> registro;
        cout << endl;
        if(registro=='S' || registro=='s'){
            cout << "ID CLIENTE: " << id << endl;
            cout << "INGRESE DNI: ";
            cin >> _dniCliente;
            cout << "INGRESAR NOMBRE: ";
            cin >> nombre;
            cout << "INGRESAR APELLIDO: ";
            cin >> apellido;
            cout << "INGRESE EMAIL: ";
            cin >> _email;
            cout << "INGRESE TELEFONO: ";
            cin >> _telefono;
            obj.setIdCliente(id);
            obj.setDniCliente(_dniCliente);
            obj.setNombreCliente(nombre);
            obj.setApellidoCliente(apellido);
            obj.setEmail(_email);
            obj.setTelfono(_telefono);
            obj.setEstado(true);
            obj.grabarEnDisco();
            cout << "CLIENTE REGISTRADO CON EXITO" << endl;
            cout << endl;
        }else{
            return -2;
        }
    }
    return -1;
}

void restaurarStock(int idColchon, int cant){
    Colchon obj;
    int pos=0;
    while(obj.leerDeDisco(pos)){
        if(obj.getIdColchon()==idColchon){
            obj.setStock(obj.getStock()+cant);
            obj.modificarEnDisco(pos);
            return;
        }
        pos++;
    }
    return;
}

void cargarVenta(){
    Venta obj;
    DetalleVenta reg;
    int cantTotal=0;
    float importeTotal=0;
    bool seguir=true;
    char continuar;
    obj.Cargar();
    if(chequearEmpleado(obj.getIdEmpleado())==-1){
        cout << "NO SE PUDO CARGAR LA VENTA" << endl;
        return;
    }
    if(obj.getCantidad()!=0){
        obj.grabarEnDisco();
        cantTotal+=obj.getCantidad();
        importeTotal+=obj.getImporte();
    }else{
        cout << "NO SE CARGO LA VENTA" << endl;
        restaurarStock(obj.getIdColchon(),obj.getCantidad());
        return;
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
        if(obj.seguirCargando()!=-1){
            if(obj.getCantidad()!=0){
                obj.grabarEnDisco();
                cantTotal+=obj.getCantidad();
                importeTotal+=obj.getImporte();
            }
        }else{
            cout << "COMPRA REALIZADA CON EXITO, APRETE ENTER PARA VER EL DETALLE" << endl;
            system("pause>null");
            system("cls");
            reg.setIDfactura(obj.getIdFactura());
            reg.setIDcliente(obj.getIdCliente());
            reg.setIDempleado(obj.getIdEmpleado());
            reg.setfecha(obj.getFecha());
            reg.setCantidad(cantTotal);
            reg.setImporte(importeTotal);
            if(importeTotal!=0){
                reg.grabarDisco();
            }
            detalleVenta(obj.getIdFactura(),obj.getIdCliente());
            return;
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
    cout << left;
    cout << setw(6) << "ID FC" << "|| ";
    cout << setw(7) << "ID EMP" << "|| ";
    cout << setw(6) << "ID CL" << "|| ";
    cout << setw(7) << "ID COL" << "|| ";
    cout << setw(5) << "CANT" << "|| ";
    cout << setw(8) << "IMPORTE" << "|| ";
    cout << setw(12) << "FECHA VENTA" << "|| ";
    cout << setw(4) << "FP" << endl;
    cout << "===========================================================================" << endl;
    while(obj.leerDeDisco(pos++)){
        obj.Mostrar();
        cout << endl;
    }
}

void detalleVenta(int idFactura, int idCliente){
    Venta obj;
    int idEmpleado;
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
        if(obj.getIdFactura()==idFactura){
            idCliente=obj.getIdCliente();
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
    delete v;
}

void recaudacionPorColchon(){
    Colchon obj;
    int *vCol;
    Venta reg;
    int anio;
    int posVen=0;
    int cantReg = obj.contarColchones()-1;
    vCol=new int[cantReg];
    if(vCol==NULL){
        return;
    }
    for(int i=0; i<cantReg; i++){
        vCol[i]=0;
    }
    cout << "INGRESAR ANIO: ";
    cin >> anio;
    cout << endl;
    while(reg.leerDeDisco(posVen++)){
        if(reg.getFecha().getAnio()==anio){
            vCol[reg.getIdColchon()-1]+=reg.getImporte();
        }
    }
    cout << "RECAUDACION POR COLCHON DEL ANIO " << anio << endl;
    cout << endl;
    cout << left;
    cout << setw(7) << "ID COL";
    cout << setw(4) << "||";
    cout << setw(11) << "IMP. TOTAL" << endl;
    cout << "-----------------------" << endl;
    for(int i=0; i<cantReg; i++){
        cout << setw(7) << i+1;
        cout << setw(4) << "||";
        cout << setw(11) << vCol[i] << endl;
    }
    delete vCol;
}

void recaudacionPorCliente(){
    Clientes obj;
    int *vCli, *vId;
    Venta reg;
    int anio;
    int posVen=0;
    int cantReg = obj.contarClientes()-1;
    vCli=new int[cantReg];
    if(vCli==NULL){
        return;
    }
    vId=new int[cantReg];
    if(vId==NULL){
        return;
    }
    for(int i=0; i<cantReg; i++){
        obj.leerDeDisco(i);
        vCli[i]=0;
        vId[i]=obj.getIdCliente();
    }
    cout << "INGRESAR ANIO: ";
    cin >> anio;
    cout << endl;
    while(reg.leerDeDisco(posVen++)){
        if(reg.getFecha().getAnio()==anio){
            for(int i=0; i<cantReg; i++){
                obj.leerDeDisco(i);
                if(reg.getIdCliente()==obj.getIdCliente()){
                    vCli[i]+=reg.getImporte();
                }
            }
        }
    }
    cout << "RECAUDACION POR CLIENTE DEL ANIO " << anio << endl;
    cout << endl;
    cout << left;
    cout << setw(7) << "ID CLI";
    cout << setw(4) << "||";
    cout << setw(11) << "IMP. TOTAL" << endl;
    cout << "-----------------------" << endl;
    for(int i=0; i<cantReg; i++){
        cout << setw(7) << vId[i];
        cout << setw(4) << "||";
        cout << setw(11) << vCli[i] << endl;
    }
    delete vId;
    delete vCli;
}

void cantVentasEmpleado(){
    Empleado obj;
    DetalleVenta reg;
    int *vEmp;
    int *vIdEmp;
    int posVen=0;
    int cantReg = obj.contarEmpleados()-1;
    vEmp=new int[cantReg];
    if(vEmp==NULL){
        return;
    }
    vIdEmp=new int[cantReg];
    if(vIdEmp==NULL){
        return;
    }
    for(int i=0; i<cantReg; i++){
        obj.leerDeDisco(i);
        vEmp[i]=0;
        vIdEmp[i]=obj.getIdEmpleado();
    }
    while(reg.leerDisco(posVen++)){
        for(int i=0; i<cantReg; i++){
            if(vIdEmp[i]==reg.getIDEmpleado()){
                vEmp[i]++;
            }
        }
    }
    cout << left;
    cout << setw(8) << "ID EMP";
    cout << setw(4) << "||";
    cout << setw(13) << "CANT VENTAS" << endl;
    cout << "-------------------------" << endl;
    for(int i=0; i<cantReg; i++){
        cout << setw(8) << vIdEmp[i];
        cout << setw(4) << "||";
        cout << setw(13) << vEmp[i] << endl;
    }
    delete vIdEmp;
    delete vEmp;
}

void empleadoMasVentas(){
    Empleado obj;
    DetalleVenta reg;
    int *vEmp;
    int *vIdEmp;
    int posVen=0;
    int cantReg = obj.contarEmpleados()-1;
    vEmp=new int[cantReg];
    if(vEmp==NULL){
        return;
    }
    vIdEmp=new int[cantReg];
    if(vIdEmp==NULL){
        return;
    }
    for(int i=0; i<cantReg; i++){
        obj.leerDeDisco(i);
        vEmp[i]=0;
        vIdEmp[i]=obj.getIdEmpleado();
    }
    while(reg.leerDisco(posVen++)){
        vEmp[reg.getIDEmpleado()-1]++;
    }
    int masVentas=vEmp[0];
    for(int i=1; i<cantReg; i++){
        if(vEmp[i]>masVentas){
            masVentas=vEmp[i];
        }
    }
    cout << "EMPLEADO CON MAS VENTAS" << endl;
    cout << "------------------------" << endl;
    cout << left;
    cout << setw(8) << "ID EMP";
    cout << setw(4) << "||";
    cout << setw(13) << "CANT VENTAS" << endl;
    cout << "------------------------" << endl;
    for(int i=0; i<cantReg; i++){
        if(vEmp[i]==masVentas){
            cout << setw(8) << vIdEmp[i];
            cout << setw(4) << "||";
            cout << setw(13) << vEmp[i] << endl;
        }
    }
    delete vIdEmp;
    delete vEmp;
}

void mesMayorFacturacion(){
    DetalleVenta obj;
    int vMes[12]={0};
    int pos=0;
    while(obj.leerDisco(pos++)){
        vMes[obj.getFecha().getMes()-1]+=obj.getImporte();
    }
    int mayorMes=vMes[0];
    for(int i=1; i<12; i++){
        if(vMes[i]>mayorMes){
            mayorMes=vMes[i];
        }
    }
    cout << "MES CON MAS FACTURACION" << endl;
    cout << "------------------------" << endl;
    cout << left;
    cout << setw(5) << "MES";
    cout << setw(4) << "||";
    cout << setw(13) << "FACTURACION" << endl;
    cout << "------------------------" << endl;
    for(int i=0; i<12; i++){
        if(vMes[i]==mayorMes){
            cout << setw(5) << i+1;
            cout << setw(4) << "||";
            cout << setw(13) << vMes[i] << endl;
        }
    }
}

void recaudacionPorAnioIngresado(){
    DetalleVenta obj;
    int anio, pos=0;
    int vMes[12]={0};
    cout << "INGRESE AÑO: ";
    cin >> anio;
    cout << endl;
    while(obj.leerDisco(pos++)){
        if(obj.getFecha().getAnio()==anio){
            vMes[obj.getFecha().getMes()-1]+=obj.getImporte();
        }
    }
    cout << "FACTURACION DEL AÑO " << anio << endl << endl;
    cout << left;
    cout << setw(7) << "MES";
    cout << setw(13) << "RECAUDACION" << endl;
    cout << "====================" << endl;
    for(int i=0; i<12; i++){
        cout << setw(7) << i+1;
        cout << setw(13) << vMes[i] << endl;
    }
}

int anioActual(){
    int e;
    time_t rawtime;
    struct tm * timeinfo;
    time (&rawtime);
    timeinfo = localtime (&rawtime);
    e=(timeinfo->tm_year+1900);
    return e;
}

void recaudacionPorSemestreAnioActual(){
    DetalleVenta obj;
    int pos=0;
    int vSemestre[2]={0};
    while(obj.leerDisco(pos++)){
        if(obj.getFecha().getAnio()==anioActual()){
            if(obj.getFecha().getMes()<7 && obj.getFecha().getMes()>0){
                vSemestre[0]+=obj.getImporte();
            }
            if(obj.getFecha().getMes()>6 && obj.getFecha().getMes()<=12){
                vSemestre[1]+=obj.getImporte();
            }
        }
    }
    cout << "FACTURACION POR SEMESTRE DEL AÑO ACTUAL " << endl << endl;
    cout << left;
    cout << setw(10) << "SEMESTRE";
    cout << setw(13) << "RECAUDACION" << endl;
    cout << "=======================" << endl;
    for(int i=0; i<2; i++){
        cout << setw(10) << i+1;
        cout << setw(13) << vSemestre[i] << endl;
    }
}

void recaudacionPorFechaIngresada(){
    DetalleVenta obj;
    int pos=0, recaudacionTotal=0;
    Fecha aux;
    aux.Cargar();
    cout << endl;
    while(obj.leerDisco(pos++)){
        if(obj.getFecha().getAnio()==aux.getAnio()){
            if(obj.getFecha().getMes()==aux.getMes()){
                if(obj.getFecha().getDia()==aux.getDia()){
                    recaudacionTotal+=obj.getImporte();
                }
            }
        }
    }
    cout << "FACTURACION DE LA FECHA: ";
    aux.Mostrar();
    cout << endl << endl;
    cout << left;
    cout << "RECAUDACION" << endl;
    cout << "============" << endl;
    cout << recaudacionTotal << endl;
}

void recaudacionPorRangoAnio(){
    DetalleVenta obj;
    int pos=0, anio, rango;
    int *vAnio;
    cout << "INGRESAR ANIO: ";
    cin >> anio;
    cout << endl;
    rango=anioActual()-anio+1;
    vAnio=new int[rango];
    if(vAnio==NULL){
        return;
    }
    for(int i=0; i<rango; i++){
        vAnio[i]=0;
    }
    while(obj.leerDisco(pos++)){
        if(obj.getFecha().getAnio()>=anio && obj.getFecha().getAnio()<=anioActual()){
            vAnio[obj.getFecha().getAnio()-anio]+=obj.getImporte();
        }
    }
    cout << "RECAUDACION ENTRE " << anio << " Y " << anioActual() << endl << endl;
    cout << left;
    cout << setw(7) << "ANIO";
    cout << setw(13) << "RECAUDACION" << endl;
    cout << "===================" << endl;
    for(int i=0; i<rango; i++){
        cout << setw(7) << i+anio;
        cout << setw(13) << vAnio[i] << endl;
    }
    delete vAnio;
}

void cantColchonVendidoPorMedida(){
    Venta obj;
    Colchon reg;
    Medida aux;
    int posVen=0, posCol=0;
    int *vMed, *vId;
    int cantReg=aux.contarMedidas()-1;
    vMed=new int[cantReg];
    if(vMed==NULL){
        return;
    }
    vId=new int[cantReg];
    if(vId==NULL){
        return;
    }
    for(int i=0; i<cantReg; i++){
        aux.leerDeDisco(i);
        vMed[i]=0;
        vId[i]=aux.getIdMedida();
    }
    while(obj.leerDeDisco(posVen++)){
        posCol=0;
        while(reg.leerDeDisco(posCol++)){
            if(obj.getIdColchon()==reg.getIdColchon()){
                vMed[reg.getMedida()-1]+=obj.getCantidad();
            }
        }
    }
    cout << left;
    cout << setw(7) << "ID MED";
    cout << setw(4) << "||";
    cout << setw(7) << "CANTIDAD" << endl;
    cout << "===================" << endl;
    for(int i=0; i<cantReg; i++){
        cout << setw(7) << vId[i];
        cout << setw(4) << "||";
        cout << setw(7) << vMed[i] << endl;
    }
    delete vId;
    delete vMed;
}

void cantColchonVendidoPorModelo(){
    Venta obj;
    Colchon reg;
    Modelo aux;
    int posVen=0, posCol=0;
    int *vMod, *vId;
    int cantReg=aux.contarModelos()-1;
    vMod=new int[cantReg];
    if(vMod==NULL){
        return;
    }
    vId=new int[cantReg];
    if(vId==NULL){
        return;
    }
    for(int i=0; i<cantReg; i++){
        aux.leerDeDisco(i);
        vMod[i]=0;
        vId[i]=aux.getIdModelo();
    }
    while(obj.leerDeDisco(posVen++)){
        posCol=0;
        while(reg.leerDeDisco(posCol++)){
            if(obj.getIdColchon()==reg.getIdColchon()){
                vMod[reg.getModeloColchon()-1]+=obj.getCantidad();
            }
        }
    }
    cout << left;
    cout << setw(10) << "MODELO";
    cout << setw(4) << "||";
    cout << setw(7) << "CANTIDAD" << endl;
    cout << "===================" << endl;
    for(int i=0; i<cantReg; i++){
        for(int j=0; j<cantReg; j++){
            aux.leerDeDisco(j);
            if(vId[i]==aux.getIdModelo()){
                cout << setw(10) << aux.getDescripcion();
            }
        }
        cout << setw(4) << "||";
        cout << setw(7) << vMod[i] << endl;
    }
    delete vId;
    delete vMod;
}

void buscarFacturaId() {
    Venta oVenta;
    int pos = 0;
    int id;
    bool encontro = false;
    cout << "INGRESAR ID A COMPARAR: ";
    cin >> id;
    system("cls");
    cout << left;
    cout << setw(6) << "ID FC" << "|| ";
    cout << setw(7) << "ID EMP" << "|| ";
    cout << setw(6) << "ID CL" << "|| ";
    cout << setw(7) << "ID COL" << "|| ";
    cout << setw(5) << "CANT" << "|| ";
    cout << setw(8) << "IMPORTE" << "|| ";
    cout << setw(12) << "FECHA VENTA" << "|| ";
    cout << setw(4) << "FP" << endl;
    cout << "===========================================================================" << endl;
    while (oVenta.leerDeDisco(pos++)) {
        if (id == oVenta.getIdFactura()) {
            oVenta.Mostrar();
            cout << endl;
            encontro = true;
        }
    }
    if (encontro == false) {
        cout << "NO SE ENCONTRO FACTURA CON ESE ID" << endl;
        return;
    }
}

void buscarFacturaClienteID() {
    Venta oVenta;
    int pos = 0;
    int id;
    bool encontro = false;
    cout << "INGRESAR ID A COMPARAR: ";
    cin >> id;
    system("cls");
    cout << left;
    cout << setw(6) << "ID FC" << "|| ";
    cout << setw(7) << "ID EMP" << "|| ";
    cout << setw(6) << "ID CL" << "|| ";
    cout << setw(7) << "ID COL" << "|| ";
    cout << setw(5) << "CANT" << "|| ";
    cout << setw(8) << "IMPORTE" << "|| ";
    cout << setw(12) << "FECHA VENTA" << "|| ";
    cout << setw(4) << "FP" << endl;
    cout << "===========================================================================" << endl;
    while (oVenta.leerDeDisco(pos++)) {
        if (id == oVenta.getIdCliente()) {
            oVenta.Mostrar();
            cout << endl;
            encontro = true;
        }
    }
    if (encontro == false) {
        cout << "NO SE ENCONTRARON FACTURAS CON ESE CLIENTE ID" << endl;
        return;
       }
}

void buscarFacturaPorColchonID() {
    Venta oVenta;
    int pos = 0;
    int id;
    bool encontro = false;
    cout << "INGRESAR ID A COMPARAR: ";
    cin >> id;
    system("cls");
    cout << left;
    cout << setw(6) << "ID FC" << "|| ";
    cout << setw(7) << "ID EMP" << "|| ";
    cout << setw(6) << "ID CL" << "|| ";
    cout << setw(7) << "ID COL" << "|| ";
    cout << setw(5) << "CANT" << "|| ";
    cout << setw(8) << "IMPORTE" << "|| ";
    cout << setw(12) << "FECHA VENTA" << "|| ";
    cout << setw(4) << "FP" << endl;
    cout << "===========================================================================" << endl;
    while (oVenta.leerDeDisco(pos++)) {
        if (id == oVenta.getIdColchon()) {
            oVenta.Mostrar();
            cout << endl;
            encontro = true;
        }
    }
    if (encontro == false) {
        cout << "NO SE ENCONTRARON FACTURAS CON ESE ID DE COLCHON" << endl;
        return;
    }
}

void buscarFacturaPorRangoFecha() {
    Venta oVenta;
    int pos = 0;
    Fecha fec1, fec2;
    bool encontro = false;
    cout << "FECHA INICIAL" << endl;
    fec1.Cargar();
    while (fechaHoy(fec1) == 0) {
        cout << "LA FECHA INICIAL NO PUEDE SER EL DIA ACTUAL, INGRESE OTRA" << endl;
        cout << "FECHA INICIAL" << endl;
        fec1.Cargar();
    }
    cout << "FECHA FINAL" << endl;
    fec2.Cargar();
    while(fec2.getAnio()<fec1.getAnio()){
        cout << "FECHA NO PERMITIDA, INGRESE OTRA" << endl;
        cout << "FECHA FINAL" << endl;
        fec2.Cargar();
    }
    if(fec2.getAnio()==fec1.getAnio()){
        while(fec2.getMes()<fec1.getMes()){
            cout << "FECHA NO PERMITIDA, INGRESE OTRA" << endl;
            cout << "FECHA FINAL" << endl;
            fec2.Cargar();
        }
    }
    while((fec2.getAnio()==fec1.getAnio() && fec2.getMes()==fec1.getMes()) && fec2.getDia()<=fec1.getDia()){
        cout << "FECHA NO PERMITIDA, INGRESE OTRA" << endl;
        cout << "FECHA FINAL" << endl;
        fec2.Cargar();
    }
    cout << endl;
    cout << left;
    cout << setw(6) << "ID FC" << "|| ";
    cout << setw(7) << "ID EMP" << "|| ";
    cout << setw(6) << "ID CL" << "|| ";
    cout << setw(7) << "ID COL" << "|| ";
    cout << setw(5) << "CANT" << "|| ";
    cout << setw(8) << "IMPORTE" << "|| ";
    cout << setw(12) << "FECHA VENTA" << "|| ";
    cout << setw(4) << "FP" << endl;
    cout << "===========================================================================" << endl;
    while(oVenta.leerDeDisco(pos)){
        if(oVenta.getFecha().getAnio()>fec1.getAnio() && oVenta.getFecha().getAnio()<fec2.getAnio()){
            oVenta.Mostrar();
            cout << endl;
            encontro = true;
        }
        if(oVenta.getFecha().getAnio()==fec1.getAnio() && oVenta.getFecha().getAnio()<=fec2.getAnio()){
            if(oVenta.getFecha().getMes()>fec1.getMes()){
                oVenta.Mostrar();
                cout << endl;
                encontro = true;
            }
        }
        if(oVenta.getFecha().getAnio()==fec1.getAnio() && oVenta.getFecha().getAnio()<=fec2.getAnio()){
            if(oVenta.getFecha().getMes()==fec1.getMes()){
                if(oVenta.getFecha().getDia()>=fec1.getDia()){
                    oVenta.Mostrar();
                    cout << endl;
                    encontro = true;
                }
            }
        }
        if(oVenta.getFecha().getAnio()>=fec1.getAnio() && oVenta.getFecha().getAnio()==fec2.getAnio()){
            if(oVenta.getFecha().getMes()<fec1.getMes()){
                oVenta.Mostrar();
                cout << endl;
                encontro = true;
            }
        }
        if(oVenta.getFecha().getAnio()>=fec1.getAnio() && oVenta.getFecha().getAnio()==fec2.getAnio()){
            if(oVenta.getFecha().getMes()==fec1.getMes()){
                if(oVenta.getFecha().getDia()<=fec1.getDia()){
                    oVenta.Mostrar();
                    cout << endl;
                    encontro = true;
                }
            }
        }
        pos++;
    }
    if(encontro == false){
        cout << "NO SE ENCONTRARON FACTURAS ENTRE ESAS FECHAS" << endl;
        return;
    }
}

void buscarFacturaCantidadTotal() {
    Venta oVenta;
    int pos = 0;
    int cantidadInicial, cantidadFinal;
    bool encontro = false;
    cout << "INGRESAR PRIMER CANTIDAD: ";
    cin >> cantidadInicial;
    while(cantidadInicial<0){
        cout << "CANTIDAD NO VALIDA, INGRESE OTRA" << endl;
        cout << "INGRESAR PRIMER CANTIDAD: ";
        cin >> cantidadInicial;
    }
    cout << "INGRESAR SEGUNDA CANTIDAD: ";
    cin >> cantidadFinal;
    while(cantidadFinal<=cantidadInicial || cantidadFinal<0){
        cout << "CANTIDAD NO VALIDA, INGRESE OTRA" << endl;
        cout << "INGRESAR SEGUNDA CANTIDAD: ";
        cin >> cantidadFinal;
    }
    system("cls");
    cout << left;
    cout << setw(6) << "ID FC" << "|| ";
    cout << setw(7) << "ID EMP" << "|| ";
    cout << setw(6) << "ID CL" << "|| ";
    cout << setw(7) << "ID COL" << "|| ";
    cout << setw(5) << "CANT" << "|| ";
    cout << setw(8) << "IMPORTE" << "|| ";
    cout << setw(12) << "FECHA VENTA" << "|| ";
    cout << setw(4) << "FP" << endl;
    cout << "===========================================================================" << endl;
    while (oVenta.leerDeDisco(pos++)) {
        if(oVenta.getCantidad()>=cantidadInicial && oVenta.getCantidad()<=cantidadFinal){
            oVenta.Mostrar();
            cout << endl;
            encontro = true;
        }
    }
    if (encontro == false) {
        cout << "NO SE ENCONTRARON FACTURAS CON ESE IMPORTE" << endl;
        return;
    }
}

void buscarFacturaImporteTotal() {
    Venta oVenta;
    int pos = 0;
    int importeInicio, importeFinal;
    bool encontro = false;
    cout << "INGRESAR PRIMER IMPORTE: ";
    cin >> importeInicio;
    while(importeInicio<0){
        cout << "IMPORTE NO VALIDO, INGRESE OTRO" << endl;
        cout << "INGRESAR PRIMER IMPORTE: ";
        cin >> importeInicio;
    }
    cout << "INGRESAR SEGUNDO IMPORTE: ";
    cin >> importeFinal;
    while(importeFinal<=importeInicio || importeFinal<0){
        cout << "IMPORTE NO VALIDO, INGRESE OTRO" << endl;
        cout << "INGRESAR SEGUNDO IMPORTE: ";
        cin >> importeFinal;
    }
    system("cls");
    cout << left;
    cout << setw(6) << "ID FC" << "|| ";
    cout << setw(7) << "ID EMP" << "|| ";
    cout << setw(6) << "ID CL" << "|| ";
    cout << setw(7) << "ID COL" << "|| ";
    cout << setw(5) << "CANT" << "|| ";
    cout << setw(8) << "IMPORTE" << "|| ";
    cout << setw(12) << "FECHA VENTA" << "|| ";
    cout << setw(4) << "FP" << endl;
    cout << "===========================================================================" << endl;
    while (oVenta.leerDeDisco(pos++)) {
        if(oVenta.getImporte()>=importeInicio && oVenta.getImporte()<=importeFinal){
            oVenta.Mostrar();
            cout << endl;
            encontro = true;
        }
    }
    if (encontro == false) {
        cout << "NO SE ENCONTRARON FACTURAS CON ESE IMPORTE" << endl;
        return;
    }
}

int submenuVentasListados(){
    int opc;
    while(true){
        cout << "MENU LISTADOS" << endl;
        cout << "---------------------------" << endl;
        cout << "1- LISTAR VENTAS" << endl;
        cout << "2- LISTAR VENTA POR ID FACTURA" << endl;
        cout << "3- LISTAR VENTA POR ID CLIENTE" << endl;
        cout << "4- LISTAR VENTA POR ID COLCHON" << endl;
        cout << "5- LISTAR VENTA POR RANGO DE FECHAS" << endl;
        cout << "6- LISTAR VENTA POR RANGO DE CANTIDAD TOTAL" << endl;
        cout << "7- LISTAR VENTA POR RANGO DE IMPORTE TOTAL" << endl;
        cout << "0- VOLVER AL MENU VENTAS" << endl;
        cout << "---------------------------" << endl;
        cout << "INGRESAR OPCION: ";
        cin >> opc;
        system("cls");
        switch(opc){
            case 1: listarVentas();
                break;
            case 2: buscarFacturaId();
                break;
            case 3: buscarFacturaClienteID();
                break;
            case 4: buscarFacturaPorColchonID();
                break;
            case 5: buscarFacturaPorRangoFecha();
                break;
            case 6: buscarFacturaCantidadTotal();
                break;
            case 7: buscarFacturaImporteTotal();
                break;
            case 0: return 0;
                break;
        }
        system("pause>null");
        system("cls");
    }
    return 0;
}

int submenuVentasInformes(){
    int opc;
    while(true){
        cout << "MENU VENTAS" << endl;
        cout << "---------------------------" << endl;
        cout << "1- INFORME RECAUDACION POR COLCHON" << endl;
        cout << "2- INFORME CANT VENTAS POR EMPLEADO" << endl;
        cout << "3- INFORME EMPLEADO CON MAS VENTAS" << endl;
        cout << "4- INFORME MES CON MAYOR FACTURACION" << endl;
        cout << "5- INFORME RECUADACION POR ANIO INGRESADO" << endl;
        cout << "6- INFORME RECAUDACION POR SEMESTRE AÑO ACTUAL" << endl;
        cout << "7- INFORME RECAUDACION POR FECHA INGRESADA" << endl;
        cout << "8- INFORME RECAUDACION POR RANGO DE AÑOS" << endl;
        cout << "9- INFORME CANT COLCHON VENDIDO POR MEDIDA" << endl;
        cout << "10- INFORME CANT COLCHON VENDIDO POR MODELO" << endl;
        cout << "11- INFORME RECAUDACION POR CLIENTE" << endl;
        cout << "0- VOLVER AL MENU VENTAS" << endl;
        cout << "---------------------------" << endl;
        cout << "INGRESAR OPCION: ";
        cin >> opc;
        system("cls");
        switch(opc){
            case 1: recaudacionPorColchon();
                break;
            case 2: cantVentasEmpleado();
                break;
            case 3: empleadoMasVentas();
                break;
            case 4: mesMayorFacturacion();
                break;
            case 5: recaudacionPorAnioIngresado();
                break;
            case 6: recaudacionPorSemestreAnioActual();
                break;
            case 7: recaudacionPorFechaIngresada();
                break;
            case 8: recaudacionPorRangoAnio();
                break;
            case 9: cantColchonVendidoPorMedida();
                break;
            case 10: cantColchonVendidoPorModelo();
                break;
            case 11: recaudacionPorCliente();
                break;
            case 0: return 0;
                break;
        }
        system("pause>null");
        system("cls");
    }
    return 0;
}

int menuVentas(){
    int opc;
    while(true){
        cout << "MENU VENTAS" << endl;
        cout << "---------------------------" << endl;
        cout << "1- INGRESAR VENTA" << endl;
        cout << "2- MENU LISTADOS" << endl;
        cout << "3- MENU INFORMES" << endl;
        cout << "0- VOLVER AL MENU PRINCIPAL" << endl;
        cout << "---------------------------" << endl;
        cout << "INGRESAR OPCION: ";
        cin >> opc;
        system("cls");
        switch(opc){
            case 1: cargarVenta();
                break;
            case 2: submenuVentasListados();
                break;
            case 3: submenuVentasInformes();
                break;
            case 0: return 0;
                break;
        }
        system("pause>null");
        system("cls");
    }
    return 0;
}
