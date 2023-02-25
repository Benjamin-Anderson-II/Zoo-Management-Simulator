#ifndef MONKEY_H
#define MONKEY_H

#include "animal.h"

class Monkey : public Animal{
public:
	Monkey();
	Monkey(int a);
	int accrue_money(bool bonus);
	int getFoodCost();
	~Monkey();
}; 

#endif