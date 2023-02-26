#ifndef CLASSREGISTRO_H_INCLUDED
#define CLASSREGISTRO_H_INCLUDED
#include <sstream>
#include <ctime>
#include "classAuto.h"



using namespace std;





int diasTranscurridos(int dia, int mes, int anio) {
    int dias = 0;
    int meses[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    for (int i = 0; i < mes - 1; i++) {
        dias += meses[i];
    }
    dias += dia;
    if (mes > 2) {
        if ((anio % 4 == 0 && anio % 100 != 0) || anio % 400 == 0) {
            dias++;
        }
    }
    dias += (anio - 1) * 365;
    return dias;
}

int  AsignarIdPorPatente(const char *patenete);

class fecha{

private:
    int dia,mes,anio;

public:

    fecha(){
       time_t t = time(NULL);
        tm timeinfo;
        localtime_s(&timeinfo, &t);
        dia=timeinfo.tm_mday;
        mes=timeinfo.tm_mon+1;
        anio=timeinfo.tm_year+1900;}

    void cargar(){
    cout<<"ingrese dia: "<<endl;
    cin>>dia;
 cout<<"ingrese mes: "<<endl;
    cin>>dia;
    cout<<"ingrese anio: "<<endl;
    cin>>dia;
    }

    void mostrar(){
    cout<<dia<<"/"<<mes<<"/"<<anio<<endl;
    }
    void setDia(int d){dia=d;}
    void setMes(int d){mes=d;}
    void setAnio(int d){anio=d;}
    int getDia(){return dia;}
    int getMes(){return mes;}
    int getAnio(){return anio;}


};


class registroD
{
private:
    int id;
    char patente[10];
    char nombre[60];
    int kmR;
    int ganancia;
    int gasto;
 fecha FechaActual;

public:

    registroD(){
    id=0;
    strcpy(patente,"noDisp");
    kmR=0;
    ganancia=0;
    gasto=0;


    }

    bool cargarRegistro()
    {
    cout<<"ingrese la Patente del vehiculo"<<endl;
        cargarCadena(patente,sizeof(patente));
       if (verificarPateneteIngresada(patente)==true){
        cout<<"Descripcion del registro: "<<endl;
        cargarCadena(nombre,sizeof(nombre));
        id=AsignarIdPorPatente(patente);
        cout<<"ingrese km actual del automovil "<<endl;
        int kmaux;
        cin>>kmaux;
        Auto reg;
        kmR= kmaux- obtenerKm(patente);
        actulizarKm(kmR,patente);
        cout<<"kilometros recoridos: "<<kmR<<endl;
        cout<<"ingrese la ganancia obtenida: "<<endl;
        cin>>ganancia;
        cout<<"ingrese los gastos"<<endl;
        cin>>gasto;
         return true;} else {cout<<"la patente no se encuentra registrada por favor verifique"<<endl; system("pause");  return false;}
    }

    void mostrarRegistro()
    {
        FechaActual.mostrar();
        cout<<"Registro N: "<<id<<endl;
        cout<<"Descripcion: " <<nombre<<endl;
        cout<<"kilometros recoridos: "<<kmR<<endl;
        cout<<"Ganancia: "<<ganancia<<endl;
        cout<<"Gastos: "<<gasto<<endl<<endl;

    }
   void setPatente(const char *p){strcpy(patente,p);}
    const char *getPatente(){return patente;}

    void setnombre(const char *p)
    {
        strcpy(nombre,p);
    }
    void setKm(int k)
    {
        kmR=k;
    }
     void setid(int k)
    {
        id=k;
    }
    const char *getnombre()
    {
        return nombre;
    }
    int getkmR()
    {
        return kmR;
    }

    int getId(){return id;}
    int getGanancia(){return ganancia;}
    int getGastos(){return gasto;}

    fecha getFechaActual(){return FechaActual;}

  bool leerDeDisco(int pos){ //pos es la posición que ocupa el registro en el archivo, empezando por 0
    FILE *p;
    p=fopen("Registro.dat","rb");
    if(p==NULL) return false;
    fseek(p, pos * sizeof (registroD), 0); ///sizeof (Auto) es el tamaño en bytes de un objeto Empresa en memoria
    bool leyo = fread(this, sizeof (registroD), 1, p);
    fclose(p);
    return leyo;

}
bool grabarEnDisco(){
    FILE *p;
    p=fopen("Registro.dat","ab");
    if(p==NULL) return false;
    bool escribio = fwrite(this, sizeof (registroD), 1, p);
    fclose(p);
    return escribio;
}

bool modificarEnDisco(int pos){
    FILE *p;
    p=fopen("Registro.dat","rb+");
    if(p==NULL) return false;
    fseek(p, pos * sizeof(registroD), 0);
    bool escribio=fwrite(this, sizeof (registroD), 1, p);
    fclose(p);
    return escribio;
}
};


int  AsignarIdPorPatente(const char * patenete ){
registroD reg;
int pos=0,cont=0;
  while (reg.leerDeDisco(pos)==1){
    if(strcmp(reg.getPatente(),patenete)==0){
      cont++;
    }
pos++;
  }
  return cont +1;
}


void menuRegistro(){
while(true){
system("cls");
    cout<<"MENU REGISTRO ACTIVIDAD"<<endl;
    cout<<"1- REGISTRAR ACTIVIDAD"<<endl;
    cout<<"2- MOSTRAR TODOS LOS REGISTROS POR PATENTE"<<endl;
    cout<<"3- SALIR PROGRAMA"<<endl;
    cout<<"SELECCIONE UNA OPCION"<<endl;
    int opc;
    cin>>opc;
     system("cls");
     switch(opc){
     case 1:{
         registroD obj;
         if (obj.cargarRegistro()==true){
            obj.grabarEnDisco();
            cout<<"registro exitoso"<<endl;
            system("pause");
         }
         else{ return;}
         }

        break;
     case 2:{
         registroD reg;
         int pos=0;
         char c[10];
         cout<<"ingrese el numero de patenete"<<endl;
        cargarCadena(c,10);


         while (reg.leerDeDisco(pos)==1){

               if(strcmp(reg.getPatente(),c)==0) {

            reg.mostrarRegistro();}
            pos++;
         }
         system("pause");
         }
        break;
     case 3:
        return  ;
     }


}




}

void menuGananciasGastos(){

while(true)
    {
        system("cls");
        cout<<"MENU AUTO"<<endl;
        cout<<"1- RESUMEN DE GANANCIA POR FECHA"<<endl;
        cout<<"2- RESUMEN DE GASTOS POR FECHA"<<endl;
        cout<<"3- RESUMEN DE GANANCIA Y GASTOS TOTALES"<<endl;
        cout<<"4- salir programa"<<endl;
        cout<<"seleccione una opcion"<<endl;
        int opc;
        cin>>opc;
        system("cls");
        switch(opc)
        {
        case 1:
       {
        registroD reg;
         int pos=0;
         char c[10];
         cout<<"ingrese el numero de patenete"<<endl;
        cargarCadena(c,10);
       if (verificarPateneteIngresada(c)==true){
        cout<<"ingrese fecha para el resumen de ganacias"<<endl;
        int d1,m1,a1;
        int d2,m2,a2;
cout<<"desde: "<<endl;
        cout<<"dia: ";cin>>d1;
        cout<<"mes: ";cin>>m1;
        cout<<"anio: ";cin>>a1;
cout<<"hasta: "<<endl;
        cout<<"dia: ";cin>>d2;
        cout<<"mes: ";cin>>m2;
        cout<<"anio: ";cin>>a2;
 int g=0;

         while (reg.leerDeDisco(pos)==1){
               if((strcmp(reg.getPatente(),c)==0)&&
                diasTranscurridos(reg.getFechaActual().getDia(),reg.getFechaActual().getMes(),reg.getFechaActual().getAnio())>= diasTranscurridos(d1,m1,a1) &&
                diasTranscurridos(reg.getFechaActual().getDia(),reg.getFechaActual().getMes(),reg.getFechaActual().getAnio())<= diasTranscurridos(d2,m2,a2))
                 {
            g+=reg.getGanancia();
            ;}
            pos++;
         }
         cout<<"gananacia del periodo: "<<g<<endl;
         system("pause");
       }
       else{
            cout<<"patente inexistente por favor verifique"<<endl;
            system("pause"); return;}
        }

        break;
        case 2:
        {
        registroD reg;
         int pos=0;
         char c[10];
         cout<<"ingrese el numero de patenete"<<endl;
        cargarCadena(c,10);
        cout<<"ingrese fecha para el resumen de gastos"<<endl;
        int d1,m1,a1;
        int d2,m2,a2;
cout<<"desde: "<<endl;
        cout<<"dia: ";cin>>d1;
        cout<<"mes: ";cin>>m1;
        cout<<"anio: ";cin>>a1;
cout<<"hasta: "<<endl;
        cout<<"dia: ";cin>>d2;
        cout<<"mes: ";cin>>m2;
        cout<<"anio: ";cin>>a2;
 int g=0;

         while (reg.leerDeDisco(pos)==1){
               if((strcmp(reg.getPatente(),c)==0)&&
                diasTranscurridos(reg.getFechaActual().getDia(),reg.getFechaActual().getMes(),reg.getFechaActual().getAnio())>= diasTranscurridos(d1,m1,a1) &&
                diasTranscurridos(reg.getFechaActual().getDia(),reg.getFechaActual().getMes(),reg.getFechaActual().getAnio())<= diasTranscurridos(d2,m2,a2))
                 {
            g+=reg.getGastos();
            ;}
            pos++;
         }
         cout<<"gastos del periodo: "<<g<<endl;

         system("pause");

        }
        break;
        case 3:
              break;
        case 4:
            return  ;

        }
    }












}





#endif // CLASSREGISTRO_H_INCLUDED
