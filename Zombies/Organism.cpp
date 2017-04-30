#include "Organism.h"
#include "City.h"
#include "Coords2d.h"
using namespace std;

Organism::Organism()
{
	
}

Organism::Organism(City* city, int width, int height){
	this->city = city;
	this->width = width;
	this->height = height;
}

Organism::~Organism()
{
}

// change return type to 2d coords
Coords2d Organism::getPosition(){
	Coords2d coords;
	coords.x = this->x;
	coords.y = this->y;

	return coords;
}

void Organism::setPosition(int x, int y){
	this->x = x;
	this->y = y;
}

int Organism::getSpecies(){
	return species;
}

bool Organism::getMoved(){
	return moved;
}

void Organism::setMoved(bool moved){
	this->moved = moved;
}

void Organism::endTurn(){
	setMoved(false);
}

// moves the organism to a square around it
void Organism::moveToSquare(int direction){
	switch (direction)
	{
	case Directions::NORTH:
		// move NORTH
		city->setOrganism(this, this->x - 1, this->y);
		city->setOrganism(nullptr, this->x + 1, this->y);
		break;
	case Directions::EAST:
		// move EAST
		city->setOrganism(this, this->x, this->y + 1);
		city->setOrganism(nullptr, this->x, this->y - 1);
		break;
	case Directions::SOUTH:
		// move SOUTH
		city->setOrganism(this, this->x + 1, this->y);
		city->setOrganism(nullptr, this->x - 1, this->y);
		break;
	case Directions::WEST:
		// move WEST
		city->setOrganism(this, this->x, this->y - 1);
		city->setOrganism(nullptr, this->x, this->y + 1);
		break;
	case Directions::NORTH_EAST:
		// move NORTH EAST
		city->setOrganism(this, this->x - 1, this->y + 1);
		city->setOrganism(nullptr, this->x + 1, this->y - 1);
		break;
	case Directions::SOUTH_EAST:
		// move SOUTH EAST
		city->setOrganism(this, this->x + 1, this->y + 1);
		city->setOrganism(nullptr, this->x - 1, this->y - 1);
		break;
	case Directions::SOUTH_WEST:
		// move SOUTH WEST
		city->setOrganism(this, this->x + 1, this->y - 1);
		city->setOrganism(nullptr, this->x - 1, this->y + 1);
		break;
	case Directions::NORTH_WEST:
		// move NORTH WEST
		city->setOrganism(this, this->x - 1, this->y - 1);
		city->setOrganism(nullptr, this->x + 1, this->y + 1);
		break;
	default:
		break;
	}
}
