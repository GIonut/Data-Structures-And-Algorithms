#pragma once;
#include "Iterator.h"
typedef int TElem;

typedef bool(*Relatie)(TElem, TElem);

//in implementarea operatiilor se va folosi functia (relatia) rel (de ex, pentru <=)
// va fi declarata in .h si implementata in .cpp ca functie externa colectiei
bool rel(TElem, TElem);

class IteratorColectie;

//referire a clasei Nod

class Nod;



//se defineste tipul PNod ca fiind adresa unui Nod

typedef Nod* PNod;



class Nod

{

public:

	friend class Colectie;

	//constructor

	Nod(TElem e, PNod urm);

	TElem getElement();

	PNod getUrmator();

private:

	TElem e;

	PNod urm;

	int frecventa = 1;

};


class Colectie {

	friend class IteratorColectie;

private:
	/* aici e reprezentarea */
	//prim este adresa primului Nod din lista
	PNod prim = nullptr;

public:
	//constructorul implicit
	Colectie();

	//adauga un element in colectie
	void adauga(TElem e);

	//sterge o aparitie a unui element din colectie
	//returneaza adevarat daca s-a putut sterge
	bool sterge(TElem e);

	//verifica daca un element se afla in colectie
	bool cauta(TElem elem) const;

	//returneaza numar de aparitii ale unui element in colectie
	int nrAparitii(TElem elem) const;


	//intoarce numarul de elemente din colectie;
	int dim() const;

	//verifica daca colectia e vida;
	bool vida() const;

	//returneaza un iterator pe colectie
	IteratorColectie iterator() const;

	// destructorul colectiei
	~Colectie();

private:

	const PNod& punere_nod(PNod nod);

};
