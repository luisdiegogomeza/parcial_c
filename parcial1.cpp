#include <iostream>
#include <stdio.h>  
#include <string.h> 


using namespace std;
const char *nombe_archivo = "archivo.dat";

struct Trabajador{
	int codigo;
	char nombre[50];
	char apellido[50];
	float sueldo;
	int total;
	
};

 void ingresar_trabajador();
void abrir_trabajador();
 void modificar_trabajador();
char eliminar_trabajador(int codigo);
int main (){
	int codigo=0;
	abrir_trabajador();
 ingresar_trabajador();
	modificar_trabajador();
	cout<<"Ingrese el codigo del que desea eliminar: ";
	cin>>codigo;
  eliminar_trabajador(codigo);
	return 0;	
}
void buscar_codigo(){
	
	FILE* archivo = fopen(nombe_archivo, "rb");
	
	int indice=0,pos=0,cod=0;
	cout<<"BUSCAR CODIGO: ";
	cin>>cod;
	Trabajador trabajador;
	
	fread ( &trabajador, sizeof(trabajador), 1, archivo );
		
		do{
			
			if (trabajador.codigo == cod){
			pos = indice;
			}
	
		fread ( &trabajador, sizeof(Trabajador), 1, archivo );
		indice += 1;
		} while (feof( archivo ) == 0);
		
	cout<<"------------------ "<<pos<<" ------------------"<<endl;
	fseek ( archivo,pos * sizeof(Trabajador), SEEK_SET );

    fread ( &trabajador, sizeof( Trabajador ), 1, archivo );

    	cout << "Codigo: " << trabajador.codigo << endl;
        cout << "Nombre: " << trabajador.nombre << endl;
        cout << "Apellido: " << trabajador.apellido << endl;
        cout << "Sueldo (con bonificacion de Q.250.00) :" << trabajador.sueldo+250 << endl;
        cout << endl;
	
	fclose(archivo);
	system("PAUSE");
}


void buscar_indice(){
	FILE* archivo = fopen(nombe_archivo, "rb");
	
	int pos=0;
	cout<<"Que registro desea ver: ";
	cin>>pos;
	cout<<"------------------ "<<pos<<" ------------------"<<endl;
	fseek ( archivo,pos * sizeof(Trabajador), SEEK_SET );
	
	Trabajador trabajador;
	
    fread ( &trabajador, sizeof( Trabajador ), 1, archivo );

    	cout << "Codigo: " << trabajador.codigo << endl;
        cout << "Nombre: " << trabajador.nombre << endl;
        cout << "Apellido: " << trabajador.apellido << endl;
        cout << "Sueldo (con bonificacion de Q.250.00):  " << trabajador.sueldo+250 << endl;
        cout << endl;
	
	fclose(archivo);

	
}


void abrir_trabajador(){

	system("cls");
	FILE* archivo = fopen(nombe_archivo, "rb");
	if(!archivo) {
		archivo = fopen(nombe_archivo, "w+b");
	}
	Trabajador trabajador;
	int registro=0;
	fread ( &trabajador, sizeof(Trabajador), 1, archivo );
	cout<<"____"<<endl;
	cout << "id" <<"|"<< "CODIGO" <<"|"<< "NOMBRE"<<"| "<<"APELLIDO"<<"| "<<"SUELDO (con bonificacion de Q.250.00)"<<" "<<endl;	
		do{
		cout<<"____"<<endl;
		cout << registro <<" |  "<< trabajador.codigo <<" | "<< trabajador.nombre<<" |"<<trabajador.apellido<<"| "<<trabajador.sueldo+250<<endl;
        
        
	fread ( &trabajador, sizeof(Trabajador), 1, archivo );
		registro += 1;	
		} while (feof( archivo ) == 0);
		
    cout<<endl;
    
		fclose(archivo);
	}
void ingresar_trabajador(){
	
	char continuar;
	FILE* archivo = fopen(nombe_archivo, "ab"); // ab
	
	
		Trabajador trabajador;
		 string nombre,apellido;
		do{
			fflush(stdin);
			
		cout<<"Ingrese el Codigo:";
		cin>>trabajador.codigo;
        cin.ignore();
        
		cout<<"Ingrese el Nombre:";
		getline(cin,nombre);
    	strcpy(trabajador.nombre, nombre.c_str()); 
			
		cout<<"Ingrese el Apellido:";
		getline(cin,apellido);
		strcpy(trabajador.apellido, apellido.c_str()); 
		
		cout<<"Ingrese el sueldo:";
		cin>>trabajador.sueldo;
		cin.ignore();
		fwrite( &trabajador , sizeof(Trabajador), 1, archivo );
		
		
		cout<<"Desea Agregar otro Nombre s/n : ";
		cin>>continuar;
		} while((continuar=='s') || (continuar=='S') );
		
	
	fclose(archivo);
	abrir_trabajador();
	//buscar_indice();	
	buscar_codigo();
}
void modificar_trabajador(){
	
	FILE* archivo = fopen(nombe_archivo, "r+b");
	
		int id;
		string nombre,apellido;	
    	Trabajador trabajador;
    
		cout << "Ingrese el ID que desea Modificar: ";
    		cin >> id;
    		fseek ( archivo, id * sizeof(Trabajador), SEEK_SET );  
	
		cout<<"Ingrese el Codigo:";
		cin>>trabajador.codigo;
        cin.ignore();
        
		cout<<"Ingrese el Nombre:";
		getline(cin,nombre);
    	strcpy(trabajador.nombre, nombre.c_str()); 
			
		cout<<"Ingrese el Apellido:";
		getline(cin,apellido);
		strcpy(trabajador.apellido, apellido.c_str()); 
		
		cout<<"Ingrese el sueldo:";
		cin>>trabajador.sueldo;
		cin.ignore();
		
		fwrite( &trabajador, sizeof(Trabajador), 1, archivo );
		
	fclose(archivo);
	abrir_trabajador();
		system("PAUSE");
}


char eliminar_trabajador(int codigo)
{
	FILE *archivo;
	FILE *auxiliar;
	Trabajador trabajador;
	char elimina;
 
	
	archivo = fopen("archivo.dat", "r+b");	
	if (archivo == NULL) { 
		elimina = 0;
 
	} else {

		elimina = 0;
		fread(&trabajador, sizeof(trabajador), 1, archivo);
		while (!feof(archivo)) {
			if (codigo == codigo) {
				fseek(archivo, ftell(archivo) - sizeof(trabajador), SEEK_SET);
				
				fwrite(&trabajador, sizeof(trabajador), 1, archivo);
				elimina = 1;
				break;
			}
			fread(&trabajador, sizeof(trabajador), 1, archivo);
		}
 
	
		fclose(archivo);
	}
 
	return elimina;
}
