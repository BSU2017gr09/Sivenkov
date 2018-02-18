/* В массиве размера N, заполненного случ.числами от 0 до 10, подсчитать количество элементов, встречающихся более одного раза. */

#include <iostream>
#include <clocale>
#include <ctime>

#define MIN_RAND 0
#define MAX_RAND 10

using namespace std;

void initArray(int* arr, int size);
void printArray(int* arr, int size);
int countNumsInArray(int* arr, int size);

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

	int count = 0;
	count = countNumsInArray(arr, N);
	cout << "Кол-во элементов, встречающихся более одного раза: " << count << "\n\n";

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

int countNumsInArray(int* arr, int size) {
	int count = 0;
	unsigned char isThereNum[11] = {};
	for (int *end = arr + size; arr < end; arr++) {
		switch (isThereNum[*arr]) {
			case 0:
				isThereNum[*arr]++;
				break;
			case 1:
				isThereNum[*arr]++;
				count++;
				break;
			default:
				break;
		}
	}
	return count;
}

void printArray(int* arr, int size) {
	for (int *end = arr + size; arr < end; arr++) {
		cout << *arr << ' ';
	}
	cout << '\n';
}