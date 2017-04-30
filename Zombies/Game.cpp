// implementation file for Game

#include "Game.h"
#include "City.h"
#include "Human.h"
#include "Zombie.h"
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <ctime>
#include <windows.h>   // WinApi header will only work on winderws
using namespace std;

Game::Game(){} // nothing needs to happen

Game::~Game(){} // nothing needs to happen, maybe

// friend function from City class
// prints the current state of the function
ostream& operator<<(ostream &output, City &city){
// help from: https://www.daniweb.com/programming/software-development/code/216345/add-a-little-color-to-your-console-text

	// ONLY WORKS ON WINDOWS
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	for (int x = 0; x < city.getHeight(); x++){
		for (int y = 0; y < city.getWidth(); y++)
		{
			if (city.getOrganism(x, y) != nullptr){
				// output H for human Z for zombie
				if (city.getOrganism(x, y)->getSpecies() == Organism::Species::HUMAN){
					SetConsoleTextAttribute(hConsole, 2); // green
					output << "O";
				}
				else{
					SetConsoleTextAttribute(hConsole, 4); // red
					output << "X";
				}
			}
			else{
				output << " ";
			}
		}
		output << endl;
	}
	SetConsoleTextAttribute(hConsole, 11);

	return output;
}

// help from: http://www.cplusplus.com/forum/unices/10491/
// clock_t is a like typedef unsigned int clock_t. Use clock_t instead of integer in this context
void mySleep(float sec){
	clock_t start_time = clock();
	clock_t end_time = sec * 1000 + start_time;
	while (clock() <= end_time);
}

bool Game::play()
{
	int extinction = NONE_EXTINCT;
	City city; // create city

	// ask if user wants default 20 * 20 grid, or custom one
	cout << "Press enter to accept default grid size, or any other key for a custom size." << endl;
	if (cin.get() == '\n'){ // if enter is pressed
		city = City(); // create default city
		gridWidth = GRID_WIDTH;
		gridHeight = GRID_HEIGHT;
	}
	else{ // any other key
		// prompt for dimensions
		// width
		do{
			cout << "Enter the width (2 - 100): " << endl;
			cin.clear();
			cin.ignore();
			cin >> gridWidth;
		} while (gridWidth < 2 || gridWidth > 100);
		// height
		do{
			cout << "Enter the height (2 - 100): " << endl;
			cin.clear();
			cin.ignore();
			cin >> gridHeight;
		} while (gridHeight < 2 || gridHeight > 100);
		city = City(gridWidth, gridHeight); // create city with custom dimensions
	}

	bool tooManyOrganisms = false;
	do{
		if (tooManyOrganisms){
			cout << "There are too many humans or zombies for this grid size, enter again." << endl << endl;
		}
		// ask for amount of humans
		do{
			cout << "Enter the amount of humans: " << endl;
			cin.clear();
			//cin.ignore();
			cin >> humans;
		} while (humans < 1);

		// ask for amount of zombies
		do{
			cout << "Enter the amount of zombies: " << endl;
			cin.clear();
			cin.ignore();
			cin >> zombies;
		} while (zombies < 1);

		// humans and zombies must be cummulatively less than amount of squares in grid
		if (humans + zombies > gridWidth * gridHeight){
			tooManyOrganisms = true;
		}
		else{
			tooManyOrganisms = false;
		}
	} while (tooManyOrganisms);

	// spawn the organisms
	int numSquares = gridWidth * gridHeight; // the amount of all squares
	int squaresLeft = numSquares;
	int organismsPlaced = 0;
	int organismsNotPlaced = humans;
	srand(time(NULL)); // seed the random
	bool canPlace; // set to true if can place organism in current spot

	// fix spawning later!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	// spawn humans
	// check each square, to see if place thing
	for (int x = 0; x < gridHeight; x++){
		for (int y = 0; y < gridWidth; y++)
		{
			// check random number if can place here
			canPlace = ((rand() % numSquares + 1) > squaresLeft);
			if (canPlace || squaresLeft == organismsNotPlaced)
			{
				// place human
				city.setOrganism(new Human(&city, gridWidth, gridHeight, x, y), x, y);
				organismsPlaced++;
				organismsNotPlaced--;
				// break out if finished placing humans
				if (organismsPlaced == humans){
					x = gridHeight;
					break;
				}
			}
			squaresLeft--;
		}
	}

	squaresLeft = numSquares;
	organismsPlaced = 0;
	organismsNotPlaced = zombies;

	// spawn zombies
	for (int x = 0; x < gridHeight; x++){
		for (int y = 0; y < gridWidth; y++)
		{
			// see if can even place organism
			if (city.getOrganism(x, y) == nullptr)
			{
				// check random number if can place here
				canPlace = ((rand() % numSquares + 1) > squaresLeft);
				if (canPlace)
				{
					// place zombie
					city.setOrganism(new Zombie(&city, gridWidth, gridHeight, x, y), x, y);
					organismsPlaced++;
					organismsNotPlaced--;
					// break out if finished placing zombies
					if (organismsPlaced == zombies){
						x = gridHeight;
						break;
					}

					// wrap back to beginning, if not all zombs got in
					if (x == gridWidth - 1 && y == gridHeight - 1){
						x = -1;
						y = -1;
					}
				}
			}
			squaresLeft--;
		}
	}

	// recycleable objects used in game loop
	Human* human; 
	Zombie* zombie;

	int iteration = 1; // the amount of iterations into the game loop

	do // start game loop
	{
		system("cls");

		// loop through all zombies to move each
		for (int x = 0; x < gridHeight; x++){
			for (int y = 0; y < gridWidth; y++)
			{
				if (city.getOrganism(x, y) != nullptr){
					if (city.getOrganism(x, y)->getSpecies() == Organism::Species::ZOMBIE
						&& !city.getOrganism(x, y)->getMoved()){
						city.getOrganism(x, y)->move();
					}
				}
			}
		}

		// loop through all humans to move each
		for (int x = 0; x < gridHeight; x++){
			for (int y = 0; y < gridWidth; y++)
			{
				if (city.getOrganism(x, y) != nullptr){
					if (city.getOrganism(x, y)->getSpecies() == Organism::Species::HUMAN
						&& !city.getOrganism(x, y)->getMoved()){
						city.getOrganism(x, y)->move();
					}
				}
			}
		}

		// loop through all zombies to convert, and starve
		for (int x = 0; x < gridHeight; x++){
			for (int y = 0; y < gridWidth; y++)
			{
				if (city.getOrganism(x, y) != nullptr){
					// convert 
					if (city.getOrganism(x, y)->getSpecies() == Organism::Species::ZOMBIE
							&& city.getOrganism(x, y)->getCounter() >= 8){
						zombie = dynamic_cast<Zombie*>(city.getOrganism(x, y));
						zombie->convert();
					}
					// starve
					if (city.getOrganism(x, y)->getSpecies() == Organism::Species::ZOMBIE
						&& city.getOrganism(x, y)->getCounter2() >= 3){
						zombie = dynamic_cast<Zombie*>(city.getOrganism(x, y));
						zombie->starve();
					}
				}
			}
		}

		// loop through all humans to recruit
		for (int x = 0; x < gridHeight; x++){
			for (int y = 0; y < gridWidth; y++)
			{
				if (city.getOrganism(x, y) != nullptr){
					if (city.getOrganism(x, y)->getSpecies() == Organism::Species::HUMAN
						&& city.getOrganism(x, y)->getCounter() >= 3){
						human = dynamic_cast<Human*>(city.getOrganism(x, y));
						human->recruit();
					}
				}
			}
		}

		// display iteration amount (amount of time steps)
		cout << "Iteration: " << iteration;
		iteration++;


		humans = 0;
		zombies = 0;
		// check for amount of humans and zombies to see if ELE
		for (int x = 0; x < gridHeight; x++){
			for (int y = 0; y < gridWidth; y++)
			{
				if (city.getOrganism(x, y) != nullptr){
					// is human
					if (city.getOrganism(x, y)->getSpecies() == Organism::Species::HUMAN){
						humans++;
					}
					// is zombie
					else{
						zombies++;
					}

					// reset moveds
					city.getOrganism(x, y)->setMoved(false);
				}
			}
		}

		// mutual extinct
		if (humans == 0 && zombies == 0){
			extinction = BOTH_EXTINCT;
		}
		// humans extinct
		else if (humans == 0){
			extinction = HUMANS_EXTINCT;
		}
		// zombies extinct
		else if (zombies == 0){
			extinction = ZOMBIES_EXTINCT;
		}

		// print current state of board
		cout << endl << city << endl << endl;

		mySleep(.1);
		
	} while (extinction == NONE_EXTINCT); // end game loop

	// loop through all organisms to delete them
	for (int x = 0; x < gridHeight; x++){
		for (int y = 0; y < gridWidth; y++){
			if (city.getOrganism(x, y) != nullptr){
				delete city.getOrganism(x, y);
			}
		}
	}

	// print results
	if (extinction == BOTH_EXTINCT){
		cout << "Everyone has gone extinct after " << iteration - 1 << " iterations!";
	}
	else if (extinction == HUMANS_EXTINCT){
		cout << "The humans have gone extinct after " << iteration - 1 << " iterations!";
	}
	else if (extinction == ZOMBIES_EXTINCT){
		cout << "The zombies have gone extinct after " << iteration - 1 << " iterations!";
	}

	// ask if user wants to play again
	cout << endl << "Press enter to play again, or anything else to quit." << endl;
	cin.clear();
	cin.ignore();
	if (cin.get() == '\n'){ // if enter is pressed
		return true;
	}
	else{
		return false;
	}
}