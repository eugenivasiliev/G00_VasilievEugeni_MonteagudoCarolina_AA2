#include "Map.h"
#include <iostream>
#include <cstdlib>

#pragma region ZONE
Zone::Zone() {
	m_unlocked = false;
	m_startPokemon = 0;
	m_condition = 0;
}

Zone::Zone(const Zones& zone, const std::pair<int, int>& lowerBound, const std::pair<int, int>& upperBound,
	const int& startPokemon, const int& condition) : 
	m_zone(zone), m_lowerBound(lowerBound), m_upperBound(upperBound),
	m_unlocked(false), m_startPokemon(startPokemon), m_condition(condition) {}

bool Zone::getUnlocked() const { return m_unlocked; }

void Zone::checkCondition(const int &collectedPokemon) { m_unlocked = m_unlocked || (collectedPokemon >= m_condition); }

int Zone::getStartPokemon() const { return m_startPokemon; }

bool Zone::isInZone(const std::pair<int, int>& pos) const { return m_lowerBound < pos && pos < m_upperBound; }

#pragma endregion

#pragma region MAP
Map::Map() {
	m_width = 0;
	m_height = 0;
	m_tiles = new Tiles* [m_width];
}

Map::Map(const Data& data) : m_width(data.m_mapWidth), m_height(data.m_mapHeight), m_minTime(data.m_minTime), m_maxTime(data.m_maxTime), m_lastMoveTime(clock()) {
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
		//m_tiles[i][m_width / 2] = EnvTiles::WALL_TILE;
		//Keep pokENTI unlocked, since it has no condition
		m_tiles[i][m_width - 1] = EnvTiles::WALL_TILE;
	}
	for (int i = 0; i < m_height; ++i) {
		m_tiles[0][i] = EnvTiles::WALL_TILE;
		m_tiles[m_height / 2][i] = EnvTiles::WALL_TILE;
		m_tiles[m_height - 1][i] = EnvTiles::WALL_TILE;
	}

	m_palletTown = Zone(Zones::PALLET_TOWN, std::make_pair(0, 0), std::make_pair(m_height/2, m_width/2),
		data.m_palletTownStartPokemon, data.m_palletTownCondition);
	m_forest = Zone(Zones::FOREST, std::make_pair(0, m_width / 2), std::make_pair(m_height / 2, m_width),
		data.m_forestStartPokemon, data.m_forestCondition);
	m_celesteCave = Zone(Zones::CELESTE_CAVE, std::make_pair(m_height / 2, m_width / 2), 
		std::make_pair(m_height, m_width),
		0, 0);
	m_pokENTILeague = Zone(Zones::POKENTI_LEAGUE, std::make_pair(m_height / 2, 0),
		std::make_pair(m_height, m_width / 2),
		0, 0);

	//Generate Pallet Town pokemon
	for (int i = 0; i < m_palletTown.getStartPokemon(); ++i) {
		std::pair<int, int> pokemonPosition;
		do {
			pokemonPosition = getRandomEmptyTile();
		} while (!(pokemonPosition < std::make_pair(m_height / 2, m_width / 2)));
		m_tiles[pokemonPosition.first][pokemonPosition.second] = PkTiles::POKEMON_TILE;
	}

	//colocar la primera pokeball en zona inicial
	placePokeball(Zones::PALLET_TOWN);
	(*this)(m_height * 3 / 4, m_width * 3 / 4) = PkTiles::MEWTWO_TILE;
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
				m_tiles[pokemonPosition.first][pokemonPosition.second] = PkTiles::POKEMON_TILE;
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

	movePokemons();

	//recolectar pokeballs al pasar por encima
	if (playerPosition == m_pokeballPosition) {
		m_tiles[m_pokeballPosition.first][m_pokeballPosition.second] = EnvTiles::EMPTY_TILE;
		placePokeball(getZone(playerPosition));
	}
}

Zones Map::getZone(const std::pair<int, int>& position) const {
	if (m_palletTown.isInZone(position)) return Zones::PALLET_TOWN;
	else if (m_forest.isInZone(position)) return Zones::FOREST;
	else if (m_celesteCave.isInZone(position)) return Zones::CELESTE_CAVE;
	else if (m_pokENTILeague.isInZone(position)) return Zones::POKENTI_LEAGUE;
	else return Zones::NONE;
}

void Map::movePokemons() {
	if (((clock() - m_lastMoveTime) / CLOCKS_PER_SEC) < (rand() % (m_maxTime - m_minTime + 1) + m_minTime)) {
		return;
	}
	m_lastMoveTime = clock();

	for (int i = 0; i < m_height; ++i) {
		for (int j = 0; j < m_width; ++j) {
			if (m_tiles[i][j].index() == static_cast<int>(Tiles_INDICES::PkTiles)) {
				std::pair<int, int> oldPos = std::make_pair(i, j);
				std::pair<int, int> newPos;
				bool validMove = false;
				while (!validMove) {
					int direction = rand() % 8;
					switch (direction) {
					case 0: newPos = oldPos + UP; break;
					case 1: newPos = oldPos + DOWN; break;
					case 2: newPos = oldPos + LEFT; break;
					case 3: newPos = oldPos + RIGHT; break;
					case 4: newPos = oldPos + UP + LEFT; break;
					case 5: newPos = oldPos + UP + RIGHT; break;
					case 6: newPos = oldPos + DOWN + LEFT; break;
					case 7: newPos = oldPos + DOWN + RIGHT; break;
					}
					validMove = (*this)(newPos) == (Tiles)EnvTiles::EMPTY_TILE && getZone(newPos) == getZone(oldPos);
				}
				updatePokemonPosition(oldPos, newPos);
			}
		}
	}
}

void Map::updatePokemonPosition(const std::pair<int, int>& oldPosition, const std::pair<int, int>& newPosition) {
	m_tiles[oldPosition.first][oldPosition.second] = EnvTiles::EMPTY_TILE;
	m_tiles[newPosition.first][newPosition.second] = PkTiles::POKEMON_TILE;
}

void Map::placePokeball(const Zones &zone) {
	std::pair<int, int> newPokeballPos = getRandomEmptyTileInZone(zone);
	m_pokeballPosition = newPokeballPos;
	m_tiles[newPokeballPos.first][newPokeballPos.second] = ObTiles::POKEBALL_TILE;
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

std::pair<int, int> Map::getRandomEmptyTileInZone(const Zones& zone) const {
	Zone zoneToFind = m_palletTown;
	assert(zone != Zones::NONE && "Invalid zone");
	switch (zone)
	{
	case Zones::PALLET_TOWN:
		zoneToFind = m_palletTown;
		break;
	case Zones::FOREST:
		zoneToFind = m_forest;
		break;
	case Zones::CELESTE_CAVE:
		zoneToFind = m_celesteCave;
		break;
	case Zones::POKENTI_LEAGUE:
		zoneToFind = m_pokENTILeague;
		break;
	default:
		break;
	}
	std::pair<int, int> pos;
	do {
		pos = getRandomEmptyTile();
	} while (!zoneToFind.isInZone(pos));
	return pos;
}

std::pair<int, int> Map::checkPokemon(std::pair<int, int> position) {
	for (short i = VK_LEFT; i <= VK_DOWN; ++i)
		if ((*this)(position + i).index() == static_cast<int>(Tiles_INDICES::PkTiles)) return position + i;
	return EMPTY_PAIR;
}

void Map::repositionPokemon(std::pair<int, int> position) {
	m_tiles[position.first][position.second] = (Tiles)EnvTiles::EMPTY_TILE;
	std::pair<int, int> newPokemonPosition = getRandomEmptyTileInZone(getZone(position));
	m_tiles[newPokemonPosition.first][newPokemonPosition.second] = (Tiles)PkTiles::POKEMON_TILE;
}

Map::~Map() {
	for (int i = 0; i < m_width; ++i)
		delete[] m_tiles[i];
	delete[] m_tiles;
}
#pragma endregion
