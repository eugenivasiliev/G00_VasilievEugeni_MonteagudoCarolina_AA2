#pragma once
#include "Map.h"
#include <Windows.h>
#include <utility>

#define STARTING_POKEMON 0

extern const std::pair<int, int> UP;
extern const std::pair<int, int> DOWN;
extern const std::pair<int, int> LEFT;
extern const std::pair<int, int> RIGHT;

extern const char EMPTY_TILE;

extern const char UP_SPRITE;
extern const char DOWN_SPRITE;
extern const char LEFT_SPRITE;
extern const char RIGHT_SPRITE;

std::pair<int, int> operator+ (const std::pair<int, int>& l, const std::pair<int, int>& r);
void operator+= (std::pair<int, int>& l, const std::pair<int, int>& r);

class Player
{
public:
	Player();
	Player(int x, int y);
	std::pair<int, int> getPosition() const;
	char getSprite() const;
	int getCapturedPokemon() const;
	void move(const short &direction, const Map &tiles);
	void incrementPokemon(bool captured);
	~Player();
private:
	std::pair<int, int> m_position;
	char m_orientation;
	int m_capturedPokemon;
};

