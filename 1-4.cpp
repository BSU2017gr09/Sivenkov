/* Элементы целочисленного массива А(N), значения которых оказались простыми числами, расположить в порядке возрастания, не нарушая порядка следования других элементов. */

#include <iostream>
#include <clocale>
#include <ctime>

using namespace std;

template<typename T>void giveMemory(T* &arr, int size);
template<typename T>void freeArray(T* &arr, int size);
template<typename T>void sortPrimes(T* arr, int l, int r);
template<typename T>void printArray(T* arr, int size, char delim = ' ');
template<typename T>void initArray(T* arr, int size);
bool isPrime(int x);

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

	sortPrimes(arr, 0, N - 1);
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

template<typename T>void sortPrimes(T* arr, int l, int r) {
	bool *isPrimeNum;
	giveMemory(isPrimeNum, r - l + 1);
	for (int i = l; i <= r; i++) {
		isPrimeNum[i] = isPrime(arr[i]);
	}

	T *end = arr + (r - l + 1);
	T tmp;
	for (T *i = arr; i < end - 1; i++) {
		for (T *j = i + 1; j < end; j++) {
			if (*i > *j && isPrimeNum[i - arr] && isPrimeNum[j - arr]) {
				tmp = *i;
				*i = *j;
				*j = tmp;
			}
		}
	} 
	freeArray(isPrimeNum, r - l + 1);
}

template<typename T>void initArray(T* arr, int size) {
	cout << "Введите элементы массива\n";
	for (T* end = arr + size; arr < end; arr++) {
		cin >> *arr;
		//*arr = rand() % 10 + 1;
	}
}

bool isPrime(int x) {
	if (x == 2) return true;
	if (!(x % 2) || x == 1) return false;

	int i;
	for (i = 3; i < sqrt(x) + 1; i += 2) {
		if (!(x % i)) return false;
	}
	return true;
}