#include <iostream>
#include <windows.h>
#include <ctime>
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

void dibujarMatriz()
{
    int matriz[FILAS][COLUMNAS];
    srand(time(0));

    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            matriz[i][j] = rand() % 100;
        }
    }

    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            int x = j * ANCHO;
            int y = i * ALTO;

            dibujarRecuadro(x, y, ANCHO, ALTO);
            int centroX = x + (ANCHO / 2) - 1;
            int centroY = y + (ALTO / 2);
            gotoxy(centroX, centroY);

            cout << matriz[i][j];
        }
    }
}

int main()
{
    system("COLOR 2");
    dibujarMatriz();

    int ultY = (FILAS - 1) * ALTO + ALTO;
    gotoxy(0, ultY + 2);

    return 0;
}

