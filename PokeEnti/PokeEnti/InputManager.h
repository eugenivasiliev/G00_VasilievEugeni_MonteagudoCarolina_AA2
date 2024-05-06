#pragma once
#include <queue>

class InputManager {
public:
	InputManager();
	short GetCurrentInput();
	void ProcessInput();
	~InputManager();
private:
	std::queue<short> m_inputs;
};