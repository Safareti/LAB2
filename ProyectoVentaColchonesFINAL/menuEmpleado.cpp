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
            if(reg.getDniUsuario()==dni && reg.getEstadoUsuario()==true){
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
    Usuario reg;
    int posEmp=0;
    int posUser=0;
    if(obj.contarEmpleados()==0){
        return -1;
    }
    while(obj.leerDeDisco(posEmp)){
        posUser=0;
        while(reg.leerDeDisco(posUser)){
            if(reg.getEstadoUsuario()==true){
                if(obj.getIdEmpleado()==id){
                    return posEmp;
                }
            }
            posUser++;
        }
        posEmp++;
    }
    return -1;
}

int verificarDNIEmpleado(int dni){
    Empleado obj;
    Usuario reg;
    int posEmp=0;
    int posUser=0;
    if(obj.contarEmpleados()==0){
        return -1;
    }
    while(obj.leerDeDisco(posEmp++)){
        posUser=0;
        while(reg.leerDeDisco(posUser++)){
            if(reg.getDniUsuario()==obj.getDniEmpleado()){
                if(obj.getDniEmpleado()==dni){
                    return posEmp;
                }
            }
        }
    }
    return -1;
}

void cargarEmpleado(){
    Empleado obj;
    obj.Cargar();
    cout << endl;
}

void listarEmpleados(){
    Empleado obj;
    Usuario reg;
    int posEmp=0, posUser=0;
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
    while(obj.leerDeDisco(posEmp++)){
        posUser=0;
        while(reg.leerDeDisco(posUser++)){
            if(obj.getDniEmpleado()==reg.getDniUsuario()){
                if(reg.getEstadoUsuario()==true){
                    obj.Mostrar();
                    cout << endl;
                }
            }
        }
    }
}

bool backUpEmpleado(){
    FILE *p;
    p=fopen("vendedores.bkp","wb");
    if(p==NULL){
        return false;
    }
    Empleado reg;
    int pos=0;
    while(reg.leerDeDisco(pos++)){
        if(fwrite(&reg, sizeof reg, 1, p)==0){
            fclose(p);
            return false;
        }
    }
    fclose(p);
    cout << "BACK UP REALIZADO CON EXITO" << endl;
    return true;
}

bool backUpUsuario(){
    FILE *p;
    p=fopen("usuarios.bkp","wb");
    if(p==NULL){
        return false;
    }
    Usuario reg;
    int pos=0;
    while(reg.leerDeDisco(pos++)){
        if(fwrite(&reg, sizeof reg, 1, p)==0){
            fclose(p);
            return false;
        }
    }
    fclose(p);
    return true;
}

bool limpiarArchivoEmpleado(){
    FILE *p;
    p=fopen("vendedores.dat","wb");
    if(p==NULL){
        return false;
    }
    fclose(p);
    return true;
}

bool limpiarArchivoUsuario(){
    FILE *p;
    p=fopen("usuarios.dat","wb");
    if(p==NULL){
        return false;
    }
    fclose(p);
    return true;
}

bool restaurarEmpleado(){
    if(limpiarArchivoEmpleado()==false){
        return false;
    }
    if(limpiarArchivoUsuario()==false){
        return false;
    }
    FILE *pEmp;
    FILE *p;
    Empleado reg;
    pEmp=fopen("vendedores.dat", "wb");
    if(pEmp==NULL){
        cout<<"ERROR DE ARCHIVO"<<endl;
        return false;
    }
    p=fopen("vendedores.bkp", "rb");
    if(p==NULL){
        fclose(pEmp);
        cout<<"ERROR DE ARCHIVO";
        return false;
    }
    int posEmp=0;
    while(reg.leerDeBU(posEmp++)){
         if(fwrite(&reg, sizeof reg, 1, pEmp)==0){
            fclose(p);
            return false;
        }
    }
    Usuario obj;
    int posUser=0;
    FILE *pUser, *p2;
    pUser=fopen("usuarios.dat", "wb");
    if(pUser==NULL){
        cout<<"ERROR DE ARCHIVO"<<endl;
        return false;
    }
    p2=fopen("usuarios.bkp", "rb");
    if(p2==NULL){
        fclose(pUser);
        cout<<"ERROR DE ARCHIVO";
        return false;
    }
    while(obj.leerDeBU(posUser++)){
         if(fwrite(&obj, sizeof obj, 1, pUser)==0){
            fclose(p2);
            return false;
        }
    }
    fclose(pEmp);
    fclose(p);
    fclose(pUser);
    fclose(p2);
    cout << "ARHIVO RESTAURADO CON EXITO" << endl;
    return true;
}

bool restaurarUsuario(){
    if(limpiarArchivoUsuario()==false){
        return false;
    }
    Usuario obj;
    int posUser=0;
    FILE *pUser, *p2;
    pUser=fopen("usuarios.dat", "wb");
    if(pUser==NULL){
        cout<<"ERROR DE ARCHIVO"<<endl;
        return false;
    }
    p2=fopen("usuarios.bkp", "rb");
    if(p2==NULL){
        fclose(pUser);
        cout<<"ERROR DE ARCHIVO";
        return false;
    }
    while(obj.leerDeBU(posUser++)){
         if(fwrite(&obj, sizeof obj, 1, pUser)==0){
            fclose(p2);
            return false;
        }
    }
    fclose(pUser);
    fclose(p2);
    return true;
}

bool guardarEmpleado(){
    FILE *pEmp;
    pEmp=fopen("vendedores.bkp","wb");
    if(pEmp==NULL){
        return false;
    }
    Empleado reg;
    Usuario obj;
    int posEmp=0;
    int posUser=0;
    while(reg.leerDeDisco(posEmp)){
        posUser=0;
        while(obj.leerDeDisco(posUser)){
            if(reg.getDniEmpleado()==obj.getDniUsuario()){
                if(obj.getEstadoUsuario()==true){
                    if(fwrite(&reg, sizeof reg, 1, pEmp)==0){
                        fclose(pEmp);
                        return false;
                    }
                }
            }
            posUser++;
        }
        posEmp++;
    }
    fclose(pEmp);
    return true;
}

bool guardarUsuario(){
    FILE *pUser;
    pUser=fopen("usuarios.bkp","wb");
    if(pUser==NULL){
        return false;
    }
    Usuario obj;
    int posUser=0;
    while(obj.leerDeDisco(posUser)){
        if(obj.getEstadoUsuario()==true){
            if(fwrite(&obj, sizeof obj, 1, pUser)==0){
                fclose(pUser);
                return false;
            }
        }
        posUser++;
    }
    fclose(pUser);
    return true;
}

void bajaEmpleado(){
    Empleado obj;
    Usuario reg;
    int posEmp=0, posUser=0;
    int idEmp, pass;
    bool encontro=false;
    cout << "INGRESAR ID EMPLEADO: ";
    cin >> idEmp;
    cout << "INGRESAR CONTRASEÑA: ";
    cin >> pass;
    cout << endl;
    while(obj.leerDeDisco(posEmp++)){
        if(obj.getIdEmpleado()==idEmp && obj.getPass()==pass){
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
    cout << setw(10) << "DNI";
    cout << setw(10) << "SUELDO";
    cout << setw(11) << "TIPO EMP.";
    cout << setw(7) << "PASS";
    cout << setw(7) << "EDAD";
    cout << setw(14) << "FECHA NAC";
    cout << setw(12) << "FECHA INGRESO" << endl;
    cout << "-------------------------------------------------------------------------------";
    cout << endl;
    while(obj.leerDeDisco(posEmp++)){
        posUser=0;
        while(reg.leerDeDisco(posUser++)){
            if(obj.getDniEmpleado()==reg.getDniUsuario()){
                if(reg.getEstadoUsuario()==true){
                    obj.Mostrar();
                    cout << endl;
                }
            }
        }
    }
    cout << endl;
    int id, dni, guardarDni;
    cout << "INGRESAR ID PARA DAR DE BAJA: ";
    cin >> id;
    cout << endl;
    posUser=0;
    posEmp=0;
    while(obj.leerDeDisco(posEmp)){
        if(obj.getIdEmpleado()==id){
            dni=obj.getDniEmpleado();
        }
        posEmp++;
    }
    guardarDni=dni;
    while(reg.leerDeDisco(posUser)){
        if(reg.getDniUsuario()==guardarDni){
            reg.setEstadoUsuario(false);
            reg.modificarEnDisco(posUser);
            guardarEmpleado();
            guardarUsuario();
            restaurarEmpleado();
            restaurarUsuario();
            cout << "EMPLEADO DADO DE BAJA CON EXITO" << endl;
            return;
        }
        posUser++;
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
    cout << setw(10) << "DNI";
    cout << setw(10) << "SUELDO";
    cout << setw(11) << "TIPO EMP.";
    cout << setw(7) << "PASS";
    cout << setw(7) << "EDAD";
    cout << setw(14) << "FECHA NAC";
    cout << setw(12) << "FECHA INGRESO" << endl;
    cout << "-------------------------------------------------------------------------------";
    cout << endl;;
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
        if(dni==obj.getDniEmpleado()){
            obj.Mostrar();
            encontro=true;
        }
    }
    if(encontro==false){
        cout << "NO SE ENCONTRO EMPLEADO CON ESE DNI" << endl;
    }
}

void listarVendedores(){
    Empleado obj;
    Usuario reg;
    int posEmp=0, posUser=0;
    cout << "VENDEDORES" << endl;
    cout << "-------------------" << endl;
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
    while(obj.leerDeDisco(posEmp++)){
        posUser=0;
        while(reg.leerDeDisco(posUser++)){
            if(obj.getDniEmpleado()==reg.getDniUsuario()){
                if(reg.getEstadoUsuario()==true){
                    if(obj.getTipoEmpleado()==1){
                        obj.Mostrar();
                        cout << endl;
                    }
                }
            }
        }
    }
}

void listarAdministradores(){
    Empleado obj;
    Usuario reg;
    int posEmp=0, posUser=0;
    cout << "ADMINISTRADORES" << endl;
    cout << "-------------------" << endl;
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
    while(obj.leerDeDisco(posEmp++)){
        posUser=0;
        while(reg.leerDeDisco(posUser++)){
            if(obj.getDniEmpleado()==reg.getDniUsuario()){
                if(reg.getEstadoUsuario()==true){
                    if(obj.getTipoEmpleado()==2){
                        obj.Mostrar();
                        cout << endl;
                    }
                }
            }
        }
    }
}

void ordenarEmpleadosMayorEdad(){
    Empleado obj;
    int cantReg=obj.contarEmpleados()-1;
    int *vEdad, aux;
    int *vIdEmp, aux2;
    vEdad=new int[cantReg];
    if(vEdad==NULL){
        return;
    }
    vIdEmp=new int[cantReg];
    if(vIdEmp==NULL){
        return;
    }
    for(int i=0; i<cantReg; i++){
        obj.leerDeDisco(i);
        vEdad[i]=obj.getEdad();
        vIdEmp[i]=obj.getIdEmpleado();
    }
    for(int i=0; i<cantReg; i++){
        for(int j=i+1; j<cantReg; j++){
            if(vEdad[i]<vEdad[j]){
                aux=vEdad[j];
                vEdad[j]=vEdad[i];
                vEdad[i]=aux;
                aux2=vIdEmp[j];
                vIdEmp[j]=vIdEmp[i];
                vIdEmp[i]=aux2;
            }
        }
    }
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
    for(int i=0; i<cantReg; i++){
        for(int j=0; j<cantReg; j++){
            obj.leerDeDisco(j);
            if(obj.getEdad()==vEdad[i] && obj.getIdEmpleado()==vIdEmp[i]){
                obj.Mostrar();
            }
        }
        cout << endl;
    }
    delete vEdad;
    delete vIdEmp;
}

void ordenarEmpleadosMenorEdad(){
    Empleado obj;
    int cantReg=obj.contarEmpleados()-1;
    int *vEdad, aux;
    int *vIdEmp, aux2;
    vEdad=new int[cantReg];
    if(vEdad==NULL){
        return;
    }
    vIdEmp=new int[cantReg];
    if(vIdEmp==NULL){
        return;
    }
    for(int i=0; i<cantReg; i++){
        obj.leerDeDisco(i);
        vEdad[i]=obj.getEdad();
        vIdEmp[i]=obj.getIdEmpleado();
    }
    for(int i=0; i<cantReg; i++){
        for(int j=i+1; j<cantReg; j++){
            if(vEdad[i]>vEdad[j]){
                aux=vEdad[j];
                vEdad[j]=vEdad[i];
                vEdad[i]=aux;
                aux2=vIdEmp[j];
                vIdEmp[j]=vIdEmp[i];
                vIdEmp[i]=aux2;
            }
        }
    }
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
    for(int i=0; i<cantReg; i++){
        for(int j=0; j<cantReg; j++){
            obj.leerDeDisco(j);
            if(obj.getEdad()==vEdad[i] && obj.getIdEmpleado()==vIdEmp[i]){
                obj.Mostrar();
            }
        }
        cout << endl;
    }
    delete vEdad;
    delete vIdEmp;
}

void ordenarEmpleadosMayorSueldo(){
    Empleado obj;
    int cantReg=obj.contarEmpleados()-1;
    float *vSueldo, aux;
    int *vIdEmp, aux2;
    vSueldo=new float[cantReg];
    if(vSueldo==NULL){
        return;
    }
    vIdEmp=new int[cantReg];
    if(vIdEmp==NULL){
        return;
    }
    for(int i=0; i<cantReg; i++){
        obj.leerDeDisco(i);
        vSueldo[i]=obj.getSueldoEmpleado();
        vIdEmp[i]=obj.getIdEmpleado();
    }
    for(int i=0; i<cantReg; i++){
        for(int j=i+1; j<cantReg; j++){
            if(vSueldo[i]<vSueldo[j]){
                aux=vSueldo[j];
                vSueldo[j]=vSueldo[i];
                vSueldo[i]=aux;
                aux2=vIdEmp[j];
                vIdEmp[j]=vIdEmp[i];
                vIdEmp[i]=aux2;
            }
        }
    }
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
    for(int i=0; i<cantReg; i++){
        for(int j=0; j<cantReg; j++){
            obj.leerDeDisco(j);
            if(obj.getSueldoEmpleado()==vSueldo[i] && obj.getIdEmpleado()==vIdEmp[i]){
                obj.Mostrar();
            }
        }
        cout << endl;
    }
    delete vSueldo;
    delete vIdEmp;
}

void ordenarEmpleadosMenorSueldo(){
    Empleado obj;
    int cantReg=obj.contarEmpleados()-1;
    float *vSueldo, aux;
    int *vIdEmp, aux2;
    vSueldo=new float[cantReg];
    if(vSueldo==NULL){
        return;
    }
    vIdEmp=new int[cantReg];
    if(vIdEmp==NULL){
        return;
    }
    for(int i=0; i<cantReg; i++){
        obj.leerDeDisco(i);
        vSueldo[i]=obj.getSueldoEmpleado();
        vIdEmp[i]=obj.getIdEmpleado();
    }
    for(int i=0; i<cantReg; i++){
        for(int j=i+1; j<cantReg; j++){
            if(vSueldo[i]>vSueldo[j]){
                aux=vSueldo[j];
                vSueldo[j]=vSueldo[i];
                vSueldo[i]=aux;
                aux2=vIdEmp[j];
                vIdEmp[j]=vIdEmp[i];
                vIdEmp[i]=aux2;
            }
        }
    }
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
    for(int i=0; i<cantReg; i++){
        for(int j=0; j<cantReg; j++){
            obj.leerDeDisco(j);
            if(obj.getSueldoEmpleado()==vSueldo[i] && obj.getIdEmpleado()==vIdEmp[i]){
                obj.Mostrar();
            }
        }
        cout << endl;
    }
    delete vSueldo;
    delete vIdEmp;
}

void ordenarEmpleadoMenorFechaIngreso(){
    Empleado obj;
    int *vIdEmp, aux2;
    Fecha *vFec, aux;
    int cantReg=obj.contarEmpleados()-1;
    vFec=new Fecha[cantReg];
    if(vFec==NULL){
        return;
    }
    vIdEmp=new int[cantReg];
    if(vIdEmp==NULL){
        return;
    }
    for(int i=0; i<cantReg; i++){
        obj.leerDeDisco(i);
        vFec[i]=obj.getFechaIngreso();
        vIdEmp[i]=obj.getIdEmpleado();
    }
    for(int i=0; i<cantReg; i++){
        for(int j=i+1; j<cantReg; j++){
            if(vFec[j].getAnio()>vFec[i].getAnio()){
                aux=vFec[j];
                vFec[j]=vFec[i];
                vFec[i]=aux;
                aux2=vIdEmp[j];
                vIdEmp[j]=vIdEmp[i];
                vIdEmp[i]=aux2;
            }
            if(vFec[j].getAnio()==vFec[i].getAnio()){
                if(vFec[j].getMes()>vFec[i].getMes()){
                    aux=vFec[j];
                    vFec[j]=vFec[i];
                    vFec[i]=aux;
                    aux2=vIdEmp[j];
                    vIdEmp[j]=vIdEmp[i];
                    vIdEmp[i]=aux2;
                }
            }
            if(vFec[j].getAnio()==vFec[i].getAnio()){
                if(vFec[j].getMes()==vFec[i].getMes()){
                    if(vFec[j].getDia()>vFec[i].getDia()){
                        aux=vFec[j];
                        vFec[j]=vFec[i];
                        vFec[i]=aux;
                        aux2=vIdEmp[j];
                        vIdEmp[j]=vIdEmp[i];
                        vIdEmp[i]=aux2;
                    }
                }
            }
        }
    }
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
    for(int i=0; i<cantReg; i++){
        for(int j=0; j<cantReg; j++){
            obj.leerDeDisco(j);
            if(vFec[i].getAnio()==obj.getFechaIngreso().getAnio() && vFec[i].getMes()==obj.getFechaIngreso().getMes() && vFec[i].getDia()==obj.getFechaIngreso().getDia() && vIdEmp[i]==obj.getIdEmpleado()){
                obj.Mostrar();
                cout << endl;
            }
        }
    }
    delete vFec;
    delete vIdEmp;
}

void ordenarEmpleadoMayorFechaIngreso(){
    Empleado obj;
    int *vIdEmp, aux2;
    Fecha *vFec, aux;
    int cantReg=obj.contarEmpleados()-1;
    vFec=new Fecha[cantReg];
    if(vFec==NULL){
        return;
    }
    vIdEmp=new int[cantReg];
    if(vIdEmp==NULL){
        return;
    }
    for(int i=0; i<cantReg; i++){
        obj.leerDeDisco(i);
        vFec[i]=obj.getFechaIngreso();
        vIdEmp[i]=obj.getIdEmpleado();
    }
    for(int i=0; i<cantReg; i++){
        for(int j=i+1; j<cantReg; j++){
            if(vFec[j].getAnio()<vFec[i].getAnio()){
                aux=vFec[j];
                vFec[j]=vFec[i];
                vFec[i]=aux;
                aux2=vIdEmp[j];
                vIdEmp[j]=vIdEmp[i];
                vIdEmp[i]=aux2;
            }
            if(vFec[j].getAnio()==vFec[i].getAnio()){
                if(vFec[j].getMes()<vFec[i].getMes()){
                    aux=vFec[j];
                    vFec[j]=vFec[i];
                    vFec[i]=aux;
                    aux2=vIdEmp[j];
                    vIdEmp[j]=vIdEmp[i];
                    vIdEmp[i]=aux2;
                }
            }
            if(vFec[j].getAnio()==vFec[i].getAnio()){
                if(vFec[j].getMes()==vFec[i].getMes()){
                    if(vFec[j].getDia()<vFec[i].getDia()){
                        aux=vFec[j];
                        vFec[j]=vFec[i];
                        vFec[i]=aux;
                        aux2=vIdEmp[j];
                        vIdEmp[j]=vIdEmp[i];
                        vIdEmp[i]=aux2;
                    }
                }
            }
        }
    }
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
    for(int i=0; i<cantReg; i++){
        for(int j=0; j<cantReg; j++){
            obj.leerDeDisco(j);
            if(vFec[i].getAnio()==obj.getFechaIngreso().getAnio() && vFec[i].getMes()==obj.getFechaIngreso().getMes() && vFec[i].getDia()==obj.getFechaIngreso().getDia() && vIdEmp[i]==obj.getIdEmpleado()){
                obj.Mostrar();
                cout << endl;
            }
        }
    }
    delete vFec;
    delete vIdEmp;
}

void modificarTipoEmpleado(){
    Empleado obj;
    int posEmp=0;
    bool admin=false;
    if(obj.contarEmpleados()==0){
        cout << "NO HAY EMPLEADOS REGISTRADOS" << endl;
        return;
    }
    while(obj.leerDeDisco(posEmp++)){
        if(obj.getTipoEmpleado()==2){
            admin=true;
        }
    }
    posEmp=0;
    int idEmp, pass, idAdmin;
    bool encontro=false;
    if(admin==true){
        cout << "INGRESAR ID EMPLEADO (ADMIN): ";
        cin >> idEmp;
        while(obj.leerDeDisco(posEmp++)){
            if(obj.getIdEmpleado()==idEmp){
                idAdmin=idEmp;
                cout << "INGRESAR CONTRASEÑA: ";
                cin >> pass;
                if(obj.getPass()==pass){
                    encontro=true;
                }
            }
        }
        if(encontro==false){
        cout << "ID EMPLEADO Y/O CONTRASEÑA INCORRECTO" << endl;
            return;
        }
        system("cls");
        listarEmpleados();
        cout << endl;
        int idEmp;
        cout << "INGRESAR ID PARA MODIFICAR EL TIPO DE EMPLEADO: ";
        cin >> idEmp;
        while(idAdmin==idEmp){
            cout << "EMPLEADO NO PERMITIDO, INGRESE OTRO" << endl;
            cout << "INGRESAR ID PARA MODIFICAR EL TIPO DE EMPLEADO: ";
            cin >> idEmp;
        }
        cout << endl;
        posEmp=0;
        int encontro=false;
        while(obj.leerDeDisco(posEmp)){
            if(obj.getIdEmpleado()==idEmp){
                if(obj.getTipoEmpleado()==1){
                    obj.setTipoEmpleado(2);
                }else{
                    obj.setTipoEmpleado(1);
                }
                obj.modificarEnDisco(posEmp);
                encontro=true;
                cout << "TIPO DE EMPLEADO MODIFICADO CON EXITO" << endl;
                return;
            }
            posEmp++;
        }
        if(encontro==false){
            cout << "ID DE EMPLEADO NO ENCONTRADO" << endl;
        }
    }
    if(encontro==false){
        listarEmpleados();
        cout << endl;
        cout << "SELECCIONAR UN EMPLEADO PARA QUE SEA ADMIN" << endl;
        cout << "INGRESA ID: ";
        cin >> idEmp;
        posEmp=0;
        while(obj.leerDeDisco(posEmp)){
            if(obj.getIdEmpleado()==idEmp && obj.getTipoEmpleado()==1){
                obj.setTipoEmpleado(2);
                obj.modificarEnDisco(posEmp);
                cout << "TIPO DE EMPLEADO MODIFICADO CON EXITO" << endl;
                return;
            }
            posEmp++;
        }
    }
}

void modificarFechaIngreso() {
    Empleado obj;
    Fecha oFecha;
    int posEmp = 0;
    bool admin = false;
    if (obj.contarEmpleados() == 0) {
        cout << "NO HAY EMPLEADOS REGISTRADOS" << endl;
        return;
    }
    while (obj.leerDeDisco(posEmp++)) {
        if (obj.getTipoEmpleado() == 2) {
            admin = true;
        }
    }
    posEmp = 0;
    int idEmp, pass, idAdmin;
    bool encontro = false;
    if (admin == true) {
        cout << "INGRESAR ID EMPLEADO (ADMIN): ";
        cin >> idEmp;
        while (obj.leerDeDisco(posEmp++)) {
            if (obj.getIdEmpleado() == idEmp) {
                idAdmin = idEmp;
                cout << "INGRESAR CONTRASEÑA: ";
                cin >> pass;
                if (obj.getPass() == pass) {
                    encontro = true;
                }
            }
        }
        if (encontro == false) {
            cout << "ID EMPLEADO Y/O CONTRASEÑA INCORRECTO" << endl;
            return;
        }
        system("cls");
        listarEmpleados();
        cout << endl;
        int idEmp;
        cout << "INGRESAR ID PARA MODIFICAR LA FECHA DE INGRESO: ";
        cin >> idEmp;
        while (idAdmin == idEmp) {
            cout << "EMPLEADO NO PERMITIDO, INGRESE OTRO" << endl;
            cout << "INGRESAR ID PARA MODIFICAR LA FECHA DE INGRESO: ";
            cin >> idEmp;
        }
        cout << endl;
        posEmp = 0;
        int encontro = false;
        while (obj.leerDeDisco(posEmp)) {
            if (obj.getIdEmpleado() == idEmp) {
                oFecha.Cargar();
                obj.setFechaIngreso(oFecha);
                obj.modificarEnDisco(posEmp);
                encontro = true;
                cout << "FECHA DE INGRESO MODIFICADO CON EXITO" << endl;
                return;
            }
            posEmp++;
        }
        if (encontro == false) {
            cout << "ID DE EMPLEADO NO ENCONTRADO" << endl;
        }
    }
    cout << "NO HAY ADMINS EN EL SISTEMA" << endl;
}

void modificarFechaNacimiento() {
    Empleado obj;
    Fecha oFecha;
    int posEmp = 0;
    bool admin = false;
    if (obj.contarEmpleados() == 0) {
        cout << "NO HAY EMPLEADOS REGISTRADOS" << endl;
        return;
    }
    while (obj.leerDeDisco(posEmp++)) {
        if (obj.getTipoEmpleado() == 2) {
            admin = true;
        }
    }
    posEmp = 0;
    int idEmp, pass, idAdmin;
    bool encontro = false;
    if (admin == true) {
        cout << "INGRESAR ID EMPLEADO (ADMIN): ";
        cin >> idEmp;
        while (obj.leerDeDisco(posEmp++)) {
            if (obj.getIdEmpleado() == idEmp) {
                idAdmin = idEmp;
                cout << "INGRESAR CONTRASEÑA: ";
                cin >> pass;
                if (obj.getPass() == pass) {
                    encontro = true;
                }
            }
        }
        if (encontro == false) {
            cout << "ID EMPLEADO Y/O CONTRASEÑA INCORRECTO" << endl;
            return;
        }
        system("cls");
        listarEmpleados();
        cout << endl;
        int idEmp;
        cout << "INGRESAR ID PARA MODIFICAR LA FECHA DE NACIMIENTO: ";
        cin >> idEmp;
        while (idAdmin == idEmp) {
            cout << "EMPLEADO NO PERMITIDO, INGRESE OTRO" << endl;
            cout << "INGRESAR ID PARA MODIFICAR LA FECHA DE NACIMIENTO: ";
            cin >> idEmp;
        }
        cout << endl;
        posEmp = 0;
        int encontro = false;
        while (obj.leerDeDisco(posEmp)) {
            if (obj.getIdEmpleado() == idEmp) {
                oFecha.Cargar();
                obj.setFechaNacimiento(oFecha);
                obj.modificarEnDisco(posEmp);
                encontro = true;
                cout << "FECHA DE NACIMIENTO MODIFICADO CON EXITO" << endl;
                return;
            }
            posEmp++;
        }
        if (encontro == false) {
            cout << "ID DE EMPLEADO NO ENCONTRADO" << endl;
        }
    }
    cout << "NO HAY ADMINS EN EL SISTEMA" << endl;
}


void modificarSueldoEmplado() {
    Empleado obj;
    int posEmp = 0;
    bool admin = false;
    if (obj.contarEmpleados() == 0) {
        cout << "NO HAY EMPLEADOS REGISTRADOS" << endl;
        return;
    }
    while (obj.leerDeDisco(posEmp++)) {
        if (obj.getTipoEmpleado() == 2) {
            admin = true;
        }
    }
    posEmp = 0;
    int idEmp, pass;
    bool encontro = false;
    if (admin == true) {
        cout << "INGRESAR ID EMPLEADO (ADMIN): ";
        cin >> idEmp;
        while (obj.leerDeDisco(posEmp++)) {
            if (obj.getIdEmpleado() == idEmp) {
                cout << "INGRESAR CONTRASEÑA: ";
                cin >> pass;
                if (obj.getPass() == pass) {
                    encontro = true;
                }
            }
        }
        if (encontro == false) {
            cout << "ID EMPLEADO Y/O CONTRASEÑA INCORRECTO" << endl;
            return;
        }
        system("cls");
        listarEmpleados();
        cout << endl;
        cout << "INGRESAR ID PARA MODIFICAR EL SUELDO NUEVO: ";
        cin >> idEmp;
        cout << endl;
        posEmp = 0;
        bool encontro = false;
        float sueldoNuevo;
        while (obj.leerDeDisco(posEmp)) {
            if (obj.getIdEmpleado() == idEmp) {
                cout << "INGRESAR SUELDO NUEVO: ";
                cin >> sueldoNuevo;
                while (sueldoNuevo <= 0) {
                    cout << "SUELDO NO PERMITIDO, INGRESE OTRO" << endl;
                    cout << "INGRESAR SUELDO NUEVO: ";
                    cin >> sueldoNuevo;
                }
                cout << endl;
                obj.setSueldoEmpleado(sueldoNuevo);
                obj.modificarEnDisco(posEmp);
                encontro = true;
                cout << "TIPO DE EMPLEADO MODIFICADO CON EXITO" << endl;
                return;
            }
            posEmp++;
        }
        if (encontro == false) {
            cout << "ID DE EMPLEADO NO ENCONTRADO" << endl;
        }
    }
    else {
        cout << "NO HAY ADMINISTRADORES EN EL SISTEMA" << endl;
    }
}

void modificarPassEmplado(){
    Empleado obj;
    int posEmp=0;
    bool admin=false;
    if(obj.contarEmpleados()==0){
        cout << "NO HAY EMPLEADOS REGISTRADOS" << endl;
        return;
    }
    while(obj.leerDeDisco(posEmp++)){
        if(obj.getTipoEmpleado()==2){
            admin=true;
        }
    }
    posEmp=0;
    int idEmp, pass;
    bool encontro=false;
    if(admin==true){
        cout << "INGRESAR ID EMPLEADO (ADMIN): ";
        cin >> idEmp;
        while(obj.leerDeDisco(posEmp++)){
            if(obj.getIdEmpleado()==idEmp){
                cout << "INGRESAR CONTRASEÑA: ";
                cin >> pass;
                if(obj.getPass()==pass){
                    encontro=true;
                }
            }
        }
        if(encontro==false){
        cout << "ID EMPLEADO Y/O CONTRASEÑA INCORRECTO" << endl;
            return;
        }
        system("cls");
        listarEmpleados();
        cout << endl;
        cout << "INGRESAR ID PARA MODIFICAR LA CONTRASEÑA: ";
        cin >> idEmp;
        cout << endl;
        posEmp=0;
        bool encontro=false;
        int passNueva;
        while(obj.leerDeDisco(posEmp)){
            if(obj.getIdEmpleado()==idEmp){
                cout << "INGRESAR CONTRASEÑA NUEVA: ";
                cin >> passNueva;
                cout << endl;
                obj.setPass(passNueva);
                obj.modificarEnDisco(posEmp);
                encontro=true;
                cout << "TIPO DE EMPLEADO MODIFICADO CON EXITO" << endl;
                return;
            }
            posEmp++;
        }
        if(encontro==false){
            cout << "ID DE EMPLEADO NO ENCONTRADO" << endl;
        }
    }
    else {
        cout << "NO HAY NINGUN ADMIN ASIGNADO EN EL SISTEMA" << endl;
    }
}

int submenuEmpleadoListados(){
    int opc;
    while(true){
        cout << "MENU LISTADOS" << endl;
        cout << "---------------------------" << endl;
        cout << "1- LISTAR EMPLEADOS" << endl;
        cout << "2- LISTAR EMPLEADO POR ID" << endl;
        cout << "3- LISTAR EMPLEADO POR DNI" << endl;
        cout << "4- LISTAR EMPLEADO TIPO VENDEDOR" << endl;
        cout << "5- LISTAR EMPLEADO TIPO ADMIN" << endl;
        cout << "6- LISTAR EMPLEADOS POR MAYOR EDAD" << endl;
        cout << "7- LISTAR EMPLEADOS POR MENOR EDAD" << endl;
        cout << "8- LISTAR EMPLEADOS POR MAYOR SUELDO" << endl;
        cout << "9- LISTAR EMPLEADOS POR MENOR SUELDO" << endl;
        cout << "10- LISTAR EMPLEADOS POR MENOR FECHA INGRESO" << endl;
        cout << "11- LISTAR EMPLEADOS POR MAYOR FECHA INGRESO" << endl;
        cout << "0- VOLVER AL MENU EMPLEADO" << endl;
        cout << "---------------------------" << endl;
        cout << "INGRESAR OPCION: ";
        cin >> opc;
        system("cls");
        switch(opc){
            case 1: listarEmpleados();
                break;
            case 2: buscarEmpleadoPorId();
                break;
            case 3: buscarEmpleadoPorDni();
                break;
            case 4: listarVendedores();
                break;
            case 5: listarAdministradores();
                break;
            case 6: ordenarEmpleadosMayorEdad();
                break;
            case 7: ordenarEmpleadosMenorEdad();
                break;
            case 8: ordenarEmpleadosMayorSueldo();
                break;
            case 9: ordenarEmpleadosMenorSueldo();
                break;
            case 10: ordenarEmpleadoMenorFechaIngreso();
                break;
            case 11: ordenarEmpleadoMayorFechaIngreso();
                break;
            case 0: return 0;
                break;
        }
        system("pause>null");
        system("cls");
    }
    return 0;
}

int submenuEmpleadoBackUp(){
    int opc;
    while(true){
        cout << "MENU BACK UP" << endl;
        cout << "---------------------------" << endl;
        cout << "1- REALIZAR BACK UP EMPLEADO Y USUARIO" << endl;
        cout << "2- RESTAURAR ARCHIVO EMPLEADO Y USUARIO" << endl;
        cout << "0- VOLVER AL MENU EMPLEADO" << endl;
        cout << "---------------------------" << endl;
        cout << "INGRESAR OPCION: ";
        cin >> opc;
        system("cls");
        switch(opc){
            case 1: backUpEmpleado();
                backUpUsuario();
                break;
            case 2: restaurarEmpleado();
                restaurarUsuario();
                break;
            case 0: return 0;
                break;
        }
        system("pause>null");
        system("cls");
    }
    return 0;
}

int submenuModificarEmpleado() {
    int opc;
    while (true) {
        cout << "MENU MODIFICAR EMPLEADO" << endl;
        cout << "---------------------------" << endl;
        cout << "1- MODIFICAR TIPO" << endl;
        cout << "2- MODIFICAR CONTRASENA" << endl;
        cout << "3- MODIFICAR FECHA INGRESO" << endl;
        cout << "4- MODIFICAR FECHA NACIMIENTO" << endl;
        cout << "5- MODIFICAR SUELDO" << endl;
        cout << "0- VOLVER AL MENU EMPLEADO" << endl;
        cout << "---------------------------" << endl;
        cout << "INGRESAR OPCION: ";
        cin >> opc;
        system("cls");
        switch (opc) {
        case 1: modificarTipoEmpleado();
            break;
        case 2: modificarPassEmplado();
            break;
        case 3: modificarFechaIngreso();
            break;
        case 4:modificarFechaNacimiento();
            break;
        case 5: modificarSueldoEmplado();
            break;
        case 0: return 0;
            break;
        default: 
            cout << "SELECCIONE UNA OPCION CORRECTA";
        }
        system("pause>null");
        system("cls");
    }
    return 0;
}

int menuEmpleado(){
    int opc;
    while(true){
        cout << "MENU EMPLEADOS" << endl;
        cout << "---------------------------" << endl;
        cout << "1- INGRESAR EMPLEADO" << endl;
        cout << "2- MENU LISTADOS" << endl;
        cout << "3- BAJA EMPLEADO" << endl;
        cout << "4- MENU MODIFICAR" << endl;
        cout << "5- CONFIGURACION" << endl;
        cout << "0- VOLVER AL MENU PRINCIPAL" << endl;
        cout << "---------------------------" << endl;
        cout << "INGRESAR OPCION: ";
        cin >> opc;
        system("cls");
        switch(opc){
            case 1: cargarEmpleado();
                break;
            case 2: submenuEmpleadoListados();
                break;
            case 3: bajaEmpleado();
                break;
            case 4: submenuModificarEmpleado();
                break;
            case 5: submenuEmpleadoBackUp();
                break;
            case 0: return 0;
                break;
        }
        system("pause>null");
        system("cls");
    }
    return 0;
}
