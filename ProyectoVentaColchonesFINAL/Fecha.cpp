#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <ctime>

using namespace std;

#include "fecha.h"

int fechaActual(int dia, int mes, int anio){
    int d, m, a;
    time_t rawtime;
    struct tm * timeinfo;
    time (&rawtime);
    timeinfo = localtime (&rawtime);
    a=timeinfo->tm_year+1900;
    m=timeinfo->tm_mon+1;
    d=timeinfo->tm_mday;
    if(anio>a){
        return 0;
    }
    if(anio==a){
        if(mes>m){
            return 0;
        }
        if(mes==m){
            if(dia>d){
                return 0;
            }
        }
    }
    return 1;
}

int fechaHoy(Fecha fecha) {
    int d, m, a;
    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    a = timeinfo->tm_year + 1900;
    m = timeinfo->tm_mon + 1;
    d = timeinfo->tm_mday;
    if (fecha.getAnio() == a && fecha.getMes() == m && fecha.getDia() == d) {
        return 0;
    }
    return 1;
}

int validarFecha(int dia, int mes, int anio){
    bool bisiesto = false;
    if(anio%4==0 && (anio%100!=100 || anio%400==0)){
        bisiesto = true;
    }
    if(fechaActual(dia,mes,anio)==0){
        cout << "FECHA NO VALIDA, INGRESE DE NUEVO" << endl;
        return 0;
    }
    if(dia>0 && dia<32 && mes>0 && mes<13 && anio>1900){
        if(mes==1 || mes==3 || mes==5 || mes==7 || mes==8 || mes==10 || mes==12){
            return 1;
        }
        else{
            if(mes==2 && dia<30 && bisiesto){
                return 1;
            }
            else if(mes==2 && dia<29 && !bisiesto){
                return 1;
            }
            else if(mes!=2 && dia<31){
                return 1;
            }
            else{
                cout << "FECHA NO VALIDA, INGRESE DE NUEVO" << endl;
                return 0;
            }
        }
    }else{
        cout << "FECHA NO VALIDA, INGRESE DE NUEVO" << endl;
        return 0;
    }
}
