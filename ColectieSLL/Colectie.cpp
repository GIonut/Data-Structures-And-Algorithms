#include "Colectie.h"
#include "Iterator.h"
#include <iostream>

using namespace std;

Nod::Nod(TElem e, PNod urm) {
	this->e = e;
	this->urm = urm;
}

TElem Nod::getElement() {
	return this->e;
}

PNod Nod::getUrmator() {
	return this->urm;
}

bool rel(TElem e1, TElem e2) {
	/* de adaugat */
	if (e1 < e2)
		return true;

	return false;
}

Colectie::Colectie() {
	/* de adaugat */
}

void Colectie::adauga(TElem e) {
	/* de adaugat */

	PNod q = new Nod(e, nullptr);

	if (this->prim == nullptr)
	{
		this->prim = q;
	}

	else {

		const PNod& p = this->punere_nod(q);
		if (p == nullptr)
		{
			if (q->e == this->prim->e)
				this->prim->frecventa++;
			else
			{
				q->urm = this->prim;
				this->prim = q;
			}
		}
		else if (p->urm == nullptr)
		{
			p->urm = q;
		}

		else if (p->urm->e == q->e)
		{
			p->urm->frecventa++;
		}

		else
		{
			q->urm = p->urm;
			p->urm = q;
		}
	}
}


bool Colectie::sterge(TElem e) {
	/* de adaugat */

	if(!this->cauta(e))
		return false;

	if (this->prim->e == e)
	{
		if (this->prim->frecventa > 1)
		{
			this->prim->frecventa--;
			return true;
		}
		PNod primul = this->prim;
		this->prim = this->prim->urm;
		delete primul;
		return true;
	}

	PNod nod_curent = this->prim;
	PNod nod_anterior = nod_curent;

	while (nod_curent->urm != nullptr && nod_curent->e != e)
	{
		nod_anterior = nod_curent;
		nod_curent = nod_curent->urm;
	}


	if (nod_curent->frecventa > 1)
	{
		nod_curent->frecventa--;
		return true;
	}
	else if (nod_curent->urm == nullptr)
	{
		delete nod_curent;
		return true;
	}
	else
	{
		nod_anterior->urm = nod_anterior->urm->urm;
		delete nod_curent;
		return true;
	}

	return false;
}


bool Colectie::cauta(TElem elem) const {
	/* de adaugat */

	PNod nod_curent = this->prim;

	if (nod_curent == nullptr)
		return false;

	while (nod_curent->urm != nullptr && nod_curent->e != elem)
		nod_curent = nod_curent->urm;

	if (nod_curent->e == elem)
		return true;
	return false;
}


int Colectie::nrAparitii(TElem elem) const {
	/* de adaugat */

	PNod nod_curent = this->prim;

	if (nod_curent == nullptr)
		return 0;

	while (nod_curent->urm != nullptr && nod_curent->e != elem)
		nod_curent = nod_curent->urm;

	if (nod_curent->e == elem)
	{
		return nod_curent->frecventa;
	}
	return 0;
}



int Colectie::dim() const {
	/* de adaugat */

	PNod nod_curent = this->prim;

	int dimensiune = 0;

	while (nod_curent != nullptr)
	{
		dimensiune += nod_curent->frecventa;
		nod_curent = nod_curent->urm;
	}
	return dimensiune;
}


bool Colectie::vida() const {
	/* de adaugat */
	if (this->prim == nullptr)
		return true;
	return false;
}


IteratorColectie Colectie::iterator() const {
	return  IteratorColectie(*this);
}


Colectie::~Colectie() {
	/* de adaugat */

	while (this->prim != nullptr)
	{
		PNod nod_curent = this->prim;
		this->prim = this->prim->urm;
		delete nod_curent;
	}
	
}

const PNod& Colectie::punere_nod(PNod nod)
{
	if (this->prim == nullptr)
		return nullptr;

	PNod nod_curent = this->prim;

	if (rel(nod->e, nod_curent->e))
		return nullptr;

	if (nod->e == this->prim->e)
		return nullptr;

	while (nod_curent->urm != nullptr && rel(nod_curent->urm->e, nod->e))
	{
		nod_curent = nod_curent->urm;
	}
	return nod_curent;
}
