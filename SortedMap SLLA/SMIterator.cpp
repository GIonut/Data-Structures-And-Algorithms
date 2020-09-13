#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>

using namespace std;

SMIterator::SMIterator(const SortedMap& m) : map(m){
	//TODO - Implementation
	this->current = this->map.head;
}

void SMIterator::first(){
	//TODO - Implementation
	this->current = this->map.head;
}

void SMIterator::next(){
	//TODO - Implementation
	if (!this->valid())
		throw exception("Next Not Valid!");
	this->current = this->map.next[this->current];
}

bool SMIterator::valid() const{
	//TODO - Implementation
	if(this->current == -1)
		return false;
	return true;
}

TElem SMIterator::getCurrent() const{
	//TODO - Implementation
	if (!this->valid())
		throw exception("Current Not Valid!");
	return this->map.elements[this->current];
}

void SMIterator::jumpBackward(int k)
{
	if (!this->valid() || k <= 0)
		throw exception("Invalid operation!");

	int elementsUntilcurrent = 0;
	int here = this->map.head;

	while (here != this->current)
	{
		elementsUntilcurrent++;
		here = this->map.next[here];
	}
	if (elementsUntilcurrent < k)
		this->current = -1;

	else
	{
		int steps = elementsUntilcurrent - k;
		here = this->map.head;
		for (int i = 0; i < steps; i++)
			here = this->map.next[here];

		this->current = here;
	}

}


