/* � ������� ������� N, ������������ ����.������� �� 0 �� 10, ���������� ������������ ����� ������������������ ������ ���������. */

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
	cout << "������� ���-�� ��������� �������\n";
	cin >> N;

	int *arr;
	try {
		arr = new int[N];
	}
	catch (...) {
		cout << "������ ��� ��������� ������ ��� �������.\n";
		system("pause");
		return 1;
	}

	initArray(arr, N);
	printArray(arr, N);

	int length;
	length = maxLenOfEqual(arr, N);
	cout << "������������ ����� ������������������ ������ ��������: " << length << "\n\n";

	system("pause");
	return 0;
}

void initArray(int* arr, int size) {
	cout << "\n������������� �������...\n";
	for (int *end = arr + size; arr < end; arr++) {
		*arr = rand() % (MAX_RAND - MIN_RAND + 1) + MIN_RAND;
	}
	cout << "������������� ���������.\n\n";
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