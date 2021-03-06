﻿#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <clocale>
#include <cstring>
#include <conio.h>
#include <fstream>
#include <Windows.h>

using namespace std;

typedef unsigned short int datint;

const datint days[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
const int paramCount = 6;
bool param[paramCount] = { true, true, true, true, true, true };			// Параметры ввода и сравнения класса Car
// неочевидно, что пользователи твоего класса должны включать эту ГЛОБАЛЬНУЮ переменную во все свои программы

void setStr(char*& dest, char* src) {
	try {
		dest = new char[strlen(src) + 1];// и тут, ха-ха-ха, утечка памяти если НЕ ты перед вызовом не проверил и не удалил...
	}
	catch (...) {	
		cout << "Ошибка при выделении памяти\n";
		system("pause");
		exit(1);
	}
	strcpy(dest, src);

};
void getStr(istream& stream, char*& str, int size) {
	while (1) {
		fflush(stdin);
		stream.getline(str, size);
		if (strlen(str)) break;
	}
}

class Date {
private:
	datint dd;
	datint mm;
	datint yyyy;

	static bool isLeap(datint year) {
		return ((!(year % 4) && (year % 100)) || !(year % 400));
	};
public:
	Date(datint dd = 0, datint mm = 0, datint yyyy = 0) : dd(dd), mm(mm), yyyy(yyyy) {};

	~Date() {};

	Date(const Date& other) : dd(other.dd), mm(other.mm), yyyy(other.yyyy) {};

	Date& operator=(const Date& other) {
		if (this != &other) {
			dd = other.dd;
			mm = other.mm;
			yyyy = other.yyyy;
		}
		return *this;
	};

	Date(const Date&& other): dd(other.dd), mm(other.mm), yyyy(other.yyyy) {};

	Date& operator=(const Date&& other) {
		if (this != &other) {
			dd = other.dd;
			mm = other.mm;
			yyyy = other.yyyy;
		}
		return *this;
	};

	bool operator==(const Date other) {
		return (this->dd == other.dd && this->mm == other.mm && this->yyyy == other.yyyy);
	}

	bool operator!=(const Date other) {
		return !(this->dd == other.dd && this->mm == other.mm && this->yyyy == other.yyyy);
	}

	friend ostream& operator<<(ostream &stream, const Date& other) {
		if (other.dd < 10) stream << '0';
		stream << other.dd << '.';
		if (other.mm < 10) stream << '0';
		stream << other.mm << '.' << other.yyyy;
		return stream;
	};

	friend istream& operator>>(istream &stream, Date& other) {
		//cout << "Введите дату\n";
		while (1) {
			stream >> other.dd >> other.mm >> other.yyyy;
			if (other.mm > 12 || other.mm < 1) {
				cout << "Ошибка, повторите ввод\n";
				continue;
			}
			if ((other.dd > 1) && (other.dd <= days[other.mm - 1])) break;
			if ((other.mm == 2) && (isLeap(other.yyyy)) && (other.dd <= days[other.mm - 1] + 1)) break;
			cout << "Ошибка, повторите ввод\n";
		}
		return stream;
	}

	datint getDay() {
		return dd;
	};

	datint getMonth() {
		return mm;
	};

	datint getYear() {
		return yyyy;
	};

};

class Car {
private:
	Date regDate;
	char* model;
	datint prodYear;
	char* owner;
	char* color;
	char* licPlate;
public:
	Car(Date inputRegDate = Date(), char* inputModel = nullptr, datint inputProdYear = 0, char* inputOwner = nullptr, char* inputColor = nullptr, char* inputLicPlate = nullptr) {
		regDate = inputRegDate; //что за колхоз? Гле список инициализации?
		prodYear = inputProdYear;
		/* вот этот код и должен быть внутти сеттера!!!! А не снаружи плодить проверки
		if (inputModel != nullptr) setStr(model, inputModel);
		else model = nullptr;*/
		if (inputModel != nullptr) setStr(model, inputModel);
		else model = nullptr;
		if (inputOwner != nullptr) setStr(owner, inputOwner);
		else owner = nullptr;
		if (inputColor != nullptr) setStr(color, inputColor);
		else color = nullptr;
		if (inputLicPlate != nullptr) setStr(licPlate, inputLicPlate);
		else licPlate = nullptr;
	};

	~Car() {
		//cout << "Car destructor\n";
		delete[] model;
		delete[] owner;
		delete[] color;
		delete[] licPlate;
	};

	datint getProdYear() {
		return prodYear;
	}

	Car(const Car& other) {
		regDate = other.regDate;
		prodYear = other.prodYear;
		if (other.model != nullptr) setStr(model, other.model);
		else model = nullptr;

		if (other.owner != nullptr) setStr(owner, other.owner);
		else owner = nullptr;

		if (other.color != nullptr) setStr(color, other.color);
		else color = nullptr;

		if (other.licPlate != nullptr) setStr(licPlate, other.licPlate);
		else licPlate = nullptr;
	};

	Car(const Car&& other) { //нет смысла в таком move. Он дублирует обычный copy. Здесь то и надо было оптимизировать!!!
		regDate = other.regDate;
		prodYear = other.prodYear;
		if (other.model != nullptr) setStr(model, other.model);
		else model = nullptr;
		if (other.owner != nullptr) setStr(owner, other.owner);
		else owner = nullptr;
		if (other.color != nullptr) setStr(color, other.color);
		else color = nullptr;
		if (other.licPlate != nullptr) setStr(licPlate, other.licPlate);
		else licPlate = nullptr;
	};

	Car& operator=(const Car& other) {
		if (this != &other) {
			regDate = other.regDate;
			prodYear = other.prodYear;
			if (other.model != nullptr) {
				delete[] model;
				setStr(model, other.model);
			}
			else model = nullptr;
			if (other.owner != nullptr) {
				delete[] owner;
				setStr(owner, other.owner);
			}
			else owner = nullptr;
			if (other.color != nullptr) {
				delete[] color;
				setStr(color, other.color);
			}
			else color = nullptr;
			if (other.licPlate != nullptr) {
				delete[] licPlate;
				setStr(licPlate, other.licPlate);
			}
			else licPlate = nullptr;
		}
		return *this;
	};

	bool operator==(const Car other) {
		if (param[0])
			if (this->regDate != other.regDate) return false;
		if (param[1])
			if (strcmp(this->model, other.model)) return false;
		if (param[2])
			if (this->prodYear != other.prodYear) return false;
		if (param[3])
			if (strcmp(this->owner, other.owner)) return false;
		if (param[4]) 
			if (strcmp(this->color, other.color)) return false;
		if (param[5])
			if (strcmp(this->licPlate, other.licPlate)) return false;

		return true;
	}

	friend ostream& operator<<(ostream& stream, const Car& other) {
		stream << "Модель: " << (other.model ? other.model : "") << "\nГод выпуска: " << other.prodYear << "\nЦвет: " << (other.color ? other.color : "") << "\nРегистрационный номер: " << (other.licPlate ? other.licPlate : "") << "\nВладелец: " << (other.owner ? other.owner : "") << "\nДата регистрации: " << other.regDate << "\n\n";
		return stream;
	}
	friend istream& operator>>(istream& stream, Car& other) {
		const int bufferSize = 255;
		char* buffer;

		try {
			buffer = new char[bufferSize];
		}
		catch (...) {
			cout << "Ошибка при выделении памяти\n";
			system("pause");
			exit(1);
		}

		if (param[0]) {
			cout << "Введите дату регистрации автомобиля: ";
			stream >> other.regDate;
		}

		if (param[1]) {
			cout << "Введите модель автомобиля: ";
			getStr(stream, buffer, bufferSize);
			setStr(other.model, buffer);
		}

		if (param[2]) {
			cout << "Введите год выпуска: ";
			while (1) {
				stream >> other.prodYear;
				if (other.prodYear > other.regDate.getYear() && param[0])
					cout << "Год выпуска больше года в дате регистрации! Повторите ввод\n";
				else break;
			}
		}

		if (param[3]) {
			cout << "Введите имя владельца: ";
			getStr(stream, buffer, bufferSize);
			setStr(other.owner, buffer);
		}

		if (param[4]) {
			cout << "Введите цвет автомобиля: ";
			getStr(stream, buffer, bufferSize);
			setStr(other.color, buffer);
		}

		if (param[5]) {
			cout << "Введите регистрационный номер: ";
			getStr(stream, buffer, bufferSize);
			setStr(other.licPlate, buffer);
		}
	}

	void writeOnDisk(ostream& stream) {//выводим в текстовом виде. Некомпактно (((((
		stream << this->regDate.getDay() << ' ' << this->regDate.getMonth() << ' ' << this->regDate.getYear() << '\n';
		stream << this->model << '\n';
		stream << this->prodYear << '\n';
		stream << this->owner << '\n';
		stream << this->color << '\n';
		stream << this->licPlate;
	};

	void getFromDisk(ifstream& stream) {
		const int bufferSize = 255;
		char* buffer;

		try {
			buffer = new char[bufferSize];
		}
		catch (...) {
			cout << "Ошибка при выделении памяти\n";
			system("pause");
			exit(1);
		}

		stream >> regDate;

		getStr(stream, buffer, bufferSize);
		setStr(model, buffer);

		stream >> prodYear;

		getStr(stream, buffer, bufferSize);
		setStr(owner, buffer);

		getStr(stream, buffer, bufferSize);
		setStr(color, buffer);

		getStr(stream, buffer, bufferSize);
		setStr(licPlate, buffer);
	};
};


class Node {

public:
	Car val;
	Node* next;

	Node(Car val = Car(), Node* next = nullptr) : val(val), next(next) {};

	~Node() {};

	Node(const Node& other) : val(other.val), next(other.next) {};

	Node(const Node&& other) : val(other.val), next(other.next) {};

	Node& operator=(const Node& other) {
		if (this != &other) {
			this->val = other.val;
			this->next = other.next;
		}
		return *this;
	};

	Node& operator=(const Node&& other) {
		if (this != &other) {
			this->val = other.val;
			this->next = other.next;
		}
		return *this;
	};

	friend ostream& operator<<(ostream& stream, const Node& other) {
		stream << other.val;
		return stream;
	}
};

class List {
private:
	Node* root;
public:
	Node*& operator[](const int& index) {
		if (index >= 0) {
			if (root == nullptr) {
				cout << "List is empty!\n";
			}
			else {
				Node* tmp = root;
				for (int i = 0; i < index; i++) {
					if (tmp == nullptr) break;
					tmp = tmp->next;
				}
				if (tmp != nullptr) return tmp;
			}
		}
	};
	int len() {
		int res = 0;
		if (root == nullptr) return res;
		Node* tmp = root;
		do {
			res++;
			tmp = tmp->next;
		} while (tmp != nullptr);
		return res;
	};
	List(Node* root = nullptr) : root(root) {};
	~List() {
		//cout << "List destructor\n";
		Node* tmp = root;
		while (tmp != nullptr) {
			tmp = tmp->next;
			//cout << "Элемент со значением " << root->val << " удален\n";
			delete root;
			root = tmp;
		}
	};

	void clear() {
		Node* tmp = root;
		while (tmp != nullptr) {
			tmp = tmp->next;
			delete root;
			root = tmp;
		}
		root = nullptr;
	};

	List& operator=(const List& other) {
		if (this == &other) return *this;
		this->~List();
		//this->print();
		if (other.root == nullptr) return *this;
		root = new Node(other.root->val);
		Node* tmp = this->root;
		Node* otherTmp = other.root->next;
		while (otherTmp != nullptr) {
			tmp->next = new Node(otherTmp->val);
			tmp = tmp->next;
			otherTmp = otherTmp->next;
		}
		return *this;
	};

	void ins(Node newNode) {
		if (root == nullptr) {
			root = new Node(newNode);
			return;
		}

		Node* tmp = root;
		while (tmp->next != nullptr) {
			tmp = tmp->next;
		}
		tmp->next = new Node(newNode);
	};

	void ins(Node newNode, int pos) {
		if (root == nullptr) return;
		Node* tmp = root;
		for (int i = 0; i < pos; i++) {
			tmp = tmp->next;
			if (tmp == nullptr) break;
		}
		if (tmp == nullptr) return;
		Node* newNodePtr = new Node(newNode);
		Node* nextNodePtr = tmp->next;
		newNodePtr->next = nextNodePtr;
		tmp->next = newNodePtr;
	};

	void ins(List& insList, int pos) {
		if (root == nullptr) return;
		if (insList.root == nullptr) return;
		Node* tmp = root;
		for (int i = 0; i < pos; i++) {
			tmp = tmp->next;
			if (tmp == nullptr) break;
		}
		if (tmp == nullptr) return;
		Node* nextNodePtr = tmp->next;
		tmp->next = insList.root;
		while (tmp->next != nullptr) {
			tmp = tmp->next;
		}
		tmp->next = nextNodePtr;
		insList.root = nullptr;
	};

	void ins(List& insList) {
		if (root == nullptr) {
			if (insList.root == nullptr) return;
			root = insList.root;
			insList.root = nullptr;
		}
		Node* tmp = root;
		while (tmp->next != nullptr) {
			tmp = tmp->next;
		}
		tmp->next = insList.root;
		insList.root = nullptr;
	}

	void del(int pos) {
		Node* tmp;
		if (root == nullptr) return;
		if (!pos) {
			tmp = root->next;
			delete root;
			root = tmp;
			return;
		}

		tmp = root;
		for (int i = 0; i < pos - 1; i++) {
			if (tmp->next == nullptr) break;
			tmp = tmp->next;
		}
		if (tmp->next == nullptr) return;
		Node* nextNodePtr = tmp->next->next;
		delete tmp->next;
		tmp->next = nextNodePtr;
	};

	void print() {
		if (root == nullptr) {
			//cout << "List is empty!\n";
			return;
		}
		Node* tmp = root;
		while (tmp != nullptr) {
			cout << tmp->val;
			tmp = tmp->next;
		}
		cout << endl;
	};

	void sort() {
		if (root == nullptr) return;
		Node* p = nullptr;
		Node* tmp = root;
		while (tmp->next != nullptr) {
			p = tmp->next;
			do {
				if (p->val.getProdYear() < tmp->val.getProdYear()) {
					Car buffer = p->val;
					p->val = tmp->val;
					tmp->val = buffer;
				}
				p = p->next;
			} while (p != nullptr);
			tmp = tmp->next;
		}
	}

	void save(ofstream& fout) {
		Node* nodeNow = root;
		while (nodeNow != nullptr) {
			nodeNow->val.writeOnDisk(fout);
			if (nodeNow->next != nullptr) fout << '\n';
			nodeNow = nodeNow->next;
		}
	};

	bool isEmpty() {
		return (root == nullptr);
	};

	void search() {
		system("cls");

		char c_input;
		int count = 0;
		bool flag = false;
		List res;
		
		Car templCar;

		cout << "Введите количество параметров для поиска\n";
		while (1) {
			fflush(stdin);
			cin >> count;
			if (count > 6 || count <= 0) cout << "Неверное количество параметров\n";
			else break;
		}

		cout << "Введите номера параметров для поиска:\n\
1 - по дате регистрации\n\
2 - по марке автомобиля\n\
3 - по году пр-ва\n\
4 - по имени владельца\n\
5 - по цвету автомобиля\n\
6 - по регистрационному номеру\n";

		for (int i = 0; i < paramCount; i++) param[i] = false;

		while (1) {
			fflush(stdin);
			for (int i = 0; i < count; i++) {
				cin >> c_input;
				c_input -= '0';
				if (c_input > 0 && c_input < 7) {
					param[c_input - 1] = true;
					flag = true;
				}
			}
			if (!flag) cout << "Ничего не выбрано, повторите ввод\n";
			else break;
		}

		cout << "Введите шаблон для поиска:\n\n";
		cin >> templCar;

		//Search

		Node* elemNow = root;
		while (elemNow != nullptr) {
			if (elemNow->val == templCar) res.ins(elemNow->val);
			elemNow = elemNow->next;
		}

		int length = res.len();
		if (!length) {
			cout << "Совпадений не найдено\n";
			system("pause");
		}
		else {
			cout << "Найдено " << length << " результатов. Показать их?(Y/N)\n";
			while (1) {
				fflush(stdin);
				cin >> c_input;
				if (c_input == 'y') {
					cout << '\n';
					res.print();
					system("pause");
					break;
				}
				if (c_input == 'n') break;
			}
		}
		for (int i = 0; i < paramCount; i++) param[i] = true;
		res.~List();
	};

	void searchNotOlder() {
		system("cls");

		Node* elemNow = root;
		datint searchYear;
		List res;
		char c_input;

		cout << "Введите год\n";
		cin >> searchYear;

		while (elemNow != nullptr) {
			if (elemNow->val.getProdYear() >= searchYear) res.ins(elemNow->val);
			elemNow = elemNow->next;
		}

		int length = res.len();
		if (!length) {
			cout << "Совпадений не найдено\n";
			system("pause");
		}
		else {
			cout << "Найдено " << length << " результатов. Показать их?(Y/N)\n";
			while (1) {
				fflush(stdin);
				cin >> c_input;
				if (c_input == 'y') {
					cout << '\n';
					res.print();
					system("pause");
					break;
				}
				if (c_input == 'n') break;
			}
		}
		res.~List();
	}
};

using namespace std;

void openBase(List&);


int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	//setlocale(LC_ALL, ".1251");

	List base;
	//base.ins(Node(Car(Date(15, 5, 2012), "BMW", 1999, "Егор Сивенков", "blue", "7777 AA-7")));
	ofstream fout;
	ifstream fin;
	char* buffer = new char[1024];
	char op;
	Car carBuffer;


	while (1) {
		system("cls");
		cout << "Выберите операцию:\n";
		cout << "0 - Выход\n";
		cout << "1 - Открыть текущюю базу данных\n";
		cout << "2 - Открыть базу данных, записаную на диск\n";
		fflush(stdin);
		cin >> op;
		op -= '0';
		if (op >= 0 && op < 3) {
			switch (op) {
			case 0:
				while (1) {
					cout << "Желаете ли вы сохранить базу?(Y/N)\n";
					fflush(stdin);
					cin >> op;
					if (op == 'y') {
						cout << "Введите путь для сохранения файла\n";
						while (1) {
							getStr(cin, buffer, 1024);
							fout.open(buffer, ios::out);
							if (!fout) cout << "Ошибка\n";
							else break;
						}
						base.save(fout);
						fout.close();
						delete[] buffer;
						return 0;
					}
					if (op == 'n') {
						base.~List();
						return 0;
					}
				}
				break;
			case 2:
				cout << "Введите путь к файлу\n";
				while (1) {
					getStr(cin, buffer, 1024);
					fin.open(buffer, ios::in);
					if (!fin) cout << "Неверный путь к файлу\n";
					else break;
				}
				
				if (base.len()) base.clear();

				while (!fin.eof()) {
					carBuffer.getFromDisk(fin);
					base.ins(carBuffer);
				}
				fin.close();
			case 1:
				openBase(base);
				break;
			default:
				break;
			}
		}
	}
}

void openBase(List& base) {
	int indexNow = 0;
	char op;
	//Car tmp(Date(15, 5, 2010), "Mercedes", 1999, "Егор Сивенков", "black", "5555 AA-7");
	Car tmpCar;

	while (1) {
		system("cls");

		cout << "0 - вернуться в главное меню	1 - Добавить новую запись	2 - Удалить текущую запись\n\
3 - Сортировка по году выпуска	4 - Список машин не старше заданного года\n\
5 - Поиск по заданной комбинации признаков\n\
[ - Предыдущая запись	] - Следующая запись\n\n";

		if (base.isEmpty()) cout << "База пуста!\n";
		else {
			cout << "Элемент " << indexNow + 1 << " из " << base.len() << "\n\n";
			cout << *base[indexNow];
		}
		fflush(stdin);
		op = _getch();
		switch (op) {
		case '0':
			return;
			break;
		case '1':
			cin >> tmpCar;
			base.ins(Node(Car(tmpCar)));
			break;
		case '2':
			cout << "Вы действительно хотите удалить данную запись?(Y/N)\n";
			while (1) {
				fflush(stdin);
				cin >> op;
				if (op == 'y') {
					base.del(indexNow);
					break;
				}
				if (op == 'n') break;
			}
			break;
		case '4':
			base.searchNotOlder();
			break;
		case '3':
			base.sort();
			break;
		case '5':
			base.search();
		case ']':
			indexNow++;
			break;
		case '[':
			indexNow--;
			break;
		}
		if (indexNow >= base.len()) indexNow--;
		if (indexNow < 0) indexNow++;
	}

}
