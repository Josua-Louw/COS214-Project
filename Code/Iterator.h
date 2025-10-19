#ifndef ITERATOR_H
#define ITERATOR_H

class Iterator {


public:
	virtual void first() = 0;

	virtual void next() = 0;

	virtual boolean isDone() = 0;

	virtual Plant* currentItem() = 0;
};

#endif
