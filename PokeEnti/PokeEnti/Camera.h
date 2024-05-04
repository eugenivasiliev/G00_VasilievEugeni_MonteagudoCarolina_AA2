#pragma once

#include "Ash.h"
#include "Map.h"
#include <utility>

class Camera {
private:
	std::pair<int, int> m_position;
	Map* map;
};