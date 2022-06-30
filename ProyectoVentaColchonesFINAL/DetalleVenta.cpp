#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iomanip>

using namespace std;

#include "DetalleVenta.h"
#include "Venta.h"

void listarDetalleVentas(){
    DetalleVenta obj;
    int pos=0;
    cout << left;
    cout << setw(10) << "ID FACT";
    cout << setw(10) << "ID CL";
    cout << setw(10) << "ID EMP";
    cout << setw(14) << "FECHA VENTA";
    cout << setw(14) << "CANT. TOTAL";
    cout << setw(15) << "IMP. TOTAL" << endl;
    cout << "-------------------------------------------------------------------------" << endl;
    while(obj.leerDisco(pos++)){
        obj.Mostrar();
        cout << endl;
    }
}

void listarVentaPorMenorEmpleado(){
    DetalleVenta obj;
    int *vEmp, *vFact, aux, aux2;
    int cantReg=obj.contarVenta()-1;
    vEmp=new int[cantReg];
    if(vEmp==NULL){
        return;
    }
    vFact=new int[cantReg];
    if(vFact==NULL){
        return;
    }
    for(int i=0; i<cantReg; i++){
        obj.leerDisco(i);
        vEmp[i]=obj.getIDEmpleado();
        vFact[i]=obj.getIDfactura();
    }
    for(int i=0; i<cantReg; i++){
        for(int j=i+1; j<cantReg; j++){
            if(vEmp[j]<vEmp[i]){
                aux=vEmp[j];
                vEmp[j]=vEmp[i];
                vEmp[i]=aux;
                aux2=vFact[j];
                vFact[j]=vFact[i];
                vFact[i]=aux2;
            }
        }
    }
    cout << left;
    cout << setw(10) << "ID FACT";
    cout << setw(10) << "ID CL";
    cout << setw(10) << "ID EMP";
    cout << setw(14) << "FECHA VENTA";
    cout << setw(14) << "CANT. TOTAL";
    cout << setw(15) << "IMP. TOTAL" << endl;
    cout << "-------------------------------------------------------------------------" << endl;
    for(int i=0; i<cantReg; i++){
        for(int j=0; j<cantReg; j++){
            obj.leerDisco(j);
            if(vEmp[i]==obj.getIDEmpleado() && vFact[i]==obj.getIDfactura()){
                obj.Mostrar();
                cout << endl;
            }
        }
    }
    delete vEmp;
    delete vFact;
}

void listarVentaPorMayorEmpleado(){
    DetalleVenta obj;
    int *vEmp, *vFact, aux, aux2;
    int cantReg=obj.contarVenta()-1;
    vEmp=new int[cantReg];
    if(vEmp==NULL){
        return;
    }
    vFact=new int[cantReg];
    if(vFact==NULL){
        return;
    }
    for(int i=0; i<cantReg; i++){
        obj.leerDisco(i);
        vEmp[i]=obj.getIDEmpleado();
        vFact[i]=obj.getIDfactura();
    }
    for(int i=0; i<cantReg; i++){
        for(int j=i+1; j<cantReg; j++){
            if(vEmp[j]>vEmp[i]){
                aux=vEmp[j];
                vEmp[j]=vEmp[i];
                vEmp[i]=aux;
                aux2=vFact[j];
                vFact[j]=vFact[i];
                vFact[i]=aux2;
            }
        }
    }
    cout << left;
    cout << setw(10) << "ID FACT";
    cout << setw(10) << "ID CL";
    cout << setw(10) << "ID EMP";
    cout << setw(14) << "FECHA VENTA";
    cout << setw(14) << "CANT. TOTAL";
    cout << setw(15) << "IMP. TOTAL" << endl;
    cout << "-------------------------------------------------------------------------" << endl;
    for(int i=0; i<cantReg; i++){
        for(int j=0; j<cantReg; j++){
            obj.leerDisco(j);
            if(vEmp[i]==obj.getIDEmpleado() && vFact[i]==obj.getIDfactura()){
                obj.Mostrar();
                cout << endl;
            }
        }
    }
    delete vEmp;
    delete vFact;
}

void listarVentaPorMenorCliente(){
    DetalleVenta obj;
    int *vCli, *vFact, aux, aux2;
    int cantReg=obj.contarVenta()-1;
    vCli=new int[cantReg];
    if(vCli==NULL){
        return;
    }
    vFact=new int[cantReg];
    if(vFact==NULL){
        return;
    }
    for(int i=0; i<cantReg; i++){
        obj.leerDisco(i);
        vCli[i]=obj.getIDcliente();
        vFact[i]=obj.getIDfactura();
    }
    for(int i=0; i<cantReg; i++){
        for(int j=i+1; j<cantReg; j++){
            if(vCli[j]<vCli[i]){
                aux=vCli[j];
                vCli[j]=vCli[i];
                vCli[i]=aux;
                aux2=vFact[j];
                vFact[j]=vFact[i];
                vFact[i]=aux2;
            }
        }
    }
    cout << left;
    cout << setw(10) << "ID FACT";
    cout << setw(10) << "ID CL";
    cout << setw(10) << "ID EMP";
    cout << setw(14) << "FECHA VENTA";
    cout << setw(14) << "CANT. TOTAL";
    cout << setw(15) << "IMP. TOTAL" << endl;
    cout << "-------------------------------------------------------------------------" << endl;
    for(int i=0; i<cantReg; i++){
        for(int j=0; j<cantReg; j++){
            obj.leerDisco(j);
            if(vCli[i]==obj.getIDcliente() && vFact[i]==obj.getIDfactura()){
                obj.Mostrar();
                cout << endl;
            }
        }
    }
    delete vCli;
    delete vFact;
}

void listarVentaPorMayorCliente(){
    DetalleVenta obj;
    int *vCli, *vFact, aux, aux2;
    int cantReg=obj.contarVenta()-1;
    vCli=new int[cantReg];
    if(vCli==NULL){
        return;
    }
    vFact=new int[cantReg];
    if(vFact==NULL){
        return;
    }
    for(int i=0; i<cantReg; i++){
        obj.leerDisco(i);
        vCli[i]=obj.getIDcliente();
        vFact[i]=obj.getIDfactura();
    }
    for(int i=0; i<cantReg; i++){
        for(int j=i+1; j<cantReg; j++){
            if(vCli[j]>vCli[i]){
                aux=vCli[j];
                vCli[j]=vCli[i];
                vCli[i]=aux;
                aux2=vFact[j];
                vFact[j]=vFact[i];
                vFact[i]=aux2;
            }
        }
    }
    cout << left;
    cout << setw(10) << "ID FACT";
    cout << setw(10) << "ID CL";
    cout << setw(10) << "ID EMP";
    cout << setw(14) << "FECHA VENTA";
    cout << setw(14) << "CANT. TOTAL";
    cout << setw(15) << "IMP. TOTAL" << endl;
    cout << "-------------------------------------------------------------------------" << endl;
    for(int i=0; i<cantReg; i++){
        for(int j=0; j<cantReg; j++){
            obj.leerDisco(j);
            if(vCli[i]==obj.getIDcliente() && vFact[i]==obj.getIDfactura()){
                obj.Mostrar();
                cout << endl;
            }
        }
    }
    delete vCli;
    delete vFact;
}

void listarVentasPorMenorImporte(){
    DetalleVenta obj;
    int *vImp, *vFact, aux, aux2;
    int cantReg=obj.contarVenta()-1;
    vImp=new int[cantReg];
    if(vImp==NULL){
        return;
    }
    vFact=new int[cantReg];
    if(vFact==NULL){
        return;
    }
    for(int i=0; i<cantReg; i++){
        obj.leerDisco(i);
        vImp[i]=obj.getImporte();
        vFact[i]=obj.getIDfactura();
    }
    for(int i=0; i<cantReg; i++){
        for(int j=i+1; j<cantReg; j++){
            if(vImp[j]<vImp[i]){
                aux=vImp[j];
                vImp[j]=vImp[i];
                vImp[i]=aux;
                aux2=vFact[j];
                vFact[j]=vFact[i];
                vFact[i]=aux2;
            }
        }
    }
    cout << left;
    cout << setw(10) << "ID FACT";
    cout << setw(10) << "ID CL";
    cout << setw(10) << "ID EMP";
    cout << setw(14) << "FECHA VENTA";
    cout << setw(14) << "CANT. TOTAL";
    cout << setw(15) << "IMP. TOTAL" << endl;
    cout << "-------------------------------------------------------------------------" << endl;
    for(int i=0; i<cantReg; i++){
        for(int j=0; j<cantReg; j++){
            obj.leerDisco(j);
            if(vImp[i]==obj.getImporte() && vFact[i]==obj.getIDfactura()){
                obj.Mostrar();
                cout << endl;
            }
        }
    }
    delete vImp;
    delete vFact;
}

void listarVentasPorMayorImporte(){
    DetalleVenta obj;
    int *vImp, *vFact, aux, aux2;
    int cantReg=obj.contarVenta()-1;
    vImp=new int[cantReg];
    if(vImp==NULL){
        return;
    }
    vFact=new int[cantReg];
    if(vFact==NULL){
        return;
    }
    for(int i=0; i<cantReg; i++){
        obj.leerDisco(i);
        vImp[i]=obj.getImporte();
        vFact[i]=obj.getIDfactura();
    }
    for(int i=0; i<cantReg; i++){
        for(int j=i+1; j<cantReg; j++){
            if(vImp[j]>vImp[i]){
                aux=vImp[j];
                vImp[j]=vImp[i];
                vImp[i]=aux;
                aux2=vFact[j];
                vFact[j]=vFact[i];
                vFact[i]=aux2;
            }
        }
    }
    cout << left;
    cout << setw(10) << "ID FACT";
    cout << setw(10) << "ID CL";
    cout << setw(10) << "ID EMP";
    cout << setw(14) << "FECHA VENTA";
    cout << setw(14) << "CANT. TOTAL";
    cout << setw(15) << "IMP. TOTAL" << endl;
    cout << "-------------------------------------------------------------------------" << endl;
    for(int i=0; i<cantReg; i++){
        for(int j=0; j<cantReg; j++){
            obj.leerDisco(j);
            if(vImp[i]==obj.getImporte() && vFact[i]==obj.getIDfactura()){
                obj.Mostrar();
                cout << endl;
            }
        }
    }
    delete vImp;
    delete vFact;
}

void listarVentasPorMenorCantidad(){
    DetalleVenta obj;
    int *vCant, *vFact, aux, aux2;
    int cantReg=obj.contarVenta()-1;
    vCant=new int[cantReg];
    if(vCant==NULL){
        return;
    }
    vFact=new int[cantReg];
    if(vFact==NULL){
        return;
    }
    for(int i=0; i<cantReg; i++){
        obj.leerDisco(i);
        vCant[i]=obj.getCantidad();
        vFact[i]=obj.getIDfactura();
    }
    for(int i=0; i<cantReg; i++){
        for(int j=i+1; j<cantReg; j++){
            if(vCant[j]<vCant[i]){
                aux=vCant[j];
                vCant[j]=vCant[i];
                vCant[i]=aux;
                aux2=vFact[j];
                vFact[j]=vFact[i];
                vFact[i]=aux2;
            }
        }
    }
    cout << left;
    cout << setw(10) << "ID FACT";
    cout << setw(10) << "ID CL";
    cout << setw(10) << "ID EMP";
    cout << setw(14) << "FECHA VENTA";
    cout << setw(14) << "CANT. TOTAL";
    cout << setw(15) << "IMP. TOTAL" << endl;
    cout << "-------------------------------------------------------------------------" << endl;
    for(int i=0; i<cantReg; i++){
        for(int j=0; j<cantReg; j++){
            obj.leerDisco(j);
            if(vCant[i]==obj.getCantidad() && vFact[i]==obj.getIDfactura()){
                obj.Mostrar();
                cout << endl;
            }
        }
    }
    delete vCant;
    delete vFact;
}

void listarVentasPorMayorCantidad(){
    DetalleVenta obj;
    int *vCant, *vFact, aux, aux2;
    int cantReg=obj.contarVenta()-1;
    vCant=new int[cantReg];
    if(vCant==NULL){
        return;
    }
    vFact=new int[cantReg];
    if(vFact==NULL){
        return;
    }
    for(int i=0; i<cantReg; i++){
        obj.leerDisco(i);
        vCant[i]=obj.getCantidad();
        vFact[i]=obj.getIDfactura();
    }
    for(int i=0; i<cantReg; i++){
        for(int j=i+1; j<cantReg; j++){
            if(vCant[j]>vCant[i]){
                aux=vCant[j];
                vCant[j]=vCant[i];
                vCant[i]=aux;
                aux2=vFact[j];
                vFact[j]=vFact[i];
                vFact[i]=aux2;
            }
        }
    }
    cout << left;
    cout << setw(10) << "ID FACT";
    cout << setw(10) << "ID CL";
    cout << setw(10) << "ID EMP";
    cout << setw(14) << "FECHA VENTA";
    cout << setw(14) << "CANT. TOTAL";
    cout << setw(15) << "IMP. TOTAL" << endl;
    cout << "-------------------------------------------------------------------------" << endl;
    for(int i=0; i<cantReg; i++){
        for(int j=0; j<cantReg; j++){
            obj.leerDisco(j);
            if(vCant[i]==obj.getCantidad() && vFact[i]==obj.getIDfactura()){
                obj.Mostrar();
                cout << endl;
            }
        }
    }
    delete vCant;
    delete vFact;
}

void listarVentasPorMayorFecha(){
    DetalleVenta obj;
    int *vFact, aux2;
    Fecha *vFec, aux;
    int cantReg=obj.contarVenta()-1;
    vFec=new Fecha[cantReg];
    if(vFec==NULL){
        return;
    }
    vFact=new int[cantReg];
    if(vFact==NULL){
        return;
    }
    for(int i=0; i<cantReg; i++){
        obj.leerDisco(i);
        vFec[i]=obj.getFecha();
        vFact[i]=obj.getIDfactura();
    }
    for(int i=0; i<cantReg; i++){
        for(int j=i+1; j<cantReg; j++){
            if(vFec[j].getAnio()>vFec[i].getAnio()){
                aux=vFec[j];
                vFec[j]=vFec[i];
                vFec[i]=aux;
                aux2=vFact[j];
                vFact[j]=vFact[i];
                vFact[i]=aux2;
            }
            if(vFec[j].getAnio()==vFec[i].getAnio()){
                if(vFec[j].getMes()>vFec[i].getMes()){
                    aux=vFec[j];
                    vFec[j]=vFec[i];
                    vFec[i]=aux;
                    aux2=vFact[j];
                    vFact[j]=vFact[i];
                    vFact[i]=aux2;
                }
            }
            if(vFec[j].getAnio()==vFec[i].getAnio()){
                if(vFec[j].getMes()==vFec[i].getMes()){
                    if(vFec[j].getDia()>vFec[i].getDia()){
                        aux=vFec[j];
                        vFec[j]=vFec[i];
                        vFec[i]=aux;
                        aux2=vFact[j];
                        vFact[j]=vFact[i];
                        vFact[i]=aux2;
                    }
                }
            }
        }
    }
    cout << left;
    cout << setw(10) << "ID FACT";
    cout << setw(10) << "ID CL";
    cout << setw(10) << "ID EMP";
    cout << setw(14) << "FECHA VENTA";
    cout << setw(14) << "CANT. TOTAL";
    cout << setw(15) << "IMP. TOTAL" << endl;
    cout << "-------------------------------------------------------------------------" << endl;
    for(int i=0; i<cantReg; i++){
        for(int j=0; j<cantReg; j++){
            obj.leerDisco(j);
            if(vFec[i].getAnio()==obj.getFecha().getAnio() && vFec[i].getMes()==obj.getFecha().getMes() && vFec[i].getDia()==obj.getFecha().getDia() && vFact[i]==obj.getIDfactura()){
                obj.Mostrar();
                cout << endl;
            }
        }
    }
    delete vFec;
    delete vFact;
}

void listarVentasPorMenorFecha(){
    DetalleVenta obj;
    int *vFact, aux2;
    Fecha *vFec, aux;
    int cantReg=obj.contarVenta()-1;
    vFec=new Fecha[cantReg];
    if(vFec==NULL){
        return;
    }
    vFact=new int[cantReg];
    if(vFact==NULL){
        return;
    }
    for(int i=0; i<cantReg; i++){
        obj.leerDisco(i);
        vFec[i]=obj.getFecha();
        vFact[i]=obj.getIDfactura();
    }
    for(int i=0; i<cantReg; i++){
        for(int j=i+1; j<cantReg; j++){
            if(vFec[j].getAnio()<vFec[i].getAnio()){
                aux=vFec[j];
                vFec[j]=vFec[i];
                vFec[i]=aux;
                aux2=vFact[j];
                vFact[j]=vFact[i];
                vFact[i]=aux2;
            }
            if(vFec[j].getAnio()==vFec[i].getAnio()){
                if(vFec[j].getMes()<vFec[i].getMes()){
                    aux=vFec[j];
                    vFec[j]=vFec[i];
                    vFec[i]=aux;
                    aux2=vFact[j];
                    vFact[j]=vFact[i];
                    vFact[i]=aux2;
                }
            }
            if(vFec[j].getAnio()==vFec[i].getAnio()){
                if(vFec[j].getMes()==vFec[i].getMes()){
                    if(vFec[j].getDia()<vFec[i].getDia()){
                        aux=vFec[j];
                        vFec[j]=vFec[i];
                        vFec[i]=aux;
                        aux2=vFact[j];
                        vFact[j]=vFact[i];
                        vFact[i]=aux2;
                    }
                }
            }
        }
    }
    cout << left;
    cout << setw(10) << "ID FACT";
    cout << setw(10) << "ID CL";
    cout << setw(10) << "ID EMP";
    cout << setw(14) << "FECHA VENTA";
    cout << setw(14) << "CANT. TOTAL";
    cout << setw(15) << "IMP. TOTAL" << endl;
    cout << "-------------------------------------------------------------------------" << endl;
    for(int i=0; i<cantReg; i++){
        for(int j=0; j<cantReg; j++){
            obj.leerDisco(j);
            if(vFec[i].getAnio()==obj.getFecha().getAnio() && vFec[i].getMes()==obj.getFecha().getMes() && vFec[i].getDia()==obj.getFecha().getDia() && vFact[i]==obj.getIDfactura()){
                obj.Mostrar();
                cout << endl;
            }
        }
    }
    delete vFec;
    delete vFact;
}

void consultaCantTotalVenta(){
    DetalleVenta obj;
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
    cout << setw(10) << "ID FACT";
    cout << setw(10) << "ID CL";
    cout << setw(10) << "ID EMP";
    cout << setw(14) << "FECHA VENTA";
    cout << setw(14) << "CANT. TOTAL";
    cout << setw(15) << "IMP. TOTAL" << endl;
    cout << "-------------------------------------------------------------------------" << endl;
    while(obj.leerDisco(pos++)){
        if(obj.getCantidad()>=rango1 && obj.getCantidad()<=rango2){
            obj.Mostrar();
            cout << endl;
        }
    }
}

void consultaImporteTotalVenta(){
    DetalleVenta obj;
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
    cout << setw(10) << "ID FACT";
    cout << setw(10) << "ID CL";
    cout << setw(10) << "ID EMP";
    cout << setw(14) << "FECHA VENTA";
    cout << setw(14) << "CANT. TOTAL";
    cout << setw(15) << "IMP. TOTAL" << endl;
    cout << "-------------------------------------------------------------------------" << endl;
    while(obj.leerDisco(pos++)){
        if(obj.getImporte()>=rango1 && obj.getImporte()<=rango2){
            obj.Mostrar();
            cout << endl;
        }
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
    cout << endl;
    while(obj.leerDeDisco(pos++)){
        if(obj.getIdFactura()==idFactura){
            idCliente=obj.getIdCliente();
            idVendedor=obj.getIdEmpleado();
            formaPago=obj.getFormaPago();
            fechaVenta=obj.getFecha();
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
        cout << setw(6) << "CANT";
        cout << setw(9) << "IMPORTE" << endl;
        cout << "----------------------------------" << endl;
        for(int i=0; i<cantReg; i++){
            pos=0;
            while(obj.leerDeDisco(pos++)){
                if(obj.getIdColchon()==i+1 && obj.getIdFactura()==idFactura){
                    importeColchon=obj.getPrecio()*v[i];
                    precioColchon=obj.getPrecio();
                    importeTotal+=importeColchon;
                    break;
                }
            }
            if(v[i]>0){
                cout << left;
                cout << setw(8) << i+1;
                cout << setw(8) << precioColchon;
                cout << setw(6) << v[i];
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
        cout << "NO SE ENCONTRO NINGUN ID DE FACTURA" << endl;
    }
    delete v;
}

int menuDetalleVenta(){
    int opc;
    while(true){
        cout << "MENU DETALLE VENTA" << endl;
        cout << "---------------------------" << endl;
        cout << "1- LISTAR FACTURAS" << endl;
        cout << "2- BUSCAR FACTURA POR ID" << endl;
        cout << "3- LISTAR VENTAS POR MENOR ID EMPLEADO" << endl;
        cout << "4- LISTAR VENTAS POR MAYOR ID EMPLEADO" << endl;
        cout << "5- LISTAR VENTAS POR MENOR ID CLIENTE" << endl;
        cout << "6- LISTAR VENTAS POR MAYOR ID CLIENTE" << endl;
        cout << "7- LISTAR VENTAS POR MENOR IMPORTE TOTAL" << endl;
        cout << "8- LISTAR VENTAS POR MAYOR IMPORTE TOTAL" << endl;
        cout << "9- LISTAR VENTAS POR MENOR CANTIDAD TOTAL" << endl;
        cout << "10- LISTAR VENTAS POR MAYOR CANTIDAD TOTAL" << endl;
        cout << "11- LISTAR VENTAS POR MENOR FECHA" << endl;
        cout << "12- LISTAR VENTAS POR MAYOR FECHA" << endl;
        cout << "13- LISTADO POR RANGO DE CANTIDAD TOTAL" << endl;
        cout << "14- LISTADO POR RANGO DE IMPORTE TOTAL" << endl;
        cout << "0- VOLVER AL MENU PRINCIPAL" << endl;
        cout << "---------------------------" << endl;
        cout << "INGRESAR OPCION: ";
        cin >> opc;
        system("cls");
        switch(opc){
            case 1: listarDetalleVentas();
                break;
            case 2: buscarDetalleVenta();
                break;
            case 3: listarVentaPorMenorEmpleado();
                break;
            case 4: listarVentaPorMayorEmpleado();
                break;
            case 5: listarVentaPorMenorCliente();
                break;
            case 6: listarVentaPorMayorCliente();
                break;
            case 7: listarVentasPorMenorImporte();
                break;
            case 8: listarVentasPorMayorImporte();
                break;
            case 9: listarVentasPorMenorCantidad();
                break;
            case 10: listarVentasPorMayorCantidad();
                break;
            case 11: listarVentasPorMenorFecha();
                break;
            case 12: listarVentasPorMayorFecha();
                break;
            case 13: consultaCantTotalVenta();
                break;
            case 14: consultaImporteTotalVenta();
                break;
            case 0: return 0;
                break;
        }
        system("pause>null");
        system("cls");
    }
    return 0;
}
