#pragma once
#include "Iterator.h"
#include "Colectie.h"
#include <exception>
#include <iostream>


IteratorColectie::IteratorColectie(const Colectie& c) : col(c) {
	/* de adaugat */
	this->curent = this->col.prim;
}

TElem IteratorColectie::element() const {
	/* de adaugat */
	if (this->valid())
	{
		return this->curent->getElement();
	}
	throw 1;
}

bool IteratorColectie::valid() const {
	/* de adaugat */
	if (this->curent != nullptr)
		return true;
	return false;
}

void IteratorColectie::urmator() {
	/* de adaugat */
	this->curent = this->curent->getUrmator();
}

void IteratorColectie::prim() {
	/* de adaugat */
	this->curent = this->col.prim;
}