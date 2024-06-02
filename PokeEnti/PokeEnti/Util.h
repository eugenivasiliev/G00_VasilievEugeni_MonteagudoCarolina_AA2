#pragma once
#include <assert.h>
#include <Windows.h>
#include <utility>
#include <variant>

#pragma region DIRECTIONS
#define UP std::make_pair(-1, 0)
#define DOWN std::make_pair(1, 0)
#define LEFT std::make_pair(0, -1)
#define RIGHT std::make_pair(0, 1)
#pragma endregion

#pragma region OPERATORS
std::pair<int, int> operator+ (const std::pair<int, int>& l, const std::pair<int, int>& r);
std::pair<int, int> operator+ (const std::pair<int, int>& l, const short& r);
void operator+= (std::pair<int, int>& l, const std::pair<int, int>& r);
void operator+= (std::pair<int, int>& l, const short& r);
bool operator< (const std::pair<int, int>& l, const std::pair<int, int>& r);
#pragma endregion

#pragma region Tiles

#define MakeVariant(name, ...) \
enum class name##_INDICES { \
	__VA_ARGS__ \
}; \
typedef std::variant<__VA_ARGS__> name;

enum class EnvironmentTiles {
	EMPTY_TILE,
	WALL_TILE,
	POKEMON_TILE
};

enum class PlayerTiles {
	LEFT_SPRITE,
	UP_SPRITE,
	RIGHT_SPRITE,
	DOWN_SPRITE
};

MakeVariant(Tiles, EnvironmentTiles, PlayerTiles)
#pragma endregion