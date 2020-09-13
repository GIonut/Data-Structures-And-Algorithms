#include "SetIterator.h"
#include "Set.h"


SetIterator::SetIterator(Set& m) : set(m)
{
	//TODO - Implementation
	this->first();
}


void SetIterator::first() {
	//TODO - Implementation
	this->currentPosition = -1;
	if (this->valid())
	{
		for (int i = 0; i < this->set.m; i++)
			if (this->set.elements[i] != EMPTY && this->set.elements[i] != DELETED)
			{
				this->currentElement = set.elements[i];
				this->currentPosition = i;
				return;
			}
	}
}


void SetIterator::next() {
	//TODO - Implementation
	if (this->valid())
	{
		int  i = 0;
		for (i = this->currentPosition+1; i < this->set.m; i++)
			if (this->set.elements[i] != EMPTY && this->set.elements[i] != DELETED)
			{
				this->currentElement = set.elements[i];
				this->currentPosition = i;
				return;
			}
		if (i == this->set.m)
			this->currentPosition = this->set.m;
	}
	else
		throw std::exception{ "Buba" };
}


TElem SetIterator::getCurrent()
{
	//TODO - Implementation
	if (this->valid())
		return this->currentElement;
	else
		throw std::exception{ "Buba" };
}

bool SetIterator::valid() const {
	//TODO - Implementation
	return this->set.actualSize != 0  && this->currentPosition < this->set.m;
}

TElem SetIterator::remove()
{
	if (valid())
	{
		this->set.remove(this->currentElement);
		if (!this->valid())
			return NULL_TELEM;

		this->next();
		return this->currentElement;
	}
	throw std::exception("Buba!");
}



