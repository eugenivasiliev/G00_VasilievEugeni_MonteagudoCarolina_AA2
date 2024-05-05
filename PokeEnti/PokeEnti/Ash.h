#pragma once
#define LEFT std::make_pair(-1, 0)
#define RIGHT std::make_pair(1, 0)
#define UP std::make_pair(0, 1)
#define DOWN std::make_pair(0, -1)
#ifndef ASH_H
#define ASH_H
#include "Map.h"
#include <Windows.h>
#include <utility>

class Player
{
public:
	Player();
	Player(int x, int y);
	int getX() const;
	int getY() const;
	int getCapturedPokemon() const;
	void setPosition(std::pair<int, int> newPos);
	void move(const short &direction, const Map &tiles);
	void draw();

private:
	std::pair<int, int> m_position;
	char m_orientation;
	int m_capturedPokemon;
};

#endif

