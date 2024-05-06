#include <iostream>
#include <Windows.h>
#include <fstream>
#include "ReadDoc.h"
#include "Map.h"
#include "Ash.h"
#include "Game.h"




int main() {
	ReadDoc reader("config,txt");
	Data data;
	
	if (!reader.readData(data)) return 0; //Get data, exit if ERROR

	Game game(data);
	game.hideCursor();

	while (game.GameLoop());
	return 0;
}