#include "Game.h"
#include <Windows.h>
#include <iostream>
#include <ctime>

Game::Game()
{

}

Game::Game(const Data &data) :
	m_state(GameState::INIT),
	m_inputManager(InputManager()),
	m_map(Map(data)),
	m_camera(Camera(std::make_pair(0, 0), data.m_mapWidth / 2, data.m_mapHeight / 2, &m_map)),
	m_player(data.m_mapWidth / 4, data.m_mapHeight / 4)
	
{

}

bool Game::playGame() {
	MenuOptions option = MenuOptions::NONE_PLAY;
	GameEnd end = GameEnd::CONTINUE;
	switch (m_state) {
	case GameState::INIT:
		init();
		m_state = GameState::MAIN_MENU;
		break;
	case GameState::MAIN_MENU:
		while(option != MenuOptions::EXIT && option != MenuOptions::PLAY) option = mainMenu(option);
		if (option == MenuOptions::EXIT) return false;
		else m_state = GameState::GAME;
		break;
	case GameState::GAME:
		while (end == GameEnd::CONTINUE) end = gameLoop();
		if (end == GameEnd::WIN) m_state = GameState::GAME_WIN;
		else if (end == GameEnd::LOSE) m_state = GameState::GAME_OVER;
		else return false;
		break;
	case GameState::GAME_OVER:
		gameOver();
		return false;
	case GameState::GAME_WIN:
		gameWin();
		m_state = GameState::INIT;
		break;
	}
	return true;
}

bool Game::init() {
	std::cout << "Title Screen" << std::endl;
	Sleep(3000);
	return true;
}

MenuOptions Game::mainMenu(const MenuOptions &currOption) {
	clock_t time = clock();

	assert((currOption == MenuOptions::NONE_EXIT || currOption == MenuOptions::NONE_PLAY) && "Invalid menu option");

	MenuOptions option = currOption;

#pragma region INPUT

	m_inputManager.ProcessInput();
	short input = m_inputManager.GetCurrentInput();

	if (input == VK_UP) option = MenuOptions::NONE_PLAY;
	if (input == VK_DOWN) option = MenuOptions::NONE_EXIT;
	if (input == VK_SPACE) return static_cast<MenuOptions>(static_cast<int>(option) - 2);

#pragma endregion

	std::cout << "\033[1;1H\033[0;0;0m";
	std::cout << "Select option" << std::endl << std::endl;
	std::cout << ((option == MenuOptions::NONE_PLAY) ? "\033[0;32;1m" : "\033[0;0;0m") << "Play" << std::endl;
	std::cout << ((option == MenuOptions::NONE_EXIT) ? "\033[0;32;1m" : "\033[0;0;0m") << "Exit" << std::endl;

	time = clock() - time;
	int msLeft = 1000 / FRAMERATE - (int)((double)(time) / CLOCKS_PER_SEC * 1000);
	if (msLeft > 0) Sleep(msLeft);

	return option;
}

GameEnd Game::gameLoop() {
	clock_t time = clock();
#pragma region INPUT

	m_inputManager.ProcessInput();
	short input = m_inputManager.GetCurrentInput();

	if (VK_LEFT <= input && input <= VK_DOWN) {
		m_camera.move(input, m_player.getPosition());
		m_player.move(input, m_map);
	}
	else if (input == VK_SPACE) m_player.incrementPokemon(m_map.checkPokemon(m_player.getPosition()));
	else if (input == VK_ESCAPE) return GameEnd::ESCAPE;

#pragma endregion
#pragma region UPDATE

	m_map.update(m_player.getPosition(), m_player.getSprite(), m_player.getCapturedPokemon());

#pragma endregion
#pragma region RENDER
	//Render map
	m_buffer << "\033[1;1H";
	//cabezera
	m_buffer << "\033[1;31mPokemons capturados:\033[1;32m[" << m_player.getCapturedPokemon() << "] ";
	m_buffer << "\033[1;31mPokeballs:\033[1;32m[" << 10 << "]\033[0m\n";
	//m_buffer << "       \033[1;32m[" << m_cityName << "]\033[0m\n";
	m_buffer << std::endl;
	m_camera.draw(m_buffer);
	std::cout << m_buffer.str();
	m_buffer.str("");
	m_buffer.clear();
	

#pragma endregion
#pragma region FRAME CONTROL

	time = clock() - time;
	int msLeft = 1000 / FRAMERATE - (int)((double)(time) / CLOCKS_PER_SEC * 1000);
	if(msLeft > 0) Sleep(msLeft);

#pragma endregion
	return GameEnd::CONTINUE;
}

void Game::gameOver() {
	std::cout << "Game Over";
	Sleep(5000);
}

void Game::gameWin() {
	std::cout << "You Win";
	Sleep(5000);
}

void Game::hideCursor() {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(out, &cursorInfo);
}
