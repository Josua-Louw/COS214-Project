#ifndef NURSERYHUB_H
#define NURSERYHUB_H

class NurseryHub : NurseryMediator {

private:
	vector<Plant*> plants;
	vector<Staff*> staff;
	vector<customer*> customers;

public:
	void assign(Command cmd);

	void notify(void sender, string event, any data);

	void registerPlant(Plant* p);

	void registerStaff(Staff* s);
};

#endif
