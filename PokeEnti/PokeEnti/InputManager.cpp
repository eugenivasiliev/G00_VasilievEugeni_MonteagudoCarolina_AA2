#include "InputManager.h"
#include <Windows.h>

#define KEYCODE_D 0x44
#define KEYCODE_F 0x46
#define KEYCODE_J 0x4A
#define KEYCODE_K 0x4B

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
	if (GetAsyncKeyState(KEYCODE_D) && (m_inputs.empty() || m_inputs.back() != KEYCODE_D)) m_inputs.push(KEYCODE_D);
	if (GetAsyncKeyState(KEYCODE_F) && (m_inputs.empty() || m_inputs.back() != KEYCODE_F)) m_inputs.push(KEYCODE_F);
	if (GetAsyncKeyState(KEYCODE_J) && (m_inputs.empty() || m_inputs.back() != KEYCODE_J)) m_inputs.push(KEYCODE_J);
	if (GetAsyncKeyState(KEYCODE_K) && (m_inputs.empty() || m_inputs.back() != KEYCODE_K)) m_inputs.push(KEYCODE_K);

	//Interaction
	if (GetAsyncKeyState(VK_SPACE) && (m_inputs.empty() || m_inputs.back() != VK_SPACE)) m_inputs.push(VK_SPACE);

	//Quit
	if (GetAsyncKeyState(VK_ESCAPE) && (m_inputs.empty() || m_inputs.back() != VK_ESCAPE)) m_inputs.push(VK_ESCAPE);
	
	//We avoid duplicate inputs in the queue
}

InputManager::~InputManager() {}