#include <iostream>
#include <cmath>
#include "lab3func.h"

void gotoxy(int x, int y) {
	COORD coordinate;
	coordinate.X = x;
	coordinate.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinate);
}

COORD GetConsoleCursorPosition(HANDLE hConsoleOutput)
{
	CONSOLE_SCREEN_BUFFER_INFO cbsi;
	if (GetConsoleScreenBufferInfo(hConsoleOutput, &cbsi))
	{
		return cbsi.dwCursorPosition;
	}
	else
	{
		COORD invalid = { 0, 0 };
		return invalid;
	}
}

void putElem(int* matrix, int n, int power, int* elem, int maxLen, int startX, int startY) {
	int elemPos = elem - matrix;
	gotoxy((elemPos % n) * (len(maxLen) + 1) + startX, elemPos / n + startY);
	cout << repeatString(" ", len(maxLen) - len(*elem)) << *elem << " ";
}

int randInt(int min, int max) {
	int i = rand() % (max + 1 - min);
	i += min;
	return i;
}

string repeatString(string s, int n) {
	string k = "";
	for (int i = 0; i < n; i++) {
		k += s;
	}
	return k;
}

double lg(double a) {
	if (a == 0) { return 0; }
	return log(a) / log(10) + pow(10, -5);
}

int len(int a) {
	int isNegative = (a < 0) ? 1 : 0;
	return int(lg(abs(a))) + 1 + isNegative;
}

int findMaxLen(int* matrix, int n, int power) {
	int maxLen = *matrix;
	for (int* i = matrix, *end = matrix + int(pow(n, power)) - 1; i <= end; i++) {
		if (len(*i) > len(maxLen)) {
			maxLen = *i;
		}
	}
	return maxLen;
}

void createMatrix(int* matrix, int n, int power, int min, int max) {
	int* end = matrix + int(pow(n, power)) - 1;
	for (matrix; matrix <= end; matrix++) {
		*matrix = randInt(min, max);
	}
}

void printMatrix(int* matrix, int n, int power) {
	int maxLen = findMaxLen(matrix, n, power);
	COORD startCoord = GetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE));
	for (int* i = matrix, *end = matrix + int(pow(n, power)) - 1; i <= end; i++) {
		putElem(matrix, n, power, i, maxLen, startCoord.X + 1, startCoord.Y);
	}
	gotoxy(startCoord.X, startCoord.Y + N);
}

void printMatrixA(int* matrix, int n, int power) {
	int state(0), * start(matrix + n), * elem(matrix), * end(matrix + int(pow(n, power)) - 1);
	int maxLen = findMaxLen(matrix, n, power);
	COORD startCoord = GetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE));
	for (int i = 0; i < int(pow(n, power)); i++) {
		int elemPos = elem - matrix, startPos = start - matrix, endPos = end - matrix;
		putElem(matrix, n, power, elem, maxLen, startCoord.X + 1, startCoord.Y);
		switch (state) {
		case 0:
			elem++;
			elemPos++;
			state += (elemPos % n == endPos % n) ? 1 : 0;
			end -= (elemPos % n == endPos % n) ? 1 : 0;
			break;
		case 1:
			elem += n;
			elemPos += n;
			state += (elemPos / n == endPos / n) ? 1 : 0;
			end -= (elemPos / n == endPos / n) ? n : 0;
			break;
		case 2:
			elem--;
			elemPos--;
			state += (elemPos % n == startPos % n) ? 1 : 0;
			start += (elemPos % n == startPos % n) ? 1 : 0;
			break;
		case 3:
			elem -= n;
			elemPos -= n;
			state += (elemPos / n == startPos / n) ? 1 : 0;
			start += (elemPos / n == startPos / n) ? n : 0;
			break;
		}
		state %= 4;
		Sleep(3);
	}
	gotoxy(startCoord.X, startCoord.Y + N);
}

void printMatrixB(int* matrix, int n, int power) {
	int state(0), * top(matrix + 1), * elem(matrix), * bot(matrix + n * (n - 1) + 1);
	int maxLen = findMaxLen(matrix, n, power);
	COORD startCoord = GetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE));
	for (int i = 0; i < n * n; i++) {
		int elemPos = elem - matrix, topPos = top - matrix, botPos = bot - matrix;
		putElem(matrix, n, power, elem, maxLen, startCoord.X + 1, startCoord.Y);
		switch (state) {
		case 0:
			elem += n;
			elemPos += n;
			state += (elemPos / n == botPos / n) ? 1 : 0;
			break;
		case 1:
			elem++;
			state++;
			bot += 2;
			break;
		case 2:
			elem -= n;
			elemPos -= n;
			state += (elemPos / n == topPos / n) ? 1 : 0;
			break;
		case 3:
			elem++;
			state++;
			top += 2;
			break;
		}
		state %= 4;
		Sleep(3);
	}
	gotoxy(startCoord.X, startCoord.Y + N);
}

void shuffleMatrix(int* matrix, int n, int power, int type) {
	int types[4][8] = { {3, n * n / 2, n * n / 2, n / 2, n / 2, -n * n / 2, 0, 0},
		{2, n * n / 2 + n / 2, n * n / 2, -n * n / 2, 0, 0, 0, 0},
		{2, n * n / 2, n / 2, n / 2, 0, 0, 0, 0},
		{2, n / 2, n * n / 2, n * n / 2, 0, 0, 0, 0} };
	int state(0), * prev(matrix), * elem(matrix), * next(matrix + types[type][1]), color = 12;
	int maxLen = findMaxLen(matrix, n, power);
	COORD startCoord = GetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE));
	SetConsoleTextAttribute(hConsole, color);
	for (int i = 0; i < n * n * types[type][0] / 4; i++) {
		int elemPos = elem - prev, prevPos = prev - matrix, nextPos = next - matrix;
		int prevMove = types[type][2 + 2 * state], nextMove = types[type][2 + 2 * state + 1];

		int temp = *(prev + elemPos);
		*(prev + elemPos) = *(next + elemPos);
		*(next + elemPos) = temp;

		putElem(matrix, n, power, prev + elemPos, maxLen, startCoord.X + 1, startCoord.Y);
		putElem(matrix, n, power, next + elemPos, maxLen, startCoord.X + 1, startCoord.Y);

		elemPos++;
		elem += 1 + ((elemPos % (n / 2)) ? 0 : (n / 2));
		if (!((i + 1) % (n * n * 1 / 4))) {
			state++;
			prev += prevMove;
			next += nextMove;
			elem = prev;
			color++;
			SetConsoleTextAttribute(hConsole, color);
		}

		Sleep(3);
	}
}

void bubbleSort(int* matrix, int n, int power) {
	int maxLen = findMaxLen(matrix, n, power);
	for (int* i = matrix, *end = matrix + int(pow(n, power)) - 1; i <= end; i++) {
		for (int* j = matrix; j - matrix < end - i; j++) {
			if (*j > *(j + 1)) {
				int temp = *j;
				*j = *(j + 1);
				*(j + 1) = temp;
				putElem(matrix, n, 2, j, maxLen);
				putElem(matrix, n, 2, j + 1, maxLen);
			}
		}
		Sleep(1);
	}
}

void shakerSort(int* matrix, int n, int power) {
	int maxLen = findMaxLen(matrix, n, power);
	for (int* i = matrix, *end = matrix + int(pow(n, power)) - 1; i <= end; i++) {
		for (int* j = matrix; j - matrix < end - i; j++) {
			if (*j > *(j + 1)) {
				int temp = *j;
				*j = *(j + 1);
				*(j + 1) = temp;
				putElem(matrix, n, 2, j, maxLen);
				putElem(matrix, n, 2, j + 1, maxLen);
			}
		}
		for (int* j = end - (i - matrix); j > i; j--) {
			if (*j < *(j - 1)) {
				int temp = *j;
				*j = *(j - 1);
				*(j - 1) = temp;
				putElem(matrix, n, 2, j, maxLen);
				putElem(matrix, n, 2, j - 1, maxLen);
			}
		}
		Sleep(1);
	}
}

void combSort(int* matrix, int n, int power) {
	float k = 1.247, s = int(pow(n, power)) - 1;
	int maxLen = findMaxLen(matrix, n, power);
	while (s >= 1) {
		for (int* i = matrix, *end = matrix + int(pow(n, power)) - 1; i + int(s) <= end; i++) {
			if (*i > *(i + int(s))) {
				int temp = *i;
				*i = *(i + int(s));
				*(i + int(s)) = temp;
				putElem(matrix, n, 2, i, maxLen);
				putElem(matrix, n, 2, i + int(s), maxLen);
			}
		}
		s /= k;
		Sleep(1);
	}
}

void insertSort(int* matrix, int n, int power) {
	int maxLen = findMaxLen(matrix, n, power);
	for (int* i = matrix + 1, *end = matrix + int(pow(n, power)); i <= end; i++) {
		int* j = i - 1;
		int key = *i;
		while ((j - matrix) >= 0 && *j > key) {
			*(j + 1) = *j;
			j -= 1;
			putElem(matrix, n, 2, j + 1, maxLen);
		}
		*(j + 1) = key;
		putElem(matrix, n, 2, j + 1, maxLen);
		Sleep(1);
	}
}

void quickSort(int* matrix, int n, int power, int maxLen, int* end, int* begin) {
	int mid;
	int* f = begin;
	int* l = end;
	mid = *(f + (l - matrix) - ((f - matrix) + (l - matrix)) / 2);
	while (f < l) {
		while (*f < mid) f++;
		while (*l > mid) l--;
		if (f <= l) {
			int temp = *f;
			*f = *l;
			*l = temp;
			putElem(matrix, n, power, f, maxLen);
			putElem(matrix, n, power, l, maxLen);
			Sleep(1);
			f++;
			l--;
		}
	}
	if (begin < l) { quickSort(matrix, n, power, maxLen, l, begin); }
	if (f < end) { quickSort(matrix, n, power, maxLen, end, f); }
}

void mathWthMatrix(int* matrix, int n, int power, int type, int a) {
	for (int* i = matrix, *end = matrix + int(pow(n, power)) - 1; i <= end; i++) {
		int b = *i;
		switch (type) {
		case 0:
			*i = b + a;
			break;
		case 1:
			*i = b - a;
			break;
		case 2:
			*i = b * a;
			break;
		case 3:
			if (!a) { break; }
			*i = b / a;
			break;
		}
	}
}
