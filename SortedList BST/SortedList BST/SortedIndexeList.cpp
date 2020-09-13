#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>
using namespace std;
#include <exception>

SortedIndexedList::SortedIndexedList(Relation r) {
	//TODO - Implementation
	this->capacity = 16; // setting the capacity to be a power of two
	this->root = -1;// the root of an empty representation is -1
	this->firstEmpty = 0; // the first empty position of the arrays is 0;
	this->actualSize = 0; // counts how many elements were added
	this->relation = r; // setting a binary relation
	this->info = new TComp[this->capacity];
	this->left = new int[this->capacity];
	this->right = new int[this->capacity];
	this->parent = new int[this->capacity];
	this->leftChildren = new int[this->capacity];
	

	int  i;
	for (i = 0; i < this->capacity; i++)
	{
		this->info[i] = NULL_TCOMP; //  setting the info array to contain only NULL vlaues;
		this->left[i] = i + 1; // setting the left array to hold the adress of the next emptyPosition
		this->right[i] = -1;
		this->parent[i] = -1;
		this->leftChildren[i] = 0;
	}
	this->left[i-1] = -1; // the last emptyPosition points to -1
}

int SortedIndexedList::size() const {
	//TODO - Implementation
	return this->actualSize;
}

bool SortedIndexedList::isEmpty() const {
	//TODO - Implementation
	if (this->actualSize == 0)
		return  true;
	return false;
}

TComp SortedIndexedList::getElement(int i) const{
	//TODO - Implementation

	if (i < 0 || i > this->actualSize)
		throw exception("Invalid Position!");

	TComp e = this->inorder(i, this->root);
	if (e == NULL_TCOMP)
		throw exception("Invalid Position!");
	return e;
}

TComp SortedIndexedList::remove(int i) {
	//TODO - Implementation

	if (i < 0 || i >= this->actualSize)
		throw exception("Invalid position!");

	int currentNode = this->root;
	int position = this->leftChildren[currentNode];
	while (i != position && currentNode != -1)
	{
		if (i > position)
		{
			currentNode = this->right[currentNode];
			position += this->leftChildren[currentNode] + 1;
		}
		else
		{
			currentNode = this->left[currentNode];
			position += this->leftChildren[currentNode] - this->leftChildren[this->parent[currentNode]];
		}
	}

	if (currentNode == -1)
		throw exception("Invalid Operation!");

	if ((this->left[currentNode] == -1 || this->parent[this->left[currentNode]] == -1) && this->right[currentNode] == -1)
	{
		int returnValue = this->info[currentNode];
		if (this->right[this->parent[currentNode]] == currentNode)
			this->right[this->parent[currentNode]] = -1;
		else if (this->left[this->parent[currentNode]] == currentNode)
		{
			this->left[this->parent[currentNode]] = -1;
			this->leftChildren[this->parent[currentNode]]--;
		}

		int parentCopy = this->parent[currentNode];
		this->left[currentNode] = this->firstEmpty;
		this->right[currentNode] = -1;
		this->parent[currentNode] = -1;
		this->leftChildren[currentNode] = 0;
		this->firstEmpty = currentNode;
		this->actualSize--;

		currentNode = parentCopy;
		while (currentNode > 0)
		{
			int parent = this->parent[currentNode];
			if (this->left[parent] == currentNode)
				this->leftChildren[parent]--;
			currentNode = parent;
		}
		return returnValue;
	}
	else if (this->left[currentNode] == -1 || this->right[currentNode] == -1)
	{
		int returnValue = this->info[currentNode];
		int descendant;
		if (this->right[currentNode] != -1)
		{
			descendant = this->right[currentNode];
			this->right[currentNode] = -1;
			this->right[this->parent[currentNode]] = descendant;
		}
		else
		{
			descendant = this->left[currentNode];
			this->left[currentNode] = -1;
			this->left[this->parent[currentNode]] = descendant;
		}

		this->parent[descendant] = this->parent[currentNode];
		this->left[currentNode] = this->firstEmpty;
		this->firstEmpty = currentNode;
		this->right[currentNode] = -1;
		this->parent[currentNode] = -1;
		this->leftChildren[currentNode] = 0;
		this->actualSize--;

		while (descendant > 0)
		{
			int parent = this->parent[descendant];
			if (this->left[parent] == descendant)
				this->leftChildren[parent]--;
			descendant = parent;
		}
		return returnValue;
	}
	else
	{
		int returnValue = this->info[currentNode];
		int node = currentNode;
		int successor;
		int c;
		if (this->right[node] != -1)
		{
			c = this->right[node];
			while (this->left[c] != -1)
			{
				c = this->left[c];
			}
			successor = c;
		}
		else
		{
			int p = this->parent[node];
			while (p != -1 && this->left[p] != node)
			{
				c = p;
				p = this->parent[p];
			}
			successor = p;
		}
		int parent = this->parent[successor];
		this->info[currentNode] = this->info[successor];
		if (this->left[parent] == successor)
		{
			this->left[parent] = this->left[successor];
		}
		else
		{
			this->right[parent] = this->right[successor];
		}

		this->left[successor] = this->firstEmpty;
		this->firstEmpty = successor;
		this->right[successor] = -1;
		this->parent[successor] = -1;
		this->leftChildren[successor] = 0;
		this->actualSize--;

		currentNode = parent;
		while (currentNode > 0)
		{
			int parent = this->parent[currentNode];
			if (this->left[parent] == currentNode)
				this->leftChildren[parent]--;
			currentNode = parent;
		}
		return returnValue;
	}

	return NULL_TCOMP;
}

int SortedIndexedList::search(TComp e) const {
	//TODO - Implementation
	int position = 0;
	//this->inorderElement(e, position, this->root);
	int currentNode = this->root;
	int isFound = -1;
	while (currentNode != -1)
	{
		if (this->relation(e, this->info[currentNode]))
		{
			if (this->info[currentNode] == e)
				isFound = currentNode;
			currentNode = this->left[currentNode];
		}
		else
		{
			currentNode = this->right[currentNode];
		}
	}// parse the tree until we find the element or we have reach a leaf node
	if (isFound == -1)
		return -1; //if the element was not found, return 0
	else
	{
		int parentNode = this->parent[isFound];
		currentNode = isFound;
		position = this->leftChildren[currentNode]; // we calculate ho many numbers are smaller then the number we searched for
		while (parentNode != -1)
		{
			if (this->right[parentNode] == currentNode)// if the node we found is the right child of his parent, then we add the elements in the left subtree of the parent to the position as well
				position = position + this->leftChildren[parentNode] + 1;
			currentNode = parentNode;
			parentNode = this->parent[parentNode];
		}
		return position;
	}
}

void SortedIndexedList::add(TComp e) {
	//TODO - Implementation
	if (this->actualSize == this->capacity) // if the arrays are full, do a resize
		this->resize();

	if (this->isEmpty()) // if the BST is empty
	{
		this->root = firstEmpty; // set the root to be at the first empty position
		this->firstEmpty = this->left[firstEmpty]; // update firstEmpty to point to the next first empty position
		this->info[this->root] = e; // set the information of the root
		this->left[this->root] = -1; // set the left child to be -1
		this->right[this->root] = -1; // set the right child to be -1
		this->leftChildren[this->root] = 0;
		this->actualSize++; // increae the actual size of the BST
	}
	else
	{
		int currentPosition = this->getPosition(e);
		int secondEmpty = this->left[firstEmpty];
		if (relation(e, this->info[currentPosition]))
		{
			this->left[currentPosition] = this->firstEmpty;
		}
		else
		{
			this->right[currentPosition] = this->firstEmpty;
		}
		this->parent[firstEmpty] = currentPosition;
		this->info[firstEmpty] = e;
		this->left[firstEmpty] = -1;
		currentPosition = firstEmpty;
		this->firstEmpty = secondEmpty;
		this->actualSize++;
		
		while (currentPosition != 0)
		{
			int parent = this->parent[currentPosition];
			if(this->left[parent] == currentPosition)
				this->leftChildren[parent]++;
			currentPosition = parent;
		}
	}		
}

ListIterator SortedIndexedList::iterator(){
	return ListIterator(*this);
}

//destructor
SortedIndexedList::~SortedIndexedList() {
	//TODO - Implementation
	delete[] info;
	delete[] left;
	delete[] right;
	delete[] parent;
}

void SortedIndexedList::resize()
{
	int i;
	int newCapacity = this->capacity * 2;
	
	TComp* newInfo = new TComp[newCapacity];
	int* newLeft = new int[newCapacity];
	int* newRight = new int[newCapacity];
	int* newParent = new int[newCapacity];
	int* newLeftChildren = new int[newCapacity];

	for (i = 0; i < this->capacity; i++)
	{
		newInfo[i] = this->info[i];
		newLeft[i] = this->left[i];
		newRight[i] = this->right[i];
		newParent[i] = this->parent[i];
		newLeftChildren[i] = this->leftChildren[i];
	}

	for (i = this->capacity; i < newCapacity; i++)
	{
		newInfo[i] = NULL_TCOMP;
		newLeft[i] = i + 1;
		newRight[i] = -1;
		newParent[i] = -1;
		newLeftChildren[i] = 0;
	}
	newLeft[i - 1] = -1;

	this->info = newInfo;
	this->left = newLeft;
	this->right = newRight;
	this->parent = newParent;
	this->leftChildren = newLeftChildren;
	this->firstEmpty = this->capacity;
	this->capacity = newCapacity;
}

int SortedIndexedList::getPosition(TComp e) const
{
	int currentPosition = this->root;
	int previousPosition = -1;
	while (currentPosition != -1 && this->info[currentPosition] != NULL_TCOMP)
	{
		if (relation(e, this->info[currentPosition])) // if the relation is satisfied
		{
			previousPosition = currentPosition;
			currentPosition = this->left[currentPosition]; // search in the left subtree
		}
		else
		{
			previousPosition = currentPosition;
			currentPosition = this->right[currentPosition]; // otherwise search in the right subtree
		}
	}

	return previousPosition;
}

TComp SortedIndexedList::inorder(int& position, int root) const
{
	TComp e = NULL_TCOMP;
	if (root != -1 && this->info[root] != NULL_TCOMP)
	{
		e = this->inorder(position, this->left[root]);
		position - 1;
		if (position == 0)
			return this->info[root];
		e = this->inorder(position, this->right[root]);
	}

	return e;
}

void SortedIndexedList::inorderElement(TComp e, int& position, int root) const
{
	if (root != -1 && this->info[root] != NULL_TCOMP)
	{
		this->inorderElement(e, position, this->left[root]);
		if (this->info[root] == e)
			return;
		position++;
		this->inorderElement(e, position, this->right[root]);
	}
}

int SortedIndexedList::removeAll()
{
	for (int i = 0; i < this->actualSize; i++)
	{
		this->info[i] = NULL_TCOMP;
		this->left[i] = i;
		this->right[i] = -1;
		this->parent[i] = -1;
		this->leftChildren[i] = 0;
	}
	int returnValue = this->actualSize;
	this->actualSize == 0;

	return this->actualSize;
}


