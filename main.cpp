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
                cout << metaX;
            } else {
                if (j >= posX - 1 && j <= posX + 1 && i >= posY - 1 && i <= posY + 1 && !(j == posX && i == posY)) {
                    cout << matriz[i][j];
                } else {
                    cout << " ";
                }
            }
        }
    }
}

int calcularResultado(int posX, int posY, const int matriz[][COLUMNAS]) {
    int result = 0;

    int numeroDerecha = matriz[posY][posX + 1];
    int numeroIzquierda = matriz[posY][posX - 1];
    if (posY > 0) {
        result += (matriz[posY - 1][posX] + matriz[posY - 1][posX - 1] + matriz[posY - 1][posX + 1]) * numeroDerecha;
    }
    if (posY < FILAS - 1) {
        result -= (matriz[posY + 1][posX] + matriz[posY + 1][posX - 1] + matriz[posY + 1][posX + 1]) * numeroIzquierda;
    }

    return result;
}




int main()
{
    system("COLOR 2");
    srand(time(0));
    int posX = 0;
    int posY = generarNumeroAleatorio(0, FILAS - 1);
    string meta = "META";
    int metaX = COLUMNAS - 1;
    int metaY = generarNumeroAleatorio(0, FILAS - 1);

    int matriz[FILAS][COLUMNAS];
    int posInicialY = generarNumeroAleatorio(0, FILAS - 1);

    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            if (j == 0) {
                matriz[i][j] = (i == posInicialY) ? 1 : generarNumeroAleatorio(1, 10);
            } else {
                matriz[i][j] = generarNumeroAleatorio(1, 10);
            }
        }
    }

    dibujarMatriz(posX, posY, meta, metaY, matriz);

    int ultY = (FILAS - 1) * ALTO + ALTO;
    gotoxy(0, ultY + 2);

    char movimiento;
    int intentos = 0;
    do {
        movimiento = getch();
        int posXAnterior = posX;
        int posYAnterior = posY;

        switch (movimiento) {
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
        gotoxy(posX * ANCHO + (ANCHO / 2) - 1, posY * ALTO + (ALTO / 2) + 1);

        if (posX == metaX && posY == metaY) {
            cout << "¡Felicidades, has alcanzado la meta!";
            break;
        }

        int resultado = calcularResultado(posX, posY, matriz);
        gotoxy(0, ultY + 4);
        cout << "Resultado: " << resultado << "      ";
        gotoxy(0, ultY + 6);
        cout << "Intentos restantes: " << 8 - intentos << "      ";

        if (resultado != 0) {
            int respuesta;
            cout << "Ingrese su respuesta: ";
            cin >> respuesta;

            if (respuesta == resultado) {
                cout << "¡Respuesta correcta!" << endl;
            } else {
                cout << "Respuesta incorrecta." << endl;
                posX = posXAnterior;
                posY = posYAnterior;
                intentos++;
            }
        }

        intentos++;
    } while (intentos < 8);

    if (intentos == 8) {
        cout << "¡Se acabaron los intentos! Game over.";
    }

    return 0;
}

