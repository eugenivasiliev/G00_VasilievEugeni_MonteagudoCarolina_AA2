#pragma once
#include "ReadDoc.h"
#include "Util.h"
#include <utility>

class Zone {
public:
	Zone();
	Zone(const int &startPokemon, const int &condition);
	bool getUnlocked() const;
	void checkCondition(const int &collectedPokemon);
	int getStartPokemon() const;
private:
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
	Tiles operator() (const std::pair<int, int> &position) const;
	Tiles operator() (const int &x, const int &y) const;
	~Map();

private:
	int m_width, m_height;
	Tiles** m_tiles;

	std::pair<int, int> getRandomEmptyTile() const;
	void repositionPokemon(std::pair<int, int> position);

	Zone m_palletTown, m_forest, m_celesteCave, m_pokENTILeague;
};
