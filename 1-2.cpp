/* Даны точки плоскости своими координатами в виде двух одномерных массивов. Точки плоскости рассортировать по возрастанию расстояния до прямой ax + by + c = 0. */

#include <iostream>
#include <clocale>
#include <ctime>

using namespace std;

template<typename T>void giveMemory(T* &arr, int size);
template<typename T>void freeArray(T* &arr, int size);
template<typename T>void qsort(T* arr, T* coordX, T* coordY, int l, int r);
template<typename T>void initCoords(T* coordX, T* coordY, int size);
template<typename T>void printCoords(T* coordX, T* coordY, int size, char delim = '\n');
template<typename T>void calculateDistance(double* distance, T* coordX, T* coordY, int size, double line[]);
template<typename T>void printDistance(T* arr, int size, char delim = ' ');

int main() {
	setlocale(LC_ALL, ".1251");
	srand(time(NULL));

	int N;
	cout << "Введите количество точек\n";
	cin >> N;

	double *coordX, *coordY;
	giveMemory(coordX, N);
	giveMemory(coordY, N);
	initCoords(coordX, coordY, N);
	printCoords(coordX, coordY, N);

	double line[3];
	cout << "Введите коэффициенты прямой в уравнении ax+by+c=0\n";
	cin >> line[0] >> line[1] >> line[2];
	while (line[0] == 0 && line[1] == 0) {
		cout << "\nОшибка. Такой прямой не существует, повторите ввод\n\n";
		cin >> line[0] >> line[1] >> line[2];
	}
	cout << '\n';

	double *distance;
	giveMemory(distance, N);
	calculateDistance(distance, coordX, coordY, N, line);
	//printDistance(distance, N);
	qsort(distance, coordX, coordY, 0, N - 1);                   //Параллельно переносим координаты точек, чтобы координаты соответствовали расстоянию
	printCoords(coordX, coordY, N);
	printDistance(distance, N);

	freeArray(distance, N);
	freeArray(coordX, N);
	freeArray(coordY, N);
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

template<typename T>void printDistance(T* arr, int size, char delim) {
	cout << "Расстояния от точек до прямой:\n";
	for (T* end = arr + size; arr < end; arr++) {
		cout << *arr << delim;
	}
	cout << "\n\n";
}

template<typename T>void freeArray(T* &arr, int size) {
	delete[size] arr;
}

template<typename T>void qsort(T* arr, T* coordX, T* coordY, int l, int r) {
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

			tmp = *(coordX + i);
			*(coordX + i) = *(coordX + j);
			*(coordX + j) = tmp;

			tmp = *(coordY + i);
			*(coordY + i) = *(coordY + j);
			*(coordY + j) = tmp;
			i++;
			j--;
		}
	} while (i <= j);
	if (l < j) qsort(arr, coordX, coordY, l, j);
	if (i < r) qsort(arr, coordX, coordY, i, r);
}

template<typename T>void initCoords(T* coordX, T* coordY, int size) {
	cout << "Введите координаты точек\n";
	for (T* end = coordX + size; coordX < end; coordX++, coordY++) {
		cin >> *coordX >> *coordY;
	}
	cout << '\n';
}

template<typename T>void printCoords(T* coordX, T* coordY, int size, char delim) {
	cout << "Координаты точек:\n";
	for (T* end = coordX + size; coordX < end; coordX++, coordY++) {
		cout << '(' << *coordX << ", " << *coordY << ')' << delim;
	}
	cout << '\n';
}

template<typename T>void calculateDistance(double* distance, T* coordX, T* coordY, int size, double line[]) {
	for (T* end = coordX + size; coordX < end; coordX++, coordY++, distance++) {
		*distance = abs(line[0] * *coordX + line[1] * *coordY + line[2]) / sqrt(line[0] * line[0] + line[1] * line[1]);
	}
}