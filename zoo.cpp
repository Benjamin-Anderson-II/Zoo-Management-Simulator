#include "zoo.h"
#include "monkey.h"
#include "seaotter.h"
#include "meerkat.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
using namespace std;
//104 wks = 2 yrs

/*********************************************************************
** Function:		Constructor
** Description:		constructs a Zoo
** Parameters:		none
** Pre-Conditions:	none
** Post-Conditions:	A zoo will be made
*********************************************************************/
Zoo::Zoo(){
	bank = 100000;
	num_animals = 0;
	exhibit = new Animal*[num_animals];
}

/*********************************************************************
** Function:		Copy Constructor
** Description:		Makes a Zoo that is a deep copy of another zoo
** Parameters:		A preexisting zoo
** Pre-Conditions:	none
** Post-Conditions:	The new Zoo will be a deep copy of the old one
*********************************************************************/
Zoo::Zoo(const Zoo& old_zoo){
	bank = old_zoo.bank;
	num_animals = old_zoo.num_animals;
	exhibit = new Animal*[num_animals];

	for(int i = 0; i < num_animals; i++){
		*exhibit[i] = *old_zoo.exhibit[i];
	}
}

/*********************************************************************
** Function:		Assignment Operator Overload
** Description:		Makes a preexisting zoo a copy of another
** Parameters:		A Zoo
** Pre-Conditions:	There must be two zoos
** Post-Conditions:	the two zoos will be identical (deep copy)
*********************************************************************/
Zoo& Zoo::operator=(const Zoo& old_zoo){
	if(this == &old_zoo) return *this; // checks to see if they are the same

	bank = old_zoo.bank;

	if (num_animals != old_zoo.num_animals) { // resizes the exhibiit if need be
		delete[] exhibit;
		exhibit = nullptr;
		num_animals = old_zoo.num_animals;
		exhibit = new Animal*[num_animals];
	}

	for(int i = 0; i < num_animals; i++){
		*exhibit[i] = *old_zoo.exhibit[i];
	}

	return *this;
}

/*********************************************************************
** Function: 		loop
** Description: 	Main gameplay Loop of the Program
** Parameters:		none
** Pre-Conditions: 	none
** Post-Conditions:	game is over
*********************************************************************/ 
void Zoo::loop(){
	//initialize variables
	int week = 0;
	int ff_weeks = 0;
	bool is_ff = false;

	//gameplay loop
	while(true){
		cout << "_________\n Week " << week << "\n_________\n";
		age();

		specialEvent();

		income(false);

		if(!is_ff) buy();

		if(expenses()||(num_animals==0&&bank<500)){
			cout << "You do not have the means to continue. Sorry.\n";
			break;
		}
		week++;

		if(!is_ff) if(quit()) break;
		fastForward(ff_weeks, is_ff);
		
	}
}

/*********************************************************************
** Function: 		age
** Description: 	Increases the age every animal in the exhibit
** Parameters:		none
** Pre-Conditions:	none
** Post-Conditions:	none
*********************************************************************/ 
void Zoo::age(){
	for(int i = 0; i < num_animals; i++){
		exhibit[i]->grow();
	}
	cout << "All " << num_animals << " of your animals have grown 1 week!\n";
}

/*********************************************************************
** Function:		specialEvent
** Description:		selects a special event from the 4 presets and enacts them
** Parameters:		none
** Pre-Conditions:	more than 1 animal must be in the exhibit
** Post-Conditions:	none
*********************************************************************/ 
void Zoo::specialEvent(){
	//initialize variables
	srand (time(NULL));				//makes it so that rand() is different every run of the game
	int special_event = rand()%4;	//specifies which event is going to happen

	if(num_animals>0){
		switch(special_event){
			case 0: //sick
			sickEvent();
			break;

			case 1: // kid
			birthEvent();
			break;

			case 2: // boom
			cout << "There was a boom in zoo attendance this week!\n";
			income(true);
			break;

			case 3: // nothing
			cout << "Nothing of note happened this week\n";
			break;

			default:break;
		}
	}
}

/*********************************************************************
** Function:		income
** Description:		Increases the bank by how many 
** Parameters:		Whether or not the income is from an event
** Pre-Conditions:	bank>=0
** Post-Conditions:	bank value will increase or stay the same
*********************************************************************/
void Zoo::income(bool bonus){
	int pre = bank; // The bank before adding money

	//If the animal at index is a child add 2x the money to the bank
	for(int i = 0; i < num_animals; i++)
		bank+=(exhibit[i]->isBaby())?exhibit[i]->accrue_money(bonus)*2:exhibit[i]->accrue_money(bonus);

	cout << "You earned $" << bank-pre << " this week!\nYour bank statement is now $" << bank << endl;
}

/*********************************************************************
** Function:		buy
** Description:		asks the user what they would like to purchase if anything, then adds the animals to the exhibit
** Parameters:		none
** Pre-Conditions:	must not be fast-forwarding
** Post-Conditions:	none
*********************************************************************/
void Zoo::buy(){
	//initialize variables
	Animal* a;
	string input;
	string number;
	int num;

	cout << "Would You like to purchase an Animal? (y/n) \n";

	//========THE LOOPS ARE TO ACCOUT FOR USER ERROR========

	while(true){//Purchase Loop
		cin >> input;
		if(input[0]=='y'){
			while(true){ //Animal Selection Loop
				cout << "Which animal would you like to purchase?\nMonkey(1): $12000(ea.)\nSea Otter(2): $4000(ea.)\nMeerkat(3): $500(ea.)\n";
				cin >> input;
				if(input[0]-'0'==0||input[0]-'0'>3)
					cout << "Invalid Input, Try Again!\n";
				else break;
			}

			cout << "How many? (max 100)\n";
			while(true){
			cin>>number;
				try{
					if(number.length()>3) throw 0;

					//Makes sure the input is a number
					for(int i = 0; i < (int)number.length(); i++)
						if(number[i]-'0'<0||number[i]-'0'>9)
							throw 0;

					num = stoi(number);

					//makes sure the number isn't too big
					if(num>100) throw 0;

					//makes "a" an animal of the previously selsected type
					switch(input[0]-'0'){
						case 1:
						a=new Monkey();
						break;
						case 2:
						a=new SeaOtter();
						break;
						case 3:
						a=new Meerkat();
						break;
						default: break;
					}

					//make sure the user can pay for it
					if(a->getCost()*num>bank) throw 1;
					break;
				} catch(int err){
					if(err==0)
						cout << "Invalid Input, Try Again!\n";
					else if(err==1)
						cout << "Not Enough Funds!\n";
					
				}
			}

			//adds the right number of animals to the exhibit, making sure each is unique
			Type sp = a->getSpecies();
			for(int i = 0; i < num; i++){
				bank-=a->getCost();
				switch(sp){
					case MONKEY:
					*this+=new Monkey(104);
					break;
					case SEAOTTER:
					*this+=new SeaOtter(104);
					break;
					case MEERKAT:
					*this+=new Meerkat(104);
					break;
					default: break;
				}
			}
			break;
		} else if(input[0]=='n'){
			break;
		} else{
			cout << "Invalid Input, Try Again!\n";
		}
	}
}

/*********************************************************************
** Function:		expenses
** Description:		pays for the cost of food of the animals, returning true if bank goes negative
** Parameters:		none
** Pre-Conditions:	bank>=0
** Post-Conditions:	bank value decreases
*********************************************************************/
bool Zoo::expenses(){
	int pre = bank; // Instance of the bank before it is changed
	for(int i = 0; i < num_animals; i++){
		bank-=exhibit[i]->getFoodCost();
	}
	cout << "Food cost " << pre-bank << " this week.\n";
	if(bank<0){
		return true;;
	}
	return false;
}

/*********************************************************************
** Function:		sickEvent
** Description:		Makes a random animal sick, and if the cost to cure it cannot be met the animal dies
** Parameters:		none
** Pre-Conditions:	Must have more than 0 animals in exhibit
** Post-Conditions:	none
*********************************************************************/
void Zoo::sickEvent(){
	int random = rand()%num_animals;//pick a random animal

	//inform the user of the type of animal that has fallen ill
	switch(exhibit[random]->getSpecies()){
		case MONKEY:
		cout << "A monkey has fallen ill!\n";
		break;
		case SEAOTTER:
		cout << "A sea otter has fallen ill!\n";
		break;
		case MEERKAT:
		cout << "A meerkat has fallen ill!\n";
		break;
		default:
		cout << "Unknown Animal has fallen ill\n";
		break;
	}

	// doubles the sick cost if the animal is a baby
	int sick_cost = (exhibit[random]->isBaby())?exhibit[random]->getCost()*0.4:exhibit[random]->getCost()*0.2;
	
	if(sick_cost>bank)	//Cannot afford treatment
		*this -= exhibit[random];
	else{				//Can afford treatment
		bank-=sick_cost;
		cout << "They were cured! ($" << sick_cost << " has been removed from your account)\n";
	}		
}

/*********************************************************************
** Function:		birthEvent
** Description:		Attempts to make a child with two parents of the same species
** Parameters:		none
** Pre-Conditions:	none
** Post-Conditions:	none
*********************************************************************/
void Zoo::birthEvent(){
	//make list of species that can have a baby
	int breedable_species_counter = 0;
	Animal** breedable_species = childBearers(breedable_species_counter);

	if(breedable_species_counter==0){ // if no species can have a baby, do nothing
		return;
	} else { // if species can, then randonly pick one
		giveBirth(*breedable_species[rand()%breedable_species_counter]);
	}
	delete[] breedable_species;
}

/*********************************************************************
** Function:		childBearers
** Description:		Makes a list of Animal species that have child bearing abilities
** Parameters:		reference to a counter
** Pre-Conditions:	counter must come in initialized to 0
** Post-Conditions:	List of animals must be returned
*********************************************************************/
Animal** Zoo::childBearers(int& counter){
	//list containing potential breedable species
	Animal** p1 = new Animal*[3];
	Animal** p2 = new Animal*[3];
	Animal** toReturn = new Animal*[3];

	//fills the list with animals given the following rules
		//1. The animal is an adult
		//2. The animal is not already in another list
		//3. indexes are: 0=Monkey, 1=SeaOtter, 2=Meerkat
	for(int i = 0; i < num_animals; i++){
		if(exhibit[i]->getSpecies()==MONKEY // is a monkey
			&&exhibit[i]->isAdult()  		// is an adult
			&&exhibit[i]!=p1[0])			// isn't in p1
		{
			if(p1[0]==nullptr)	//is p1
				p1[0] = exhibit[i];
			else 				//is p2
				p2[0] = exhibit[i];
			
		}

		if(exhibit[i]->getSpecies()==SEAOTTER // is a sea otter
			&&exhibit[i]->isAdult()  		  // is an adult
			&&exhibit[i]!=p1[1])			  // isn't in p1
		{
			if(p1[1]==nullptr)	//is p1
				p1[1] = exhibit[i];
			else 				//is p2
				p2[1] = exhibit[i];
		}

		if(exhibit[i]->getSpecies()==MEERKAT // is a meerkat
			&&exhibit[i]->isAdult()  		 // is an adult
			&&exhibit[i]!=p1[2])			 // isn't in p1
		{
			if(p1[2]==nullptr)	//is p1
				p1[2] = exhibit[i];
			else 				//is p2
				p2[2] = exhibit[i];
		}
	}

	for (int i = 0; i < 3; i++){
		if(p1[i]!=nullptr&&p2[i]!=nullptr){ //if has two suitable parents
			toReturn[counter] = p1[i];
			counter++; // increases the counter that was passed by reference
		}
	}

	delete[] p1;
	delete[] p2;

	return toReturn;
}


/*********************************************************************
** Function:		giveBirth
** Description:		adds children to the exhibit, the number and species are determined by the parent
** Parameters:		Animal, to reference for child
** Pre-Conditions:	none
** Post-Conditions:	new animals will be present within the exhibit
*********************************************************************/
void Zoo::giveBirth(Animal parent){
	for(int i = 0; i < parent.getBabiesToMake(); i++){
		Animal* a;
		switch(parent.getSpecies()){ // find the parent's species

			case MONKEY:
			cout << "NEW MONKEY BIRTHED\n";
			a = new Monkey();
			break;

			case SEAOTTER:
			cout << "NEW SEA OTTER BIRTHED\n";
			a = new SeaOtter();
			break;

			case MEERKAT:
			cout << "NEW MEERKAT BIRTHED\n";
			a = new Meerkat();
			break;

			default:
			cerr << "Improper parent type specified\n";
			break;
		}
		*this+=a;
	}
}

/*********************************************************************
** Function:		quit
** Description:		asks the user if they would like to quit the program and does if they do
** Parameters:		none
** Pre-Conditions:	game must be ongoing
** Post-Conditions:	game will end
*********************************************************************/
bool Zoo::quit(){
	string inp;
	cout << "Would You Like To Quit?(y/n)\n";
	cin >> inp;
	if(inp[0]=='y')
		return true;
	else if (inp[0]!='n')
		cout << "Invalid input, try again next week!\n";
	return false;
}

/*********************************************************************
** Function:		fastForward
** Description:		asks the user if they would like to fast forward to a certain week
* 						if they do then it asks how many, and will proceed to play out the weeks without the user
** Parameters:		reference to the number of weeks that will be fast forwarded
* 					reference to a bool telling if the game is already fast forwarding
** Pre-Conditions:	game must be ongoing
** Post-Conditions:	the user will not have been able to control X number of weeks
*********************************************************************/
void Zoo::fastForward(int& ff_weeks, bool& is_ff){

	//Loops are present to account for user misinput

	string inp;
	string number;
	int num;
	if(!is_ff){
			cout << "Would You Like to fast forward?(y/n)\n";
			cin >> inp;
			if(inp[0]=='y'){
				is_ff=true;
				cout << "How many weeks?\n";
				while(true){
					cin >> number;
					try{
						for(int i = 0; i < (int)number.length(); i++)
							if(number[i]-'0'<0||number[i]-'0'>9)
								throw 0;

						num = stoi(number);
						break;
					} catch(...){
						cout << "You did not enter an integer. Try Again.\n";
					}
				}
				ff_weeks=num;
			}
			else if (inp[0]!='n')
				cout << "Invalid input, try again next week!\n";
		} else {
			ff_weeks--;
			if(ff_weeks==0) 
				is_ff = false;
		}
}

/*********************************************************************
** Function:		getExhibit
** Description:		returns exhibit
** Parameters:		none
** Pre-Conditions:	none
** Post-Conditions:	none
*********************************************************************/
Animal** Zoo::getExhibit(){
	return exhibit;
}

/*********************************************************************
** Function:		Addition Assignment Operator Overload
** Description:		Adds an Animal to the Exhibit through the Zoo
** Parameters:		pointer to the animal that is to be added
** Pre-Conditions:	A zoo must already exist
** Post-Conditions:	The exhibit will have one more animal
*********************************************************************/
void Zoo::operator+=(Animal* new_animal){
	Animal** new_exhibit = new Animal*[num_animals+1];
	for(int i = 0; i < num_animals; i++){
		new_exhibit[i] = exhibit[i];
	}
	num_animals++;
	new_exhibit[num_animals-1] = new_animal;
	delete[] exhibit;
	exhibit = new Animal*[num_animals];
	for(int i = 0; i < num_animals; i++){
		exhibit[i] = new_exhibit[i];
	}
	delete[] new_exhibit;
}

/*********************************************************************
** Function:		Subtraction Assignment Operator Overload
** Description:		Removes an animal from the exhibit through the Zoo
** Parameters:		Pointer to the animal that is to be removed
** Pre-Conditions:	The animal must already be contained within the zoo
** Post-Conditions:	The exhibit will have 1 less animal
*********************************************************************/
void Zoo::operator-=(Animal* dead_animal){ // Remove a dead animal
	Animal** new_exhibit = new Animal*[num_animals-1];
	bool killed = false;
	num_animals--;
	for(int i = 0; i < num_animals; i++){
		if(exhibit[i]==dead_animal){
			killed=true;
		}
		new_exhibit[i] = exhibit[(!killed)?i:i+1];
	}
	delete[]exhibit;
	exhibit = new Animal*[num_animals];
	for(int i = 0; i < num_animals; i++){
		exhibit[i] = new_exhibit[i];
	}
	delete[]new_exhibit;
}

/*********************************************************************
** Function:		getNumAnimals
** Description:		returns the number of animals in the exhibit
** Parameters:		none
** Pre-Conditions:	none
** Post-Conditions:	none
*********************************************************************/
int Zoo::getNumAnimals(){
	return num_animals;
}

/*********************************************************************
** Function:		Destructor
** Description:		Destroys the Zoo and deletes the exhibit
** Parameters:		none
** Pre-Conditions:	Zoo must exist
** Post-Conditions:	Zoo will no longer exist
*********************************************************************/
Zoo::~Zoo(){
	delete[] exhibit;
}