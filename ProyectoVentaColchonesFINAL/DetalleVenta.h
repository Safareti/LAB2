#ifndef DETALLEVENTA_H_INCLUDED
#define DETALLEVENTA_H_INCLUDED

#include "Colchon.h"
#include "fecha.h"

int menuDetalleVenta();

class DetalleVenta {
private:
    int _idFactura;
    int _idCliente;
    int _idEmpleado;
    Fecha _fecha;
    int _cantidad;
    int _importe;
public:
    /// SETS
    void setIDfactura (int IDfactura){_idFactura = IDfactura;}
    void setIDcliente(int IDcliente){_idCliente = IDcliente;}
    void setIDempleado(int idEmpleado){_idEmpleado = idEmpleado;}
    void setfecha(Fecha fecha){_fecha = fecha;}
    void setCantidad (int Cantidad) {_cantidad = Cantidad;}
    void setImporte (int Importe){_importe = Importe;}

    /// GETS
    int getIDfactura (){return _idFactura;}
    int getIDcliente(){return _idCliente;}
    int getIDEmpleado(){return _idEmpleado;}
    Fecha getFecha (){return _fecha;}
    int getCantidad (){return _cantidad;}
    int getImporte (){return _importe;}

    void Mostrar(){
        cout << setw(10) << _idFactura;
        cout << setw(10) << _idCliente;
        cout << setw(10) << _idEmpleado;
        cout << setw(2) << this->getFecha().getDia() << "/";
        cout << setw(2) << this->getFecha().getMes() << "/";
        cout << setw(8) << this->getFecha().getAnio();
        cout << setw(14) << _cantidad;
        cout << setw(15) << _importe;
    }

    bool grabarDisco(){
        FILE *pVenta;
        pVenta=fopen("detalleventa.dat","ab");
        if(pVenta==NULL){
            cout << "NO SE PUDO ABRIR EL ARCHIVO" << endl;
            return 0;
        }
        bool escribio=fwrite(this,sizeof(DetalleVenta),1,pVenta);
        fclose(pVenta);
        return escribio;
    };

    bool leerDisco(int pos){
        FILE *pVenta;
        pVenta=fopen("detalleventa.dat","rb");
        if(pVenta==NULL){
            cout << "NO SE PUDO ABRIR EL ARCHIVO" << endl;
            return 0;
        }
        fseek(pVenta,pos*sizeof(DetalleVenta),0);
        int leyo=fread(this,sizeof(DetalleVenta),1,pVenta);
        fclose(pVenta);
        return leyo;
    }
    int contarVenta(){
		FILE* pVenta;
		pVenta = fopen("detalleventa.dat", "rb");
		if (pVenta == NULL) {
			return 0;
		}
		int bytes, cantRegistros;
		fseek(pVenta, 0, SEEK_END);
		bytes = ftell(pVenta);
		fclose(pVenta);
		cantRegistros = bytes / sizeof(DetalleVenta) + 1;
		return cantRegistros;
	}
};

#endif // DETALLEVENTA_H_INCLUDED
