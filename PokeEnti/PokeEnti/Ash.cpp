#include "Ash.h"
#include <iostream>

std::pair<int, int> operator+ (const std::pair<int, int>& l, const std::pair<int, int>& r);
void operator+= (std::pair<int, int>& l, const std::pair<int, int>& r);

Player::Player() : m_position({ 0,0 }), m_orientation('>'), m_capturedPokemon(0) {}
Player::Player(int x, int y) : m_position({ x, y }), m_orientation('>'), m_capturedPokemon(0) {}

int Player::getX() const {
	return m_position.first;
}

int Player::getY() const {
	return m_position.second;
}

int Player::getCapturedPokemon() const {
	return m_capturedPokemon;
}

void Player::setPosition(std::pair<int, int> newPos) {
	//Check first validity of input
	m_position = newPos;
}

void Player::move(const short &direction, const Map &tiles) {
	switch (direction) {
	case VK_UP:
		if (tiles(m_position + UP) == ' ')
			m_position += UP;
		m_orientation = '^';
		break;
	case VK_LEFT:
		if (tiles(m_position + LEFT) == ' ')
			m_position += LEFT;
		m_orientation = '<';
		break;
	case VK_DOWN:
		if (tiles(m_position + DOWN) == ' ')
			m_position += DOWN;
		m_orientation = 'v';
		break;
	case VK_RIGHT:
		if (tiles(m_position + RIGHT) == ' ')
			m_position += RIGHT;
		m_orientation = '>';
		break;
	}
}

void Player::draw() {
	std::cout << m_orientation;
}