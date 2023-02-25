#include "meerkat.h"
#include <iostream>
using namespace std;

/*********************************************************************
** Function:		Constructor 
** Description:		constructs a base Meerkat
** Parameters:		none
** Pre-Conditions:	none
** Post-Conditions:	an Meerkat will be made
*********************************************************************/
Meerkat::Meerkat(){
	species = MEERKAT;
	cost = 500;
	babies_to_make = 3;
}

/*********************************************************************
** Function:		Constructor 
** Description:		constructs a base Meerkat
** Parameters:		age
** Pre-Conditions:	none
** Post-Conditions:	an Meerkat will be made
*********************************************************************/
Meerkat::Meerkat(int a) : Animal{a}{
	species = MEERKAT;
	cost = 500;
	babies_to_make = 3;
}

/*********************************************************************
** Function:		getFoodCost
** Description:		returns the base food cost
** Parameters:		none
** Pre-Conditions:	none
** Post-Conditions:	none
*********************************************************************/
int Meerkat::getFoodCost(){
	return base_food_cost;
}

/*********************************************************************
** Function:		Destructor
** Description:		destroys the Meerkat
** Parameters:		none
** Pre-Conditions:	Meerkat must exist
** Post-Conditions:	Meerkat will no longer exist
*********************************************************************/
Meerkat::~Meerkat(){
	cout << "A meerkat has died.\n";
}