#ifndef INC_2DGAMEENGINE_RENDERSYSTEM_H
#define INC_2DGAMEENGINE_RENDERSYSTEM_H

#include <SDL_render.h>

#include "../Components/SpriteComponent.h"
#include "../Components/TransformComponent.h"
#include "../ECS/ECS.h"
#include "../AssetStore/AssetStore.h"


class RenderSystem: public System{
    public:
        RenderSystem() {
            RequireComponent<TransformComponent>();
            RequireComponent<SpriteComponent>();
        }

        void Update(SDL_Renderer* renderer, const std::unique_ptr<AssetStore>& assetStore) {
            auto entities = GetSystemEntities();
            Logger::Log("RenderSystem processing " + std::to_string(entities.size()) + " entities");

            for (auto entity: GetSystemEntities()) {
                const auto transform = entity.GetComponent<TransformComponent>();
                const auto sprite = entity.GetComponent<SpriteComponent>();

                SDL_Rect srcRect = sprite.srcRect;
                SDL_Rect dstRect = {
                    static_cast<int>(transform.position.x),
                    static_cast<int>(transform.position.y),
                    static_cast<int>(sprite.width * transform.scale.x),
                    static_cast<int>(sprite.height * transform.scale.y)
                };

                Logger::Log("dstRect: x=" + std::to_string(dstRect.x) +
                   " y=" + std::to_string(dstRect.y) +
                   " w=" + std::to_string(dstRect.w) +
                   " h=" + std::to_string(dstRect.h));

                SDL_RenderCopyEx(
                    renderer,
                    assetStore->GetTexture(sprite.assetId),
                    &srcRect,
                    &dstRect,
                    transform.rotation,
                    NULL,
                    SDL_FLIP_NONE
                    );
            }
        }
};


#endif //INC_2DGAMEENGINE_RENDERSYSTEM_H