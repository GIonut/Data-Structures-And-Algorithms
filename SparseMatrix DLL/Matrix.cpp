#include "Matrix.h"
#include <exception>
using namespace std;

Matrix::Matrix(int nrLines, int nrCols) {
	   
	//TODO - Implementation
	this->head = NULL;
	this->tail = this->head;
	this->size = 0;
	this->numberOfLines = nrLines;
	this->numberOfColumns = nrCols;
	this->currentColumn = 0;
	this->currentLine = 0;
}


int Matrix::nrLines() const {
	//TODO - Implementation
	return this->numberOfLines;
}


int Matrix::nrColumns() const {
	//TODO - Implementation
	return this->numberOfColumns;
}


TElem Matrix::element(int i, int j) const {
	//TODO - Implementation

	if (i < 0 || j < 0 || i > this->numberOfLines || j > this->numberOfColumns)
		throw exception("invalid Position!");

	Node* nodeAfter = this->getTheRightPosition(i, j);

	if (nodeAfter == NULL)
		return NULL_TELEM;

	if(nodeAfter->line == i && nodeAfter->column == j)
		return nodeAfter->value;

	return NULL_TELEM;
}

TElem Matrix::modify(int i, int j, TElem e) {
	//TODO - Implementation
	if (i < 0 || j < 0 || i > this->numberOfLines || j > this->numberOfColumns)
		throw exception("invalid Position!");

	const TElem& currentElement = this->element(i, j);

	if (currentElement == NULL_TELEM)
	{
		if (e == NULL_TELEM)
			return currentElement;
		else
			return this->addElement(i, j, e);
	}
	else
	{
		if (e != NULL_TELEM)
			return this->setElement(i, j, e);
		else
			return this->removeElement(i, j);
	}
}

Node* Matrix::getTheRightPosition(int line, int column) const
{

	Node* currentNode = this->head;

	while (currentNode != NULL && currentNode->line < line)
	{
		currentNode = currentNode->next;
	}

	while (currentNode != NULL && currentNode->line == line && currentNode->column < column)
	{
		currentNode = currentNode->next;
	}

	return currentNode;
}

TElem Matrix::addElement(int line, int column, const TElem& element)
{
	Node* nodeAfter = getTheRightPosition(line, column);

	Node* newNode = new Node;
	newNode->next = NULL;
	newNode->value = element;
	newNode->line = line;
	newNode->column = column;
	newNode->previous = NULL;

	if (this->head == NULL)
	{
		this->head = newNode;
		this->tail = this->head;
	}
	else if (nodeAfter == this->head)
	{
		newNode->next = this->head;
		this->head->previous = newNode;
		this->head = newNode;
	}
	else if (nodeAfter == NULL)
	{
		newNode->previous = this->tail;
		this->tail->next = newNode;
		this->tail = newNode;
	}
	else
	{
		newNode->previous = nodeAfter->previous;
		nodeAfter->previous->next = newNode;
		newNode->next = nodeAfter;
		nodeAfter->previous = newNode;
	}

	return NULL_TELEM;
}

TElem Matrix::setElement(int line, int column, const TElem& element)
{
	Node* rightNode = getTheRightPosition(line, column);
	TElem previousElement = rightNode->value;
	rightNode->value = element;

	return previousElement;
}

TElem Matrix::removeElement(int line, int column)
{
	Node* rightNode = this->getTheRightPosition(line, column);

	TElem previousElement = rightNode->value;

	if (rightNode == this->head)
	{
		this->head = rightNode->next;
		this->head->previous = NULL;
	}
	else if (rightNode == this->tail)
	{
		this->tail = rightNode->previous;
		this->tail->next = NULL;
	}
	else
	{
		rightNode->previous->next = rightNode->next;
		rightNode->next->previous = rightNode->previous;
	}

	delete rightNode;

	return previousElement;
}

pair<int, int> Matrix::positionOf(TElem elem) const
{
	if (this->head == NULL) // if the matrix has no non-Null elements
		return pair<int, int>(-1, -1);

	Node* currentNode = this->head;
	while (currentNode != NULL && currentNode->value != elem)
	{
		currentNode = currentNode->next;
	}

	if(currentNode == NULL)
		return pair<int, int>(-1, -1);

	return pair<int, int>(currentNode->line, currentNode->column);
}


void Matrix::first() {
	
	this->currentLine = 0;
	this->currentColumn = 0;
}


void Matrix::next() {
	//TODO - Implementation
	if (this->currentColumn == this->nrColumns() - 1)
	{
		if (this->currentLine == this->nrLines() - 1)
		{
			this->first();
		}
		else
		{
			this->currentLine++;
			this->currentColumn = 0;
		}
	}
	else
	{
		this->currentColumn++;
	}
}


TElem Matrix::getCurrent()
{
	return this->element(currentLine, currentColumn);
}

bool Matrix::valid() const {
	
	if(this->head == NULL)
		return false;
	if (this->currentLine == this->nrLines() && this->currentColumn == this->nrColumns())
		return false;
	else
		return true;
}
