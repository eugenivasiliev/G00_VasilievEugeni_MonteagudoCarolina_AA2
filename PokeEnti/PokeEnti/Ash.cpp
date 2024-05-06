#include "Ash.h"
#include <iostream>

const char UP_SPRITE = '^';
const char DOWN_SPRITE = 'v';
const char LEFT_SPRITE = '<';
const char RIGHT_SPRITE = '>';

Player::Player() : m_position({ 0,0 }), m_orientation(RIGHT_SPRITE), m_capturedPokemon(0) {}
Player::Player(int x, int y) : m_position({ y, x }), m_orientation(RIGHT_SPRITE), m_capturedPokemon(STARTING_POKEMON) {}

std::pair<int, int> Player::getPosition() const {
	return m_position;
}

char Player::getSprite() const {
	return m_orientation;
}

int Player::getCapturedPokemon() const {
	return m_capturedPokemon;
}

void Player::incrementPokemon(bool captured) {
	m_capturedPokemon += captured;
}

void Player::move(const short &direction, const Map &tiles) {
	switch (direction) {
	case VK_UP:
		if (tiles(m_position + UP) == EMPTY_TILE)
			m_position += UP;
		m_orientation = UP_SPRITE;
		break;
	case VK_LEFT:
		if (tiles(m_position + LEFT) == EMPTY_TILE)
			m_position += LEFT;
		m_orientation = LEFT_SPRITE;
		break;
	case VK_DOWN:
		if (tiles(m_position + DOWN) == EMPTY_TILE)
			m_position += DOWN;
		m_orientation = DOWN_SPRITE;
		break;
	case VK_RIGHT:
		if (tiles(m_position + RIGHT) == EMPTY_TILE)
			m_position += RIGHT;
		m_orientation = RIGHT_SPRITE;
		break;
	}
}

Player::~Player() {}