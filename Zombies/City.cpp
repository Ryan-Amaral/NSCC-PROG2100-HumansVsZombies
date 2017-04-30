// implementation file for City

#include "City.h"
#include "Organism.h"
#include "Coords2d.h"
using namespace std;


City::City(){
	grid = new Organism**[GRID_HEIGHT];
	for (int i = 0; i < GRID_HEIGHT; i++){
		grid[i] = new Organism*[GRID_WIDTH];
	}
	gridWidth = GRID_WIDTH;
	gridHeight = GRID_HEIGHT;
	initializeGrid();
}

City::City(const int width, const int height){
	grid = new Organism**[height];
	for (int i = 0; i < height; i++){
		grid[i] = new Organism*[width];
	}

	gridWidth = width;
	gridHeight = height;
	initializeGrid();
}

City::~City(){}

void City::initializeGrid(){
	for (int x = 0; x < gridHeight; x++){
		for (int y = 0; y < gridWidth; y++){
			grid[x][y] = nullptr;
		}
	}
}

Organism* City::getOrganism(int x, int y){
	return grid[x][y];
}

void City::setOrganism(Organism* organism, int x, int y){
	grid[x][y] = organism;
	if (organism != nullptr){
		organism->setPosition(x, y);
	}
}

int City::getWidth(){
	return gridWidth;
}

int City::getHeight(){
	return gridHeight;
}

// swaping happens in city so zombie can be deleted
void City::swapZombieForHuman(Organism* newHuman){
	// delete the old zombie
	delete this->getOrganism(newHuman->getPosition().x, newHuman->getPosition().y);
	// make new human
	this->setOrganism(newHuman, newHuman->getPosition().x, newHuman->getPosition().y);
}