#include "Game.h"
#include <Windows.h>


bool Game::GameLoop() {
	long frameStart, frameEnd;
	frameStart = GetTickCount64();

	//Process Input
	inputManager.ProcessInput();
	short input = inputManager.GetCurrentInput();

	if (input == VK_UP || input == VK_LEFT || input == VK_DOWN || input == VK_RIGHT) {
		//Movement
		player.move(input);
	}
	else if (input == VK_SPACE) {
		//Interact
	}
	else {
		//Quit
		return false;
	}

	frameEnd = GetTickCount64();
	Sleep(1000 / FRAMERATE - (frameEnd - frameStart));
}

