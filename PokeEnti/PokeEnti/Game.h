#pragma once
#include "Ash.h"
#include "Datos.h"
#include "Map.h"
#include "ReadDoc.h"
#include "InputManager.h"
#include "Camera.h"

#define FRAMERATE 30

class Game {
public:
	Game();
	Game(int m_mapWidth, int m_mapHeight, int m_palletTownStartPokemon, int m_palletTownCondition, int m_forestStartPokemon, int m_forestCondition);
	bool GameLoop();
private:
	Player m_player;
	InputManager m_inputManager;
	Camera m_camera;
	Map m_map;
	int m_mapWidth, m_mapHeight;
	int m_palletTownStartPokemon, m_palletTownCondition;
	int m_forestStartPokemon, m_forestCondition;
};