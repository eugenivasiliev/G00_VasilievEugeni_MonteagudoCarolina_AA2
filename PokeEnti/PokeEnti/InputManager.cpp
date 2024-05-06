#include "InputManager.h"
#include <Windows.h>

InputManager::InputManager() {}

short InputManager::GetCurrentInput() {
	if (m_inputs.empty()) return NULL;
	short currentInput = m_inputs.front();
	m_inputs.pop();
	return currentInput;
}

void InputManager::ProcessInput() {
	//Movement inputs
	if (GetAsyncKeyState(VK_LEFT)) m_inputs.push(VK_LEFT);
	if (GetAsyncKeyState(VK_UP)) m_inputs.push(VK_UP);
	if (GetAsyncKeyState(VK_RIGHT)) m_inputs.push(VK_RIGHT);
	if (GetAsyncKeyState(VK_DOWN)) m_inputs.push(VK_DOWN);

	//Interaction
	if (GetAsyncKeyState(VK_SPACE)) m_inputs.push(VK_SPACE);

	//Quit
	if (GetAsyncKeyState(VK_ESCAPE)) m_inputs.push(VK_ESCAPE);
}

InputManager::~InputManager() {}