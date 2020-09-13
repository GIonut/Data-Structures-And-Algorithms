#pragma once

#include "SortedMultiMap.h"
#include <vector>
#include <algorithm>

class SMMIterator{
	friend class SortedMultiMap;
private:
	//DO NOT CHANGE THIS PART
	const SortedMultiMap& map;
	SMMIterator(const SortedMultiMap& map);
	int current;
	Relation r = this->map.relation;
	TElem* elements;
	int size;
	//TODO - Representation

public:
	void first();
	void next();
	bool valid() const;
   	TElem getCurrent() const;

};

