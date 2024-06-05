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

bool Game::init() {
	std::cout << "Title Screen" << std::endl;
	Sleep(3);
	return true;
}

MenuOptions Game::mainMenu(const MenuOptions &currOption) {
	clock_t time = clock();

	assert((currOption == MenuOptions::NONE_EXIT || currOption == MenuOptions::NONE_PLAY) && "Invalid menu option");

#pragma region INPUT

	m_inputManager.ProcessInput();
	short input = m_inputManager.GetCurrentInput();

	if(VK_UP)

	if (VK_UP <= input && input <= VK_DOWN) {
		m_camera.move(input, m_player.getPosition());
		m_player.move(input, m_map);
	}

#pragma endregion

	std::cout << "\033[1;1H\033[0;0;0m";
	std::cout << "Select option" << std::endl << std::endl;
	std::cout << ((currOption == MenuOptions::NONE_PLAY) ? "\033[0;32;1m" : "\033[0;0;0m") << "Play" << std::endl;
	std::cout << ((currOption == MenuOptions::NONE_PLAY) ? "\033[0;32;1m" : "\033[0;0;0m") << "Exit" << std::endl;

	time = clock() - time;
	int msLeft = 1000 / FRAMERATE - (int)((double)(time) / CLOCKS_PER_SEC * 1000);
	if (msLeft > 0) Sleep(msLeft);

	return currOption;
}

bool Game::gameLoop() {
	clock_t time = clock();
#pragma region INPUT

	m_inputManager.ProcessInput();
	short input = m_inputManager.GetCurrentInput();

	if (VK_UP <= input && input <= VK_DOWN) {
		m_camera.move(input, m_player.getPosition());
		m_player.move(input, m_map);
	}
	else if (input == VK_SPACE) m_player.incrementPokemon(m_map.checkPokemon(m_player.getPosition()));
	else if (input == VK_ESCAPE) return false;

#pragma endregion
#pragma region UPDATE

	m_map.update(m_player.getPosition(), m_player.getSprite(), m_player.getCapturedPokemon());

#pragma endregion
#pragma region RENDER

	m_camera.draw();
	std::cout << std::endl << "Pokemon captured: " << m_player.getCapturedPokemon();

#pragma endregion
#pragma region FRAME CONTROL

	time = clock() - time;
	int msLeft = 1000 / FRAMERATE - (int)((double)(time) / CLOCKS_PER_SEC * 1000);
	if(msLeft > 0) Sleep(msLeft);

#pragma endregion
	return true;
}

void Game::hideCursor() {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(out, &cursorInfo);
}
