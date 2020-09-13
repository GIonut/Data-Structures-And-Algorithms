#pragma once
//DO NOT INCLUDE SETITERATOR

//DO NOT CHANGE THIS PART
#define NULL_TELEM -111111
#define EMPTY -222222
#define DELETED -333333
typedef int TElem;
class SetIterator;

class Set {
	//DO NOT CHANGE THIS PART
	friend class SetIterator;

    private:
		//TODO - Representation
        TElem* elements;
        int m;
        int actualSize;

    public:
        //implicit constructor
        Set();

        //adds an element to the set
		//returns true if the element was added, false otherwise (if the element was already in the set and it was not added)
        /*
        Complexity: O(m) but Theta(1) on average - it uses function resizeAndRehash with Theta(m) but it is amortized
            Best Case: Theta(1) - if the iterator is invalid or if the first element is found at position 0 in the set
            Average Case: Theta(n)
            Worst Case: Theta(n) - if the first element is found at position m-1 in the set
        */
        bool add(TElem e);

        //removes an element from the set
		//returns true if e was removed, false otherwise
        /*
        Complexity: O(m) but Theta(1) on average
            Best Case: Theta(1) - if the iterator is invalid or if the first element is found at position 0 in the set
            Average Case: Theta(n)
            Worst Case: Theta(n) - if the first element is found at position m-1 in the set
        */
        bool remove(TElem e);

        //checks whether an element belongs to the set or not
        /*
        Complexity: O(m) but Theta(1) on average
            Best Case: Theta(1) - if the iterator is invalid or if the first element is found at position 0 in the set
            Average Case: Theta(n)
            Worst Case: Theta(n) - if the first element is found at position m-1 in the set
        */
        bool search(TElem elem) const;

        //returns the number of elements;
        //Complexity: Theta(1)
        int size() const;

        //check whether the set is empty or not;
        //Complexity: Theta(1)
        bool isEmpty() const;

        //return an iterator for the set
        SetIterator iterator();

        // destructor
        ~Set();

private:

    int hash(TElem k, int i) const;

    // Complexity: Theta(m) - amortized
    void resizeAndRehash();

};





