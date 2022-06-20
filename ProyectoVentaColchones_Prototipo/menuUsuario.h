#ifndef MENUUSUARIO_H_INCLUDED
#define MENUUSUARIO_H_INCLUDED

int menuUsuarios();
void cargarUsuario();

class Usuario{
private:
    char nombreUsuario[30];
    char apellidoUsuario[30];
    int dniUsuario;
    bool estado;
public:
    void Cargar(){
        cout << "INGRESAR NOMBRE DE USUARIO: ";
        cin >> nombreUsuario;
        cout << "INGRESAR APELLIDO DE USUARIO: ";
        cin >> apellidoUsuario;
        estado=true;
    }
    void Mostrar(){
        cout << "DNI USUARIO: " << dniUsuario << endl;
        cout << "NOMBRE Y APELLIDO: " << nombreUsuario << " " << apellidoUsuario << endl;
    }
    int grabarEnDisco(){
        FILE *pUser;
        pUser=fopen("usuarios.dat","ab");
        if(pUser==NULL){
            cout << "NO SE PUDO ABRIR EL ARCHIVO" << endl;
            return 0;
        }
        int leyo=fwrite(this,sizeof(Usuario),1,pUser);
        fclose(pUser);
        return leyo;
    }
    int leerDeDisco(int pos){
        FILE *pUser;
        pUser=fopen("usuarios.dat","rb");
        if(pUser==NULL){
            cout << "NO SE PUDO ABRIR EL ARCHIVO" << endl;
            return 0;
        }
        fseek(pUser,pos*sizeof(Usuario),0);
        int leyo=fread(this,sizeof(Usuario),1,pUser);
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

#endif // MENUUSUARIO_H_INCLUDED
