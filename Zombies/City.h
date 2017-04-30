#ifndef _CITY_H
#define _CITY_H

#include <iostream>

using namespace std;

class Organism;

const int GRID_WIDTH = 20;
const int GRID_HEIGHT = 20;

class City
{
private:
	void initializeGrid();

protected:
	Organism*** grid; // the 2d organism array
	int gridWidth;
	int gridHeight;

public:

	City(); // create city with grid of default size
	City(int width, int height); // create city with grid of custom size
	virtual ~City();

	Organism* getOrganism(int x, int y);
	void setOrganism(Organism *organism, int x, int y);

	int getWidth();
	int getHeight();

	void move();

	void swapZombieForHuman(Organism* newHuman);

	friend ostream& operator<<(ostream &output, City &city);

};

#endif

