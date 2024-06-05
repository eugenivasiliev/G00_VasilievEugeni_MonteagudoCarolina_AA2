#pragma once
#include "Player.h"
#include "Map.h"
#include "ReadDoc.h"
#include "InputManager.h"
#include "Camera.h"

#define FRAMERATE 30

enum class GameEnd {
	CONTINUE,
	WIN,
	LOSE,
	ESCAPE
};

enum class GameState {
	INIT,
	MAIN_MENU,
	GAME,
	GAME_OVER,
	GAME_WIN
};

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
	bool playGame();
	void init();
	MenuOptions mainMenu(const MenuOptions &currOption);
	GameEnd gameLoop();
	void gameOver();
	void gameWin();
	void hideCursor();
private:
	std::ostringstream m_buffer;
	GameState m_state;
	InputManager m_inputManager;
	Map m_map;
	Camera m_camera;
	Player m_player;
};
