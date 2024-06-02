#include "Map.h"
#include <iostream>

#pragma region ZONE
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
#pragma endregion

#pragma region MAP
Map::Map() {
	m_width = 0;
	m_height = 0;
	m_tiles = new Tiles* [m_width];
}

Map::Map(const Data& data) : m_width(data.m_mapWidth), m_height(data.m_mapHeight) {
	//Initialise
	m_tiles = new Tiles* [m_height];
	for (int i = 0; i < m_height; ++i) {
		m_tiles[i] = new Tiles[m_width];
		for (int j = 0; j < m_width; ++j)
			m_tiles[i][j] = EnvTiles::EMPTY_TILE;
	}

	//Walls
	for (int i = 0; i < m_width; ++i) {
		m_tiles[i][0] = EnvTiles::WALL_TILE;
		m_tiles[i][m_width / 2] = EnvTiles::WALL_TILE;
		m_tiles[i][m_width - 1] = EnvTiles::WALL_TILE;
	}
	for (int i = 0; i < m_height; ++i) {
		m_tiles[0][i] = EnvTiles::WALL_TILE;
		m_tiles[m_height / 2][i] = EnvTiles::WALL_TILE;
		m_tiles[m_height - 1][i] = EnvTiles::WALL_TILE;
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
		m_tiles[pokemonPosition.first][pokemonPosition.second] = EnvTiles::POKEMON_TILE;
	}

}

void Map::update(const std::pair<int, int> &playerPosition, const PlTiles &playerSprite, const int& capturedPokemon) {
	for (int i = 0; i < m_width; ++i)
		for (int j = 0; j < m_height; ++j)
			if (m_tiles[j][i].index() == static_cast<int>(Tiles_INDICES::PlTiles))
				m_tiles[j][i] = EnvTiles::EMPTY_TILE;
	m_tiles[playerPosition.first][playerPosition.second] = playerSprite;
	if (!m_palletTown.getUnlocked()) {
		m_palletTown.checkCondition(capturedPokemon);
		if (m_palletTown.getUnlocked()) {
			//Clear Pallet Town wall
			for (int i = 1; i < m_height / 2; ++i)
				m_tiles[i][m_width / 2] = EnvTiles::EMPTY_TILE;
			//Generate Forest pokemon
			for (int i = 0; i < m_forest.getStartPokemon(); ++i) {
				std::pair<int, int> pokemonPosition;
				do {
					pokemonPosition = getRandomEmptyTile();
				} while (!(pokemonPosition < std::make_pair(m_height / 2, m_width) && std::make_pair(0, m_width / 2) < pokemonPosition));
				m_tiles[pokemonPosition.first][pokemonPosition.second] = EnvTiles::POKEMON_TILE;
			}
		}
	}
	else if (!m_forest.getUnlocked()) {
		m_forest.checkCondition(capturedPokemon);
		if (m_forest.getUnlocked())
			//Clear Forest wall
			for (int i = m_width / 2 + 1; i < m_width - 1; ++i)
				m_tiles[m_height / 2][i] = EnvTiles::EMPTY_TILE;
		//Would generate next pokemon set, but it is not declared
	}
}

Tiles Map::operator() (const std::pair<int, int>& position) const {
	return m_tiles[position.first][position.second];
}

Tiles Map::operator() (const int &x, const int &y) const {
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
	} while ((*this)(y, x) != (Tiles)EnvTiles::EMPTY_TILE);
	return std::make_pair(y, x);
}

bool Map::checkPokemon(std::pair<int, int> position) {
	for (short i = VK_LEFT; i <= VK_DOWN; ++i)
		if ((*this)(position + i) == (Tiles)EnvTiles::POKEMON_TILE) {
			repositionPokemon(position + i);
			return true;
		}
	return false;
}

void Map::repositionPokemon(std::pair<int, int> position) {
	m_tiles[position.first][position.second] = (Tiles)EnvTiles::EMPTY_TILE;
	std::pair<int, int> newPokemonPosition = getRandomEmptyTile();
	m_tiles[newPokemonPosition.first][newPokemonPosition.second] = (Tiles)EnvTiles::POKEMON_TILE;
}

Map::~Map() {
	for (int i = 0; i < m_width; ++i)
		delete[] m_tiles[i];
	delete[] m_tiles;
}
#pragma endregion
