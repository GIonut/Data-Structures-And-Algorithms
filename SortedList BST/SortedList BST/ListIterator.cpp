#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>

using namespace std;

ListIterator::ListIterator(const SortedIndexedList& list) : list(list) {
	//TODO - Implementation
	this->first();
}

void ListIterator::first(){
	//TODO - Implementation
	int node = this->list.root;
	while (!this->s.empty())
		this->s.pop();
	while (node != -1)
	{
		this->s.push(node);
		node = this->list.left[node];
	}
	if (!this->s.empty())
	{
		this->currentNode = this->s.top();
	}
	else
		this->currentNode = -1;
}

void ListIterator::next(){
	//TODO - Implementation
	if (!valid())
		throw exception("Invalid Iterator!");
	int node = this->s.top();
	this->s.pop();
	if (this->list.right[node] != -1)
	{
		node = this->list.right[node];
		while (node != -1)
		{
			this->s.push(node);
			node = this->list.left[node];
		}
	}
	if (!this->s.empty())
	{
		this->currentNode = this->s.top();
	}
	else
		this->currentNode = -1;
}

bool ListIterator::valid() const{
	//TODO - Implementation
	if(this->currentNode == -1)
		return false;
	return true;
}

TComp ListIterator::getCurrent() const{
	//TODO - Implementation
	if (this->valid())
		return this->list.info[this->currentNode];
	return NULL_TCOMP;
}


