#pragma once
#include "ReadDoc.h"
#include <utility>

extern const std::pair<int, int> UP;
extern const std::pair<int, int> DOWN;
extern const std::pair<int, int> LEFT;
extern const std::pair<int, int> RIGHT;

extern const char EMPTY_TILE;
extern const char WALL_TILE;
extern const char POKEMON_TILE;

std::pair<int, int> operator+ (const std::pair<int, int>& l, const std::pair<int, int>& r);
bool operator< (const std::pair<int, int>& l, const std::pair<int, int>& r);

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
	void update(const std::pair<int, int>& playerPosition, const char& playerSprite, const int& capturedPokemon);
	int getWidth() const;
	int getHeight() const;
	bool checkPokemon(std::pair<int, int> position);
	char operator() (const std::pair<int, int> &position) const;
	char operator() (const int &x, const int &y) const;
	~Map();

private:
	int m_width, m_height;
	char** m_tiles;

	std::pair<int, int> getRandomEmptyTile() const;
	void repositionPokemon(std::pair<int, int> position);

	Zone m_palletTown, m_forest, m_celesteCave, m_pokENTILeague;
};
