/* В массиве размера N, заполненного случ.числами от 0 до 10, определить максимальную длину последовательности равных элементов. */

#include <iostream>
#include <clocale>
#include <ctime>

#define MIN_RAND 0
#define MAX_RAND 10

using namespace std;

void initArray(int* arr, int size);
void printArray(int* arr, int size);
int maxLenOfEqual(int* arr, int size);

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

	int length;
	length = maxLenOfEqual(arr, N);
	cout << "Максимальная длина последовательности равных элеменов: " << length << "\n\n";

	system("pause");
	return 0;
}

void initArray(int* arr, int size) {
	cout << "\nИнициализация массива...\n";
	for (int *end = arr + size; arr < end; arr++) {
		*arr = rand() % (MAX_RAND - MIN_RAND + 1) + MIN_RAND;
	}
	cout << "Инициализация завершена.\n\n";
}



void printArray(int* arr, int size) {
	for (int *end = arr + size; arr < end; arr++) {
		cout << *arr << ' ';
	}
	cout << '\n';
}

int maxLenOfEqual(int* arr, int size) {
	int lenMax = 0;
	if (size == 0) return lenMax;
	lenMax = 1;
	int lenNow = 1;
	arr++;
	for (int *end = arr + size; arr < end; arr++) {
		if (*arr == *(arr - 1)) lenNow++;
		else {
			if (lenNow > lenMax) lenMax = lenNow;
			lenNow = 1;
		}
	}
	return lenMax;
}