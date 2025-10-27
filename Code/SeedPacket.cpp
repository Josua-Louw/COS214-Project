#include "SeedPacket.h"

// Get the price of the seeds
double SeedPacket::getPrice() const {
	return cost;
}

std::string SeedPacket::getName() const {
    return name;
}

SeedPacket::SeedPacket(const SeedPacket& other) : OrderPlant(other) {}

// Clone the seeds
PlantImplementor* SeedPacket::clone() {
	return new SeedPacket(*this);
}

// Get the type of plant the seeds are of
PLANT_TYPE SeedPacket::getType() const {
	return PLANT_TYPE::SEED_PACKET;
}

void SeedPacket::decorate(OrderPlant* orderPlant) {
	//N.A.
}