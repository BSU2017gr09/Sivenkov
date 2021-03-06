/* Положительные элементы массива А(N) переставить в конец массива, сохраняя порядок следования. Отрицательные элементы расположить в порядке убывания. Дополнительный массив не использовать. */

#include <iostream>
#include <clocale>
#include <ctime>

using namespace std;

template<typename T>void giveMemory(T* &arr, int size);
template<typename T>void freeArray(T* &arr, int size);
template<typename T>void qsort(T* arr, int l, int r);
template<typename T>void printArray(T* arr, int size, char delim = ' ');
template<typename T>void initArray(T* arr, int size);
template<typename T>void shuffleArray(T* arr, int size);

int main() {
	setlocale(LC_ALL, ".1251");
	srand(time(NULL));

	int N;
	cout << "Введите кол-во элементов массива\n";
	cin >> N;

	int *arr;
	giveMemory(arr, N);
	initArray(arr, N);
	printArray(arr, N);

	shuffleArray(arr, N);
	printArray(arr, N);

	freeArray(arr, N);
	system("pause");
	return 0;
}

template<typename T>void giveMemory(T* &arr, int size) {
	try {
		arr = new T[size];
	}
	catch (...) {
		cout << "Ошибка при выделении памяти для массива. ";
		system("pause");
		exit(1);
	}
}

template<typename T>void printArray(T* arr, int size, char delim) {
	cout << "Элементы массива:\n";
	for (T* end = arr + size; arr < end; arr++) {
		cout << *arr << delim;
	}
	cout << "\n\n";
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
		while (*(arr + i) > middle) i++;
		while (*(arr + j) < middle) j--;
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

template<typename T>void initArray(T* arr, int size) {
	cout << "Введите элементы массива\n";
	for (T* end = arr + size; arr < end; arr++) {
		cin >> *arr;
		//*arr = rand() % 101 - 50;
	}
}

template<typename T>void shuffleArray(T* arr, int size) {
	T *start = arr;
	T *end = arr + size;
	T tmp;

	T *k = arr + size - 1;
	for (T* i = end - 1; i >= start; i--) {
		if (*i > 0) {
			tmp = *i;
			*i = *k;
			*k = tmp;
			k--;
		}
	}

	k = start;
	for (T* i = start; i < end; i++) {
		if (*i < 0) {
			tmp = *i;
			*i = *k;
			*k = tmp;
			k++;
		}
	}
	qsort(arr, 0, k - start - 1);
}