#ifndef CLIENTES_H_INCLUDED
#define CLIENTES_H_INCLUDED
#include "Usuarios.h"

int menuClientes();
int verificarIDCliente(int);
int verificarDNICliente(int);

class Clientes {
private:
    int _idCliente;
	int _dniCliente;
	char _nombreCliente[30];
	char _apellidoCliente[30];
	float _saldoCuenta;
	char _email[30];
	char _telefono[30];
	bool _estado;

public:
	// INICIO SETS
	void setDniCliente(int dni){_dniCliente=dni;}
	void setIdCliente(int id){_idCliente = id;}
	void setNombreCliente(char *nombre){strcpy(_nombreCliente,nombre);}
	void setApellidoCliente(char *apellido){strcpy(_apellidoCliente,apellido);}
	void setSaldoCuenta(float saldo){_saldoCuenta = saldo;}
	void setEmail(char* email){strcpy(_email, email);}
	void setTelfono(char* telefono){strcpy(_telefono, telefono);}
	void setEstado(bool est){_estado=est;}
	//INICIO GETS
	int getDniCliente(){return _dniCliente;}
	int getIdCliente(){return _idCliente;}
	char *getNombreCliente(){return _nombreCliente;}
	char *getApellidoCliente(){return _apellidoCliente;}
	float getSaldo(){return _saldoCuenta;}
	char* getEmail(){return _email;}
	char* getTelefono(){return _telefono;}
	bool getEstado(){return _estado;}

	void Cargar() {
	    cout << "INGRESAR ID CLIENTE: ";
        cin >> _idCliente;
        if(verificarIDCliente(_idCliente)!=-1){
            cout << "ID YA EXISTENTE" << endl;
            return;
	    }
		cout << "INGRESAR DNI DEL CLIENTE: ";
        cin >> _dniCliente;
        if(verificarDNICliente(_dniCliente)!=-1){
            cout << "DNI YA EXISTENTE" << endl;
            return;
        }
        cout << "INGRESAR SALDO DE CUENTA: ";
        cin >> _saldoCuenta;
        cout << "INGRESAR MAIL: ";
        cin >> _email;
        cout << "INGRESAR TELEFONO: ";
        cin >> _telefono;
	}
	void Mostrar() {
	    cout << setw(6) << _idCliente;
		cout << setw(10) << _dniCliente;
		cout << setw(12) << _saldoCuenta;
		cout << setw(25) << _email;
		cout << setw(15) << _telefono;
	}
	int grabarEnDisco() {
		FILE *pCliente;
		pCliente = fopen("clientes.dat", "ab");
		if (pCliente == NULL) {
			cout << "NO SE PUDO ABRIR EL ARCHIVO" << endl;
			return 0;
		}
		int leyo = fwrite(this, sizeof(Clientes), 1, pCliente);
		fclose(pCliente);
		return leyo;
	}
	int leerDeDisco(int pos) {
		FILE *pCliente;
		pCliente = fopen("clientes.dat", "rb");
		if (pCliente == NULL) {
			cout << "NO SE PUDO ABRIR EL ARCHIVO" << endl;
			return 0;
		}
		fseek(pCliente, pos * sizeof(Clientes), 0);
		int leyo = fread(this, sizeof(Clientes), 1, pCliente);
		fclose(pCliente);
		return leyo;
	}

	int contarClientes() {
		FILE* pClientes;
		pClientes = fopen("clientes.dat", "rb");
		if (pClientes == NULL) {
			return -1;
		}
		int bytes, cantRegistros;
		fseek(pClientes, 0, SEEK_END);
		bytes = ftell(pClientes);
		fclose(pClientes);
		cantRegistros = bytes / sizeof(Clientes) + 1;
		return cantRegistros;
	}

	bool buscarIdCliente(int idCliente) {
		int p=0;
		while (leerDeDisco(p++)) {
			if (idCliente == getIdCliente()){
				return true;
			}
		}
		return false;
	}
};

#endif //CLIENTES_H_INCLUDED
