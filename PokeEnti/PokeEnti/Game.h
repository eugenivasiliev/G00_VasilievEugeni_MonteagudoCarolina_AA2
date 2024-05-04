#pragma once
#include "Ash.h"
#include "Datos.h"
#include "Map.h"
#include "PlayerView.h"
#include "ReadDoc.h"
#include "InputManager.h"

#define FRAMERATE 60

class Game {
public:
	bool GameLoop();
private:
	Player player;
	InputManager inputManager;
};