#ifndef CLASSAUTO_H_INCLUDED
#define CLASSAUTO_H_INCLUDED


void cargarCadena();


bool verificarPateneteIngresada(char *pateneteIngresada);

void actulizarKm(int kmR,const char * patente);





void cargarCadena(char *pal, int tam)
{
    int i;
    fflush(stdin);
    for(i=0; i<tam; i++)
    {
        pal[i]=cin.get();
        if(pal[i]=='\n') break;
    }
    pal[i]='\0';
    fflush(stdin);
}

class Auto
{
private:
    char patente[10];
    int km;
public:
    Auto()
    {
        strcpy(patente,"NodDisponible");
        km=0;
    }
    bool cargarAuto()
    {
        cout<<"ingrese la Patente del vehiculo"<<endl;
        cargarCadena(patente,sizeof(patente));
        if(verificarPateneteIngresada(patente)==true)
        {

            return 0 ;

        }
        else
        {
            cout<<"patente no registrada desea registrarla"<<endl;

            int x;
            cout<<"ingrese 1 para registrar y guardar el registro"<<endl;
            cin>>x;

            system("cls");
            if(x==1)
            {
                cout<<"patenete: "<<patente<<endl;
                cout<<"ingrese km del automovil "<<endl;
                cin>>km;
                return 1;
            } else{return 0;}
        }

    }




    void mostrarAuto()
    {
        cout<<"Patente: " <<patente<<endl;
        cout<<"kilometraje: "<<km<<endl<<endl;
    }

    void setPatente(const char *p)
    {
        strcpy(patente,p);
    }
    void setKm(int k)
    {
        km=k;
    }
    const char *getPatente()
    {
        return patente;
    }
    int getkm()
    {
        return km;
    }

    bool leerDeDisco(int pos)  //pos es la posición que ocupa el registro en el archivo, empezando por 0
    {
        FILE *p;
        p=fopen("Autos.dat","rb");
        if(p==NULL) return false;
        fseek(p, pos * sizeof (Auto), 0); ///sizeof (Auto) es el tamaño en bytes de un objeto Empresa en memoria
        bool leyo = fread(this, sizeof (Auto), 1, p);
        fclose(p);
        return leyo;
    }

    bool grabarEnDisco()
    {
        FILE *p;
        p=fopen("Autos.dat","ab");
        if(p==NULL) return false;
        bool escribio = fwrite(this, sizeof (Auto), 1, p);
        fclose(p);
        return escribio;
    }
    bool modificarEnDisco(int pos)
    {
        FILE *p;
        p=fopen("Autos.dat","rb+");
        if(p==NULL) return false;
        fseek(p, pos * sizeof(Auto), 0);
        bool escribio=fwrite(this, sizeof (Auto), 1, p);
        fclose(p);
        return escribio;

    }
};


void actulizarKm(int kmR, const char *patente){

Auto obj;
int pos=0;
while (obj.leerDeDisco(pos)==1){
    if(strcmp(obj.getPatente(),patente)==0){
        obj.setKm(obj.getkm()+kmR);
        obj.modificarEnDisco(pos);
    }
    pos++;
}
}

int obtenerKm(const char *patente){

Auto obj;
int pos=0;
while (obj.leerDeDisco(pos)==1){
    if(strcmp(obj.getPatente(),patente)==0){
     return obj.getkm();
    }
    pos++;
}
}



bool verificarPateneteIngresada(char *pateneteIngresada)
{

    Auto reg;
    int pos=0;

    while (reg.leerDeDisco(pos)==1)
    {

        if(strcmp(pateneteIngresada,reg.getPatente())==0)
        {

            cout<<"Patente Registrada"<<endl<<endl;
            system("pause");

            return true;

        }
        pos++;
    }

    return false;
}


void menuAutos()
{

    while(true)
    {

        system("cls");
        cout<<"MENU AUTO"<<endl;
        cout<<"1- REGISTRAR NUEVO AUTO"<<endl;
        cout<<"2- MOSTRAR TODOS LOS AUTOS REGISTRADOS"<<endl;
        cout<<"3- ATRAS"<<endl;
        cout<<"seleccione una opcion"<<endl;
        int opc;
        cin>>opc;
        system("cls");
        switch(opc)
        {
        case 1:
        {
            Auto reg;
            if(reg.cargarAuto()==true){
            reg.grabarEnDisco();
            cout<<"registro exitoso la patente: "<<reg.getPatente()<<" se cargo en el sistema"<<endl;
            system("pause");}
        }

        break;
        case 2:
        {
            Auto reg;
            int pos=0;
            while (reg.leerDeDisco(pos)==1)
            {
                reg.mostrarAuto();
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


#endif // CLASSAUTO_H_INCLUDED
