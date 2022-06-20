#ifndef FECHA_H_INCLUDED
#define FECHA_H_INCLUDED

#include <iostream>
using namespace std;

class Fecha{
private:
    int dia, mes, anio;
public:
    void Cargar(){
        cout << "INGRESAR DIA: ";
        cin >> dia;
        cout << "INGRESAR MES: ";
        cin >> mes;
        cout << "INGRESAR ANIO: ";
        cin >> anio;
    }
    void Mostrar(){
        cout << dia << "/" << mes << "/" << anio;
    }
    ///sets
    void setDia(int d){dia=d;}
    void setMes(int m){mes=m;}
    void setAnio(int a){anio=a;}
    ///gets
    int getDia(){return dia;}
    int getMes(){return mes;}
    int getAnio(){return anio;}
};

#endif // FECHA_H_INCLUDED
