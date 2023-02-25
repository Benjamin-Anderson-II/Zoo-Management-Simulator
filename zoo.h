#ifndef ZOO_H
#define ZOO_H

#include "animal.h"

class Zoo final {
private:
	int bank{};			//How much money the user has available at a given time
	Animal** exhibit;	//This contains pointers to all of the animals in the zoo
	int num_animals{};	//The number of animals present in the zoo at any given time
		
	void age();
	void specialEvent();
	void income(bool bonus);
	void buy();
	bool expenses();
	bool quit();
	void fastForward(int&,bool&);
	void birthEvent();
	void sickEvent();
	void giveBirth(Animal);
	Animal** childBearers(int& counter);
public:
	/*Constructors and Overloads*/
	Zoo();
	Zoo(const Zoo&);
	Zoo& operator=(const Zoo&);
	void operator+=(Animal*);
	void operator-=(Animal*);

	/*getters*/
	Animal** getExhibit();
	int getNumAnimals();


	void loop();

	~Zoo();
};

#endif