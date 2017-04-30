#include "Human.h"
#include <vector>
#include <time.h>
using namespace std;

Human::Human()
{
	species = Organism::Species::HUMAN;
}

Human::Human(City* city, int width, int height, int x, int y){
	species = Organism::Species::HUMAN;
	this->city = city;
	this->width = width;
	this->height = height;
	this->x = x;
	this->y = y;
}

Human::~Human(){

}

int Human::getCounter(){
	return recruitCounter;
}

void Human::move(){
	setMoved(true);
	recruitCounter++;

	int truffleShuffle;
	srand(time(NULL));
	vector<int> whatsAround;

	// search south only when x is less than height -1
	if (this->x < this->height - 1){
		if (this->city->getOrganism(this->x + 1, this->y) == nullptr){
			whatsAround.push_back(Directions::SOUTH);
		}
	}

	// search north only when x is greater than 0
	if (this->x > 0){
		if (this->city->getOrganism(this->x - 1, this->y) == nullptr){
			whatsAround.push_back(Directions::NORTH);
		}
	}

	// search west only when y is greater than 0
	if (this->y > 0){
		if (this->city->getOrganism(this->x, this->y - 1) == nullptr){
			whatsAround.push_back(Directions::WEST);
		}
	}

	// search east only when y is less than width -1
	if (this->y < this->width - 1){
		if (this->city->getOrganism(this->x, this->y + 1) == nullptr){
			whatsAround.push_back(Directions::EAST);
		}
	}

	// if empty space, go to one
	if (whatsAround.size() > 0){
		truffleShuffle = (rand() % whatsAround.size());
		moveToSquare(whatsAround.at(truffleShuffle));
	}
}

void Human::recruit(){
	this->recruitCounter = 0;
	int truffleShuffle;
	srand(time(NULL));
	vector<int> whatsAround;

	// search south only when x is less than height -1
	if (this->x < this->height - 1){
		if (this->city->getOrganism(this->x + 1, this->y) == nullptr){
			whatsAround.push_back(Directions::SOUTH);
		}
	}

	// search north only when x is greater than 0
	if (this->x > 0){
		if (this->city->getOrganism(this->x - 1, this->y) == nullptr){
			whatsAround.push_back(Directions::NORTH);
		}
	}

	// search west only when y is greater than 0
	if (this->y > 0){
		if (this->city->getOrganism(this->x, this->y - 1) == nullptr){
			whatsAround.push_back(Directions::WEST);
		}
	}

	// search east only when y is less than width -1
	if (this->y < this->width - 1){
		if (this->city->getOrganism(this->x, this->y + 1) == nullptr){
			whatsAround.push_back(Directions::EAST);
		}
	}

	// if empty space, go to one
	if (whatsAround.size() > 0){
		truffleShuffle = (rand() % whatsAround.size());
		createHuman(whatsAround.at(truffleShuffle));
	}
}

int Human::getCounter2(){
	return 0;
}

void Human::createHuman(int direction){
	switch (direction)
	{
	case Directions::NORTH:
		// move NORTH
		city->setOrganism(new Human(this->city, this->width, this->height, this->x - 1, this->y), this->x - 1, this->y);
		break;
	case Directions::EAST:
		// move EAST
		city->setOrganism(new Human(this->city, this->width, this->height, this->x, this->y + 1), this->x, this->y + 1);
		break;
	case Directions::SOUTH:
		// move SOUTH
		city->setOrganism(new Human(this->city, this->width, this->height, this->x + 1, this->y), this->x + 1, this->y);
		break;
	case Directions::WEST:
		// move WEST
		city->setOrganism(new Human(this->city, this->width, this->height, this->x, this->y - 1), this->x, this->y - 1);
		break;
	default:
		break;
	}
}