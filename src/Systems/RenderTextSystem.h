#ifndef INC_2DGAMEENGINE_RENDERTEXTSYSTEM_H
#define INC_2DGAMEENGINE_RENDERTEXTSYSTEM_H

#include <SDL_render.h>

#include "../Components/LifeTimeComponent.h"
#include "../Components/TextComponent.h"
#include "../ECS/ECS.h"

class RenderTextSystem: public System {
  public:
    RenderTextSystem() {
      RequireComponent<TextComponent>();
      RequireComponent<LifeTimeComponent>();
      RequireComponent<TransformComponent>();
    }
    ~RenderTextSystem() = default;

    void Update(SDL_Renderer* renderer, const std::unique_ptr<AssetStore>& assetStore) {
      for (auto e : GetSystemEntities()) {
        if (!e.HasComponent<TextComponent>()) return;

        auto& text = e.GetComponent<TextComponent>();
        auto& lifeTime = e.GetComponent<LifeTimeComponent>();

        if (SDL_GetTicks() > lifeTime.destroyAt) {
          e.Kill();
          continue;
        }

        auto& transform = e.GetComponent<TransformComponent>();
        TTF_Font* font = assetStore->GetFont(text.fontId);
        if (!font) {
          continue;
        }
        Logger::Log(std::to_string(text.color.r) + std::to_string(text.color.g) + std::to_string(text.color.b) + " " + text.fontId);
        SDL_Surface* surface = TTF_RenderText_Blended(font, text.text.c_str(), text.color);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_Rect destRect = {
          static_cast<int>(transform.position.x),
          static_cast<int>(transform.position.y),
          surface->w,
          surface->h
        };
        SDL_RenderCopy(renderer, texture, nullptr, &destRect);
        SDL_FreeSurface(surface);
      }
    }
};

#endif
