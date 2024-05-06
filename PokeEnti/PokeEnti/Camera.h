#pragma once

#include "Map.h"
#include <utility>
#include <Windows.h>
#include <sstream>

extern const std::pair<int, int> UP;
extern const std::pair<int, int> DOWN;
extern const std::pair<int, int> LEFT;
extern const std::pair<int, int> RIGHT;

extern const char EMPTY_TILE;
extern const char WALL_TILE;
extern const char POKEMON_TILE;

extern const char UP_SPRITE;
extern const char DOWN_SPRITE;
extern const char LEFT_SPRITE;
extern const char RIGHT_SPRITE;

std::pair<int, int> operator+ (const std::pair<int, int>& l, const std::pair<int, int>& r);
void operator+= (std::pair<int, int>& l, const std::pair<int, int>& r);
bool operator< (const std::pair<int, int> &l, const std::pair<int, int> &r);

class Camera {
public:
	Camera();
	Camera(const std::pair<int, int>& position, const int& width, const int& height, Map* map);
	void draw();
	void move(const short &direction, const std::pair<int, int>& playerPosition);
	~Camera();
private:
	std::ostringstream buffer;
	std::pair<int, int> m_position;
	int m_width, m_height;
	Map* m_map;
};