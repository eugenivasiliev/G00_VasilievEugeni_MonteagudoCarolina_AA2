#include "InputManager.h"
#include <Windows.h>

short InputManager::GetCurrentInput() {
	if (inputs.empty()) return NULL;
	short currentInput = inputs.front();
	inputs.pop();
	return currentInput;
}

void InputManager::ProcessInput() {
	//Movement inputs
	if (GetAsyncKeyState(VK_LEFT)) inputs.push(VK_LEFT);
	if (GetAsyncKeyState(VK_UP)) inputs.push(VK_UP);
	if (GetAsyncKeyState(VK_RIGHT)) inputs.push(VK_RIGHT);
	if (GetAsyncKeyState(VK_DOWN)) inputs.push(VK_DOWN);

	//Interaction
	if (GetAsyncKeyState(VK_SPACE)) inputs.push(VK_SPACE);

	//Quit
	if (GetAsyncKeyState(VK_ESCAPE)) inputs.push(VK_ESCAPE);
}