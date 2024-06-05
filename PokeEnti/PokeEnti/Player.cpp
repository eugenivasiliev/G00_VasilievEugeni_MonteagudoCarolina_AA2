#include "Player.h"
#include <iostream>

Player::Player() : m_position({ 0,0 }), m_orientation(PlTiles::RIGHT_SPRITE), m_capturedPokemon(0), m_pokeballCount(0) {}
Player::Player(const int &x, const int &y) : m_position({ y, x }), m_orientation(PlTiles::RIGHT_SPRITE), m_capturedPokemon(STARTING_POKEMON), m_pokeballCount(0) {}

std::pair<int, int> Player::getPosition() const {
	return m_position;
}

PlTiles Player::getSprite() const {
	return m_orientation;
}

int Player::getCapturedPokemon() const {
	return m_capturedPokemon;
}

int Player::getPokeballCount() const {
	return m_pokeballCount;
}

void Player::decreasePokeball() {
	m_pokeballCount--;
}

void Player::incrementPokemon(const int &captured) {
	m_capturedPokemon += captured;
}

void Player::move(const short &direction, Map &tiles) {
	/*if (tiles(m_position + direction) == (Tiles)EnvTiles::EMPTY_TILE) m_position += direction;
	m_orientation = static_cast<PlTiles>(direction - VK_LEFT);*/

	std::pair<int, int> newPosition = m_position + direction;
	if (tiles(newPosition) == (Tiles)EnvTiles::EMPTY_TILE || tiles(newPosition) == (Tiles)ObTiles::POKEBALL_TILE) {
		m_position = newPosition;
		if (tiles(newPosition) == (Tiles)ObTiles::POKEBALL_TILE) {
			getPokeball();
			tiles.placePokeball(tiles.getZone(newPosition));
		}
	}
	m_orientation = static_cast<PlTiles>(direction - VK_LEFT);
}

void Player::getPokeball() {
	m_pokeballCount++;
}

Player::~Player() {}
