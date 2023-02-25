#include "seaotter.h"
#include <iostream>
using namespace std;

/*********************************************************************
** Function:		Constructor 
** Description:		constructs a base Sea Otter
** Parameters:		none
** Pre-Conditions:	none
** Post-Conditions:	an Sea Otter will be made
*********************************************************************/
SeaOtter::SeaOtter(){
	species = SEAOTTER;
	cost = 4000;
	babies_to_make = 1;
}

/*********************************************************************
** Function:		Constructor 
** Description:		constructs a base Sea Otter
** Parameters:		age
** Pre-Conditions:	none
** Post-Conditions:	an Sea Otter will be made
*********************************************************************/
SeaOtter::SeaOtter(int a) : Animal{a}{
	species = SEAOTTER;
	cost = 4000;
	babies_to_make = 1;
}

/*********************************************************************
** Function:		getFoodCost
** Description:		returns the base food cost
** Parameters:		none
** Pre-Conditions:	none
** Post-Conditions:	none
*********************************************************************/
int SeaOtter::getFoodCost(){
	return base_food_cost*2;
}

/*********************************************************************
** Function:		Destructor
** Description:		destroys the Sea Otter
** Parameters:		none
** Pre-Conditions:	Sea Otter must exist
** Post-Conditions:	Sea Otter will no longer exist
*********************************************************************/
SeaOtter::~SeaOtter(){
	cout << "A sea otter has died.\n";
}