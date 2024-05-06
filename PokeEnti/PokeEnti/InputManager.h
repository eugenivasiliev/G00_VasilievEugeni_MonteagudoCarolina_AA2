#pragma once
#include <queue>
#define MAX_INPUTS_BUFFERED 3

class InputManager {
public:
	InputManager();
	short GetCurrentInput();
	void ProcessInput();
	~InputManager();
private:
	std::queue<short> m_inputs;
};