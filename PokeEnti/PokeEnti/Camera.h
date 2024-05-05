#pragma once

#include "Map.h"
#include <utility>
#include <Windows.h>

class Camera {
public:
	void draw();
	void setPosition(std::pair<int, int> newPos);
	void move(short direction);
private:
	std::pair<int, int> m_position;
	int m_width, m_height;
	Map* m_map;
};