#include "Game.h"
#include <Windows.h>
#include <iostream>
#include <ctime>

Game::Game()
{

}

Game::Game(const Data &data) :
	isInCombat(EMPTY_PAIR),
	m_pokemonHealth(30), m_mewtwoHealth(50), m_attackDamage(10),
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

void Game::init() {
	std::cout << "Title Screen" << std::endl;
	Sleep(3000);
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
	else if (input == VK_SPACE) isInCombat = m_map.checkPokemon(m_player.getPosition());
	else if (input == VK_ESCAPE) return GameEnd::ESCAPE;

#pragma endregion
#pragma region UPDATE

	m_map.update(m_player.getPosition(), m_player.getSprite(), m_player.getCapturedPokemon());

#pragma endregion
#pragma region RENDER
	m_buffer.str("");
	m_buffer.clear();
	m_buffer << "\033[1;1H";
	m_buffer << "\033[1;31mPokemons capturados:\033[1;32m[" << m_player.getCapturedPokemon() << "] ";
	m_buffer << "\033[1;31mPokeballs:\033[1;32m[" << m_player.getPokeballCount() << "]\033[0m\n";
	m_buffer << std::endl;
	m_camera.draw(m_buffer);
	std::cout << m_buffer.str();
	if (isInCombat != EMPTY_PAIR) {
		m_inputManager.ClearQueue();
		combat(isInCombat);
		m_map.repositionPokemon(isInCombat);
		isInCombat = EMPTY_PAIR;
		system("cls");
	}
	

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

void Game::combat(std::pair<int, int> pokemonPosition) {
	std::ostringstream buffer;
	int numPokeballs = 10;
	std::cout << "\033[s";
	std::string name;
	int health;
	Tiles tile = m_map(pokemonPosition);
	if (tile == (Tiles)PkTiles::POKEMON_TILE) {
		name = "Random name";
		health = m_pokemonHealth;
	}
	else if (tile == (Tiles)PkTiles::MEWTWO_TILE) {
		name = "Mewtwo";
		health = m_mewtwoHealth;
	}
	CombatMenu option = CombatMenu::NONE_ATTACK;
	bool inCombat = true;
	while (inCombat) {
		buffer.str("");
		buffer.clear();
		buffer << "\033[u\033[0;0;0m" << name << ' ' << health << ' ' << numPokeballs << std::endl;
		option = combatMenu(option, buffer);
		std::cout << buffer.str();
		switch (option) {
		case CombatMenu::ATTACK:
			health -= m_attackDamage;
			inCombat = health > 0;
			option = CombatMenu::NONE_ATTACK;
			break;
		case CombatMenu::CAPTURE:
			if (numPokeballs > 0) {
				numPokeballs--;
				if (tile == (Tiles)PkTiles::POKEMON_TILE)
					inCombat = rand() % (m_pokemonHealth * 7 / 6) <= health;
				else if (tile == (Tiles)PkTiles::MEWTWO_TILE)
					inCombat = rand() % (m_mewtwoHealth * 7 / 6) <= health;
			}
			option = CombatMenu::NONE_CAPTURE;
			break;
		case CombatMenu::FLEE:
			inCombat = false;
			option = CombatMenu::NONE_FLEE;
			break;
		}
	}
}

CombatMenu Game::combatMenu(const CombatMenu& currOption, std::ostringstream& buffer) {
	clock_t time = clock();

	//assert(static_cast<int>(currOption) < static_cast<int>(CombatMenu::COUNT) &&
		//"Invalid combat menu option");

	CombatMenu option = currOption;

#pragma region INPUT

	m_inputManager.ProcessInput();
	short input = m_inputManager.GetCurrentInput();

	if (input == VK_UP) option = static_cast<CombatMenu>(max(static_cast<int>(option) - 1, 0));
	if (input == VK_DOWN)
		option = static_cast<CombatMenu>(
			min(static_cast<int>(option) + 1,
				static_cast<int>(CombatMenu::COUNT) - 1));
	if (input == VK_SPACE) {
		option = static_cast<CombatMenu>(static_cast<int>(option) + static_cast<int>(CombatMenu::COUNT) + 1);
	}

#pragma endregion

	buffer << "\033[0;0;0mSelect option" << std::endl << std::endl;
	buffer << ((option == CombatMenu::NONE_ATTACK) ? "\033[0;32;1m" : "\033[0;0;0m") << "Attack" << std::endl;
	buffer << ((option == CombatMenu::NONE_CAPTURE) ? "\033[0;32;1m" : "\033[0;0;0m") << "Capture" << std::endl;
	buffer << ((option == CombatMenu::NONE_FLEE) ? "\033[0;32;1m" : "\033[0;0;0m") << "Flee" << std::endl;

	time = clock() - time;
	int msLeft = 1000 / FRAMERATE - (int)((double)(time) / CLOCKS_PER_SEC * 1000);
	if (msLeft > 0) Sleep(msLeft);

	return option;
}

void Game::hideCursor() {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(out, &cursorInfo);
}
