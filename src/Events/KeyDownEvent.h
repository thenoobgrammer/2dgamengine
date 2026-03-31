#ifndef INC_2DGAMEENGINE_KEYDOWNEVENT_H
#define INC_2DGAMEENGINE_KEYDOWNEVENT_H

#include "../EventBus/Event.h"
#include <SDL.h>

class KeyDownEvent: public Event {
    public:
        SDL_Keycode symbol;
        KeyDownEvent(SDL_Keycode symbol) : symbol(symbol) {}
};

#endif //INC_2DGAMEENGINE_KEYDOWNEVENT_H
