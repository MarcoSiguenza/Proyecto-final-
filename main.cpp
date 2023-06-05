#include <iostream>
#include <windows.h>
#include <ctime>
#include <cstdio>
#include <conio.h>
#include <string>
#define FILAS 5
#define COLUMNAS 5
#define ANCHO 12
#define ALTO 4
using namespace std;

void gotoxy(int x, int y)
{
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hCon, dwPos);
}

void dibujarRecuadro(int x, int y, int ancho, int alto)
{
    gotoxy(x, y);
    for (int i = 0; i <= ancho; i++) {
        cout << char(220);
    }

    gotoxy(x, y + alto);
    for (int i = 0; i <= ancho; i++) {
        cout << char(220);
    }

    for (int i = y + 1; i < y + alto; i++) {
        gotoxy(x, i);
        cout << char(179);

        gotoxy(x + ancho, i);
        cout << char(179);
    }

    gotoxy(x, y);
    cout << char(220);

    gotoxy(x + ancho, y);
    cout << char(220);

    gotoxy(x, y + alto);
    cout << char(220);

    gotoxy(x + ancho, y + alto);
    cout << char(220);
}

int generarNumeroAleatorio(int min, int max)
{
    return min + rand() % (max - min + 1);
}

void dibujarMatriz(int posX, int posY, const string& metaX, int metaY, int matriz[][COLUMNAS])
{

    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            int x = j * ANCHO;
            int y = i * ALTO;

            dibujarRecuadro(x, y, ANCHO, ALTO);
            int centroX = x + (ANCHO / 2) - 1;
            int centroY = y + (ALTO / 2);
            gotoxy(centroX, centroY);

            if (j == posX && i == posY) {
                cout << ":)";
                gotoxy(centroX, centroY + 1);
            } else if (j == COLUMNAS - 1 && i == metaY) {
                if (posX == COLUMNAS - 1 && posY == metaY) {
                    cout << matriz[i][j];
                } else if (posX >= COLUMNAS - 2 && posY >= metaY - 1 && posY <= metaY + 1) {
                    cout << matriz[i][j];
                } else {
                    cout << metaX;
                }
            } else {
                if (j >= posX - 1 && j <= posX + 1 && i >= posY - 1 && i <= posY + 1 && !(j == posX && i == posY)) {
                    cout << matriz[i][j];
                } else {
                    cout << " ";
                }
            }
        }
    }
    gotoxy(0, (FILAS - 1) * ALTO + ALTO + 1);
    cout<<"Presiona enter para empezar";
}



int calcularResultado(int posX, int posY, const int matriz[][COLUMNAS]) {
    int result = 0;

    int numeroDerecha = 0;
    if (posX < COLUMNAS - 1) {
        numeroDerecha = matriz[posY][posX + 1];
    }

    int numeroIzquierda = 0;
    if (posX > 0) {
        numeroIzquierda = matriz[posY][posX - 1];
    }

    if (posY > 0) {
        int numeroArriba = matriz[posY - 1][posX];
        int numeroArribaIzquierda = (posX > 0) ? matriz[posY - 1][posX - 1] : 0;
        int numeroArribaDerecha = (posX < COLUMNAS - 1) ? matriz[posY - 1][posX + 1] : 0;
        result += (numeroArriba + numeroArribaIzquierda + numeroArribaDerecha) * numeroDerecha;
    }

    if (posY < FILAS - 1) {
        int numeroAbajo = matriz[posY + 1][posX];
        int numeroAbajoIzquierda = (posX > 0) ? matriz[posY + 1][posX - 1] : 0;
        int numeroAbajoDerecha = (posX < COLUMNAS - 1) ? matriz[posY + 1][posX + 1] : 0;
        result -= (numeroAbajo + numeroAbajoIzquierda + numeroAbajoDerecha) * numeroIzquierda;
    }

    return result;
}

void generarNuevosNumerosAleatorios(int matriz[][COLUMNAS], int fila, int posX, int posY)
{
    for (int j = 0; j < COLUMNAS; j++) {
        if (j == 0 || (fila == posY && j == posX)) {
            matriz[fila][j] = generarNumeroAleatorio(1, 10);
        } else {
            matriz[fila][j] = generarNumeroAleatorio(1, 10);
        }
    }
}
void instrucciones ();
int main()
{

    instrucciones ();
    system ("COLOR 0B");
    system("cls");
    srand(time(0));
    int posX = 0;
    int posY = generarNumeroAleatorio(0, FILAS - 1);
    string meta = "META";
    int metaX = COLUMNAS - 1;
    int metaY = generarNumeroAleatorio(0, FILAS - 1);
    int matriz[FILAS][COLUMNAS];
    int posInicialY = generarNumeroAleatorio(0, FILAS - 1);

    for (int i = 0; i < FILAS; i++) {
        generarNuevosNumerosAleatorios(matriz, i, posX, posY);
    }

    dibujarMatriz(posX, posY, meta, metaY, matriz);

    int ultY = (FILAS - 1) * ALTO + ALTO;
    gotoxy(0, ultY + 2);

    char movimiento;
    int intentos = 0;
    bool movimientoValido = true;
    bool primeraMovida = true;
    do {
        movimiento = getch();
        int posXAnterior = posX;
        int posYAnterior = posY;

        movimientoValido = true;

char primerMovimiento;
char segundoMovimiento;
gotoxy(0, ultY + 1);
cout << "Ingresa tu primer movimiento (w/a/s/d): ";
primerMovimiento = getch();

switch (primerMovimiento) {
    case 'w':
        if (posY > 0) {
            posY--;
        }
        break;
    case 'a':
        if (posX > 0) {
            posX--;
        }
        break;
    case 's':
        if (posY < FILAS - 1) {
            posY++;
        }
        break;
    case 'd':
        if (posX < COLUMNAS - 1) {
            posX++;
        }
        break;
}

system("cls");

dibujarMatriz(posX, posY, meta, metaY, matriz);
gotoxy(0, ultY + 1);
cout << "Ingresa tu segundo movimiento (w/a/s/d): ";
segundoMovimiento = getch();

switch (segundoMovimiento) {
    case 'w':
        if (posY > 0) {
            posY--;
        }
        break;
    case 'a':
        if (posX > 0) {
            posX--;
        }
        break;
    case 's':
        if (posY < FILAS - 1) {
            posY++;
        }
        break;
    case 'd':
        if (posX < COLUMNAS - 1) {
            posX++;
        }
        break;
}


if (!movimientoValido) {
    continue;
}

if (primeraMovida) {
    meta = " ";
    primeraMovida = false;
}

system("cls");
generarNuevosNumerosAleatorios(matriz, posYAnterior, posXAnterior, posY);
dibujarMatriz(posX, posY, meta, metaY, matriz);
gotoxy(posX * ANCHO + (ANCHO / 2) - 1, posY * ALTO + (ALTO / 2) + 1);

if (posX == metaX && posY == metaY) {
    gotoxy(0, ultY + 1);
    cout << "¡Felicidades, has alcanzado la meta!" << endl;
    break;
}

int resultado = calcularResultado(posX, posY, matriz);
gotoxy(0, ultY + 1);
cout << "Intentos restantes: " << 8 - intentos << "      ";


if (resultado != 0) {
    int respuesta;
    cout << "Ingrese su respuesta: ";
    cin >> respuesta;

    if (respuesta == resultado) {
        cout << "¡Respuesta correcta! Presiona enter para ingresar otro movimiento" << endl;
        intentos++;
    } else {
        cout << "Respuesta incorrecta. Presiona enter para regresar a la posición anterior." << endl;
        posX = posXAnterior;
        posY = posYAnterior;
        getch();
        system("cls");
        dibujarMatriz(posX, posY, meta, metaY, matriz);
        continue;
    }
}

intentos++;

    } while (intentos < 8 && movimientoValido);

    if (intentos == 8) {
        cout << "¡Se acabaron los intentos! Perdiste :(." << endl;
    }

    return 0;
}
void instrucciones (){
    system ("COLOR B1");
    cout << "=== INSTRUCCIONES ===" << endl;
    cout << "Utiliza las teclas 'W'(Arriba) , 'A'(Izquierda), 'S'(Abajo) y 'D'(Derecha) para moverte en el juego." << endl;
    cout << "El objetivo es llegar a la casilla marcada con 'META' (meta) en la ultima columna." << endl;
    cout << "En cada movimiento, se mostraran numeros alrededor de tu posicion actual." << endl;
    cout << "Debes calcular el resultado de la operacion e ingresar el valor correcto." << endl;
    cout << "Los calculos se realizan de la siguiente manera:" << endl;
    cout << "1. Los tres numeros sobre el se suman y se multiplican por el numero de la derecha." << endl;
    cout << "2. Los tres numeros de abajo se suman y se multiplican por el numero de la izquierda." << endl;
    cout << "3. Los dos resultados de arriba se restan." << endl;
    cout << "Por ejemplo, considera la siguiente situacion" << endl;
    cout << "   7  4  1" << endl;
    cout << "   2  :) 6" << endl;
    cout << "   3  8  5" << endl;
    cout << "Los calculos serian:" << endl;
    cout << "(7 + 4 + 1) * 6 = 72" << endl;
    cout << "(3 + 8 + 5) * 2 = 32" << endl;
    cout << "72 - 32 = 40" << endl;
    cout << "Entonces, debes ingresar el valor '40'." << endl;
    cout << "¡Buena suerte! Presiona cualquier tecla para dirigirte al juego." << endl;
    cout << "NOTA: TIENES QUE MEMORIZAR LA META PORQUE DESPUES DEL SEGUNDO MOVIMIENTO LA PALABRA DESAPARECERA" << endl;
    cout << "NOTA: SI LLEGASTE A LA META EN TU PRIMER MOVIMIENTO, SOLO PRESIONA ENTER" << endl;
    getch();
    system("cls");
}