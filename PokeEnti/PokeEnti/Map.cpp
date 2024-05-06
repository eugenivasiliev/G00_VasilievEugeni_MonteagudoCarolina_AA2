#include "Map.h"
#include <iostream>

const char EMPTY_TILE = ' ';
const char WALL_TILE = 'X';
const char POKEMON_TILE = 'P';



/*
************************************
			Zone methods
************************************
*/

Zone::Zone() {
	m_unlocked = false;
	m_startPokemon = 0;
	m_condition = 0;
}

Zone::Zone(const int &startPokemon, const int &condition) {
	m_unlocked = false;
	m_startPokemon = startPokemon;
	m_condition = condition;
}

bool Zone::getUnlocked() const { return m_unlocked; }

void Zone::checkCondition(const int &collectedPokemon) { m_unlocked = m_unlocked || (collectedPokemon >= m_condition); }

int Zone::getStartPokemon() const { return m_startPokemon; }



/*
************************************
			Map methods
************************************
*/

Map::Map() {
	m_width = 0;
	m_height = 0;
	m_tiles = new char* [m_width];
}

Map::Map(const Data& data) : m_width(data.m_mapWidth), m_height(data.m_mapHeight) {
	//Initialise
	m_tiles = new char* [m_height];
	for (int i = 0; i < m_height; ++i) {
		m_tiles[i] = new char[m_width];
		for (int j = 0; j < m_width; ++j)
			m_tiles[i][j] = EMPTY_TILE;
	}

	//Walls
	for (int i = 0; i < m_width; ++i) {
		m_tiles[i][0] = WALL_TILE;
		m_tiles[i][m_width / 2] = WALL_TILE;
		m_tiles[i][m_width - 1] = WALL_TILE;
	}
	for (int i = 0; i < m_height; ++i) {
		m_tiles[0][i] = WALL_TILE;
		m_tiles[m_height / 2][i] = WALL_TILE;
		m_tiles[m_height - 1][i] = WALL_TILE;
	}

	m_palletTown = Zone(data.m_palletTownStartPokemon, data.m_palletTownCondition);
	m_forest = Zone(data.m_forestStartPokemon, data.m_forestCondition);
	m_celesteCave = Zone(0, 0);
	m_pokENTILeague = Zone(0, 0);

	//Generate Pallet Town pokemon
	for (int i = 0; i < m_palletTown.getStartPokemon(); ++i) {
		std::pair<int, int> pokemonPosition;
		do {
			pokemonPosition = getRandomEmptyTile();
		} while (!(pokemonPosition < std::make_pair(m_height / 2, m_width / 2)));
		m_tiles[pokemonPosition.first][pokemonPosition.second] = POKEMON_TILE;
	}

}

void Map::update(const std::pair<int, int> &playerPosition, const char &playerSprite, const int& capturedPokemon) {
	for (int i = 0; i < m_width; ++i)
		for (int j = 0; j < m_height; ++j)
			if (m_tiles[j][i] == '^' || m_tiles[j][i] == 'v' || m_tiles[j][i] == '<' || m_tiles[j][i] == '>')
				m_tiles[j][i] = EMPTY_TILE;
	m_tiles[playerPosition.first][playerPosition.second] = playerSprite;
	if (!m_palletTown.getUnlocked()) {
		m_palletTown.checkCondition(capturedPokemon);
		if (m_palletTown.getUnlocked()) {
			//Clear Pallet Town wall
			for (int i = 1; i < m_height / 2; ++i)
				m_tiles[i][m_width / 2] = EMPTY_TILE;
			//Generate Forest pokemon
			for (int i = 0; i < m_forest.getStartPokemon(); ++i) {
				std::pair<int, int> pokemonPosition;
				do {
					pokemonPosition = getRandomEmptyTile();
				} while (!(pokemonPosition < std::make_pair(m_height / 2, m_width) && std::make_pair(0, m_width / 2) < pokemonPosition));
				m_tiles[pokemonPosition.first][pokemonPosition.second] = POKEMON_TILE;
			}
		}
	}
	else if (!m_forest.getUnlocked()) {
		m_forest.checkCondition(capturedPokemon);
		if (m_forest.getUnlocked())
			//Clear Forest wall
			for (int i = m_width / 2 + 1; i < m_width - 1; ++i)
				m_tiles[m_height / 2][i] = EMPTY_TILE;
		//Would generate next pokemon set, but it is not declared
	}
}

char Map::operator() (const std::pair<int, int>& position) const {
	return m_tiles[position.first][position.second];
}

char Map::operator() (const int &x, const int &y) const {
	return m_tiles[x][y];
}

int Map::getWidth() const {
	return m_width;
}

int Map::getHeight() const {
	return m_height;
}

std::pair<int, int> Map::getRandomEmptyTile() const {
	int x, y;
	do {
		x = rand() % m_width;
		y = rand() % m_height;
	} while ((*this)(y, x) != ' ');
	return std::make_pair(y, x);
}

bool Map::checkPokemon(const std::pair<int, int> position) {
	if ((*this)(position + UP) == POKEMON_TILE) repositionPokemon(position + UP);
	else if ((*this)(position + DOWN) == POKEMON_TILE) repositionPokemon(position + DOWN);
	else if ((*this)(position + LEFT) == POKEMON_TILE) repositionPokemon(position + LEFT);
	else if ((*this)(position + RIGHT) == POKEMON_TILE) repositionPokemon(position + RIGHT);
	else return false;
	return true;
}

void Map::repositionPokemon(const std::pair<int, int> position) {
	m_tiles[position.first][position.second] = EMPTY_TILE;
	std::pair<int, int> newPokemonPosition = getRandomEmptyTile();
	m_tiles[newPokemonPosition.first][newPokemonPosition.second] = POKEMON_TILE;
}

Map::~Map() {
	for (int i = 0; i < m_width; ++i)
		delete[] m_tiles[i];
	delete[] m_tiles;
}