#pragma once
#include "Player.h"
#include "Map.h"
#include "ReadDoc.h"
#include "InputManager.h"
#include "Camera.h"

#define FRAMERATE 30

enum class MenuOptions {
	PLAY,
	EXIT,
	NONE_PLAY,
	NONE_EXIT
};

class Game {
public:
	Game();
	Game(const Data &data);
	bool init();
	MenuOptions mainMenu(const MenuOptions &currOption);
	bool gameLoop();
	void hideCursor();
private:
	std::ostringstream m_buffer;
	InputManager m_inputManager;
	Map m_map;
	Camera m_camera;
	Player m_player;
};