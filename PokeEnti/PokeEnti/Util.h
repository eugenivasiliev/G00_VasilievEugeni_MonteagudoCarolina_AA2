#pragma once
#include <assert.h>
#include <Windows.h>
#include <utility>
#include <variant>

#define FRAMERATE 30

#pragma region DIRECTIONS
#define EMPTY_PAIR std::make_pair(-1, -1)
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

#pragma region TILES

#define MakeVariant(name, ...) \
enum class name##_INDICES { \
	__VA_ARGS__ \
}; \
typedef std::variant<__VA_ARGS__> name;

//Environment tiles
enum class EnvTiles { 
	EMPTY_TILE,
	WALL_TILE
};

//Pokemon Tiles
enum class PkTiles {
	POKEMON_TILE,
	MEWTWO_TILE
};

//Player tiles
enum class PlTiles {
	LEFT_SPRITE,
	UP_SPRITE,
	RIGHT_SPRITE,
	DOWN_SPRITE
};

//Object tiles
enum class ObTiles {
	POKEBALL_TILE
};

MakeVariant(Tiles, EnvTiles, PkTiles, PlTiles, ObTiles)

#pragma endregion
