#pragma once
#include <queue>

class InputManager {
public:
	short GetCurrentInput();
	void ProcessInput();
private:
	std::queue<short> inputs;
};