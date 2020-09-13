#pragma once
#include <utility>

//DO NOT CHANGE THIS PART
typedef int TElem;

using namespace std;

#define NULL_TELEM 0

struct Node
{
	Node* next;
	Node* previous;
	TElem value;
	int line;
	int column;

};


class Matrix {
	int currentLine = 0;
	int currentColumn = 0;
	void first();
	void next();
	TElem getCurrent();
	bool valid() const;
private:

	//TODO - Representation
	Node* head;
	Node* tail;
	int size;
	int numberOfLines = 0;
	int numberOfColumns = 0;

public:
	//constructor
	Matrix(int nrLines, int nrCols); // Theta(1)

	//returns the number of lines
	int nrLines() const; // Theta(1)

	//returns the number of columns
	int nrColumns() const; // Theta(1)

	//returns the element from line i and column j (indexing starts from 0)
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem element(int i, int j) const;	// Complexity : O(n)  - uses getTheRightPosition()
										// the maximum number of steps would be n, if the element is positioned
										// last in the sparse matrix with n Non-NULL elements. 

	//modifies the value from line i and column j
	//returns the previous value from the position
	//throws exception if (i,j) is not a valid position in the Matrix
	//Complexity: it uses function element- O(n) and then another three function with O(n) complexity, but separately;
	// for each case, the complexity will be O(n) + O(n) = O(n);
	TElem modify(int i, int j, TElem e);

	/*returns the position of element elem from the Matrix (as a line, column pair). 
	If elem occurs multiple times, any position where it appears is fine.
	If elem is not in the Matrix, return the pair <-1, -1>.*/
	pair<int, int> positionOf(TElem elem) const; // O(n) - n is the number of non null elements in the sparse matrix.

private:

	/*
	returns the position where the element on line = line and column = column should be placed in the sparse matrix
	Input:	int line, column
	Output:	int position
	Complexity:
		Best Case: Theta(1) when the element should be placed on the first position
		Average Case: 1/n*1 + 1/n*2+ 1/n*3 + ... + 1/n*n = Theta(n) where n represents 
						the number of Non-NULL elements in the sparse matrix
		Worst Case: Theta(n) when the element should be placed on the last position
		
		Overall Complexity: O(n)
	*/
	Node* getTheRightPosition(int line, int column) const;


	/*
	sets an element at the right position in the sparse matrix from NULL_TELEM to Non-NULL
	Input:	int - line, column
			const TElem& - a constant reference of the element that is going to be added
	Output: TElem - a NULL_TELEM(the element on the position line and column in the sparse matrix)

	Complexity: O(n) - the same as getTheRightPosition()
	*/
	TElem addElement(int, int, const TElem&);

	/*
	change the Non-NULL element from the position line, column in the matrix with element
	Input:	int - line, column
			const TElem& - a constant reference of the element that is going to be changed with
	Complexity: O(n) -uses the function getTherightPosition
	*/
	TElem setElement(int line, int column, const TElem& element);

	/*
	sets an element at the right position in the sparse matrix from Non-NULL to NULL_TELEM
	Input:	int - line, column
	Output: TElem - the element on the position line and column in the sparse matrix before being set to NULL;

	Complexity: O(n) - same as the getTheRightPosition()
	*/
	TElem removeElement(int, int);

};
