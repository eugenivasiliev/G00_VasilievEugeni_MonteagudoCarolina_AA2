#include "Camera.h"
#include <iostream>

Camera::Camera() : m_position(std::make_pair(0, 0)), m_width(0), m_height(0), m_map(nullptr) {}

Camera::Camera(const std::pair<int, int>& position, const int& width, const int& height, Map* map) : 
	m_position(position), 
	m_width(width), m_height(height), 
	m_map(map) {}

void Camera::draw() {
	//Render map
	m_buffer << "\033[1;1H";
	for (int i = m_position.first; i < m_height + m_position.first; ++i) {
		for (int j = m_position.second; j < m_width + m_position.second; ++j) {
			Tiles tile = (*m_map)(i, j);
			switch (tile.index())
			{
			case static_cast<int>(Tiles_INDICES::EnvTiles):
				if(tile == (Tiles)EnvTiles::EMPTY_TILE) m_buffer << "\033[0;0;0m ";
				else if (tile == (Tiles)EnvTiles::WALL_TILE) m_buffer << "\033[47m\033[1;37mX";
				break;
			case static_cast<int>(Tiles_INDICES::PlTiles):
				m_buffer << "\033[0;32;1m";
				if (tile == (Tiles)PlTiles::LEFT_SPRITE) m_buffer << "<";
				else if (tile == (Tiles)PlTiles::UP_SPRITE) m_buffer << "^";
				else if (tile == (Tiles)PlTiles::RIGHT_SPRITE) m_buffer << ">";
				else if (tile == (Tiles)PlTiles::DOWN_SPRITE) m_buffer << "v";
				break;
			case static_cast<int>(Tiles_INDICES::PkTiles):
				if (tile == (Tiles)PkTiles::POKEMON_TILE) m_buffer << "\033[0;33mP";
				break;
			default:
				assert(false && "Undrawable tile");
				break;
			}
			m_buffer << "\033[0;0;0m";
			
		}
		m_buffer << std::endl;
	}
	std::cout << m_buffer.str();
	m_buffer.str("");
	m_buffer.clear();
}

void Camera::move(const short &direction, const std::pair<int, int> &playerPosition) {
	switch (direction) {
	case VK_UP:
		if(m_position.first > 0 && playerPosition.first <= m_position.first + m_height / 2) m_position += UP;
		break;
	case VK_DOWN:
		if (m_position.first + m_height < m_map->getHeight() && playerPosition.first >= m_position.first + m_height / 2) m_position += DOWN;
		break;
	case VK_LEFT:
		if (m_position.second > 0 && playerPosition.second <= m_position.second + m_width / 2) m_position += LEFT;
		break;
	case VK_RIGHT:
		if (m_position.second + m_width < m_map->getWidth() && playerPosition.second >= m_position.second + m_width / 2) m_position += RIGHT;
		break;
	}
}
