/* ������ ����� ������� N ������������������� ���������� ������� �� ���������� �� -N �� N. �������� ������� ������������ ������ ��������� ������� ������ �� k ���������. */

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

	int k;
	cout << "������� ���-�� ���������� ������ ���������\n";
	cin >> k;
	k = N - k;

	cyclicReshuffle(arr, N, k);
	printArray(arr, N);

	system("pause");
	return 0;
}

void initArray(int* arr, int size) {
	cout << "\n������������� �������...\n";
	for (int *end = arr + size; arr < end; arr++) {
		*arr = rand() % (size - (-size) + 1) + (-size);
	}
	cout << "������������� ���������.\n\n";
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