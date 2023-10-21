#include <iostream>
#include <cstdlib>
#include <limits>
#include <windows.h>
#include <math.h>
#include <string>
#include <ctime>
#include <vector>
#include <cctype>
using namespace std;
//Global
double CantidadGen = 0;
double CantidadAu = 0;
//Cola
class Cola{
    private:
        int ID;
        int Tiempo;
        string Nombre;
        int x;
        int y;
        Cola* Siguiente;
    public:
        bool Cola_Vacia(Cola *&);
        string getNombre(Cola *&);
        int getID(Cola *&);
        void Agregar(Cola *&, int ID_, string Nombre_);
        void Agregar(Cola *&, int ID_, int Tiempo_, string Nombre_);
        void Eliminar(Cola *&);
        void gotoxy(int x, int y);
        void Mostrar_monos(Cola *&);
        void Pantalla(Cola *&);
        void Entrada();
        void Banco();
        void setXY(int, int);
        int getX();
        int getY();
        void moverPersonasEnCola(Cola *&);
        void Mostrar_monos_desde_posicion(Cola *&, int);
        void PersonaDentro(Cola *&, int Elemento);
        void Mostrar_monos_columnas(Cola *&, int, int);
        void Fuera(Cola *&, int);
};
void Cola::setXY(int nueva_X, int nueva_Y){
    this->x = nueva_X;
    this->y = nueva_Y;
}
int Cola::getX(){
    return this->x;
}
int Cola::getY(){
    return this->y;
}
string Cola::getNombre(Cola *& Fila){
    if(Cola_Vacia(Fila) == false){
        return Fila->Nombre;
    }
}
int Cola::getID(Cola *& Fila){
    if(Cola_Vacia(Fila) == false){
        return Fila->ID;
    }
}
bool Cola::Cola_Vacia(Cola *&Fila){
    Cola *Temporal = Fila;
    if(Temporal == NULL){
        cout << "Vacio" << endl;
        Sleep(1000);
        return true;
    }else{
        return false;
    }
}
void Cola::Agregar(Cola*& Fila, int ID_, string Nombre_){
    Cola* Temporal = new Cola();
    Temporal->ID = ID_;
    Temporal->Nombre = Nombre_;
    Temporal->Siguiente = NULL;
    if (Fila == NULL) {
        Fila = Temporal;
    }else{
        Cola* Ultimo = Fila;
        while (Ultimo->Siguiente != NULL){
            Ultimo = Ultimo->Siguiente;
        }
        Ultimo->Siguiente = Temporal;
    }
}
void Cola::Agregar(Cola*& Fila, int ID_, int Tiempo_, string Nombre_){
    Cola* Temporal = new Cola();
    Temporal->ID = ID_;
    Temporal->Tiempo = Tiempo_;
    Temporal->Nombre = Nombre_;
    Temporal->Siguiente = NULL;
    if (Fila == NULL) {
        Fila = Temporal;
    }else{
        Cola* Ultimo = Fila;
        while (Ultimo->Siguiente != NULL){
            Ultimo = Ultimo->Siguiente;
        }
        Ultimo->Siguiente = Temporal;
    }
}
void Cola::Eliminar(Cola*& Fila) {
    if (!Cola_Vacia(Fila)) {
        Cola* Temporal = Fila;
        Fila = Fila->Siguiente;
        delete Temporal;
    }
}
void Cola::gotoxy(int x, int y){
    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hcon, dwPos);
}
void Cola::Mostrar_monos(Cola *&Fila){
    int x = 39;
    int contador = 0;
    int mov = 0;
    if (!Cola_Vacia(Fila)) {
        Cola *actual = Fila;
        while (actual != NULL && contador < 10) {
            gotoxy(x, 10);
            cout << " O ";
            gotoxy(x, 11);
            printf("%c%c%c",47, 124, 92);
            gotoxy(x, 12);
            printf("%c %c",47, 92);
            x -= 4;
            actual = actual->Siguiente;
            contador++;
        }
    }
}
void Cola::Mostrar_monos_desde_posicion(Cola *&Fila, int posicion_inicial){
    int x = 39;
    int contador = 0;
    if (!Cola_Vacia(Fila)) {
        Cola *actual = Fila;
        while (actual != NULL) {
            if (contador >= posicion_inicial && contador < 10){
                gotoxy(x, 10);
                cout << " O ";
                gotoxy(x, 11);
                printf("%c%c%c", 47, 124, 92);
                gotoxy(x, 12);
                printf("%c %c", 47, 92);
            }
            x -= 4;
            actual = actual->Siguiente;
            contador++;
        }
    }
}
void Cola::Pantalla(Cola *&Fila){
    int x = 0, y = 0;
    gotoxy(x,y);
    printf("%c", 218);
    x ++;
    //Techo y suelo
    for(int j = 0; j < 32; j++){
        gotoxy(x,y);
        printf("%c", 196);
        gotoxy(x,8);
        printf("%c", 196);
        x ++;
    }
    y += 8;
    gotoxy(x,y);
    printf("%c", 217);
    y --;
    //Paredes
    for(int h = 0; h < 6; h++){
        gotoxy(x, y);
        printf("%c", 179);
        gotoxy(0, y);
        printf("%c", 179);
        gotoxy(5, y);
        printf("%c", 179);
        gotoxy(24, y);
        printf("%c", 179);
        y --;
    }
    gotoxy(x,y);
    printf("%c", 180);
    x --;
    //TITULO
    for(int l = 0; l < 31; l++){
        gotoxy(x,y);
        printf("%c", 196);
        x --;
    }
    x += 32;
    y --;
    gotoxy(x,y);
    printf("%c", 191);
    //Goto manual
    gotoxy(0,1);
    printf("%c", 195);
    gotoxy(0,8);
    printf("%c", 192);
    gotoxy(5,1);
    printf("%c", 197);
    gotoxy(24,1);
    printf("%c", 197);
    gotoxy(5,8);
    printf("%c", 193);
    gotoxy(24,8);
    printf("%c", 193);
    gotoxy(5,0);
    printf("%c", 194);
    gotoxy(24,0);
    printf("%c", 194);
    //Titulos
    gotoxy(2,1);
    cout << "ID";
    gotoxy(12,1);
    cout << "NOMBRE";
    gotoxy(26,1);
    cout << "Tiempo";
    int contador = 0;
    Cola* actual = Fila;
    while(actual != NULL && contador < 6){
        gotoxy(1, 2 + contador);
        cout << actual->ID;
        gotoxy(9, 2 + contador);
        cout << actual->Nombre;
        gotoxy(28, 2 + contador);
        cout << actual->Tiempo;
        contador++;
        actual = actual->Siguiente;
    }
}
void Cola::Entrada(){
    gotoxy(50, 20);
    printf("%c%c%c%c%c%c%c%c%c%c%c", 200, 205, 205, 205, 205, 205, 205, 205, 205, 205,188);
}
void Cola::Banco(){
    int Contador = 0;
    gotoxy(15,15);
    printf("%c%c%c%c%c%c%c%c%c%c%c", 201, 205, 205, 205, 205, 205, 205, 205, 205, 205,187);
    //ATM
    for(int j = 0; j < 5; j++){
        for(int i = 0; i < 20; i++){
            gotoxy(40 + Contador, 1 + i);
            printf("%c", 186);
            gotoxy(50 + Contador, 1 + i);
            printf("%c", 186);
        }
        gotoxy(40 + Contador, 0);
        printf("%c%c%c%c%c%c%c%c%c%c%c", 201, 196, 196, 196, 196, 196, 196, 196, 196, 196, 187);
        gotoxy(40 + Contador, 4);
        printf("%c%c%c%c%c%c%c%c%c%c%c", 204, 196, 196, 196, 196, 196, 196, 196, 196, 196, 185);
        gotoxy(47 + Contador, 1);
        cout << "O";
        gotoxy(46 + Contador, 2);
        printf("%c%c%c", 47, 179, 92);
        gotoxy(46 + Contador, 3);
        printf("%c %c", 47, 92);
        gotoxy(43 + Contador, 1);
        cout << "O";
        gotoxy(42 + Contador, 2);
        printf("%c%c%c", 47, 179, 92);
        gotoxy(42 + Contador, 3);
        printf("%c %c", 47, 92);
        Contador += 11;
    }
    gotoxy(44, 0);
    cout << "ATM";
    gotoxy(54, 0);
    cout << "Caja1";
    gotoxy(65, 0);
    cout << "Caja2";
    gotoxy(76, 0);
    cout << "Caja3";
    gotoxy(85, 0);
    cout << "Gerencia";
}
void Cola::moverPersonasEnCola(Cola *&Fila) {
    if(Cola_Vacia(Fila) == false){
        int x = 39;
        int y = 10;
        Cola *actual = Fila;
        int contador = 0;
        int conty = 0;
        Entrada();
        Mostrar_monos(Fila);
        Sleep(200);
        for (int m = 0; m < 15; m++){
            system("cls");
            Entrada();
            Mostrar_monos_desde_posicion(Fila, 1);
            if (contador % 2 == 0) {
                gotoxy(x + contador, y);
                cout << " O ";
                gotoxy(x + contador, 11);
                printf("%c%c%c", 47, 124, 92);
                gotoxy(x + contador, 12);
                printf("%c %c", 47, 92);
            } else {
                gotoxy(x + contador, y + conty);
                cout << " O ";
                gotoxy(x + contador, y + 1 + conty);
                printf("%c%c%c", 47, 124, 92);
                gotoxy(x + contador, y + 2 + conty);
                printf(" %c ", 179);
            }
            contador++;
            Sleep(100);
        }
        for(int j = 0; j < 8; j++){
            system("cls");
            Entrada();
            Mostrar_monos_desde_posicion(Fila, 1);
            if (conty % 2 == 0) {
                gotoxy(x + contador, y + conty);
                cout << " O ";
                gotoxy(x + contador, y + 1 + conty);
                printf("%c%c%c", 47, 124, 92);
                gotoxy(x + contador, y + 2 + conty);
                printf("%c %c", 47, 92);
            } else {
                gotoxy(x + contador, y + conty);
                cout << " O ";
                gotoxy(x + contador, y + 1 + conty);
                printf("%c%c%c", 47, 124, 92);
                gotoxy(x + contador, y + 2 + conty);
                printf(" %c ", 179);
            }
            conty++;
            Sleep(100);
            }
    }
}
void Cola::PersonaDentro(Cola *&Fila, int Elemento){
    if(Cola_Vacia(Fila) == false){
        int puntx = 0, punty = 0;
        switch(Elemento){
            case 1:{
                puntx = 29;
                punty = 19;
            }break;
            case 2:{
                puntx = 40;
                punty = 19;
            }break;
            case 3:{
                puntx = 51;
                punty = 19;
            }break;
            case 4:{
                puntx = 62;
                punty = 19;
            }break;
            case 5:{
                puntx = 73;
                punty = 19;
            }break;
        }
        int contra = 0;
        int f = 0;
        Cola *actual = Fila;
        while(actual != NULL){
            int x = 18;
            int y = 15;
            int contador = 0;
            int conty = 0;
            int county = 0;
            Banco();
            Pantalla(Fila);
            Mostrar_monos_columnas(Fila, Elemento, contra);
            for(int j = 0; j < 8; j++){
                system("cls");
                Banco();
                Pantalla(Fila);
                Mostrar_monos_columnas(Fila, Elemento, contra);
                if (conty % 2 == 0) {
                    gotoxy(x + contador, y + conty);
                    cout << " O ";
                    gotoxy(x + contador, y + 1 + conty);
                    printf("%c%c%c", 47, 124, 92);
                    gotoxy(x + contador, y + 2 + conty);
                    printf("%c %c", 47, 92);
                } else {
                    gotoxy(x + contador, y + conty);
                    cout << " O ";
                    gotoxy(x + contador, y + 1 + conty);
                    printf("%c%c%c", 47, 124, 92);
                    gotoxy(x + contador, y + 2 + conty);
                    printf(" %c ", 179);
                }
                conty++;
                Sleep(100);
            }
            for (int m = 0; m < puntx; m++){
                system("cls");
                Banco();
                Pantalla(Fila);
                Mostrar_monos_columnas(Fila, Elemento, contra);
                if (contador % 2 == 0) {
                    gotoxy(x + contador, y + conty);
                    cout << " O ";
                    gotoxy(x + contador, y + 1 + conty);
                    printf("%c%c%c", 47, 124, 92);
                    gotoxy(x + contador, y + 2 + conty);
                    printf("%c %c", 47, 92);
                } else {
                    gotoxy(x + contador, y + conty);
                    cout << " O ";
                    gotoxy(x + contador, y + 1 + conty);
                    printf("%c%c%c", 47, 124, 92);
                    gotoxy(x + contador, y + 2 + conty);
                    printf(" %c ", 179);
                }
                contador++;
                Sleep(100);
            }
            for(int j = 0; j < punty; j++){
                system("cls");
                Banco();
                Pantalla(Fila);
                Mostrar_monos_columnas(Fila, Elemento, contra);
                if (conty % 2 == 0) {
                    gotoxy(x + contador, y + conty + f);
                    cout << " O ";
                    gotoxy(x + contador, y + 1 + conty + f);
                    printf("%c%c%c", 47, 124, 92);
                    gotoxy(x + contador, y + 2 + conty + f);
                    printf("%c %c", 47, 92);
                } else {
                    gotoxy(x + contador, y + conty + f);
                    cout << " O ";
                    gotoxy(x + contador, y + 1 + conty + f);
                    printf("%c%c%c", 47, 124, 92);
                    gotoxy(x + contador, y + 2 + conty + f);
                    printf(" %c ", 179);
                }
                conty -- ;
                Sleep(100);
            }
            f += 3;
            Mostrar_monos_columnas(Fila, Elemento, contra);
            contra ++;
            actual = actual->Siguiente;
        }
    }
}
void Cola::Mostrar_monos_columnas(Cola *& Fila, int Elemento, int Limite){
    int puntx = 0;
    switch(Elemento){
            case 1:{
                puntx = 47;
            }break;
            case 2:{
                puntx = 58;
            }break;
            case 3:{
                puntx = 69;
            }break;
            case 4:{
                puntx = 80;
            }break;
            case 5:{
                puntx = 91;
            }break;
        }
    int contador = 0, y = 5, contd = 0;
    if (!Cola_Vacia(Fila)) {
        Cola *actual = Fila;
        while(actual != NULL && contd < Limite){
            gotoxy(puntx, y + contador);
            cout << " O ";
            gotoxy(puntx, y + 1 + contador);
            printf("%c%c%c",47, 124, 92);
            gotoxy(puntx, y + 2 + contador);
            printf("%c %c",47, 92);
            actual = actual->Siguiente;
            contador += 3;
            contd ++;
        }
    }
}
void Cola::Fuera(Cola *&Fila, int Elemento){

}
//Ar
string generarNombreAleatorio();
int generarNumeroAleatorio(int min, int max);
int obtenerEnteroValidado(const string& mensaje);
int obtenerOpcionValidada(const string& mensaje);
string obtenerCadenaAlfabeticaValidada(const string& mensaje);

//Main
int main()
{
    bool opc = false;
    Cola *Fila1 = NULL;
    Cola *Fila2 = NULL;
    Cola *Fila3 = NULL;
    Cola *Fila4 = NULL;
    Cola *Fila5 = NULL;
    Cola *Fila6 = NULL;
    Cola *Fila7 = NULL;
    Cola General;
    Cola ATM;
    Cola ATC;
    Cola Caja_1;
    Cola Caja_2;
    Cola Caja_3;
    Cola Gerencia;
    int ID_, Tiempo_;
    string Nombre_;
    do{
        system("cls");
        cout << "Que desea realizar?\n1) Agregar\n2) Iniciar Banco\n3) Iniciar Cajero Automatico\n0) Salir\nSu seleccion: ";
        int opcion = obtenerOpcionValidada("Que desea realizar?\n1) Agregar\n2) Iniciar Banco\n3) Iniciar Cajero Automatico\n0) Salir\nSu seleccion: ");
        switch(opcion){
            case 0:{
                cout << "Gracias!!!" << endl;
                Sleep(1000);
                opc = true;
            }break;
            case 1:{
                //Agregar
                system("cls");
                bool Sal = false;
                cout << "1) Manual\n2) Automatico\n3) Agregar a Cajero Automatico de manera automatica\n0) Regresar\nSu seleccion: ";
                int Menu2 = obtenerEnteroValidado("1) Manual\n2) Automatico\n3) Agregar a Cajero Automatico\nSu seleccion: ");
                do{
                    switch(Menu2){
                        case 0:{
                            //Salir Menu de agregar
                            system("cls");
                            cout << "Regresando..." << endl;
                            Sleep(1000);
                            Sal = true;
                        }break;
                        case 1:{
                            // Agregar a general manual
                            system("cls");
                            cout << "Cuantas personas deseas ingresar a la cola general?\nSu seleccion: ";
                            int Cantidad = obtenerEnteroValidado("Cuantas personas deseas ingresar a la cola general?\nSu seleccion: ");
                            if (Cantidad >= 1) {
                                for (int i = 0; i < Cantidad; i++){
                                    system("cls");
                                    ID_ = generarNumeroAleatorio(1,9999);
                                    cout << "ID: " << ID_ << endl;
                                    cout << "Ingrese un nombre: ";
                                    Nombre_= obtenerCadenaAlfabeticaValidada("Ingrese un nombre: ");
                                    General.Agregar(Fila1, ID_, Nombre_);
                                    CantidadGen ++;
                                }
                            }
                            Sal = true;
                        }break;
                        case 2:{
                            //Agregar a general Automatico
                            system("cls");
                            cout << "Cuantas personas deseas ingresar a la cola?\nSu seleccion: ";
                            int Cantidad = obtenerEnteroValidado("Cuantas personas deseas ingresar a la cola general?\nSu seleccion: ");
                            if (Cantidad >= 1) {
                                for (int i = 0; i < Cantidad; i++){
                                    system("cls");
                                    ID_ = generarNumeroAleatorio(1,9999);
                                    Nombre_ = generarNombreAleatorio();
                                    General.Agregar(Fila1, ID_, Nombre_);
                                    CantidadGen ++;
                                }
                            }
                            system("cls");
                            cout << "Se encolaron las " << Cantidad << " personas de forma exitosa." << endl;
                            Sleep(2000);
                            Sal = true;
                        }break;
                        case 3:{
                            //Agregar a cajero automatico automatico
                            system("cls");
                            cout << "Cuantas personas deseas ingresar a la cola del cajero automatico?\nSu seleccion: ";
                            int Cantidad = obtenerEnteroValidado("Cuantas personas deseas ingresar a la cola del cajero automatico?\nSu seleccion: ");
                            if (Cantidad >= 1) {
                                for (int i = 0; i < Cantidad; i++){
                                    system("cls");
                                    ID_ = generarNumeroAleatorio(1,9999);
                                    Tiempo_ = generarNumeroAleatorio(1,2);
                                    Nombre_ = generarNombreAleatorio();
                                    ATM.Agregar(Fila1, ID_, Tiempo_, Nombre_);
                                    CantidadAu ++;
                                }
                            }
                            system("cls");
                            cout << "Se encolaron las " << Cantidad << " personas de forma exitosa." << endl;
                            Sleep(2000);
                            Sal = true;
                        }break;
                        default:{
                            cout << "Por favor seleccione una opcion valida" << endl;
                            Sleep(1000);
                            Sal = false;
                        }break;
                    }
                }while(Sal != true);
            }break;
            case 2: {
                //Inicio
                system("cls");
                while(CantidadGen > 0){
                    General.moverPersonasEnCola(Fila1);
                    int Num = generarNumeroAleatorio(1, 5);
                    int Time = generarNumeroAleatorio(1, 6);
                    switch(Num){
                        case 1:{
                        //Atencion al cliente
                            ATC.Agregar(Fila2, General.getID(Fila1), Time, General.getNombre(Fila1));
                            General.Eliminar(Fila1);
                        }break;
                        case 2:{
                            //Caja 1
                            Caja_1.Agregar(Fila3, General.getID(Fila1), Time, General.getNombre(Fila1));
                            General.Eliminar(Fila1);
                        }break;
                        case 3:{
                            //Caja 2
                            Caja_2.Agregar(Fila4, General.getID(Fila1), Time, General.getNombre(Fila1));
                            General.Eliminar(Fila1);
                        }break;
                        case 4:{
                            //Caja 3
                            Caja_3.Agregar(Fila5, General.getID(Fila1), Time, General.getNombre(Fila1));
                            General.Eliminar(Fila1);
                        }break;
                        case 5:{
                            //Gerencia
                            Gerencia.Agregar(Fila6, General.getID(Fila1), Time, General.getNombre(Fila1));
                            General.Eliminar(Fila1);
                        } break;
                    }

                    CantidadGen --;
                }
                ATC.PersonaDentro(Fila2, 1);
                system("cls");
                Caja_1.PersonaDentro(Fila3, 2);
                system("cls");
                Caja_2.PersonaDentro(Fila4, 3);
                system("cls");
                Caja_3.PersonaDentro(Fila5, 4);
                system("cls");
                Gerencia.PersonaDentro(Fila6, 5);
                system("cls");
            }break;
            case 3:{
                General.PersonaDentro(Fila1, 1);
            }break;
            default:{
                cout << "Por favor seleccione una opcion valida" << endl;
                Sleep(1000);
                opc = false;
            }break;
        }
    }while(opc != true);
    return 0;
}
//Validar entrada
int obtenerEnteroValidado(const string& mensaje){
    int valor;
    while (true) {
        cin >> valor;
        if (cin.fail()) {
            cout << "Ingrese un valor numerico valido." << endl;
            cin.clear();
            Sleep(1000);
            system("cls");
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << mensaje;
        } else {
            break;
        }
    }
    return valor;
}
//Validar menú
int obtenerOpcionValidada(const string& mensaje){
    int opcion;
    while(true) {
        string entrada;
        cin >> entrada;
        try{
            opcion = stoi(entrada);
            break;
        }catch (const invalid_argument& e){
            cout << "Ingrese un valor numerico valido." << endl;
        }
        Sleep(1000);
        system("cls");
        cout << mensaje;
    }
    return opcion;
}
// Función para generar un número aleatorio en un rango específico
int generarNumeroAleatorio(int min, int max){
    return min + rand() % (max - min + 1);
}
// Función para generar un nombre aleatorio de una lista predefinida
string generarNombreAleatorio(){
    vector<string> nombres ={
    "Juan", "María", "Luis", "Ana", "Pedro", "Laura", "Carlos", "Sofía", "Diego", "Valeria",
    "José", "Isabella", "Andrés", "Camila", "Francisco", "Elena", "Antonio", "Valentina",
    "Manuel", "Gabriela", "Fernando", "Daniela", "Javier", "Adriana", "Miguel", "Carolina",
    "Ricardo", "Ximena", "Roberto", "Paula", "Jorge", "Natalia", "Alejandro", "Victoria",
    "Rafael", "Alejandra", "Daniel", "Marta", "Gustavo", "Patricia", "Simón", "Clara",
    "Cristian", "Laura", "Esteban", "Julia"
    };
    int indice = generarNumeroAleatorio(0, nombres.size() - 1);
    return nombres[indice];
}
//Funcion para validar cadena de caracteres
string obtenerCadenaAlfabeticaValidada(const string& mensaje){
    string cadena;
    while(true){
        cin.ignore();
        getline(cin, cadena);
        bool esValida = true;
        for (char c : cadena) {
            if(!isalpha(c) && !isspace(c)){
                esValida = false;
                break;
            }
        }
        if(esValida){
            break;
        }else{
            cout << "Ingrese una cadena que solo contenga letras del alfabeto y/o espacios." <<endl;
        }
        Sleep(1000);
        system("cls");
        cout << mensaje;
    }
    return cadena;
}
