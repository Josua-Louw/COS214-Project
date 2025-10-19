#ifndef ORDER_H
#define ORDER_H

class Order {

private:
	vector<Plant*> plants;

public:
	double getTotalCost();

	void addPlant(Plant* plant);
};

#endif
