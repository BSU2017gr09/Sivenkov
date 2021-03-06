/* Расположить в порядке возрастания элементы массива А(N), начиная с k-го элемента. */

#include <iostream>
#include <clocale>
#include <ctime>

using namespace std;

template<typename T>void initArray(T* arr, int size);
template<typename T>void giveMemory(T* &arr, int size);
template<typename T>void printArray(T* arr, int size, char delim = ' ');
template<typename T>void freeArray(T* &arr, int size);
template<typename T>void qsort(T* arr, int l, int r);

int main() {
	setlocale(LC_ALL, ".1251");
	srand(time(NULL));

	int N;
	cout << "Введите размер массива\n";
	cin >> N;

	int *arr;
	giveMemory(arr, N);
	initArray(arr, N);
	printArray(arr, N);

	int k;
	cout << "Введите позицию начала сортировки\n";
	cin >> k;
	qsort(arr, k, N - 1);
	printArray(arr, N);

	freeArray(arr, N);
	system("pause");
	return 0;	
}

template<typename T>void initArray(T* arr, int size) {
	cout << "Введите элементы массива\n";
	for (T* end = arr + size; arr < end; arr++) {
		cin >> *arr;
		//*arr = rand() % 101;
	}
}

template<typename T>void giveMemory(T* &arr, int size) {
	try {
		arr = new T[size];
	}
	catch (...) {
		cout << "Ошибка при выделении памяти для массива\n";
		system("pause");
		exit(1);
	}
}

template<typename T>void printArray(T* arr, int size, char delim) {
	cout << "Элементы массива:\n";
	for (T* end = arr + size; arr < end; arr++) {
		cout << *arr << delim;
	}
	cout << '\n';
}

template<typename T>void freeArray(T* &arr, int size) {
	delete[size] arr;
}

template<typename T>void qsort(T* arr, int l, int r) {
	int i = l;
	int j = r;
	T tmp;
	T middle = *(arr + ((l + r) / 2));
	do {
		while (*(arr + i) < middle) i++;
		while (*(arr + j) > middle) j--;
		if (i <= j) {
			tmp = *(arr + i);
			*(arr + i) = *(arr + j);
			*(arr + j) = tmp;
			i++;
			j--;
		}
	} while (i <= j);
	if (l < j) qsort(arr, l, j);
	if (i < r) qsort(arr, i, r);
}