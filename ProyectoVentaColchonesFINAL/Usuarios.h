#ifndef USUARIOS_H_INCLUDED
#define USUARIOS_H_INCLUDED

using namespace std;
#include <iomanip>
#include <cstring>

int menuUsuarios();

class Usuario{
private:
    char nombreUsuario[30];
    char apellidoUsuario[30];
    int dniUsuario;
    bool estado;
public:
    void Mostrar(){
        cout << setw(12) << dniUsuario;
        cout << setw(12) << nombreUsuario;
        cout << setw(10) << apellidoUsuario << endl;
    }
    int grabarEnDisco(){
        FILE *pUser;
        pUser=fopen("usuarios.dat","ab");
        if(pUser==NULL){
            cout << "NO SE PUDO ABRIR EL ARCHIVO" << endl;
            return 0;
        }
        int escribio=fwrite(this,sizeof(Usuario),1,pUser);
        fclose(pUser);
        return escribio;
    }
    int leerDeDisco(int pos){
        FILE *pUser;
        pUser=fopen("usuarios.dat","rb");
        if(pUser==NULL){
            cout << "NO SE PUDO ABRIR EL ARCHIVO" << endl;
            return -1;
        }
        fseek(pUser,pos*sizeof(Usuario),0);
        int leyo=fread(this,sizeof(Usuario),1,pUser);
        fclose(pUser);
        return leyo;
    }
    int modificarEnDisco(int pos){
        FILE *pUser;
        pUser=fopen("usuarios.dat","rb+");
        if(pUser==NULL){
            cout << "NO SE PUDO ABRIR EL ARCHIVO" << endl;
            return -1;
        }
        fseek(pUser,pos*sizeof(Usuario),0);
        int leyo=fwrite(this,sizeof(Usuario),1,pUser);
        fclose(pUser);
        return leyo;
    }
    int contarUsuarios(){
        FILE *pUser;
        pUser=fopen("usuarios.dat","rb");
        if(pUser==NULL){
            return -1;
        }
        int bytes, cantRegistros;
        fseek(pUser,0,SEEK_END);
        bytes=ftell(pUser);
        fclose(pUser);
        cantRegistros=bytes/sizeof(Usuario)+1;
        return cantRegistros;
    }
    bool leerDeBU(int pos){
        FILE *pCol;
        bool leyo;
        pCol=fopen("usuarios.bkp", "rb");
        if(pCol==NULL){
            return false;
        }
        fseek(pCol,pos*sizeof*this, 0);
        leyo=fread(this, sizeof*this, 1, pCol);
        fclose(pCol);
        return leyo;
    }
    ///sets
    void setNombreUsuario(char *n){strcpy(nombreUsuario,n);}
    void setApellidoUsuario(char *a){strcpy(apellidoUsuario,a);}
    void setDniUsuario(int d){dniUsuario=d;}
    void setEstadoUsuario(bool est){estado=est;}
    ///gets
    char *getNombreUsuario(){return nombreUsuario;}
    char *getApellidoUsuario(){return apellidoUsuario;}
    int getDniUsuario(){return dniUsuario;}
    bool getEstadoUsuario(){return estado;}
};

#endif // USUARIOS_H_INCLUDED
