#include "Ash.h"

Player::Player() : m_x(0), m_y(0){}
Player::Player(int inicioX, int inicioY) : m_x(inicioX), m_y(inicioY){}

int Player::getY() const {
	return m_y;
}

int Player::getX() const {
	return m_x;
}

void Player::setPosition(int x, int y) {
	//Check first validity of input
	m_x = x;
	m_y = y;
}

void Player::move(short direction) {
	switch (direction) {
	case VK_UP:
		setPosition(m_x, m_y + 1);
		break;
	case VK_LEFT:
		setPosition(m_x - 1, m_y);
		break;
	case VK_DOWN:
		setPosition(m_x, m_y - 1);
		break;
	case VK_RIGHT:
		setPosition(m_x + 1, m_y);
		break;
	}
}