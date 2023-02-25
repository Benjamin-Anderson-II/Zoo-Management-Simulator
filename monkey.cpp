#include "monkey.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;

/*********************************************************************
** Function:		Constructor 
** Description:		constructs a base monkey
** Parameters:		none
** Pre-Conditions:	none
** Post-Conditions:	an Monkey will be made
*********************************************************************/
Monkey::Monkey(){
	species = MONKEY;
	cost = 12000;
}

/*********************************************************************
** Function:		Constructor 
** Description:		constructs a base monkey
** Parameters:		age
** Pre-Conditions:	none
** Post-Conditions:	an Monkey will be made
*********************************************************************/
Monkey::Monkey(int a) : Animal{a}{
	species = MONKEY;
	cost = 12000;
}

/*********************************************************************
** Function:		accrue_money
** Description:		checks to see whether the money is from an event and returns an amount accordingly
** Parameters:		whether or not the money is for an event
** Pre-Conditions:	none
** Post-Conditions:	returns an int
*********************************************************************/
int Monkey::accrue_money(bool bonus){
	srand (time(NULL));
	return (bonus) ? (this->isBaby())?(rand()%700+500)*2:(rand()%700+500) : cost*0.03;
}

/*********************************************************************
** Function:		getFoodCost
** Description:		returns the base food cost
** Parameters:		none
** Pre-Conditions:	none
** Post-Conditions:	none
*********************************************************************/
int Monkey::getFoodCost(){
	return base_food_cost*4;
}

/*********************************************************************
** Function:		Destructor
** Description:		destroys the Monkey
** Parameters:		none
** Pre-Conditions:	Monkey must exist
** Post-Conditions:	Monkey will no longer exist
*********************************************************************/
Monkey::~Monkey(){
	cout << "A monkey has died.\n";
}