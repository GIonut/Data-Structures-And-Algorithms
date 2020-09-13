#include <assert.h>

#include "SortedMap.h"
#include "SMIterator.h"
#include "ShortTest.h"
#include <exception>
using namespace std;

bool relatie1(TKey cheie1, TKey cheie2) {
	if (cheie1 <= cheie2) {
		return true;
	}
	else {
		return false;
	}
}

void testAll(){
	SortedMap sm(relatie1);
	assert(sm.size() == 0);
	assert(sm.isEmpty());
    sm.add(1,2);
    assert(sm.size() == 1);
    assert(!sm.isEmpty());
    assert(sm.search(1)!=NULL_TVALUE);
    TValue v =sm.add(1,3);
    assert(v == 2);
    assert(sm.search(1) == 3);
    SMIterator it = sm.iterator();
    it.first();
    while (it.valid()){
    	TElem e = it.getCurrent();
    	assert(e.second != NULL_TVALUE);
    	it.next();
    }
    assert(sm.remove(1) == 3);
    assert(sm.isEmpty());


    // test jumpBackwards()
    SortedMap map(relatie1);
    map.add(0, 0);
    map.add(1, 1);
    map.add(2, 2);
    map.add(3, 3);
    map.add(4, 4);
    map.add(5, 5);
    map.add(6, 6);
    map.add(7, 7);
    map.add(8, 8);
    map.add(9, 9);

    SMIterator i = map.iterator();

    i.jumpBackward(3);
    assert(i.valid() == 0);

    i.first();

    try {
        i.jumpBackward(-1);
        assert(false);
    }
    catch (...)
    {
        assert(true);
    }

    for (int k = 0; k < 5; k++)
        i.next();

    i.jumpBackward(3);
    TElem element = i.getCurrent();
    assert(element.first == 2);

}

