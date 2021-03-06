﻿#include <iostream>
#include <clocale>
#include <complex.h>

using namespace std;

class Complex {
	private:
		double re;
		double im;
		double binPower(double a, int n) {
			double res;
			if (n == 1) return a;
			if (!n) return 1;
			if (n % 2) {
				n--;
				res = binPower(a, n / 2);
				return res * res * a;
			}
			else {
				res = binPower(a, n / 2);
				return res * res;
			}
		}
	public:
		Complex(double re = 0, double im = 0, bool debug = false): re(re), im(im) {
			if (debug) cout << "Complex constructor is working\n";
		};

		~Complex() {};

		Complex(Complex&& other) {
			re = other.re;
			im = other.im;
		};

		Complex& operator=(const Complex &other) {
			if (this != &other) {
				this->re = other.re;
				this->im = other.im;
			}
			return *this;
		};

		Complex& operator+=(const Complex &other) {
			this->re += other.re;
			this->im += other.im;
			return *this;
		};

		Complex& operator-=(const Complex &other) {
			this->re -= other.re;
			this->im -= other.im;
			return *this;
		};

		Complex& operator*=(const Complex &other) {
			double resRe = other.re * this->re - other.im * this->im;
			double resIm = other.re * this->im + other.im * this->re;
			this->re = resRe;
			this->im = resIm;
			return *this;
		};

		Complex& operator/=(const Complex &other) {
			if (!other.re && !other.im) {
				cout << "Exception: Dividing by zero. ";
				system("pause");
				exit(1);
			}
			double resRe = (this->re * other.re + this->im * other.im) / (other.re * other.re + other.im * other.im);
			double resIm = (other.re * this->im - this->re * other.im) / (other.re * other.re + other.im * other.im);
			this->re = resRe;
			this->im = resIm;
			return *this;
		};

		Complex operator+(const Complex& other) {
			return Complex(this->re + other.re, this->im + other.im);
		}

		Complex operator-(const Complex& other) {
			return Complex(this->re - other.re, this->im - other.im);
		}

		Complex operator*(const Complex& other) {
			return Complex(other.re * this->re - other.im * this->im, other.re * this->im + other.im * this->re);
		}

		Complex operator/(const Complex& other) {
			if (!other.re && !other.im) {
				cout << "Exception: Dividing by zero. ";
				system("pause");
				exit(1);
			}
			return Complex((this->re * other.re + this->im * other.im) / (other.re * other.re + other.im * other.im), (other.re * this->im - this->re * other.im) / (other.re * other.re + other.im * other.im));
		}

		Complex operator==(const Complex& other) {
			if (this->im == other.im && this->re == other.re) return true;
			else return false;
		}

		Complex operator!=(const Complex& other) {
			if (this->im == other.im && this->re == other.re) return false;
			else return true;
		}

		Complex operator^(const int power) {					// Возведение в степень работает ТОЛЬКО в том случае, если power - целое число
			double r = this->abs();
			double fi = acos(this->re / r);
			fi *= power;
			if (power < 0)
				r = 1 / binPower(r, -power);
			else 
				r = binPower(r, power);
			return Complex(r * cos(fi), r * sin(fi));
		}

		friend ostream& operator<<(ostream &stream, Complex &tmp) {
			stream << tmp.re;
			if (tmp.im != 0) {
				if (tmp.im > 0) stream << '+';
				if (tmp.im != 1) stream << tmp.im;
				stream << 'i';
			}
			return stream;
		};																
		friend istream& operator>>(istream &stream, Complex &tmp) {
			stream >> tmp.re >> tmp.im;
			return stream;
		};

		double abs() {
			return sqrt(this->re * this->re + this->im * this->im);
		};

		double getre() {
			return re;
		}

		double getim() {
			return im;
		}
};

int main() {
	setlocale(LC_ALL, ".1251");
//и чего тут пусто????
	system("pause");
	return 0;
}
