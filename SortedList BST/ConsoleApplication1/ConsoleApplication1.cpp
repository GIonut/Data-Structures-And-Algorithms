#include<iostream>
#include <string>
#include <assert.h>
#include<vector>
#include <ostream>
using namespace std;

class Complex
{
private :
	int a, b;
public:
	Complex() { a = b = 0; };
	Complex(int _a, int _b) : a(_a), b(_b) {};
	Complex(Complex& z) { a = z.a; b = z.b; };
	Complex(const Complex& z) { this->a = z.a; this->b = z.b; };

	int getReal() { return a; };
	int getImaginary() { return b; };
	bool operator==(Complex& other) { return a == other.a and b == other.b; };
	Complex operator/(int n) { if (n == 0) throw runtime_error("Division by 0!"); this->a /= n; this->b /= n; return *this; };
	friend ostream& operator<<(ostream& stream, const Complex& z) { stream << z.a << " " << z.b << "i"; return stream; };
	
};

template<typename T>
class Vector
{
	vector<T> v
public:
	Vector(vector<T> _v) : v{ _v } {}
	void printAll(ostream& stream) {
		for (auto element : v)
			stream << element << ", ";
	}

};

int main()
{
	Complex a{}, b{ 1, 2 }, c{ 6, 4 }, d{ b };
	assert(a.getReal() == 0 && a.getImaginary() == 0);
	assert(c.getImaginary() == 4);
	assert(b == d);
	Complex res1 = c / 2;
	cout << res1 << "\n";
	try
	{
		Complex res2 = b / 0;
	}
	catch (runtime_error& ex)
	{
		assert(strcmp(ex.what(), "Division by 0!") == 0);
	}

	Vector<string> v1{ vector<string>{"hello", "bye" } };
	v1.printAll(cout);
	Vector<Complex> v1{ vector<Complex>{a,b,c,d} };
	v1.printAll(cout);

	return 0;
}