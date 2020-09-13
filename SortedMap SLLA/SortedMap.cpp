#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
using namespace std;

SortedMap::SortedMap(Relation r) {
	//TODO - Implementation

	this->capacity = 10;
	this->head = -1;
	this->elements = new TElem[10];
	this->next = new int[10]{ -1 };
	this->relation = r;

	for (int i = 0; i < this->capacity - 1; i++)
	{
		this->next[i] = i + 1;
	}

	this->next[this->capacity-1] = -1;
	this->firstEmpty = 0;

}

TValue SortedMap::add(TKey k, TValue v) {
	//TODO - Implementation

	if (this->isEmpty())
	{
		int secondEmpty = this->next[this->firstEmpty];// keeps the next empty position in the SLLA
		this->head = this->firstEmpty;// occupy the first empty position
		this->elements[this->head] = TElem(k, v);// set the value
		this->next[this->head] = -1;// set the links
		this->firstEmpty = secondEmpty;// set the new empty position
		return NULL_TVALUE;
	}

	if (this->firstEmpty == -1)/// if the SLLA is full
		this->resize();
	 
		int previousPosition = this->getTheRightPosition(k);

		if (previousPosition == -1)// if the element must be inserted at the beginning of the SLLA
		{
			if (this->elements[head].first == k)// if the keys are equal
			{
				int oldValue = this->elements[head].second;
				this->elements[head].second = v;
				return oldValue;
			}
			int currentPosition = this->head;
			int secondEmpty = this->next[this->firstEmpty];
			this->head = this->firstEmpty;
			this->elements[this->head] = TElem(k, v);
			this->next[this->head] = currentPosition;
			this->firstEmpty = secondEmpty;
			return NULL_TVALUE;
		}

		int currentPosition = this->next[previousPosition];// if we don't have to insert at the beginning

		if (currentPosition == -1)// must insert on the last position
		{
			if (this->elements[currentPosition].first == k)
			{
				int oldValue = this->elements[currentPosition].second;
				this->elements[currentPosition].second = v;
				return oldValue;
			}
			int secondEmpty = this->next[this->firstEmpty];
			this->elements[this->firstEmpty] = TElem(k, v);// occupy the first empty position
			this->next[this->firstEmpty] = -1;
			this->next[previousPosition] = this->firstEmpty;
			this->firstEmpty = secondEmpty;
		}
		else
		{
			TElem &currentPair = this->elements[currentPosition];
			if (currentPair.first == k)
			{
				int oldValue = currentPair.second;
				currentPair.second = v;
				return oldValue;
			}
			else
			{
				int secondEmpty = this->next[this->firstEmpty];
				this->elements[this->firstEmpty] = TElem(k, v);
				this->next[this->firstEmpty] = currentPosition;
				this->next[previousPosition] = this->firstEmpty;
				this->firstEmpty = secondEmpty;
			}
		}
		
		return NULL_TVALUE;
}

TValue SortedMap::search(TKey k) const {
	//TODO - Implementation

	int current = this->head;

	while (current != -1 && this->elements[current].first != k)
	{
		current = this->next[current];
	}

	if (current == -1)
		return NULL_TVALUE;

	return this->elements[current].second;
}

TValue SortedMap::remove(TKey k) {
	//TODO - Implementation
	
	if (this->isEmpty())
		return NULL_TVALUE;

	int previousPosition = this->getTheRightPosition(k);

	if (previousPosition == -1)
	{
		

		if (this->relation(k, this->head) && k != this->elements[this->head].first)
			return NULL_TVALUE;
		
		if (this->next[this->head] == -1) // if after the removal the container will be empty
		{
			this->next[this->head] = this->firstEmpty;
			this->firstEmpty = this->head;
			this->head = -1;
			return this->elements[this->firstEmpty].second;
		}

		int newHead = this->next[this->head];
		this->next[this->head] = this->firstEmpty;
		this->firstEmpty = this->head;
		this->head = newHead;
		return this->elements[this->firstEmpty].second;
	}
	
	int currentPosition = this->next[previousPosition];

	if (currentPosition == -1)// did not find the key to remove
		return NULL_TVALUE;

	if (this->next[currentPosition] == -1)
	{
		this->next[currentPosition] = this->firstEmpty;
		this->firstEmpty = currentPosition;
		this->next[previousPosition] = -1;
	}
	else
	{
		this->next[previousPosition] = this->next[currentPosition];
		this->next[currentPosition] = this->firstEmpty;
		this->firstEmpty = currentPosition;
	}

	return this->elements[currentPosition].second;
}

int SortedMap::size() const {
	//TODO - Implementation
	if (this->isEmpty())
		return 0;
	
	int count = 0;
	int current = this->head;
	
	while (current != -1)
	{
		current = this->next[current];
		count++;
	}

	return count;
}

bool SortedMap::isEmpty() const {
	//TODO - Implementation
	if (this->head == -1)
		return true;
	return false;
}

SMIterator SortedMap::iterator() const {
	return SMIterator(*this);
}

SortedMap::~SortedMap() {
	//TODO - Implementation
	delete[] this->elements;
	delete[] this->next;
}


int SortedMap::getTheRightPosition(TKey K)
{
	int current = this->head;
	int previous = -1;
	while (current != -1 && !(*relation)(K, this->elements[current].first))
	{
		previous = current;
		current = this->next[current];
	}

	return previous;
}

void SortedMap::resize()
{
	TElem *newElements = new TElem[2 * this->capacity];
	int* newNext = new int[2 * this->capacity];
	
	int current = this->head;

	while (current != -1)
	{
		newElements[current] = this->elements[current];
		newNext[current] = this->next[current];
		current = this->next[current];
	}

	delete[] this->elements;
	delete[] this->next;

	this->elements = newElements;
	this->next = newNext;

	for (int i = capacity; i < capacity * 2 - 1; i++)
		this->next[i] = i + 1;

	this->next[this->capacity * 2 - 1] = -1;
	this->firstEmpty = capacity;
	this->capacity *= 2;
}
