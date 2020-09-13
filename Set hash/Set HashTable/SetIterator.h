#pragma once
#include "Set.h"
#include <exception>

class SetIterator
{
	//DO NOT CHANGE THIS PART
	friend class Set;
private:
	//DO NOT CHANGE THIS PART
	Set& set;
	SetIterator(Set& s);

	//TODO - Representation
	TElem currentElement = NULL_TELEM;
	int currentPosition = -1;

public:
	/*
	Compexity:	O(m) - Theta(1) on average
		Best Case: Theta(1) - if the iterator is invalid or if the first element is found at position 0 in the set
		Average Case: Theta(n)
		Worst Case: Theta(n) - if the first element is found at position m-1 in the set
	*/
	void first();

	/*
	Compexity:	O(m) - Theta(1) on average
		Best Case: Theta(1) - if the iterator is invalid or if the first element is found at position 0 in the set
		Average Case: Theta(n)
		Worst Case: Theta(n) - if the first element is found at position m-1 in the set
	*/
	void next();

	// Complexity: Theta(1)
	TElem getCurrent();

	// Complexity: Theta(1)
	bool valid() const;

	//removes and returns the current element from the iterator
	//after the operation the current element from the Iterator is the next element from the Set, or, if the removed element was the last one, the iterator is invalid
	//throws exception if the iterator is invalid
	// Complexity: O(m) + O(m) because it uses function itr::next() and set::remove(), which are - Theta(1) on average
	TElem remove();

};


