#ifndef FECHA_H_INCLUDED
#define FECHA_H_INCLUDED

#include <iostream>
using namespace std;

int validarFecha(int,int,int);

class Fecha{
private:
    int dia, mes, anio;
public:
    void Cargar(){
        cout << "INGRESA EL DIA: ";
        cin >> dia;
        cout << "INGRESA EL MES: ";
        cin >> mes;
        cout << "INGRESA EL ANIO: ";
        cin >> anio;
        while(validarFecha(dia,mes,anio)==0){
            cout << "INGRESA EL DIA: ";
            cin >> dia;
            cout << "INGRESA EL MES: ";
            cin >> mes;
            cout << "INGRESA EL ANIO: ";
            cin >> anio;
        }
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
