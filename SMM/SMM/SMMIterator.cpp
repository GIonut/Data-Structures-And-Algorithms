#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>

void swap(TElem& a, TElem& b) {
	auto t = a;
	a = b;
	b = t;
}

int partition(TElem arr[], int low, int high, Relation r) {
	TElem pivot = arr[high];
	int i = (low - 1);

	for (int j = low; j <= high - 1; j++) {
		if (r(arr[j].first, pivot.first)) { // <--- Using relation here
			i++;
			swap(arr[i], arr[j]);
		}
	}

	swap(arr[i + 1], arr[high]);
	return (i + 1);
}

void quickSort(TElem arr[], int low, int high, Relation r) {
	if (low < high) {
		int pi = partition(arr, low, high, r);

		quickSort(arr, low, pi - 1, r);
		quickSort(arr, pi + 1, high, r);
	}
}

SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d) {
	//TODO - Implementation
	this->elements = new TElem[map.m];
	this->size = 0;

	for (int i = 0; i < this->map.m; i++)
	{
		Node* node = this->map.elems[i];
		while (node != NULL)
		{
			this->elements[size++] = node->pair;
			node = node->next;
		}
	}


	quickSort(this->elements, 0, this->map.m - 1, this->map.relation);
}

void SMMIterator::first(){
	//TODO - Implementation
	this->current = 0;
}

void SMMIterator::next(){
	//TODO - Implementation
	exception ex;
	if (this->current < this->size)
		this->current++;
	else
		throw ex;
}

bool SMMIterator::valid() const {
	//TODO - Implementation
	if (this->current >= 0 && this->current < this->size)
		return true;
	return false;
}

TElem SMMIterator::getCurrent() const {
	//TODO - Implementation
	exception ex;
	if (0 <= this->current && this->current < this->size)
		return this->elements[this->current];
	else
		throw ex;
}


