#ifndef STAFF_H
#define STAFF_H

class Staff : Person {

private:
	Staff nextStaff;
	vector<Command*> taskList;
	NurseryMediator* nurseryHub;

public:
	virtual void receiveCommand(Command* command) = 0;
};

#endif
