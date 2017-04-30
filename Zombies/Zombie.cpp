#include "Zombie.h"
#include "City.h"
#include <vector>
#include <time.h>
#include "Human.h"
using namespace std;

Zombie::Zombie()
{
	species = Organism::Species::ZOMBIE;
}

Zombie::Zombie(City *city, int width, int height, int x, int y){
	species = Organism::Species::ZOMBIE;
	this->city = city;
	this->width = width;
	this->height = height;
	this->x = x;
	this->y = y;
}

Zombie::~Zombie()
{
	
}

void Zombie::move(){
	setMoved(true);
	convertCounter++;
	starveCounter++;

	int truffleShuffle;
	srand(time(NULL));
	vector<int> whatsAround;

	// look for humans around zombies
	// search south only when x is less than height -1
	if (this->x < this->height - 1){
		if (this->city->getOrganism(this->x + 1, this->y) != nullptr){
			if (this->city->getOrganism(this->x + 1, this->y)->getSpecies() == Species::HUMAN){
				whatsAround.push_back(Directions::SOUTH);
			}
		}
	}

	// search north only when x is greater than 0
	if (this->x > 0){
		if (this->city->getOrganism(this->x - 1, this->y) != nullptr){
			if (this->city->getOrganism(this->x - 1, this->y)->getSpecies() == Species::HUMAN){
				whatsAround.push_back(Directions::NORTH);
			}
		}
	}

	// search west only when y is greater than 0
	if (this->y > 0){
		if (this->city->getOrganism(this->x, this->y - 1) != nullptr){
			if (this->city->getOrganism(this->x, this->y - 1)->getSpecies() == Species::HUMAN){
				whatsAround.push_back(Directions::WEST);
			}
		}
	}

	// search east only when y is less than width -1
	if (this->y < this->width - 1){
		if (this->city->getOrganism(this->x, this->y + 1) != nullptr){
			if (this->city->getOrganism(this->x, this->y + 1)->getSpecies() == Species::HUMAN){
				whatsAround.push_back(Directions::EAST);
			}
		}
	}

	// north west
	if (this->x > 0 && this->y > 0){
		if (this->city->getOrganism(this->x - 1, this->y - 1) != nullptr){
			if (this->city->getOrganism(this->x - 1, this->y - 1)->getSpecies() == Species::HUMAN){
				whatsAround.push_back(Directions::NORTH_WEST);
			}
		}
	}

	// north east
	if (this->x > 0 && this->y < this->width - 1){
		if (this->city->getOrganism(this->x - 1, this->y + 1) != nullptr){
			if (this->city->getOrganism(this->x - 1, this->y + 1)->getSpecies() == Species::HUMAN){
				whatsAround.push_back(Directions::NORTH_EAST);
			}
		}
	}

	// south west
	if (this->x < this->height - 1 && this->y > 0){
		if (this->city->getOrganism(this->x + 1, this->y - 1) != nullptr){
			if (this->city->getOrganism(this->x + 1, this->y - 1)->getSpecies() == Species::HUMAN){
				whatsAround.push_back(Directions::SOUTH_WEST);
			}
		}
	}

	// south east
	if (this->x < this->height - 1 && this->y < this->width - 1){
		if (this->city->getOrganism(this->x + 1, this->y + 1) != nullptr){
			if (this->city->getOrganism(this->x + 1, this->y + 1)->getSpecies() == Species::HUMAN){
				whatsAround.push_back(Directions::SOUTH_EAST);
			}
		}
	}

	// if humans are around zombie, eat one
	if (whatsAround.size() > 0){
		truffleShuffle = (rand() % whatsAround.size());
		eatHuman(whatsAround.at(truffleShuffle));
		starveCounter = 0;
		return;
	}


	// otherwise go to a random square, if atleast one is opened

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
		return;
	}
}

void Zombie::eatHuman(int direction){
	switch (direction)
	{
	case Directions::NORTH:
		// move NORTH
		delete city->getOrganism(this->x - 1, this->y);
		city->setOrganism(this, this->x - 1, this->y);
		city->setOrganism(nullptr, this->x + 1, this->y);
		break;
	case Directions::EAST:
		// move EAST
		delete city->getOrganism(this->x, this->y + 1);
		city->setOrganism(this, this->x, this->y + 1);
		city->setOrganism(nullptr, this->x, this->y - 1);
		break;
	case Directions::SOUTH:
		// move SOUTH
		delete city->getOrganism(this->x + 1, this->y);
		city->setOrganism(this, this->x + 1, this->y);
		city->setOrganism(nullptr, this->x - 1, this->y);
		break;
	case Directions::WEST:
		// move WEST
		delete city->getOrganism(this->x, this->y - 1);
		city->setOrganism(this, this->x, this->y - 1);
		city->setOrganism(nullptr, this->x, this->y + 1);
		break;
	case Directions::NORTH_EAST:
		// move NORTH EAST
		delete city->getOrganism(this->x - 1, this->y + 1);
		city->setOrganism(this, this->x - 1, this->y + 1);
		city->setOrganism(nullptr, this->x + 1, this->y - 1);
		break;
	case Directions::SOUTH_EAST:
		// move SOUTH EAST
		delete city->getOrganism(this->x + 1, this->y + 1);
		city->setOrganism(this, this->x + 1, this->y + 1);
		city->setOrganism(nullptr, this->x - 1, this->y - 1);
		break;
	case Directions::SOUTH_WEST:
		// move SOUTH WEST
		delete city->getOrganism(this->x + 1, this->y - 1);
		city->setOrganism(this, this->x + 1, this->y - 1);
		city->setOrganism(nullptr, this->x - 1, this->y + 1);
		break;
	case Directions::NORTH_WEST:
		// move NORTH WEST
		delete city->getOrganism(this->x - 1, this->y - 1);
		city->setOrganism(this, this->x - 1, this->y - 1);
		city->setOrganism(nullptr, this->x + 1, this->y + 1);
		break;
	default:
		break;
	}
}

int Zombie::getCounter(){
	return convertCounter;
}

int Zombie::getCounter2(){
	return starveCounter;
}

// turn human into a zombie
void Zombie::convert(){
	int truffleShuffle;
	srand(time(NULL));
	vector<int> whatsAround;

	// look for humans around zombies
	// search south only when x is less than height -1
	if (this->x < this->height - 1){
		if (this->city->getOrganism(this->x + 1, this->y) != nullptr){
			if (this->city->getOrganism(this->x + 1, this->y)->getSpecies() == Species::HUMAN){
				whatsAround.push_back(Directions::SOUTH);
			}
		}
	}

	// search north only when x is greater than 0
	if (this->x > 0){
		if (this->city->getOrganism(this->x - 1, this->y) != nullptr){
			if (this->city->getOrganism(this->x - 1, this->y)->getSpecies() == Species::HUMAN){
				whatsAround.push_back(Directions::NORTH);
			}
		}
	}

	// search west only when y is greater than 0
	if (this->y > 0){
		if (this->city->getOrganism(this->x, this->y - 1) != nullptr){
			if (this->city->getOrganism(this->x, this->y - 1)->getSpecies() == Species::HUMAN){
				whatsAround.push_back(Directions::WEST);
			}
		}
	}

	// search east only when y is less than width -1
	if (this->y < this->width - 1){
		if (this->city->getOrganism(this->x, this->y + 1) != nullptr){
			if (this->city->getOrganism(this->x, this->y + 1)->getSpecies() == Species::HUMAN){
				whatsAround.push_back(Directions::EAST);
			}
		}
	}

	// north west
	if (this->x > 0 && this->y > 0){
		if (this->city->getOrganism(this->x - 1, this->y - 1) != nullptr){
			if (this->city->getOrganism(this->x - 1, this->y - 1)->getSpecies() == Species::HUMAN){
				whatsAround.push_back(Directions::NORTH_WEST);
			}
		}
	}

	// north east
	if (this->x > 0 && this->y < this->width - 1){
		if (this->city->getOrganism(this->x - 1, this->y + 1) != nullptr){
			if (this->city->getOrganism(this->x - 1, this->y + 1)->getSpecies() == Species::HUMAN){
				whatsAround.push_back(Directions::NORTH_EAST);
			}
		}
	}

	// south west
	if (this->x < this->height - 1 && this->y > 0){
		if (this->city->getOrganism(this->x + 1, this->y - 1) != nullptr){
			if (this->city->getOrganism(this->x + 1, this->y - 1)->getSpecies() == Species::HUMAN){
				whatsAround.push_back(Directions::SOUTH_WEST);
			}
		}
	}

	// south east
	if (this->x < this->height - 1 && this->y < this->width - 1){
		if (this->city->getOrganism(this->x + 1, this->y + 1) != nullptr){
			if (this->city->getOrganism(this->x + 1, this->y + 1)->getSpecies() == Species::HUMAN){
				whatsAround.push_back(Directions::SOUTH_EAST);
			}
		}
	}

	// if humans are around zombie, eat one
	if (whatsAround.size() > 0){
		truffleShuffle = (rand() % whatsAround.size());
		convertHuman(whatsAround.at(truffleShuffle));
		convertCounter = 0;
	}
}

void Zombie::convertHuman(int direction){
	switch (direction)
	{
	case Directions::NORTH:
		// move NORTH
		delete city->getOrganism(this->x - 1, this->y);
		city->setOrganism(new Zombie(this->city, width, height, this->x - 1, this->y), this->x - 1, this->y);
		break;
	case Directions::EAST:
		// move EAST
		delete city->getOrganism(this->x, this->y + 1);
		city->setOrganism(new Zombie(this->city, width, height, this->x + 1, this->y), this->x, this->y + 1);
		break;
	case Directions::SOUTH:
		// move SOUTH
		delete city->getOrganism(this->x + 1, this->y);
		city->setOrganism(new Zombie(this->city, width, height, this->x + 1, this->y), this->x + 1, this->y);
		break;
	case Directions::WEST:
		// move WEST
		delete city->getOrganism(this->x, this->y - 1);
		city->setOrganism(new Zombie(this->city, width, height, this->x, this->y - 1), this->x, this->y - 1);
		break;
	case Directions::NORTH_EAST:
		// move NORTH EAST
		delete city->getOrganism(this->x - 1, this->y + 1);
		city->setOrganism(new Zombie(this->city, width, height, this->x - 1, this->y + 1), this->x - 1, this->y + 1);
		break;
	case Directions::SOUTH_EAST:
		// move SOUTH EAST
		delete city->getOrganism(this->x + 1, this->y + 1);
		city->setOrganism(new Zombie(this->city, width, height, this->x + 1, this->y + 1), this->x + 1, this->y + 1);
		break;
	case Directions::SOUTH_WEST:
		// move SOUTH WEST
		delete city->getOrganism(this->x + 1, this->y - 1);
		city->setOrganism(new Zombie(this->city, width, height, this->x + 1, this->y - 1), this->x + 1, this->y - 1);
		break;
	case Directions::NORTH_WEST:
		// move NORTH WEST
		delete city->getOrganism(this->x - 1, this->y - 1);
		city->setOrganism(new Zombie(this->city, width, height, this->x - 1, this->y - 1), this->x - 1, this->y - 1);
		break;
	default:
		break;
	}
}

// get rid of zombie
void Zombie::starve(){
	this->city->swapZombieForHuman(new Human(this->city, this->width, this->height, this->x, this->y));
}