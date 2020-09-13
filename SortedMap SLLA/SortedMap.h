#pragma once
//DO NOT INCLUDE SORTEDMAPITERATOR

//DO NOT CHANGE THIS PART
typedef int TKey;
typedef int TValue;
#include <utility>
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -11111
#define NULL_TPAIR pair<TKey, TValue>(-11111, -11111);
class SMIterator;
typedef bool(*Relation)(TKey, TKey);


class SortedMap {
	friend class SMIterator;
    private:
		//TODO - Representation
		TElem *elements;
		int *next;
		int head{};
		int firstEmpty{};
		int capacity{};
		Relation relation;

    public:

    // implicit constructor
    SortedMap(Relation r); // Complexity Theta(n), n- the initial capacity, because we need to initialize the empty positions

	// adds a pair (key,value) to the map
	// if the key already exists in the map, then the value associated to the key is replaced by the new value and the old value is returned
	// if the key SMes not exist, a new pair is added and the value null is returned
	// Complexity:	O(n) amortized - it uses the function getTheRightPosition with O(n) complexity 
	//				and the function resize with Theta(n) complexity, where n is the capacity of the map multiplied by two
	//		BestCase: Theta(1) if the key must be added in front of the head or if the map is empty
	//		WorstCase = AverageCase the same as for the getTheRightPosition function
	TValue add(TKey c, TValue v);

	// searches for the key and returns the value associated with the key if the map contains the key or null: NULL_TVALUE otherwise
	// Complexity:	O(n) where n is the number of pairs (key, value) from the map
	//			BestCase: Theta(1) - when the map is empty or when the element that is being searched for is found on the position indicated by the head
	//			WorstCase: Theta(n) - when the element was not found and the list was not empty or when the element is found on the last position in the map
	//			AverageCase: Theta(n) - 1/n * 1 + 1/n * 2 + 1/n * 3 + ... + 1/n * n = n + 1 ~ n
	TValue search(TKey c) const;


	// removes a key from the map and returns the value associated with the key if the key existed ot null: NULL_TVALUE otherwise
	// Complexity: O(n) it uses the function getTheRightPosition()
	//		BestCase: Theta(1) - if the head is removed or if the map is empty
	//		WorstCase = AverageCase the same as for the getTheRightPosition function
	TValue remove(TKey c);

	// returns the number of pairs (key,value) from the map
	// Complexity: Theta(n)
	int size() const;

	//checks whether the map is empty or not
	// Complexity: Theta(1)
	bool isEmpty() const;

    // return the iterator for the map
    // the iterator will return the keys following the order given by the relation
    SMIterator iterator() const;

    // destructor
	// Complexity: Theta(1)
    ~SortedMap();

private:

	// return the index where the TKey k should be positioned in the map;
	// Complexity: O(n) n-the number of keys in the map
	//		BestCase: Theta(1) if the key is found at the first position in the map
	//		WorstCase: Theta(n) if the key is found at the last position in the map or it is not found at all
	//		AverageCase: Theta(n) AverageCase: Theta(n) - 1/n * 1 + 1/n * 2 + 1/n * 3 + ... + 1/n * n = n + 1 ~ n
	int getTheRightPosition(TKey K);

	// resizes the array of elements and the array of nexts; memory is allocated
	// Complexity: Theta(n) where n is, in fact the capacity of the map multiplied by two;
	void resize();
};
