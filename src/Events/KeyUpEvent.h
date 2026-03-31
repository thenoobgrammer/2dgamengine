#ifndef INC_2DGAMEENGINE_KEYUPEVENT_H
#define INC_2DGAMEENGINE_KEYUPEVENT_H

#include "../EventBus/Event.h"
#include <SDL.h>

class KeyUpEvent: public Event {
    public:
        SDL_Keycode symbol;
        KeyUpEvent(SDL_Keycode symbol) : symbol(symbol) {}
};

#endif //INC_2DGAMEENGINE_KEYUPEVENT_H
