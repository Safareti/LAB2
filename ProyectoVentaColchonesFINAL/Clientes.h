#ifndef CLIENTES_H_INCLUDED
#define CLIENTES_H_INCLUDED
#include "Usuarios.h"

int menuClientes();
int verificarIDCliente(int);
int verificarDNICliente(int);
void modificarCliente(int,int);

class Clientes {
private:
    int _idCliente;
	int _dniCliente;
	char _nombreCliente[30];
	char _apellidoCliente[30];
	char _email[30];
	char _telefono[30];
	bool _estado;

public:
	// INICIO SETS
	void setDniCliente(int dni){_dniCliente=dni;}
	void setIdCliente(int id){_idCliente = id;}
	void setNombreCliente(char *nom){strcpy(_nombreCliente,nom);}
	void setApellidoCliente(char *ape){strcpy(_apellidoCliente,ape);}
	void setEmail(char* email){strcpy(_email, email);}
	void setTelfono(char* telefono){strcpy(_telefono, telefono);}
	void setEstado(bool est){_estado=est;}
	//INICIO GETS
	int getDniCliente(){return _dniCliente;}
	int getIdCliente(){return _idCliente;}
	char *getNombreCliente(){return _nombreCliente;}
	char *getApellidoCliente(){return _apellidoCliente;}
	char *getEmail(){return _email;}
	char *getTelefono(){return _telefono;}
	bool getEstado(){return _estado;}

	void Cargar() {
	    char registrar;
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
            cout << "DESEAS REGISTRARLO? ";
            cin >> registrar;
            if(registrar=='s'){
                modificarCliente(_dniCliente, _idCliente);
                return;
            }else{
                cout << "NO SE REGISTRO EL EMPLEADO" << endl;
                return;
            }
        }
        cout << "INGRESAR NOMBRE: ";
        cin >> _nombreCliente;
        cout << "INGRESAR APELLIDO: ";
        cin >> _apellidoCliente;
        cout << "INGRESAR MAIL: ";
        cin >> _email;
        cout << "INGRESAR TELEFONO: ";
        cin >> _telefono;
        _estado=true;
        grabarEnDisco();
		cout << "CLIENTE REGISTRADO CON EXITO" << endl;
	}
	void Mostrar() {
	    cout << setw(4) << _idCliente;
		cout << setw(10) << _dniCliente;
		cout << setw(11) << _nombreCliente;
		cout << setw(11) << _apellidoCliente;
		cout << setw(17) << _email;
		cout << setw(12) << _telefono;
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
			return 0;
		}
		fseek(pCliente, pos * sizeof(Clientes), 0);
		int leyo = fread(this, sizeof(Clientes), 1, pCliente);
		fclose(pCliente);
		return leyo;
	}
    bool modificarEnDisco(int pos){
        FILE *p;
        p=fopen("clientes.dat","rb+");
        if(p==NULL){
            cout << "NO SE PUDO ABRIR EL ARCHIVO" << endl;
            return false;
        }
        fseek(p,sizeof(Clientes)*pos,0);
        bool leyo=fwrite(this, sizeof(Clientes), 1, p);
        fclose(p);
        return leyo;
    }
	int contarClientes() {
		FILE* pClientes;
		pClientes = fopen("clientes.dat", "rb");
		if (pClientes == NULL) {
			return 1;
		}
		int bytes, cantRegistros;
		fseek(pClientes, 0, SEEK_END);
		bytes = ftell(pClientes);
		fclose(pClientes);
		cantRegistros = bytes / sizeof(Clientes) + 1;
		return cantRegistros;
	}
	bool leerDeBU(int pos){
        FILE *pCol;
        bool leyo;
        pCol=fopen("clientes.bkp", "rb");
        if(pCol==NULL){
            return false;
        }
        fseek(pCol,pos*sizeof*this, 0);
        leyo=fread(this, sizeof*this, 1, pCol);
        fclose(pCol);
        return leyo;
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
