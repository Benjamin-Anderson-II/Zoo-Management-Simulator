#include "animal.h"
#include <iostream>
using namespace std;

/*********************************************************************
** Function:		Constructor 
** Description:		constructs a base animal
** Parameters:		none
** Pre-Conditions:	none
** Post-Conditions:	an animal will be made
*********************************************************************/
Animal::Animal(){
	species = UNDECLARED;
	age = 0;
	cost = 0;
	babies_to_make = 1;
	base_food_cost = 25;
}

/*********************************************************************
** Function:		Constructor 
** Description:		constructs a base animal
** Parameters:		an age
** Pre-Conditions:	none
** Post-Conditions:	an animal will be made
*********************************************************************/
Animal::Animal(int a){
	species = UNDECLARED;
	age = a;
	cost = 0;
	babies_to_make = 1;
	base_food_cost = 25;
}

/*********************************************************************
** Function:		grow
** Description:		increases the animals age by 1 (week)
** Parameters:		none
** Pre-Conditions:	none
** Post-Conditions:	animal will be 1 week older
*********************************************************************/
void Animal::grow(){
	age+=1;
}

/*********************************************************************
** Function:		isBaby
** Description:		checks to see whether the function is a baby (<7 wks)
** Parameters:		none
** Pre-Conditions:	none
** Post-Conditions:	none
*********************************************************************/
bool Animal::isBaby(){
	return (age<7)?true:false;
}

/*********************************************************************
** Function:		isAdult
** Description:		checks to see whether the animal is an adult (>104 wks)
** Parameters:		none
** Pre-Conditions:	none
** Post-Conditions:	none
*********************************************************************/
bool Animal::isAdult(){
	return (age>=104)?true:false;
}

/*********************************************************************
** Function:		accrue_money
** Description:		checks to see whether the money is from an event and returns an amoutn accordingly
** Parameters:		whether or not the money is for an event
** Pre-Conditions:	none
** Post-Conditions:	returns an int
*********************************************************************/
int Animal::accrue_money(bool bonus){
	return (bonus)?0:cost*0.05;
}

/*********************************************************************
** Function:		getFoodCost
** Description:		returns the base food cost
** Parameters:		none
** Pre-Conditions:	none
** Post-Conditions:	none
*********************************************************************/
int Animal::getFoodCost(){
	return base_food_cost;
}

/*********************************************************************
** Function:		getCost
** Description:		returns the cost of the animal
** Parameters:		none
** Pre-Conditions:	none
** Post-Conditions:	none
*********************************************************************/
int Animal::getCost(){
	return cost;
}

/*********************************************************************
** Function:		getBabiesToMake
** Description:		returns the number of children that the species can have at a given time
** Parameters:		none
** Pre-Conditions:	none
** Post-Conditions:	none
*********************************************************************/
int Animal::getBabiesToMake(){
	return babies_to_make;
}

/*********************************************************************
** Function:		getSpecies
** Description:		returns the animal's species
** Parameters:		none
** Pre-Conditions:	none
** Post-Conditions:	none
*********************************************************************/
Type Animal::getSpecies(){
	return species;
}

/*********************************************************************
** Function:		getAge
** Description:		returns the animal's age
** Parameters:		none
** Pre-Conditions:	none
** Post-Conditions:	none
*********************************************************************/
int Animal::getAge(){
	return age;
}

/*********************************************************************
** Function:		Destructor
** Description:		destroys the animal
** Parameters:		none
** Pre-Conditions:	animal must exist
** Post-Conditions:	animal will no longer exist
*********************************************************************/
Animal::~Animal(){
	//cout << "Animal Destroyed\n";
}