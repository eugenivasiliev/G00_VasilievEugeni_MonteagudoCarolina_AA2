#include "Game.h"
#include <Windows.h>
#include <iostream>

const std::pair<int, int> UP = std::make_pair(-1, 0);
const std::pair<int, int> DOWN = std::make_pair(1, 0);
const std::pair<int, int> LEFT = std::make_pair(0, -1);
const std::pair<int, int> RIGHT = std::make_pair(0, 1);

std::pair<int, int> operator+ (const std::pair<int, int>& l, const std::pair<int, int>& r) {
	return std::make_pair(l.first + r.first, l.second + r.second);
}

bool operator< (const std::pair<int, int> &l, const std::pair<int, int> &r) {
	return (l.first < r.first && l.second < r.second);
}

void operator+= (std::pair<int, int>& l, const std::pair<int, int>& r) {
	l = l + r;
}

Game::Game() :
	m_mapWidth(0), m_mapHeight(0),
	m_palletTownStartPokemon(0), m_palletTownCondition(0),
	m_forestStartPokemon(0), m_forestCondition(0)
{

}

Game::Game(const Data &data) :
	m_mapWidth(data.m_mapWidth), m_mapHeight(data.m_mapHeight), 
	m_palletTownStartPokemon(data.m_palletTownStartPokemon), m_palletTownCondition(data.m_palletTownCondition), 
	m_forestStartPokemon(data.m_forestStartPokemon), m_forestCondition(data.m_forestCondition),
	m_inputManager(InputManager()),
	m_map(Map(data)),
	m_camera(Camera(std::make_pair(0, 0), data.m_mapWidth / 2, data.m_mapHeight / 2, &m_map)),
	m_player(data.m_mapWidth / 4, data.m_mapHeight / 4)
	
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
	frameEnd = GetTickCount64();
	Sleep(1000 / FRAMERATE - (frameEnd - frameStart));
	return true;
}

void Game::hideCursor() {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(out, &cursorInfo);
}