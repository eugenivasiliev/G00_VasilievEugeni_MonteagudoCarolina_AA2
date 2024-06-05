#pragma once
#include "ReadDoc.h"
#include "Util.h"
#include <utility>
#include <time.h>

enum class Zones {
	PALLET_TOWN,
	FOREST,
	CELESTE_CAVE,
	POKENTI_LEAGUE,
	NONE
};

class Zone {
public:
	Zone();
	Zone(const Zones &zone, const std::pair<int, int> &lowerBound, const std::pair<int, int> &upperBound, 
		const int &startPokemon, const int &condition);
	bool isInZone(const std::pair<int, int> &pos) const;
	bool getUnlocked() const;
	void checkCondition(const int &collectedPokemon);
	int getStartPokemon() const;
	
private:
	Zones m_zone;
	std::pair<int, int> m_lowerBound, m_upperBound;
	bool m_unlocked;
	int m_startPokemon, m_condition;
	
};

class Map
{
public:
	Map();
	Map(const Data &data);
	void update(const std::pair<int, int>& playerPosition, const PlTiles& playerSprite, const int& capturedPokemon);
	int getWidth() const;
	int getHeight() const;
	bool checkPokemon(std::pair<int, int> position);
	Zones getZone(const std::pair<int, int>& position) const;
	Tiles operator() (const std::pair<int, int> &position) const;
	Tiles operator() (const int &x, const int &y) const;

	void movePokemons();

	~Map();

private:
	int m_width, m_height;
	Tiles** m_tiles;

	std::pair<int, int> getRandomEmptyTile() const;
	std::pair<int, int> getRandomEmptyTileInZone(const Zones& zone) const;
	void repositionPokemon(std::pair<int, int> position);

	Zone m_palletTown, m_forest, m_celesteCave, m_pokENTILeague;
	//pokemon movement
	void updatePokemonPosition(const std::pair<int, int>& oldPosition, const std::pair<int, int>& newPosition);
	clock_t m_lastMoveTime;
	int m_minTime, m_maxTime;
	
};
