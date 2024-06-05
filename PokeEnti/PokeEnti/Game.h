#pragma once
#include "Player.h"
#include "Map.h"
#include "ReadDoc.h"
#include "InputManager.h"
#include "Camera.h"

enum class CombatMenu {
	NONE_ATTACK,
	NONE_CAPTURE,
	NONE_FLEE,
	COUNT,
	ATTACK,
	CAPTURE,
	FLEE
};

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
	GAME_WIN,
	ESCAPE
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
	void gameLoop();
	void gameOver();
	void gameWin();
	void hideCursor();
	void combat(std::pair<int, int> pokemonPosition);
	CombatMenu combatMenu(const CombatMenu& currOption, std::ostringstream& buffer);
private:
	bool m_canWin;
	std::ostringstream m_buffer;
	int m_pokemonHealth, m_mewtwoHealth, m_attackDamage;
	std::pair<int, int> isInCombat;
	GameState m_state;
	InputManager m_inputManager;
	Map m_map;
	Camera m_camera;
	Player m_player;
};
