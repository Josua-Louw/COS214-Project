#ifndef PLANT_H
#define PLANT_H

class Plant : GreenHouse {

private:
	CareStrategy* strategy;

	string name;

public:
	virtual void water() = 0;

	virtual void feed() = 0;

	virtual double getPrice() = 0;

	virtual Plant* clone() = 0;

	string getName();

	virtual string getType() = 0;
};

#endif
