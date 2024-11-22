#include <iostream>
#include <conio.h>
#include "lab3func.h"

using namespace std;

int matrix[N][N];

bool active = 1;
unsigned char state[2] = { 0, 0 };
unsigned char prevState[2] = { -1, -1 };
unsigned char length[11] = { 7, 1, 3, 4, 5, N, 5, 2 * N + 2, N, N, N };
unsigned char step[11] = { 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0 };
int sort = -1;
int printType = 0, shuffleType = 0, actType = 0;
int nMath = 0;





void mainMenu() {
	printf(" [ Создать матрицу ]\n");
	printf(" [ Вывести матрицу ]\n");
	printf(" [ Перемешать матрицу ]\n");
	printf(" [ Выбранная сортировка ]: ");
	string s = "";
	switch (sort) {
	case 0:
		s = "bubble sort";
		break;
	case 1:
		s = "shaker sort";
		break;
	case 2:
		s = "comb sort";
		break;
	case 3:
		s = "insert sort";
		break;
	case 4:
		s = "quick sort";
		break;
	}
	cout << s << "\n";
	printf(" [ Сортировка матрицы ]\n");
	printf(" [ Изменение матрицы ]\n");
	printf(" [ ИДЗ 1 ]\n");
}

void f1CreateMatrix() {
	createMatrix(matrix[0], N, 2);
	printf(" Создана матрица %d на %d\n", N, N);
}

void f2PrintMatrix() {
	printf(" [ Поэлементный ]\n");
	printf(" [ Тип A \"Улитка\" ]\n");
	printf(" [ Тип B \"Змейка\"]\n");
}

void f3ShuffleMatrix() {
	printf(" [ Тип A \"По часовой стрелке\" ]\n");
	printf(" [ Тип B \"Крестом\" ]\n");
	printf(" [ Тип C \"По вертикали\" ]\n");
	printf(" [ Тип D \"По горизонтали\" ]\n");
}

void f4ChooseSort() {
	printf(" [ bubble sort ]  \n");
	printf(" [ shaker sort ]  \n");
	printf(" [ comb sort ]    \n");
	printf(" [ insert sort ]  \n");
	printf(" [ quick sort ]   \n");
	if (sort > -1) {
		gotoxy(18, sort % 5 + 1);
		putchar('*');
	}
	gotoxy(0, 6);
}

void f5SortMatrix() {
	if (sort == -1) {
		cout << " Не выбрана сортировка!" << repeatString("\n", N);
		return;
	}
	printMatrix(matrix[0], N, 2);
	gotoxy(1, 1);
	switch (sort) {
	case 0:
		bubbleSort(matrix[0], N, 2);
		break;
	case 1:
		shakerSort(matrix[0], N, 2);
		break;
	case 2:
		combSort(matrix[0], N, 2);
		break;
	case 3:
		insertSort(matrix[0], N, 2);
		break;
	case 4:
		int maxLen = findMaxLen(matrix[0], N, 2);
		quickSort(&matrix[0][0], N, 2, maxLen, &matrix[0][0] + N * N - 1, &matrix[0][0]);
		break;
	}
	gotoxy(0, N + 1);

}

void f6ChangeMatrix() {
	printf(" Введите число: ");
	cin >> nMath;
	gotoxy(16, 1);
	cout << nMath << endl;
	printf(" [ + ]\n");
	printf(" [ - ]\n");
	printf(" [ * ]\n");
	(nMath != 0) ? printf(" [ / ]\n") : printf(" На 0 делить нельзя\n");
}

void f7IHT1() {
	int matrix1[N][N];
	createMatrix(matrix1[0], N, 2, -30, 30);
	printf(" Новая матрица:\n");
	printMatrix(matrix1[0], N, 2);
	for (int i = 0; i < N * N; i++) {
		*(matrix[0] + i) += *(matrix1[0] + i);
	}
	printf(" Изменённая матрица:\n");
	printMatrix(matrix[0], N, 2);
}

void print() {
	int len = 0;
	cout << "\b";
	cout << " ";
	if (prevState[0] != state[0]) {
		system("cls");
		gotoxy(0, 1);
		switch (state[0]) {
		case 0:
			mainMenu();
			break;
		case 1:
			f1CreateMatrix();
			break;
		case 2:
			f2PrintMatrix();
			break;
		case 3:
			f3ShuffleMatrix();
			break;
		case 4:
			f4ChooseSort();
			break;
		case 5:
			f5SortMatrix();
			break;
		case 6:
			f6ChangeMatrix();
			break;
		case 7:
			f7IHT1();
			break;
		case 8:
			switch (printType) {
			case 0:
				printMatrix(matrix[0], N, 2);
				break;
			case 1:
				printMatrixA(matrix[0], N, 2);
				break;
			case 2:
				printMatrixB(matrix[0], N, 2);
				break;
			}
			break;
		case 9:
			printMatrix(matrix[0], N, 2);
			gotoxy(0, 1);
			shuffleMatrix(matrix[0], N, 2, shuffleType);
			SetConsoleTextAttribute(hConsole, 15);
			gotoxy(0, N + 1);
			break;
		case 10:
			mathWthMatrix(matrix[0], N, 2, actType, nMath);
			printMatrix(matrix[0], N, 2);
			break;
		}
		printf(" exit");
	}
	prevState[0] = state[0];
	gotoxy(0, 0);
	printf(" Практическая работа No3");
	len = length[state[0]] + 1;
	state[1] = state[1] % len;
	gotoxy(0, state[1] + 1);
	printf("%c", 62);
}

void activateFunc() {
	if (state[1] == length[state[0]]) {
		switch (state[0]) {
		case 0:
			active = 0;
			break;
		case 8:
			state[0] = 2;
			break;
		case 9:
			state[0] = 3;
			break;
		case 10:
			state[0] = 6;
			break;
		default:
			state[0] = 0;
		}
		return;
	}
	switch (state[0]) {
	case 0:
		switch (state[1]) {
		default:
			state[0] = state[1] + 1;
		}
		break;
	case 2:
		state[0] = 8;
		printType = state[1];
		break;
	case 3:
		state[0] = 9;
		shuffleType = state[1];
		break;
	case 4:
		switch (state[1]) {
		default:
			sort = state[1];
			state[0] = 0;
			break;
		}
		break;
	case 6:
		actType = state[1] - 1;
		if (actType == 3 && nMath == 0) { break; }
		state[0] = 10;
		break;
	}
}

int menu()
{
	print();
	char c = _getch();
	while (active) {
		c = _getch();
		switch (c) {
		case 72:
			state[1] += length[state[0]] + 1 - step[state[0]];
			state[1] = state[1] % (length[state[0]] + 1);
			break;
		case 80:
			state[1] += step[state[0]];
			state[1] = state[1] % (length[state[0]] + 1);
			break;
		case 13:
			activateFunc();
			state[1] = length[state[0]] + step[state[0]];
			state[1] = state[1] % (length[state[0]] + 1);
			break;
		}
		print();
	}

	gotoxy(0, 20);
	system("pause");
	return 0;
}


int main() {
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));

	menu();

	SetConsoleTextAttribute(hConsole, 15);
	gotoxy(0, 20);

	return 0;
}