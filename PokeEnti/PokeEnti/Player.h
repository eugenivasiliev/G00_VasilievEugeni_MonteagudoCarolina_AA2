#pragma once
#include "Map.h"
#include "Util.h"
#include <Windows.h>
#include <utility>

#define STARTING_POKEMON 0

class Player
{
public:
	Player();
	Player(const int &x, const int &y);
	std::pair<int, int> getPosition() const;
	PlTiles getSprite() const;
	int getCapturedPokemon() const;
	void move(const short &direction, const Map &tiles);
	void incrementPokemon(const bool &captured);
	~Player();
private:
	std::pair<int, int> m_position;
	PlTiles m_orientation;
	int m_capturedPokemon;
};