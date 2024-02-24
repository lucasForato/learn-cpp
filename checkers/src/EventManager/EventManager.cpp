#include "EventManager.h"
#include "raylib.h"

using namespace std;

void EventManager::connect(bool triggered, std::function<void()> handler)
{
	if(triggered)
		handler();
};

bool EventManager::CLICK()
{
	SetGesturesEnabled(4); // event for clicking
	int gesture = GetGestureDetected();
	if(gesture) {
    gesture = 0;
		return true;
  }
	return false;
};
