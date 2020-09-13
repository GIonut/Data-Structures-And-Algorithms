#pragma once
#include "SortedMap.h"

//DO NOT CHANGE THIS PART
class SMIterator{
	friend class SortedMap;
private:
	const SortedMap& map;
	SMIterator(const SortedMap& mapionar);

	//TODO - Representation
	int current{};
public:
	void first();
	void next();
	bool valid() const;
    TElem getCurrent() const;
	/*
	complexity: O(n)
	bestCase:Theta(1) k <= 0, current is not valid or k > then number of elements until current or if current points to the first position
	WorstCase: if current points to the last element and k is 1 -> Theta(n) + Theta(n-1) = Theta(n) where n is the number of elements in the container
	*/
	void jumpBackward(int k);
};

