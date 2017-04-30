#ifndef _Human_H
#define _Human_H

#include "Organism.h"
#include "City.h"

class Human : public Organism
{
private:
	int recruitCounter; // starts at zero and the human recruits a new human after 3 turns
	void createHuman(int direction);
public:
	Human();
	Human(City* city, int width, int height, int x, int y);
	virtual ~Human();

	// inherited methods
	virtual void move();
	virtual int getCounter();
	virtual int getCounter2();

	void recruit(); // create a new human in an adjacent square
};

#endif
