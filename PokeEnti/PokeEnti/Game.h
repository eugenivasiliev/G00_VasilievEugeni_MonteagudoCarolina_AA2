#pragma once
#include "Ash.h"
#include "Map.h"
#include "ReadDoc.h"
#include "InputManager.h"
#include "Camera.h"

#define FRAMERATE 25

class Game {
public:
	Game();
	Game(const Data &data);
	bool GameLoop();
	void hideCursor();
private:
	InputManager m_inputManager;
	Map m_map;
	Camera m_camera;
	Player m_player;
	
	int m_mapWidth, m_mapHeight;
	int m_palletTownStartPokemon, m_palletTownCondition;
	int m_forestStartPokemon, m_forestCondition;
};