#ifndef _City_H
#define _City_H

#include "Organism.h"

class Zombie : public Organism
{
private:
	int convertCounter; // starts at zero and the zombie turns a surrounding human into a zombie after eight turns
	int starveCounter; // starts at zero and the zombie turns into a human after 3 turns
public:
	Zombie();
	Zombie(City *city, int width, int height, int x, int y);
	virtual ~Zombie();

	// inherited methods
	virtual void move();
	void eatHuman(int direction);
	virtual int getCounter(); // used for convert
	virtual int getCounter2(); // used for starve

	void convert(); // turns a surrounding human into a zombie
	void convertHuman(int direction); // the actual modifying of human
	void starve(); // convert the zombie back to human
};

#endif