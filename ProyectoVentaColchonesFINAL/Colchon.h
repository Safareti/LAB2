#ifndef COLCHON_H_INCLUDED
#define COLCHON_H_INCLUDED

int menuColchones();
int verificarIdMedida(int);
int verificarIdModelo(int);

class Colchon{
private:
    int _idColchon;
    int _stock;
    int _idMedida;
    float _precio;
    int _idModelo;
    bool _estado;
public:
    void setIdColchon(int idColchon){_idColchon = idColchon;}
    void setStock(int stock){_stock = stock;}
    void setMedida(int medida){_idMedida = medida;}
    void setPrecio(float precio){_precio = precio;}
    void setModeloColchon(int modelo){_idModelo = modelo;;}
    void setEstado(bool estado){_estado = estado;}

    int getIdColchon(){return _idColchon;}
    int getStock(){return _stock;}
    int getMedida(){return _idMedida;}
    float getPrecio(){return _precio;}
    int getModeloColchon(){return _idModelo;}
    bool getEstado(){return _estado;}

    void Cargar();
    void Mostrar();
    bool grabarEnDisco();
    bool leerDeDisco(int);
    bool modificarEnDisco(int pos){
        FILE *p;
        p=fopen("colchones.dat","rb+");
        if(p==NULL){
            cout << "NO SE PUDO ABRIR EL ARCHIVO" << endl;
            return false;
        }
        fseek(p,sizeof(Colchon)*pos,0);
        bool leyo=fwrite(this, sizeof(Colchon), 1, p);
        fclose(p);
        return leyo;
    }
    int contarColchones() {
		FILE* pColchon;
		pColchon = fopen("colchones.dat", "rb");
		if (pColchon == NULL) {
			return -1;
		}
		int bytes, cantRegistros;
		fseek(pColchon, 0, SEEK_END);
		bytes = ftell(pColchon);
		fclose(pColchon);
		cantRegistros = bytes / sizeof(Colchon) + 1;
		return cantRegistros;
	}
	bool leerDeBU(int pos){
        FILE *pCol;
        bool leyo;
        pCol=fopen("colchones.bkp", "rb");
        if(pCol==NULL){
            return false;
        }
        fseek(pCol,pos*sizeof*this, 0);
        leyo=fread(this, sizeof*this, 1, pCol);
        fclose(pCol);
        return leyo;
    }
};

class Modelo{
private:
    int idModelo;
    char descripcion[30];
public:
    void Mostrar(){
        cout << "ID MODELO: " << idModelo << endl;
        cout << "DESCRIPCION: " << descripcion << endl;
    }
    void Cargar(){
        cout << "INGRESAR ID DE MODELO: ";
        cin >> idModelo;
        if(verificarIdModelo(idModelo)!=-1){
            cout << "ID MODELO YA EXISTENTE" << endl;
            return;
        }
        cout << "INGRESAR DESCRIPCION (SIN ESPACIOS): ";
        cin >> descripcion;
        grabarEnDisco();
        cout << "MODELO INGRESADO CON EXITO" << endl;
    }
    int grabarEnDisco() {
		FILE *pMod;
		pMod = fopen("modelos.dat", "ab");
		if (pMod == NULL) {
			cout << "NO SE PUDO ABRIR EL ARCHIVO" << endl;
			return 0;
		}
		int leyo = fwrite(this, sizeof(Modelo), 1, pMod);
		fclose(pMod);
		return leyo;
	}
	int leerDeDisco(int pos) {
		FILE *pMod;
		pMod = fopen("modelos.dat", "rb");
		if (pMod == NULL) {
			cout << "NO SE PUDO ABRIR EL ARCHIVO" << endl;
			return 0;
		}
		fseek(pMod, pos * sizeof(Modelo), 0);
		int leyo = fread(this, sizeof(Modelo), 1, pMod);
		fclose(pMod);
		return leyo;
	}
	bool modificarEnDisco(int pos){
        FILE *p;
        p=fopen("modelos.dat","rb+");
        if(p==NULL){
            cout << "NO SE PUDO ABRIR EL ARCHIVO" << endl;
            return false;
        }
        fseek(p,sizeof(Modelo)*pos,0);
        bool leyo=fwrite(this, sizeof(Modelo), 1, p);
        fclose(p);
        return leyo;
    }
	int contarModelos(){
        FILE *pMod;
        pMod=fopen("modelos.dat","rb");
        if(pMod==NULL){
            return -1;
        }
        int bytes, cantRegistros;
        fseek(pMod,0,SEEK_END);
        bytes=ftell(pMod);
        fclose(pMod);
        cantRegistros=bytes/sizeof(Modelo)+1;
        return cantRegistros;
    }
	///sets
	void setIdModelo(int id){idModelo=id;}
	void setDescripcion(const char *des){strcpy(descripcion,des);}
	///gets
	int getIdModelo(){return idModelo;}
	char *getDescripcion(){return descripcion;}
};

class Medida{
private:
    int idMedida;
    float ancho, alto, largo;
public:
    void Cargar(){
        cout << "INGRESAR ID DE MEDIDA: ";
        cin >> idMedida;
        if(verificarIdMedida(idMedida)!=-1){
            cout << "ID MEDIDA YA EXISTENTE" << endl;
            return;
        }
        cout << "IGNRESAR LARGO: ";
        cin >> largo;
        while (largo < 1) {
            cout << "INGRESE UN LARGO CORRECTO POR FAVOR: ";
            cin >> largo;
        }
        cout << "INGRESAR ANCHO: ";
        cin >> ancho;
        while (ancho < 1) {
            cout << "INGRESE UN ANCHO CORRECTO POR FAVOR: ";
            cin >> ancho;
        }
        cout << "INGRESAR ALTO: ";
        cin >> alto;
        while (alto < 1) {
            cout << "INGRESE UN ALTO CORRECTO POR FAVOR: ";
            cin >> alto;
        }
        grabarEnDisco();
        cout << "MEDIDA INGRESADA CON EXITO" << endl;
    }
    void Mostrar(){
        cout << "ID MEDIDA: " << idMedida << endl;
        cout << "LARGO: " << largo << endl;
        cout << "ANCHO: " << ancho << endl;
        cout << "ALTO: " << alto << endl;
    }
    int grabarEnDisco() {
		FILE *pMed;
		pMed = fopen("medidas.dat", "ab");
		if (pMed == NULL) {
			cout << "NO SE PUDO ABRIR EL ARCHIVO" << endl;
			return 0;
		}
		int leyo = fwrite(this, sizeof(Medida), 1, pMed);
		fclose(pMed);
		return leyo;
	}
	int leerDeDisco(int pos) {
		FILE *pMed;
		pMed = fopen("medidas.dat", "rb");
		if (pMed == NULL) {
			cout << "NO SE PUDO ABRIR EL ARCHIVO" << endl;
			return 0;
		}
		fseek(pMed, pos * sizeof(Medida), 0);
		int leyo = fread(this, sizeof(Medida), 1, pMed);
		fclose(pMed);
		return leyo;
	}
	int contarMedidas(){
        FILE *pMed;
        pMed=fopen("medidas.dat","rb");
        if(pMed==NULL){
            return -1;
        }
        int bytes, cantRegistros;
        fseek(pMed,0,SEEK_END);
        bytes=ftell(pMed);
        fclose(pMed);
        cantRegistros=bytes/sizeof(Medida)+1;
        return cantRegistros;
    }
	///sets
	void setIdMedida(int id){idMedida=id;}
	void setLargo(float _largo){largo=_largo;}
	void setAncho(float _ancho){ancho=_ancho;}
	void setAlto(float _alto){alto=_alto;}
	///gets
	int getIdMedida(){return idMedida;}
	float getLargo(){return largo;}
	float getAncho(){return ancho;}
	float getAlto(){return alto;}
};

#endif // COLCHON_H_INCLUDED
