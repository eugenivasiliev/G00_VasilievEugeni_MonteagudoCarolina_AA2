#include "Map.h"
#include <iostream>

std::pair<int, int> operator+ (const std::pair<int, int>& l, const std::pair<int, int>& r);

Map::Map() {
	m_width = 0;
	m_height = 0;
}

Map::Map(const int& width, const int& height, const int& palletTownStartPokemon, const int& palletTownCondition, const int& forestStartPokemon, const int& forestCondition) : m_width(width), m_height(height) {
	//Initialise
	m_tiles = new char* [m_width];
	for (int i = 0; i < m_width; ++i) {
		m_tiles[i] = new char[m_height];
		for (int j = 0; j < m_height; ++j)
			m_tiles[i][j] = ' ';
	}

	//Walls
	for (int i = 0; i < m_width; ++i) {
		m_tiles[i][0] = 'X';
		m_tiles[i][m_height/2] = 'X';
		m_tiles[i][m_height - 1] = 'X';
	}
	for (int i = 0; i < m_height; ++i) {
		m_tiles[0][i] = 'X';
		m_tiles[m_width/2][i] = 'X';
		m_tiles[m_width - 1][i] = 'X';
	}

	m_palletTown = Zone(palletTownStartPokemon, palletTownCondition, std::make_pair(0, 0), m_width / 2, m_height / 2);
	m_forest = Zone(forestStartPokemon, forestCondition, std::make_pair(m_width/2, 0), m_width / 2, m_height / 2);
	m_celesteCave = Zone(0, 0, std::make_pair(m_width / 2, m_height / 2), m_width / 2, m_height / 2);
	m_pokENTILeague = Zone(0, 0, std::make_pair(0, m_height / 2), m_width / 2, m_height / 2);

}

void Map::update() {

}

char Map::operator() (const std::pair<int, int> &position) const {
	return m_tiles[position.first][position.second];
}

char Map::operator() (int x, int y) {
	return m_tiles[x][y];
}

int Map::getWidth() const {
	return m_width;
}

int Map::getHeight() const {
	return m_height;
}

Zone::Zone() {
	m_unlocked = false;
	m_startPokemon = 0;
	m_condition = 0;
	m_position = std::make_pair(0,0);
	m_width = 0;
	m_height = 0;
	m_pokemon = nullptr;
}

Zone::Zone(int startPokemon, int condition, std::pair<int, int> position, int width, int height) {
	m_unlocked = false;
	m_startPokemon = startPokemon;
	m_condition = condition;
	m_position = position;
	m_width = width;
	m_height = height;
	m_pokemon = new std::pair<int, int>[m_startPokemon];
}

bool Zone::getUnlocked() { return m_unlocked; }

void Zone::checkCondition(int collectedPokemon) { m_unlocked = m_unlocked || collectedPokemon >= m_condition; }

bool Zone::checkPokemon(std::pair<int, int> position) {
	for (int i = 0; i < m_startPokemon; i++) {
		std::pair<int, int> pokemon = m_pokemon[i];
		if (position == pokemon + std::make_pair(0, -1) ||
			position == pokemon + std::make_pair(0, 1) ||
			position == pokemon + std::make_pair(-1, 0) ||
			position == pokemon + std::make_pair(1, 0)) { //Check if adjacent to pokemon
			//Randomise pokemon to a new position
			return true;
		}
	}
	return false;
}