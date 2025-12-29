#ifndef INC_2DGAMEENGINE_MOUSEEVENT_H
#define INC_2DGAMEENGINE_MOUSEEVENT_H

#include "../EventBus/Event.h"
#include <SDL.h>

class MouseEvent: public Event {
public:
  SDL_MouseMotionEvent motionEvent;
  SDL_MouseButtonEvent buttonEvent;
  MouseEvent(SDL_MouseMotionEvent motionEvent) : motionEvent(motionEvent) {}
  MouseEvent(SDL_MouseButtonEvent buttonEvent) : buttonEvent(buttonEvent) {}
};

#endif
