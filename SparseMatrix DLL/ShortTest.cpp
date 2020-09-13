#include <assert.h>
#include "Matrix.h"
#include <exception>
#include <utility>

using namespace std;

void testAll() { 
	Matrix m(4, 4);
	assert(m.nrLines() == 4);
	assert(m.nrColumns() == 4);	
	m.modify(1, 1, 5);
	assert(m.element(1, 1) == 5);
	TElem old = m.modify(1, 1, 6);
	assert(m.element(1, 2) == NULL_TELEM);
	assert(old == 5);

	
	// tests for positionOf

	Matrix matrix(4, 4);
	pair <int, char> p;
	p = matrix.positionOf(5);
	assert(p.first == -1);
	assert(p.second == -1);

	matrix.modify(1, 1, 2);
	matrix.modify(1, 2, 3);
	matrix.modify(2, 2, 3);
	matrix.modify(3, 3, 6);

	assert(matrix.positionOf(2).first == 1);
	assert(matrix.positionOf(2).second == 1);

	p = matrix.positionOf(3);
	assert(p.first == 1);
	assert(p.second == 2);

	p = matrix.positionOf(6);
	assert(p.first == 3);
	assert(p.second == 3);

	p = matrix.positionOf(4);
	assert(p.first == -1);
	assert(p.second == -1);




}