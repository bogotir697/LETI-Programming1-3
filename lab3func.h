#pragma once

#include <windows.h>

using namespace std;

#define N 10
#define hConsole GetStdHandle(STD_OUTPUT_HANDLE)

void gotoxy(int x, int y);
COORD GetConsoleCursorPosition(HANDLE hConsoleOutput);
void putElem(int* matrix, int n, int power, int* elem, int maxLen, int startX = 1, int startY = 1);
int randInt(int min, int max);
string repeatString(string s, int n);
double lg(double a);
int len(int a);
int findMaxLen(int* matrix, int n, int power);
void createMatrix(int* matrix, int n, int power, int min = 1, int max = N * N);
void printMatrix(int* matrix, int n, int power);
void printMatrixA(int* matrix, int n, int power);
void printMatrixB(int* matrix, int n, int power);
void shuffleMatrix(int* matrix, int n, int power, int type);
void bubbleSort(int* matrix, int n, int power);
void shakerSort(int* matrix, int n, int power);
void combSort(int* matrix, int n, int power);
void insertSort(int* matrix, int n, int power);
void quickSort(int* matrix, int n, int power, int maxLen, int* end, int* begin);
void mathWthMatrix(int* matrix, int n, int power, int type, int a);