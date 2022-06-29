#ifndef VENTA_H_INCLUDED
#define VENTA_H_INCLUDED
#include "Fecha.h"
#include "Colchon.h"

int menuVentas();

class Venta{
private:
    int _idFactura;
    int _idCliente;
    int _IdEmpleado;
    int _idColchon;
    float _precio;
    int _cantidad;
    Fecha _fecha;
    char _formaPago;
    float _importe;
public:
    void setIdFactura(int idFactura){_idFactura = idFactura;}
    void setIdCliente(int idCliente){_idCliente = idCliente;}
    void setIdEmpleado(int idEmpleado){_IdEmpleado = idEmpleado;}
    void setIdColchon(int idColchon){_idColchon=idColchon;}
    void setPrecio(float precio){_precio=precio;}
    void setCantidad(int cant){_cantidad=cant;}
    void setFecha(Fecha fec){_fecha = fec;}
    void setFormaPago(char formaPago){_formaPago=formaPago;}
    void setImporte(float imp){_importe=imp;}

    int getIdFactura(){return _idFactura;}
    int getIdCliente(){return _idCliente;}
    int getIdEmpleado(){return _IdEmpleado;}
    int getIdColchon(){return _idColchon;}
    float getPrecio(){return _precio;}
    int getCantidad(){return _cantidad;}
    Fecha getFecha(){return _fecha;}
    char getFormaPago(){return _formaPago;}
    float getImporte(){return _importe;}

    void Cargar();
    int seguirCargando();
    void Mostrar();
    bool grabarEnDisco();
    bool leerDeDisco(int);
    int contarVenta() {
		FILE* pVenta;
		pVenta = fopen("ventas.dat", "rb");
		if (pVenta == NULL) {
			return 1;
		}
		int bytes, cantRegistros;
		fseek(pVenta, 0, SEEK_END);
		bytes = ftell(pVenta);
		fclose(pVenta);
		cantRegistros = bytes / sizeof(Venta) + 1;
		return cantRegistros;
	}
};

#endif // VENTA_H_INCLUDED
