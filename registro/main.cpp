#include <iostream>
#include <vector>
#include <cstring>
#include <ctime>
using namespace std;
#include "classRegistro.h"
#include "classAuto.h"


int main()
{



while(true){




system("cls");
    cout<<"MENU"<<endl;
    cout<<"1- REGISTRAR AUTO"<<endl;
    cout<<"2- REGISTROS DE ACTIVIDADES"<<endl;
    cout<<"3- GANANCIAS Y GASTOS"<<endl;
    cout<<"4- SALIR PROGRAMA"<<endl;

    cout<<"seleccione una opcion"<<endl;
    int opc;
    cin>>opc;
     system("cls");
     switch(opc){
     case 1:{
     menuAutos();
         }
        break;
     case 2:{
         menuRegistro();

         }

        break;
     case 3:
         menuGananciasGastos();

        break;
         case 4:

        return false;
     }


}





    return 0;
}
