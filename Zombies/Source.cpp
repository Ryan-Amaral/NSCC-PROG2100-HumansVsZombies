#include "Game.h"

using namespace std;

int main(){

	Game game; // create the game object

	cout << "Welcome to the Zombies vs Humans Game!" << endl << endl;
	
	while (game.play());

	return 0;
}