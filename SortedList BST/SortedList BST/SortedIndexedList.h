#pragma once
//DO NOT INCLUDE LISTITERATOR

//DO NOT CHANGE THIS PART
class ListIterator;
typedef int TComp;
typedef bool (*Relation)(TComp, TComp);
#define NULL_TCOMP -11111

class SortedIndexedList {
private:
	friend class ListIterator;
private:
	//TODO - Representation
	TComp* info;
	int* left;
	int* right;
	int* parent;
	int* leftChildren;
	int root;
	int firstEmpty;
	int capacity;
	int actualSize;
	Relation relation;

public:
	// constructor
	SortedIndexedList(Relation r);

	// returns the size of the list
	//Theta(1)
	int size() const;

	//checks if the list is empty
	//Theta(1)
	bool isEmpty() const;

	// returns an element from a position
	//throws exception if the position is not valid
	TComp getElement(int pos) const;

	// adds an element in the sortedList (to the corresponding position)
	// O(n) + Theta(n) - amortized -> O(n), with Theta(log2n) on average.
	void add(TComp e);

	// removes an element from a given position
	// returns the removed element
	// throws an exception if the position is not valid
	TComp remove(int pos);

	// searches for an element and returns the first position where the element appears or -1 if the element is not in the list
	int search(TComp e) const;

	// returns an iterator set to the first element of the list or invalid if the list is empty
	ListIterator iterator();

	//removes from the list all elements that appear in list
	//returns the number of removed elements
	int removeAll();

	//destructor
	~SortedIndexedList();

private:
	// resizes the arrays, doubling their capacity
	// Theta(2*n) = Theta(n)
	void resize();

	// returns the position in the array where the parent node of e should be found
	// O(n) but on average Theta(log2n)
	int getPosition(TComp e) const;

	// performs an inorder traversal of the graph and returns the position'th element in the tree 
	// O(n)
	TComp inorder(int& position, int root) const;

	// performs an inorder traversal of the graph and returns the position of the element given as a parameter 
	// O(n);
	void inorderElement(TComp e, int& position, int root) const;

	

};
