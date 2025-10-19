#ifndef NURSERYMEDIATOR_H
#define NURSERYMEDIATOR_H

class NurseryMediator {


public:
	virtual void notify(void sender, string event, any data) = 0;

	virtual void assign(Command cmd) = 0;

	virtual void registerPlant(Plant* p) = 0;

	virtual void registerStaff(Staff* s) = 0;
};

#endif
