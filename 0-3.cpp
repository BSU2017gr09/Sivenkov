/* Массив чисел размера N проинициализировать случайными числами из промежутка от -N до N. Написать функцию циклического сдвига элементов массива вправо на k элементов. */

#include <iostream>
#include <clocale>
#include <ctime>

using namespace std;

void initArray(int* arr, int size);
void printArray(int* arr, int size);
void cyclicReshuffle(int *arr, int size, int k);
void reverse(int *arr, int l, int r);

int main() {
	srand(time(NULL));
	setlocale(LC_ALL, ".1251");

	int N;
	cout << "Введите кол-во элементов массива\n";
	cin >> N;

	int *arr;
	try {
		arr = new int[N];
	}
	catch (...) {
		cout << "Ошибка при выделении памяти для массива.\n";
		system("pause");
		return 1;
	}

	initArray(arr, N);
	printArray(arr, N);

	int k;
	cout << "Введите кол-во сдвигаемых вправо элементов\n";
	cin >> k;
	k = N - k;

	cyclicReshuffle(arr, N, k);
	printArray(arr, N);

	system("pause");
	return 0;
}

void initArray(int* arr, int size) {
	cout << "\nИнициализация массива...\n";
	for (int *end = arr + size; arr < end; arr++) {
		*arr = rand() % (size - (-size) + 1) + (-size);
	}
	cout << "Инициализация завершена.\n\n";
}



void printArray(int* arr, int size) {
	for (int *end = arr + size; arr < end; arr++) {
		cout << *arr << ' ';
	}
	cout << '\n';
}

void reverse(int *arr, int l, int r) {
	int tmp;
	while (l < r) {
		tmp = *(arr + l);
		*(arr + l) = *(arr + r);
		*(arr + r) = tmp;
		l++;
		r--;
	}
}

void cyclicReshuffle(int *arr, int size, int k) {
	if (size == 0) return;
	reverse(arr, 0, k - 1);
	reverse(arr, k, size - 1);
	reverse(arr, 0, size - 1);
}