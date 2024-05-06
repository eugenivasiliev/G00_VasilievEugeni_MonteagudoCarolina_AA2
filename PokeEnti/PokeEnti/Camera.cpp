#include "Camera.h"
#include <iostream>


Camera::Camera() : m_position(std::make_pair(0, 0)), m_width(0), m_height(0), m_map(nullptr) {}

Camera::Camera(const std::pair<int, int>& position, const int& width, const int& height, Map* map) : 
	m_position(position), 
	m_width(width), m_height(height), 
	m_map(map) {}

void Camera::draw() {
	//Render map
	buffer << "\033[1;1H";
	for (int i = m_position.first; i < m_height + m_position.first; ++i) {
		for (int j = m_position.second; j < m_width + m_position.second; ++j) {
			if((*m_map)(i, j) == WALL_TILE) buffer << "\033[47m\033[1;37m";
			else if((*m_map)(i, j) == POKEMON_TILE) buffer << "\033[0;33m";
			else if((*m_map)(i, j) == UP_SPRITE || (*m_map)(i, j) == DOWN_SPRITE || (*m_map)(i, j) == LEFT_SPRITE || (*m_map)(i, j) == RIGHT_SPRITE) buffer << "\033[0;32;1m";
			buffer << (*m_map)(i, j);
			buffer << "\033[0;0;0m";
			
		}
		buffer << std::endl;
	}
	std::cout << buffer.str();
	buffer.str("");
	buffer.clear();
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

Camera::~Camera(){}