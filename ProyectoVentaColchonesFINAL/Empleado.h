#ifndef EMPLEADO_H_INCLUDED
#define EMPLEADO_H_INCLUDED

#include <iomanip>
#include "Usuarios.h"
#include "fecha.h"
#include <ctime>

int menuEmpleado();
int verificarID(int); ///verifica que el id ingresado no se repita
int verificarDNIEmpleado(int); ///verifica que el dni ingresado no se repita
void verificarEmpleadoUsuario(int); ///si el dni que recibe no se encuentra en el archivo de usuarios lo graba junto al nombre y apellido
int modificarUsuario(int);
void modificarEmpleado(int, int);

class Empleado{
private:
    int dniEmpleado;
    int idEmpleado;
    float sueldoEmpleado;
    Fecha fechaNacimiento;
    int edad;
    Fecha fechaIngreso;
    int tipoEmpleado; ///1- Vendedor. 2- Administrador
    int pass;
public:
    void Cargar(){
        cout << "INGRESAR ID EMPLEADO: ";
        cin >> idEmpleado;
        if(verificarID(idEmpleado)!=-1){
            cout << "ID EXISTENTE" << endl;
            cout << "NO SE REGISTRO EL EMPLEADO" << endl;
            return;
        }
        cout << "INGRESAR DNI VENDEDOR: ";
        cin >> dniEmpleado;
        if(verificarDNIEmpleado(dniEmpleado)!=-1){
            cout << "DNI EXISTENTE" << endl;
            cout << "NO SE REGISTRO EL EMPLEADO" << endl;
            return;
        }
        verificarEmpleadoUsuario(dniEmpleado);
        cout << "INGRESAR SUELDO: ";
        cin >> sueldoEmpleado;
        setTipoEmpleado(1);
        cout << "INGRESAR CONTRASEÑA (NUMERICA): ";
        cin >> pass;
        cout << "INGRESAR FECHA DE NACIMIENTO" << endl;
        fechaNacimiento.Cargar();
        this->setEdad(Edad());
        cout << "INGRESAR FECHA DE INGRESO" << endl;
        fechaIngreso.Cargar();
        grabarEnDisco();
        cout << "EMPLEADO REGISTRADO CON EXITO" << endl;
    }
    void Mostrar(){
        cout << setw(6) << idEmpleado;
        cout << setw(10) << dniEmpleado;
        cout << setw(10) << sueldoEmpleado;
        cout << setw(11) << tipoEmpleado;
        cout << setw(7) << pass;
        cout << setw(7) << edad;
        cout << setw(2) << this->getFechaNacimiento().getDia() << "/";
        cout << setw(2) << this->getFechaNacimiento().getMes() << "/";
        cout << setw(8) << this->getFechaNacimiento().getAnio();
        cout << setw(2) << this->getFechaIngreso().getDia() << "/";
        cout << setw(2) << this->getFechaIngreso().getMes() << "/";
        cout << setw(4) << this->getFechaIngreso().getAnio();
    }
    int grabarEnDisco(){
        FILE *pVen;
        pVen=fopen("vendedores.dat","ab");
        if(pVen==NULL){
            cout << "NO SE PUDO ABRIR EL ARCHIVO" << endl;
            return 0;
        }
        int escribio=fwrite(this,sizeof(Empleado),1,pVen);
        fclose(pVen);
        return escribio;
    }
    int leerDeDisco(int pos){
        FILE *pVen;
        pVen=fopen("vendedores.dat","rb");
        if(pVen==NULL){
            cout << "NO SE PUDO ABRIR EL ARCHIVO" << endl;
            return 0;
        }
        fseek(pVen,pos*sizeof(Empleado),0);
        int leyo=fread(this,sizeof(Empleado),1,pVen);
        fclose(pVen);
        return leyo;
    }
    int modificarEnDisco(int pos){
        FILE *p;
        p=fopen("vendedores.dat","rb+");
        if(p==NULL){
            return -1;
        }
        fseek(p,sizeof(Empleado)*pos,0);
        int leyo=fwrite(this,sizeof(Empleado),1,p);
        fclose(p);
        return leyo;
    }
    int Edad(){
        int e;
        time_t rawtime;
        struct tm * timeinfo;
        time (&rawtime);
        timeinfo = localtime (&rawtime);
        e=(timeinfo->tm_year+1900)-(this->getFechaNacimiento().getAnio());
        if(timeinfo->tm_mon+1<this->getFechaNacimiento().getMes()){
            e=e-1;
            this->setEdad(e);
            return e;
        }
        if(timeinfo->tm_mon+1==this->getFechaNacimiento().getMes()){
            if(timeinfo->tm_mday<this->getFechaNacimiento().getDia()){
                e=e-1;
                this->setEdad(e);
                return e;
            }
        }
        this->setEdad(e);
        return e;
    }
    int contarEmpleados(){
        FILE *pVen;
        pVen=fopen("vendedores.dat","rb");
        if(pVen==NULL){
            return 0;
        }
        int bytes, cantRegistros;
        fseek(pVen,0,SEEK_END);
        bytes=ftell(pVen);
        fclose(pVen);
        cantRegistros=bytes/sizeof(Empleado)+1;
        return cantRegistros;
    }
    bool leerDeBU(int pos){
        FILE *pCol;
        bool leyo;
        pCol=fopen("vendedores.bkp", "rb");
        if(pCol==NULL){
            return false;
        }
        fseek(pCol,pos*sizeof*this, 0);
        leyo=fread(this, sizeof*this, 1, pCol);
        fclose(pCol);
        return leyo;
    }
    ///sets
    void setIdEmpleado(int id){idEmpleado=id;}
    void setDniEmpleado(int dni){dniEmpleado=dni;}
    void setSueldoEmpleado(float sueldo){sueldoEmpleado=sueldo;}
    void setFechaNacimiento(Fecha fn){fechaNacimiento=fn;}
    void setEdad(int e){edad=e;}
    void setFechaIngreso(Fecha fi){fechaIngreso=fi;}
    void setTipoEmpleado(int tipo){tipoEmpleado=tipo;}
    void setPass(int p){pass=p;}
    ///gets
    int getIdEmpleado(){return idEmpleado;}
    int getDniEmpleado(){return dniEmpleado;}
    float getSueldoEmpleado(){return sueldoEmpleado;}
    Fecha getFechaNacimiento(){return fechaNacimiento;}
    int getEdad(){return edad;}
    Fecha getFechaIngreso(){return fechaIngreso;}
    int getTipoEmpleado(){return tipoEmpleado;}
    int getPass(){return pass;}
};

#endif // EMPLEADO_H_INCLUDED
