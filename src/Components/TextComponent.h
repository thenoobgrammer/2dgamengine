#ifndef INC_2DGAMEENGINE_TEXTCOMPONENT_H
#define INC_2DGAMEENGINE_TEXTCOMPONENT_H

#include <SDL_pixels.h>
#include <string>

struct TextComponent {
  std::string text;
  std::string fontId;
  SDL_Color color;

  TextComponent(std::string text = "", std::string fontId = "", SDL_Color color = SDL_Color{0, 0, 0, 0}) : text(text), fontId(fontId), color(color) {}
};

#endif // INC_2DGAMEENGINE_TEXTCOMPONENT_H
