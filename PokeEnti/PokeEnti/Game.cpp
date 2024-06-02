#include "Game.h"
#include <Windows.h>
#include <iostream>
#include <ctime>

Game::Game()
{

}

Game::Game(const Data &data) :
	m_inputManager(InputManager()),
	m_map(Map(data)),
	m_camera(Camera(std::make_pair(0, 0), data.m_mapWidth / 2, data.m_mapHeight / 2, &m_map)),
	m_player(data.m_mapWidth / 4, data.m_mapHeight / 4)
	
{

}

bool Game::gameLoop() {

	clock_t time = clock();

	//Process Input
	m_inputManager.ProcessInput();
	short input = m_inputManager.GetCurrentInput();

	if (input == VK_UP || input == VK_LEFT || input == VK_DOWN || input == VK_RIGHT) {
		//Movement
		m_camera.move(input, m_player.getPosition());
		m_player.move(input, m_map);
	}
	else if (input == VK_SPACE) {
		//Interact
		m_player.incrementPokemon(m_map.checkPokemon(m_player.getPosition()));
	}
	else if (input == VK_ESCAPE) {
		//Quit
		return false;
	}

	//Update
	m_map.update(m_player.getPosition(), m_player.getSprite(), m_player.getCapturedPokemon());

	//Render map
	m_camera.draw();
	std::cout << std::endl << "Pokemon captured: " << m_player.getCapturedPokemon();

	//Frame control
	time = clock() - time;
	int msLeft = 1000 / FRAMERATE - (int)((double)(time) / CLOCKS_PER_SEC * 1000);
	if(msLeft > 0) Sleep(msLeft);
	return true;
}

void Game::hideCursor() {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(out, &cursorInfo);
}
