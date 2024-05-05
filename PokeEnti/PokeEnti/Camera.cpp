#include "Camera.h"
#include <iostream>

std::pair<int, int> operator+ (const std::pair<int, int>& l, const std::pair<int, int>& r);

bool operator< (std::pair<int, int> l, std::pair<int, int> r) {
	return (l.first < r.first && l.second < r.second);
}

void Camera::draw() {
	//Render map
	for (int i = m_position.first; i < m_width; ++i)
		for (int j = m_position.second; j < m_height; ++j)
			std::cout << (*m_map)(i, j);
}

void Camera::setPosition(std::pair<int, int> newPos) {
	//Check first validity of input
	m_position = newPos;
}

void Camera::move(short direction) {
	switch (direction) {
	case VK_UP:
		setPosition(m_position + std::make_pair(0, 1));
		break;
	case VK_LEFT:
		setPosition(m_position + std::make_pair(-1, 0));
		break;
	case VK_DOWN:
		setPosition(m_position + std::make_pair(0, -1));
		break;
	case VK_RIGHT:
		setPosition(m_position + std::make_pair(1, 0));
		break;
	}
}