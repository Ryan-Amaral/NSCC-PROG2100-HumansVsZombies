// header file for the Game class
#ifndef _GAME_H
#define _GAME_H

#include <iostream>

using namespace std;

enum ExtinctionType { NONE_EXTINCT, HUMANS_EXTINCT, ZOMBIES_EXTINCT, BOTH_EXTINCT };

class Game
{
private:
	int gridWidth; // the width of the grid of the city
	int gridHeight; // the height of the grid of the city
	int humans; // the amount of humans
	int zombies; // the amount of zombies

public:
	Game();
	virtual ~Game();

	bool play(); // start the game, and keep iterating, returns true if want to play again
};

#endif