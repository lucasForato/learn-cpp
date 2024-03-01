#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <functional>

enum EventType {
  CLICK = 4,
};

class EventManager {
public:
  static bool CLICK();
  static void connect(bool triggered, std::function<void()> handler);
};

#endif
