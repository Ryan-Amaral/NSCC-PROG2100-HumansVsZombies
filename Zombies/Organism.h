#ifndef _Organism_H
#define _Organism_H

#include <iostream>
#include "Coords2d.h"

using namespace std;

class City;

class Organism
{
protected:
	int x;
	int y;
	int width; // width of city
	int height; // height of city
	bool moved; // did this thing move this turn
	int species;
	City* city;

	enum Directions { NORTH, EAST, SOUTH, WEST, NORTH_EAST, SOUTH_EAST, SOUTH_WEST, NORTH_WEST, NUM_DIRECTIONS };

public:
	Organism();
	Organism(City* city, int width, int height);
	virtual ~Organism();

	enum Species { HUMAN, ZOMBIE };

	virtual void move() = 0;
	virtual int getCounter() = 0;
	virtual int getCounter2() = 0;
	void endTurn();
	
	int getSpecies(); //this could also be coded concrete here
	Coords2d getPosition();
	void setPosition(int x, int y);
	bool getMoved();
	void setMoved(bool moved);
	void moveToSquare(int direction);

	friend ostream& operator<<(ostream &output, Organism* organism);
};

#endif
