#include "Player.h"
#include <iostream>

Player::Player() : m_position({ 0,0 }), m_orientation(PlayerTiles::RIGHT_SPRITE), m_capturedPokemon(0) {}
Player::Player(const int &x, const int &y) : m_position({ y, x }), m_orientation(PlayerTiles::RIGHT_SPRITE), m_capturedPokemon(STARTING_POKEMON) {}

std::pair<int, int> Player::getPosition() const {
	return m_position;
}

PlayerTiles Player::getSprite() const {
	return m_orientation;
}

int Player::getCapturedPokemon() const {
	return m_capturedPokemon;
}

void Player::incrementPokemon(const bool &captured) {
	m_capturedPokemon += captured;
}

void Player::move(const short &direction, const Map &tiles) {
	if (tiles(m_position + direction) == (Tiles)EnvironmentTiles::EMPTY_TILE) m_position += direction;
	m_orientation = static_cast<PlayerTiles>(direction - VK_LEFT);
}

Player::~Player() {}
