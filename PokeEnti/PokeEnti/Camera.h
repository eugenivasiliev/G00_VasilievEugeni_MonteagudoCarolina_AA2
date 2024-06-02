#pragma once

#include "Map.h"
#include "Util.h"
#include <utility>
#include <Windows.h>
#include <sstream>

class Camera {
public:
	Camera();
	Camera(const std::pair<int, int>& position, const int& width, const int& height, Map* map);
	void draw();
	void move(const short &direction, const std::pair<int, int>& playerPosition);
private:
	std::ostringstream m_buffer;
	std::pair<int, int> m_position;
	int m_width, m_height;
	Map* m_map;
};
