#ifndef INC_2DGAMEENGINE_RENDERSYSTEM_H
#define INC_2DGAMEENGINE_RENDERSYSTEM_H

#include <algorithm>
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
            // TODO: Sort how the entities of our system by z-index
            //  ..
            struct RenderableEntity {
                TransformComponent transform;
                SpriteComponent sprite;
            };
            std::vector<RenderableEntity> renderableEntities;
            for (auto entity: GetSystemEntities()) {
                RenderableEntity renderableEntity;
                renderableEntity.transform = entity.GetComponent<TransformComponent>();
                renderableEntity.sprite = entity.GetComponent<SpriteComponent>();
                renderableEntities.emplace_back(renderableEntity);
            }

            std::sort(renderableEntities.begin(), renderableEntities.end(), [](const RenderableEntity& a, const RenderableEntity& b) {
                return a.sprite.zIndex < b.sprite.zIndex;
            });

            for (auto entity: renderableEntities) {
                const auto transform = entity.transform;
                const auto sprite = entity.sprite;

                SDL_Rect srcRect = sprite.srcRect;
                SDL_Rect dstRect = {
                    static_cast<int>(transform.position.x),
                    static_cast<int>(transform.position.y),
                    static_cast<int>(sprite.width * transform.scale.x),
                    static_cast<int>(sprite.height * transform.scale.y)
                };

                // Logger::Log("dstRect: x=" + std::to_string(dstRect.x) +
                //    " y=" + std::to_string(dstRect.y) +
                //    " w=" + std::to_string(dstRect.w) +
                //    " h=" + std::to_string(dstRect.h));

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