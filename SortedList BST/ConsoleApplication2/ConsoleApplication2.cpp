#include<iostream>
#include<string>
#include<vector>
#include <assert.h>
#include<algorithm>
using namespace std;

class Car
{
private:
	string name;
	int nr;

public:
	Car(string _name, int _nr) : name(_name), nr(_nr) {}
	friend ostream& operator<<(ostream& os, Car& car)
	{
		return os << car.name << " " << to_string(car.nr);
	}
	bool operator<=(Car& other)
	{
		return this->nr <= other.nr;
	}

};

template<typename T, typename U>
class List
{
private:
	vector<pair<T, U>> v;
	U n{};
public:
	List() {}
	void add(T Telem, U Uelem) { v.push_back(pair<T, U>(Telem, Uelem)); }
	void printReverse(ostream& os)
	{
		for (auto it = v.rbegin(); it != v.rend(); it++)
			os << it->first << "->" << it->second << "\n";
	}
	void sortByFirstComponent()
	{
		if (this->v.size() == 0)
			throw runtime_error("List is empty!");
		sort(this->v.begin(), this->v.end(), [&](auto i, auto j) {return i.first <= j.first; });
	}
	void sortBySecondComponent()
	{
		if (this->v.size() == 0)
			throw runtime_error("List is empty!");
		sort(this->v.begin(), this->v.end(), [&](auto i, auto j) { return i.second <= j.second; });
	}
};

int main()
{
	List<Car, int> list1;
	try
	{
		list1.sortByFirstComponent();
		assert(false);
	}
	catch (runtime_error& e)
	{
		assert(strcmp(e.what(), "List is empty!") == 0);
	};


	list1.add(Car{ "Audi", 20 }, 8);
	list1.add(Car{ "Volkswagen", 10 }, 9);
	list1.add(Car{ "Bentley", 300 }, 10);
	cout << "Salut";

	list1.sortByFirstComponent();
	list1.printReverse(std::cout); //prints : B 300 ->10; Audi 20 ->8; V 10 -> 9
	list1.sortBySecondComponent();
	list1.printReverse(std::cout); //prints Bentley 300 -> 10; V 10 -> 9; Audi 20 -> 8

}