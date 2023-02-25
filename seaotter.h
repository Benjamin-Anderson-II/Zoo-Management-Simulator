#ifndef SEAOTTER_H
#define SEAOTTER_H

#include "animal.h"

class SeaOtter : public Animal {
public:
	SeaOtter();
	SeaOtter(int a);
	int getFoodCost();
	~SeaOtter();
};

#endif