#include <windows.h>
#include <iostream>
#include <direct.h>
#include <stdlib.h>
#define ANCHO 60
#define ALTO 25
#define SECCIONES 5
#define SECCIONES2 5

using namespace std;

void gotoxy(int x, int y)
{
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hCon, dwPos);
}

void recuadro()
{
    for (int i = 0; i < ANCHO; i++)
    {
        gotoxy(i * 2, 0);
        cout << char(220);
        gotoxy(i * 2, ALTO);
        cout << char(220);
    }

    for (int i = 0; i <= ALTO; i++)
    {
        gotoxy(0, i);
        cout << char(220);
        gotoxy(ANCHO * 2 - 1, i);
        cout << char(220);
    }
}

void dibujarEje()
{
    for (int i = 0; i <= ANCHO * 2; i++)
    {
        gotoxy(i, 5);
        cout << char(95);
    }
    for (int i = 0; i <= ANCHO * 2; i++)
    {
        gotoxy(i, 10);
        cout << char(95);
    }
    for (int i = 0; i <= ANCHO * 2; i++)
    {
        gotoxy(i, 15);
        cout << char(95);
    }
    for (int i = 0; i <= ANCHO * 2; i++)
    {
        gotoxy(i, 20);
        cout << char(95);
    }

    int seccion = ANCHO / SECCIONES;
    for (int i = 1; i < SECCIONES; i++)
    {
        int x = i * seccion * 2;
        for (int j = 1; j < ALTO; j++)
        {
            gotoxy(x, j);
            cout << char(179);
        }
    }
}

int main()
{
    system("cls");
    system("color 40");
    dibujarEje();
    recuadro();

    int casilla;
    int seccions = ANCHO / SECCIONES;
    char respuesta;


    int fila;
    int columna;

    if (casilla <= SECCIONES)
    {
        fila = 1;
        columna = (casilla - 1) * seccions * 2 + seccions;
    }
    else
    {
        fila = 2;
        columna = (casilla - SECCIONES - 1) * seccions * 2 + seccions;
    }

    int y = fila * (ALTO / 2) - 1;

    system("cls");
    system("color 40");
    dibujarEje();
    recuadro();




    return 0;
}

