#include <cstdlib>
#include <time.h>
#include "Game.h"




int main() {

	srand(time(NULL));

	ReadDoc reader("config.txt");
	Data data;

	if (!reader.readData(data)) return 0; //Get data, exit if ERROR

	Game game(data);
	game.hideCursor();
	while (game.gameLoop());
	game.~Game();
	return 0;
}
