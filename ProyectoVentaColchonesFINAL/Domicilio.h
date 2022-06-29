#ifndef DOMICILIO_H_INCLUDED
#define DOMICILIO_H_INCLUDED

class Domicilio {
private:
    char _provincia [30];
    char _localidad [30];
    char _calle [30];
    int _numero;
    int _codigoPostal;
public:
    /// SETS
    void setProvincia (const char *Provincia){strcpy(_provincia, Provincia);}
    void setLocalidad(const char *Localidad){strcpy(_localidad, Localidad);}
    void setCalle(int Calle){_calle = Calle;}
    void setNumero(int Numero){_numero = Numero;}
    void setcodigoPostal (int codigoPostal) {_codigoPostal = codigoPostal;}

    /// GETS
    const char getProvincia(){return _provincia;}
    const char getLocalidad(){return _localidad;}
    const char getCalle (){return _calle;}
    int getNumero (){return _numero;}
    int getcodigoPostal (){return _codigoPostal;}



    void Cargar (){
        cout << "PROVINCIA: ";
        cin >> _provincia;
        cout << "LOCALIDAD: ";
        cin >> _localidad;
        cout << "CALLE: ";
        cin >> _calle;
        cout << "NUMERO: ";
        cin >> _numero;
        cout << "CODIGO POSTAL: ";
        cin >> _codigoPostal;
    }

    void Mostrar (){
        cout << "PROVINCIA: ";
        cout >> _provincia << endl;
        cout << "LOCALIDAD: ";
        cout >> _localidad << endl;
        cout << "CALLE: ";
        cout >> _calle << endl;
        cout << "NUMERO: ";
        cout >> _numero << endl;
        cout << "CODIGO POSTAL: ";
        cout >> _codigoPostal << endl;
    }

    }
    bool grabarDisco(){
        FILE *pDomicilio;
        pDomicilio=fopen("domicilios.dat","ab");
        if(pDomicilio==NULL){
            cout << "NO SE PUDO ABRIR EL ARCHIVO" << endl;
            return 0;
        }
        bool escribio=fwrite(this,sizeof(Domicilio),1,pDomicilio);
        fclose(pDomicilio);
        return escribio;
    };

    bool leerDisco(int pos){
        FILE *pDomicilio;
        pDomicilio=fopen("domicilios.dat","rb");
        if(pDomicilio==NULL){
            cout << "NO SE PUDO ABRIR EL ARCHIVO" << endl;
            return 0;
        }
        fseek(pVen,pos*sizeof(Domicilio),0);
        int leyo=fread(this,sizeof(Vendedor),1,pDomicilio);
        fclose(pDomicilio);
        return leyo;
    }
};

#endif // DOMICILIO_H_INCLUDED
