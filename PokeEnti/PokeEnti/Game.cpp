#include "Game.h"
#include <Windows.h>
#include <iostream>

Game::Game() :
	m_mapWidth(0), m_mapHeight(0),
	m_palletTownStartPokemon(0), m_palletTownCondition(0),
	m_forestStartPokemon(0), m_forestCondition(0)
{

}

Game::Game(int mapWidth, int mapHeight, int palletTownStartPokemon, int palletTownCondition, int forestStartPokemon, int forestCondition) :
	m_mapWidth(mapWidth), m_mapHeight(mapHeight), 
	m_palletTownStartPokemon(palletTownStartPokemon), m_palletTownCondition(palletTownCondition), 
	m_forestStartPokemon(forestStartPokemon), m_forestCondition(forestCondition) 
{
	
}

bool Game::GameLoop() {
	long frameStart, frameEnd;
	frameStart = GetTickCount64();

	//Process Input
	m_inputManager.ProcessInput();
	short input = m_inputManager.GetCurrentInput();

	if (input == VK_UP || input == VK_LEFT || input == VK_DOWN || input == VK_RIGHT) {
		//Movement
		m_player.move(input, m_map);
	}
	else if (input == VK_SPACE) {
		//Interact
	}
	else if (input == VK_ESCAPE) {
		//Quit
		return false;
	}

	//Update
	//Render map
	std::cout << "\033[u\033[J\033[s";
	m_player.draw();
	std::cout << std::endl;
	std::cout << std::endl;

	//Frame control
	frameEnd = GetTickCount64();
	Sleep(1000 / FRAMERATE - (frameEnd - frameStart));
	return true;
}

