#include "Set.h"
#include "SetITerator.h"
#include <string>

Set::Set() {
	//TODO - Implementation
	this->m = 17;
	this->elements = new TElem[17];

	for (int i = 0; i < this->m; i++)
		this->elements[i] = EMPTY;

	this->actualSize = 0;
}


bool Set::add(TElem elem) {
	//TODO - Implementation

	int i = 0;
	int position = this->hash(elem, i);

	while (i < this->m && this->elements[position] != EMPTY && this->elements[position] != DELETED && this->elements[position] != elem)
	{
		i++;
		position = this->hash(elem, i);
	}
	
	if (this->elements[position] == elem)
		return false;

	if (i == m)
	{
		this->resizeAndRehash();
		this->add(elem);
		return true;
	}
	else {
		this->elements[position] = elem;
		this->actualSize++;
		return true;
	}

}


bool Set::remove(TElem elem) {
	//TODO - Implementation

	int i = 0;
	int position = this->hash(elem, i);

	while (i < this->m && this->elements[position] != elem && this->elements[position] != EMPTY)
	{
		i++;
		position = this->hash(elem, i);
	}

	if (i == m || this->elements[position] == EMPTY)
		return false;
	
	this->elements[position] = DELETED;
	this->actualSize--;
	return true;
}

bool Set::search(TElem elem) const {
	//TODO - Implementation

	if (this->actualSize == 0)
		return false;

	int i = 0;
	int position = this->hash(elem, i);

	while (i < m && this->elements[position] != elem && this->elements[position] != EMPTY)
	{
		i++;
		position = this->hash(elem, i);
	}

	if (i == m || this->elements[position] == EMPTY)
		return false;

	return true;
}


int Set::size() const {
	//TODO - Implementation
	return this->actualSize;
}


bool Set::isEmpty() const {
	//TODO - Implementation
	return this->actualSize == 0;
}


Set::~Set() {
	//TODO - Implementation
	delete[] this->elements;
}


SetIterator Set::iterator() {
	return SetIterator(*this);
}

int Set::hash(TElem k, int i) const
{
	int firstHash = abs(k) % m;
	int secondHash = 1 + abs(k) % (m - 1);
	return (firstHash + i * secondHash) % this->m;
}

int findPrime(int m)
{
	const int n = 2 * m + 1;

	bool* prime = new bool[n];

	for (int i = 0; i < n; i++)
		prime[i] = true;

	for (int p = 2; p * p < n; p++)
	{
		if (prime[p] == true)
		{
			for (int i = p * p; i < n; i += p)
				prime[i] = false;
		}
	}

	for (int i = n-1; i >= 2; i--)
		if (prime[i] == true)
		{
			m = i;
			break;
		}

	delete[] prime;

	return m;
}

void Set::resizeAndRehash()
{
	int oldCapacity = m;
	this->actualSize = 0;
	this->m = findPrime(m);

	TElem* newElementsArray = new TElem[this->m];
	TElem* temporaryElementsArray = this->elements;
	this->elements = newElementsArray;

	for (int i = 0; i < this->m; i++)
		this->elements[i] = EMPTY;

	for (int i = 0; i < oldCapacity; i++)
	{
		this->add(temporaryElementsArray[i]);
	}

	delete[] temporaryElementsArray;
}

