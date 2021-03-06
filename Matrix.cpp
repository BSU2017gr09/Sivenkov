﻿/* 79. В каждом столбце массива А(N,М) после первого отрицательного
элемента вставить максимальную цепочку из положительных элементов
данного столбца.Расположить столбцы в порядке возрастания по количеству
вставленных элементов. */

#include <iostream>
#include <clocale>
#include <iomanip>
#include <ctime>

/* N - кол-во строк
   M - кол-во столбцов
   первый индекс - номер столбца
   второй индекс - номер строки
*/

using namespace std;

typedef void menu(int**&, int&, int&, int*&);
typedef menu* ptrMenu;

void exit(int**&, int&, int&, int*&);
void help(int**&, int&, int&, int*&);
void input(int**&, int&, int&, int*&);
void transform(int**&, int&, int&, int*&);
void output(int**&, int&, int&, int*&);

void foreach(int**&, int&, int&, int*&, ptrMenu);

template<typename T>void giveMemory(T*&, int);
void freeMemory(int**&, int);

void transformCol(int*&, int&);


int main() {
	setlocale(LC_ALL, ".1251");
	srand(time(NULL));

	int** matrix = nullptr;
	int N, M;
	char op;

	int* colSize = nullptr; // не понял что именно ты тут будешь хранить. По названию НЕ ОЧВИДНО. Комментария нет...

	ptrMenu function[] = { exit, help, input, transform, output };

	while (1) {
		cout << "Choose the operation number:\n";
		cout << "0 - Exit\n";
		cout << "1 - Help\n";
		cout << "2 - Input matrix\n";
		cout << "3 - Transform matrix\n";
		cout << "4 - Print matrix\n";

		cin >> op;
		op -= '0';
		if (op >= 0 && op < 5) {
			foreach(matrix, N, M, colSize, function[op]);
		}
	}
}

void foreach(int**& matrix, int& N, int& M, int*& colSize, ptrMenu function) {
	function(matrix, N, M, colSize);
}

void exit(int**& matrix, int& N, int& M, int*& colSize) {
	if (colSize != nullptr) delete[] colSize; //лишняя проверка
	if (matrix != nullptr) freeMemory(matrix, M); //лишняя проверка
	exit(0);
}

void help(int**& matrix, int& N, int& M, int*& colSize) {
	cout << "79. В каждом столбце массива А(N,М) после первого отрицательного\n\
элемента вставить максимальную цепочку из положительных элементов\n\
данного столбца.Расположить столбцы в порядке возрастания по количеству\n\
вставленных элементов.\n\n";
}

void input(int**& matrix, int& N, int& M, int*& colSize) {
	if (matrix != nullptr) freeMemory(matrix, M); //лишняя проверка
	if (colSize != nullptr) delete[] colSize; //лишняя проверка
	cout << "Enter nubber of rows\n";
	cin >> N;
	cout << "Enter number of columns\n";
	cin >> M;
	giveMemory(matrix, M);
	giveMemory(colSize, M);
	for (int i = 0; i < M; i++) {
		giveMemory(matrix[i], N);
		colSize[i] = N;
	}

	//cout << "Enter matrix's elements:\n";

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			//cin >> matrix[j][i];
			matrix[j][i] = rand() % 201 - 100;
		}
	}
}

template<typename T>void giveMemory(T*& arr, int size) {
	try {
		arr = new T[size];
	}
	catch (...) {
		cout << "Error in allocating memory\n";
		system("pause");
		exit(1);
	}
}

void freeMemory(int**& matrix, int M) {
	for (int i = 0; i < M; i++) {
		delete[] matrix[i]; //лучше потом еще =nullptr 
	}
	delete[] matrix; //лучше потом еще =nullptr
}

void output(int**& matrix, int& N, int& M, int*& colSize) {
	if (matrix == nullptr || colSize == nullptr) return;
	system("cls");
	int max = N;
	for (int i = 0; i < M; i++) {
		if (colSize[i] > max) {
			max = colSize[i]; //что это?
		}
	}

	for (int i = 0; i < max; i++) {
		for (int j = 0; j < M; j++) {
			if (colSize[j] <= i) cout << setw(4) << " ";
			else cout << setw(4) << matrix[j][i];
		}
		cout << '\n';
	}
	cout << '\n';
}

void transform(int**& matrix, int& N, int& M, int*& colSize) {
	for (int i = 0; i < M; i++) {
		transformCol(matrix[i], colSize[i]);
	}
}

void transformCol(int*& arr, int& size) {
	int indexNegative = -1;

	int indexLineNow = -1;
	int lengthNow = 0;
	int indexLineMax = -1;
	int lengthMax = 0;
	bool flag = false;

	for (int i = 0; i < size; i++) {
		if (arr[i] > 0) {
			if (!lengthNow) indexLineNow = i;
			lengthNow++;
		}
		if (arr[i] <= 0) {
			if (lengthNow > lengthMax) {
				indexLineMax = indexLineNow;
				lengthMax = lengthNow;
			}
			lengthNow = 0;
			indexLineNow = -1;

			if (arr[i] < 0 && !flag) {
				flag = true;
				indexNegative = i;
			}
		}
	}
	if (lengthNow > lengthMax) {
		indexLineMax = indexLineNow;
		lengthMax = lengthNow;
	}

	if (indexNegative == -1 || indexLineMax == -1) return;

	int* buffer;
	int bufferSize = size;
	giveMemory(buffer, bufferSize);
	for (int i = 0; i < size; i++) buffer[i] = arr[i];
	delete[] arr;
	size += lengthMax;
	giveMemory(arr, size);
	for (int i = 0; i < size; i++) arr[i] = buffer[i];

	int k = bufferSize - 1;
	while (k >= indexNegative + 1) {
		arr[k + lengthMax] = arr[k];
		k--;
	}

	if (indexLineMax > indexNegative) indexLineMax += lengthMax;
	
	for (int i = indexNegative + 1, j = 0; j < lengthMax; j++, i++) {
		arr[i] = arr[indexLineMax + j];
	}
}
