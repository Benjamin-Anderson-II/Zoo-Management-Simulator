/**********************************************************
** Program: 	zoo_tycoon.cpp
** Author:		Benjamin Anderson II
** Date: 		July, 31 2022
** Description: 
** Input:		Questions provided by the computer 
**					about how the user wantsto proceed in 
** 					playing the game
** Output:		The current state of the game. Including 
** 					the current week, abnk account balance
** 					whether or not a certain action is 
** 					possible and whether the game is ending
**********************************************************/

#include "zoo.h"
#include "monkey.h"
#include "seaotter.h"
#include "meerkat.h"

#include <iostream>
using namespace std;

/*********************************************************************
** Function:		main
** Description:		main function
** Parameters:		arguments passed by command line
** Pre-Conditions:	none
** Post-Conditions:	none
*********************************************************************/
int main(int argc, char const *argv[])
{
	Zoo z;
	//z+=new Monkey();
	//cout << z.getExhibit()[0]->getSpecies() << endl;
	z.loop();
	return 0;
}