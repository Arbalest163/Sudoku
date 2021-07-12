#include "SudokuGame.h"


int main()
{
	srand(static_cast<unsigned int>(time(0)));
	SudokuGame Game;
	Game.runGame();
	return 0;

}