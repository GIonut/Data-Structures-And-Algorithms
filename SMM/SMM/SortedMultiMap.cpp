#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;


SortedMultiMap::SortedMultiMap(Relation r) {
	//TODO - Implementation
	this->relation = r;
	this->m = 2;
	this->length = 0;
	this->elems = new Node * [this->m]();
}

void SortedMultiMap::add(TKey c, TValue v) {
	//TODO - Implementation
	if ((float)this->length / this->m >= 1)
	{
		this->m *= 2;
		Node** newEls = new Node * [this->m]();
		for (int i = 0; i < this->m / 2; i++)
		{
			Node* current = this->elems[i];
			while (current != NULL)
			{
				Node* next = current->next;
				int bucket = this->hashFunction(current->pair.first);
				if (newEls[bucket] == NULL)
				{
					current->next = NULL;
					newEls[bucket] = current;
				}
				else
				{
					current->next = newEls[bucket];
					newEls[bucket] = current;
				}
				current = next;
			}
		}
		delete[] this->elems;
		this->elems = newEls;
	}
	int bucket = this->hashFunction(c);
	Node* newNode = new Node;
	newNode->pair = TElem{ c,v };

	if (this->elems[bucket] == nullptr)
	{
		newNode->next = nullptr;
		this->elems[bucket] = newNode;

	}
	else
	{
		newNode->next = this->elems[bucket];
		this->elems[bucket] = newNode;
	}
	this->length += 1;
	//Complexity: O(n)
}

vector<TValue> SortedMultiMap::search(TKey c) const {
	//TODO - Implementation
	vector<TValue> values;
	Node* current = new Node;
	int hash = this->hashFunction(c);
	current = this->elems[hash];
	while (current != NULL)
	{
		if (current->pair.first == c)
			values.push_back(current->pair.second);
		current = current->next;
	}
	return values;
}

bool SortedMultiMap::remove(TKey c, TValue v) {
	//TODO - Implementation
	int bucket = this->hashFunction(c);
	TElem myPair{ c,v };
	Node* prev = NULL;
	Node* current = this->elems[bucket];
	if (current == NULL)
		return false;
	while (current != NULL && current->pair != myPair)
	{
		prev = current;
		current = current->next;
	}
	if (current == NULL)
		return false;
	if (prev == NULL)
	{
		this->elems[bucket] = current->next;
		delete current;
		this->length -= 1;
		return true;
	}
	prev->next = current->next;
	delete current;
	this->length -= 1;
	return  true;
	//Complexity: Theta(n)
}


int SortedMultiMap::size() const {
	//TODO - Implementation
	return this->length;
}

bool SortedMultiMap::isEmpty() const {
	//TODO - Implementation
	if (this->length == 0)
		return true;
	return false;
}

SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}

SortedMultiMap::~SortedMultiMap() {
	//TODO - Implementation
	for(int i=0;i<this->m;i++)
	{
		Node* current = this->elems[i];
		while (current != NULL)
		{
			Node* next = current->next;
			delete current;
			current = next;
		}
	}
	delete[] this->elems;
}

int SortedMultiMap::hashFunction(TKey key) const
{
	return abs(key) % this->m;
}