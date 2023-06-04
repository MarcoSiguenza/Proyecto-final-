#include <iostream>
#include <windows.h>
#include <ctime>
#include <cstdio>
#include <conio.h>
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

void dibujarMatriz(int posX, int posY)
{
    int matriz[FILAS][COLUMNAS];
    srand(time(0));

    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            if (j == posX && i == posY) {
                matriz[i][j] = 1;
            } else {
                matriz[i][j] = generarNumeroAleatorio(1, 10);
            }
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

            if (j == posX && i == posY) {
                cout << ":)";
                gotoxy(centroX, centroY + 1);
            } else {
                if (j >= posX - 1 && j <= posX + 1 && i >= posY - 1 && i <= posY + 1) {
                    cout << matriz[i][j];
                } else {
                    cout << " ";
                }
            }
        }
    }
}

int main()
{
    system("COLOR 2");
    int posX = 0;
    int posY = FILAS - 1;
    dibujarMatriz(posX, posY);

    int ultY = (FILAS - 1) * ALTO + ALTO;
    gotoxy(0, ultY + 2);

    char movimiento;
    do {
        movimiento = getch();
        switch (movimiento) {
            case 'w':
                if (posY > 0) {
                    posY--;
                    system("cls");
                    dibujarMatriz(posX, posY);
                    gotoxy(posX * ANCHO + (ANCHO / 2) - 1, posY * ALTO + (ALTO / 2) + 1);
                }
                break;
            case 'a':
                if (posX > 0) {
                    posX--;
                    system("cls");
                    dibujarMatriz(posX, posY);
                    gotoxy(posX * ANCHO + (ANCHO / 2) - 1, posY * ALTO + (ALTO / 2) + 1);
                }
                break;
            case 's':
                if (posY < FILAS - 1) {
                    posY++;
                    system("cls");
                    dibujarMatriz(posX, posY);
                    gotoxy(posX * ANCHO + (ANCHO / 2) - 1, posY * ALTO + (ALTO / 2) + 1);
                }
                break;
            case 'd':
                if (posX < COLUMNAS - 1) {
                    posX++;
                    system("cls");
                    dibujarMatriz(posX, posY);
                    gotoxy(posX * ANCHO + (ANCHO / 2) - 1, posY * ALTO + (ALTO / 2) + 1);
                }
                break;
        }
    } while (movimiento != 'q');

    return 0;
}




