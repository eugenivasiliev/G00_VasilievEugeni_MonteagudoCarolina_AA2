#include "InputManager.h"
#include <Windows.h>
#include <iostream>

InputManager::InputManager() { m_inputs = {}; }

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
	for(short i = VK_LEFT; i <= VK_DOWN; ++i) if (GetAsyncKeyState(i) && (m_inputs.empty() || m_inputs.back() != i)) m_inputs.push(i);

	//Interaction
	if (GetAsyncKeyState(VK_SPACE) && (m_inputs.empty() || m_inputs.back() != VK_SPACE)) m_inputs.push(VK_SPACE);

	//Quit
	if (GetAsyncKeyState(VK_ESCAPE) && (m_inputs.empty() || m_inputs.back() != VK_ESCAPE)) m_inputs.push(VK_ESCAPE);
	
	//We avoid duplicate inputs in the queue
}

InputManager::~InputManager() {}
