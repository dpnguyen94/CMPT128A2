#include <iostream>

using namespace std;

class Polynomial {
public:
	Polynomial();
	Polynomial(double C);
	Polynomial(const double a[], int size);
	Polynomial(const Polynomial& P);
	~Polynomial();
	friend Polynomial operator + (const Polynomial& P1, const Polynomial& P2);
	friend Polynomial operator - (const Polynomial& P1, const Polynomial& P2);
	friend Polynomial operator * (const Polynomial& P1, const Polynomial& P2);
	void operator = (const Polynomial& P);
	double& operator [] (int i);
	double evaluate(double x);
	int getSize();
	friend ostream& operator << (ostream& outs, const Polynomial& P);
private:
	int size;
	double *p;
};

Polynomial:: Polynomial() {
	size = 1;
	p = new double [size];
	p[0] = 0.0;	
}

Polynomial::Polynomial(double C) {
	size = 1;
	p = new double [size];
	p[0] = C;
}

Polynomial::Polynomial(const double a[], int size) {
	this -> size = size;
	p = new double [size];
	for (int i = 0; i < size; i ++) p[i] = a[i];
}

Polynomial::Polynomial(const Polynomial& P) {
	size = P.size;
	p = new double [size];
	for (int i = 0; i < size; i ++) p[i] = P.p[i];
}

Polynomial::~Polynomial() {
	delete [] p;
}

Polynomial operator + (const Polynomial& P1, const Polynomial& P2) {
	int size = P1.size > P2.size ? P1.size : P2.size;
	double *p = new double [size];

	for (int i = 0; i < size; i ++) {
		if (i >= P1.size) p[i] = P2.p[i];
		if (i >= P2.size) p[i] = P1.p[i];
		if (i < P1.size && i < P2.size) p[i] = P1.p[i] + P2.p[i];
	}

	return Polynomial(p,size);
}

Polynomial operator - (const Polynomial& P1, const Polynomial& P2) {
	int size = P1.size > P2.size ? P1.size : P2.size;
	double *p = new double [size];

	for (int i = 0; i < size; i ++) {
		if (i >= P1.size) p[i] = -P2.p[i];
		if (i >= P2.size) p[i] = P1.p[i];
		if (i < P1.size && i < P2.size) p[i] = P1.p[i] - P2.p[i];
	}

	return Polynomial(p,size);
}

Polynomial operator * (const Polynomial& P1, const Polynomial& P2) {
	int size = P1.size + P2.size - 1;
	double *p = new double [size];

	for (int i = 0; i < size; i ++) p[i] = 0.0;
	
	for (int i = 0; i < P1.size; i ++) 
		for (int k = 0; k < P2.size; k ++) 
			p[i + k] += P1.p[i] * P2.p[k];

	return Polynomial(p,size);
}

void Polynomial::operator = (const Polynomial& P) {
	delete [] p;
	size = P.size;
	p = new double [size];
	for (int i = 0; i < size; i ++) p[i] = P.p[i];
}

double& Polynomial::operator [] (int i) {
	return p[i];
}

double Polynomial::evaluate(double x) {
	double result = 0.0;
	for (int i = 0; i < size; i ++) {
		double temp = 1.0;
		for (int k = 0; k < i; k ++) temp *= x;
		result += p[i] * temp;
	}

	return result;
}

int Polynomial::getSize() {
	return size;
}

ostream& operator << (ostream& outs, const Polynomial& P) {
	outs << P.p[0] << " ";
	for (int i = 1; i < P.size; i ++) {
		if (P.p[i] > 0.0) outs << "+ " << P.p[i] << "x^" << i << " ";
		if (P.p[i] < 0.0) outs << "- " << -P.p[i] << "x^" << i << " ";
	}
	
	return outs;
}

//Q1
int compare_str(const char s1[], const char s2[]) {
	int len1 = 0, len2 = 0;
	while (s1[len1] != '\0') len1 ++;
	while (s2[len2] != '\0') len2 ++;

	int i = 0;
	while (i < len1 && i < len2) {
		if (s1[i] > s2[i]) return 1;
		if (s1[i] < s2[i]) return -1;

		i ++;
	}

	if (len1 > len2) return 1;
	if (len1 < len2) return -1;

	return 0;
}

//Q3
void swap(char a[], int start, int end) {
	if (start >= end) return;
	
	char temp = a[start];
	a[start] = a[end];
	a[end] = temp;
	
	swap(a,start + 1,end - 1);
}

void reverse(char a[], int size) {
	swap(a,0,size - 1);
}

int main() {
	//testing code
	Polynomial empty;
	cout << "Empty polynomial is " << empty << endl << endl;
	double one[] = {1};
	Polynomial One(one, 1);
	double quad[] = {3, 2, 1};
	double five[] = {1, 2, 4, 3.2, 5};
	Polynomial q(quad, 3);
	Polynomial c(five, 5);
	cout << "Polynomial One is: " << One << endl << endl;
	cout << "Polynomial q is: " << q << endl << endl;
	cout << "Polynomial c is: " << c << endl << endl;
	q[1] = 8;
	cout << "After q[1] = 8, q is: " << q << endl << endl;
	Polynomial p = q;
	cout << "Ater Polynomial p = q , polynomial p is: " << p << endl << endl;
	Polynomial r;
	r = c;
	cout << "After r = c, polynomial r is: " << r << endl << endl;
	cout << "Polynomial c:" << endl;
	for (int i = 0; i < 5; i++)
	cout << " term with degree " << i << " has coefficient " << c[i] << endl;
	cout << endl << "value of p(3.5) is " << p.evaluate(3.5) << endl;
	cout << "value of r(2) is " << r.evaluate(2) << endl;
	r = q + r;
	cout << endl << "After r = q + r, polynomial r is: " << r << endl;
	cout << "value of r(2) is " << r.evaluate(2) << endl << endl;
	r = One - q;
	cout << "value of (One - q)(2) is " << r.evaluate(2) << endl << endl;
	r = q * c;
	cout << "size of q*c is " << r.getSize() << endl;
	cout << "Polynomial q is: " << q << endl;
	cout << "Polynomial c is: " << c << endl;
	cout << "Polynomial r (= q*c) is: " << r << endl << endl;
	cout << "value of r(2) is " << r.evaluate(2) << endl << endl;
	cout << "5 + q makes polynomial " << 5 + q << endl << endl;
	cout << "5 * q makes polynomial " << 5 * q << endl << endl;
	cout << "q - 5 makes polynomial " << q - 5 << endl << endl;
	system("pause");
	return 0;
}