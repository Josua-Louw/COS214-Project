#include "SeedPacket.h"

// Get the price of the seeds
double SeedPacket::getPrice() const {
	return cost;
}

std::string SeedPacket::getName() const {
    return name;
}

// Clone the seeds
PlantImplementor* SeedPacket::clone() {
	// TODO - implement SeedPacket::clone
	throw "Not yet implemented";
}

// Get the type of plant the seeds are of
std::string SeedPacket::getType() const {
	return "SeedPacket";
}

void SeedPacket::decorate(OrderPlant* orderPlant) {
	//N.A.
}