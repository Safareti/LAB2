#ifndef ADMINISTRADOR_H_INCLUDED
#define ADMINISTRADOR_H_INCLUDED

#include <ctime>
#include "fecha.h"
int menuAdministradores();

class Administrador{
private:
    int _dniAdmin;
    int _idAdmin;
    int _passAdmin;
    Fecha _fechaNac;
    int _edad;
    float _sueldo;
    Fecha _fechaIngreso;
public:
    void setDniAdmin(int dni){_dniAdmin=dni;}
    void setIdAdmin(int idAdmin){_idAdmin = idAdmin;}
    void setPassAdmin(int passAdmin){_passAdmin = passAdmin;}
    void setFechaNacimiento(Fecha fn){_fechaNac=fn;}
    void setEdad(int edad){_edad = edad;}
    void setSueldo(float s){_sueldo=s;}
    void setFechaIngreso(Fecha fi){_fechaIngreso=fi;}

    int getDniAdmin(){return _dniAdmin;}
    int getIdAdmin(){return _idAdmin;}
    int getPassAdmin(){return _passAdmin;}
    Fecha getFechaNacimiento(){return _fechaNac;}
    int getEdad(){return _edad;}
    float getSueldo(){return _sueldo;}
    Fecha getFechaIngreso(){return _fechaIngreso;}
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
    int contarAdministradores(){
        FILE *pVen;
        pVen=fopen("admin.dat","rb");
        if(pVen==NULL){
            return -1;
        }
        int bytes, cantRegistros;
        fseek(pVen,0,SEEK_END);
        bytes=ftell(pVen);
        fclose(pVen);
        cantRegistros=bytes/sizeof(Administrador)+1;
        return cantRegistros;
    }
    void Cargar();
    void Mostrar();
    bool grabarEnDisco();
    bool leerDeDisco(int);
};

#endif // ADMINISTRADOR_H_INCLUDED
