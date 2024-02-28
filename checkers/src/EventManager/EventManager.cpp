#include "EventManager.h"
#include "raylib.h"
#include <iostream>

using namespace std;

void EventManager::connect(bool triggered, std::function<void()> handler)
{
	if(triggered)
		handler();
};

bool EventManager::CLICK()
{
	if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		return true;
	return false;
};
