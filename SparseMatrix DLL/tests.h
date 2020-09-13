#pragma once
#include <iostream>
#include "Matrix.h"

void test()
{
	Matrix m(4, 4);
	m.modify(1, 1, 5);
	std::cout << m.element(1, 1);
}

void tests()
{
	test();
}