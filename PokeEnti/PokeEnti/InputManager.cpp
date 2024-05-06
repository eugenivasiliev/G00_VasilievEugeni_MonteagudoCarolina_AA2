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
	//Catch too many buffered inputs
	if (m_inputs.size() >= MAX_INPUTS_BUFFERED) return;

	//Movement inputs
	if (GetAsyncKeyState(VK_LEFT) && (m_inputs.empty() || m_inputs.back() != VK_LEFT)) m_inputs.push(VK_LEFT);
	if (GetAsyncKeyState(VK_UP) && (m_inputs.empty() || m_inputs.back() != VK_UP)) m_inputs.push(VK_UP);
	if (GetAsyncKeyState(VK_RIGHT) && (m_inputs.empty() || m_inputs.back() != VK_RIGHT)) m_inputs.push(VK_RIGHT);
	if (GetAsyncKeyState(VK_DOWN) && (m_inputs.empty() || m_inputs.back() != VK_DOWN)) m_inputs.push(VK_DOWN);

	//Interaction
	if (GetAsyncKeyState(VK_SPACE) && (m_inputs.empty() || m_inputs.back() != VK_SPACE)) m_inputs.push(VK_SPACE);

	//Quit
	if (GetAsyncKeyState(VK_ESCAPE) && (m_inputs.empty() || m_inputs.back() != VK_ESCAPE)) m_inputs.push(VK_ESCAPE);
	
	//We avoid duplicate inputs in the queue
}

InputManager::~InputManager() {}