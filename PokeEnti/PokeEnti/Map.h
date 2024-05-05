#pragma once
#ifndef MAP_H
#define MAP_H

#include "Datos.h"
#include "Ash.h"
#include <utility>

class Zone {
public:
	Zone();
	Zone(int startPokemon, int condition, std::pair<int, int> position, int width, int height);
	bool getUnlocked();
	void checkCondition(int collectedPokemon);
	bool checkPokemon(std::pair<int, int> position);
private:
	bool m_unlocked;
	int m_startPokemon, m_condition;
	std::pair<int, int> m_position;
	int m_width, m_height;
	std::pair<int, int>* m_pokemon;
};

class Map
{
public:
	Map();
	Map(const int& m_width, const int& m_height, const int& palletTownStartPokemon, const int& palletTownCondition, const int& forestStartPokemon, const int& forestCondition);
	void update();
	int getWidth() const;
	int getHeight() const;
	char operator() (const std::pair<int, int> &position) const;
	char operator() (int x, int y);

private:
	int m_width, m_height;
	char** m_tiles;

	Zone m_palletTown, m_forest, m_celesteCave, m_pokENTILeague;
};

#endif