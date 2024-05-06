#pragma once
#include "Player.h"
#include "Map.h"
#include "ReadDoc.h"
#include "InputManager.h"
#include "Camera.h"

#define FRAMERATE 30

class Game {
public:
	Game();
	Game(const Data &data);
	bool gameLoop();
	void hideCursor();
	~Game();
private:
	InputManager m_inputManager;
	Map m_map;
	Camera m_camera;
	Player m_player;
};