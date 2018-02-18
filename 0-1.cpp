/* � ������� ������� N, ������������ ����.������� �� 0 �� 10, ���������� ���������� ���������, ������������� ����� ������ ����. */

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

	int count = 0;
	count = countNumsInArray(arr, N);
	cout << "���-�� ���������, ������������� ����� ������ ����: " << count << "\n\n";

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